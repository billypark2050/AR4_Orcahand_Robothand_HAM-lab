"""ROS-free core of the ORCA hand driver (unit-testable without rclpy).

Owns the orca_core hand object and everything that is not ROS plumbing:
  * name/unit mapping   ROS "<prefix><joint>" [rad]  <->  orca_core "<joint>" [deg]
  * a target that is approached at a bounded joint speed (streaming commands)
  * trajectory sampling (FollowJointTrajectory, linear interpolation)
  * torque state and an e-stop latch

orca_core already clamps every command to the config's joint ROMs; the speed
limit here is an additional guard against large jumps from a bad command.
"""
from __future__ import annotations

import bisect
import math
import threading
from dataclasses import dataclass, field
from typing import Iterable, Mapping, Sequence


class HandNotReadyError(RuntimeError):
    pass


@dataclass
class TrajectorySample:
    """A joint trajectory in orca_core units, sampled by time since start."""

    joints: list[str]
    times: list[float]                 # seconds from start, strictly increasing
    positions: list[list[float]]       # deg, one row per time

    def sample(self, t: float) -> dict[str, float]:
        if t <= self.times[0]:
            row = self.positions[0]
        elif t >= self.times[-1]:
            row = self.positions[-1]
        else:
            i = bisect.bisect_right(self.times, t)
            t0, t1 = self.times[i - 1], self.times[i]
            a = (t - t0) / (t1 - t0)
            p0, p1 = self.positions[i - 1], self.positions[i]
            row = [x0 + a * (x1 - x0) for x0, x1 in zip(p0, p1)]
        return dict(zip(self.joints, row))

    @property
    def duration(self) -> float:
        return self.times[-1]


@dataclass
class HandBackend:
    prefix: str = "hand_"
    max_speed_deg_s: float = 180.0
    hand: object = None
    joint_ids: list[str] = field(default_factory=list)
    _target: dict[str, float] = field(default_factory=dict)
    _commanded: dict[str, float] = field(default_factory=dict)
    _torque: bool = False
    _estopped: bool = False
    _lock: threading.RLock = field(default_factory=threading.RLock)

    # ------------------------------------------------------------ lifecycle
    @classmethod
    def from_orca_core(cls, config_path: str = "", calibration_path: str = "",
                       model_name: str = "", mock: bool = False, **kw) -> "HandBackend":
        import orca_core  # imported lazily so the module is importable without it

        args = {"mock": mock}
        if config_path:
            args["config_path"] = config_path
        if calibration_path:
            args["calibration_path"] = calibration_path
        if model_name:
            args["model_name"] = model_name
        elif mock and not config_path:
            args["model_name"] = "orcahand-right"
        hand = orca_core.load_hand(**args)
        return cls(hand=hand, joint_ids=list(hand.config.joint_ids), **kw)

    def connect(self) -> str:
        ok, msg = self.hand.connect(interactive=False)
        if not ok:
            raise HandNotReadyError(f"connect failed: {msg}")
        return msg

    def ensure_calibrated(self) -> None:
        if not self.hand.calibrated:
            raise HandNotReadyError(
                "hand is not calibrated for this config. Run calibration first "
                "(orca_ui Setup tab or `scripts/calibrate.py <config.yaml>`) with ROS stopped, "
                "and point `config_path` at that same config.yaml.")

    def start(self, move_to_neutral: bool = True) -> None:
        """Torque on + control mode/current from config. Never calibrates."""
        self.ensure_calibrated()
        self.hand.init_joints(force_calibrate=False, move_to_neutral=move_to_neutral)
        with self._lock:
            self._torque = True
            self._estopped = False
            now = self.read_deg()
            self._commanded = dict(now)
            self._target = dict(now)

    def shutdown(self, disable_torque: bool = True) -> None:
        with self._lock:
            try:
                if disable_torque and self.hand is not None:
                    self.hand.disable_torque()
            finally:
                self._torque = False
                if self.hand is not None:
                    self.hand.disconnect()

    # ------------------------------------------------------------ safety
    def set_torque(self, on: bool) -> None:
        with self._lock:
            if on:
                if self._estopped:
                    raise HandNotReadyError("e-stop latched; call reset_estop first")
                self.ensure_calibrated()
                self.hand.enable_torque()
                now = self.read_deg()
                self._commanded, self._target = dict(now), dict(now)
            else:
                self.hand.disable_torque()
            self._torque = on

    def estop(self) -> None:
        with self._lock:
            self._estopped = True
            self._torque = False
            self.hand.disable_torque()

    def reset_estop(self) -> None:
        with self._lock:
            self._estopped = False

    @property
    def torque_enabled(self) -> bool:
        return self._torque

    @property
    def estopped(self) -> bool:
        return self._estopped

    # ------------------------------------------------------------ names / units
    def ros_name(self, joint: str) -> str:
        return f"{self.prefix}{joint}"

    def core_name(self, name: str) -> str | None:
        """Accept prefixed or bare names; return the orca_core id or None."""
        if self.prefix and name.startswith(self.prefix):
            name = name[len(self.prefix):]
        return name if name in self.joint_ids else None

    def ros_names(self) -> list[str]:
        return [self.ros_name(j) for j in self.joint_ids]

    def to_core_deg(self, names: Sequence[str], positions_rad: Sequence[float]) -> dict[str, float]:
        out, unknown = {}, []
        for n, p in zip(names, positions_rad):
            j = self.core_name(n)
            if j is None:
                unknown.append(n)
            elif not math.isfinite(p):
                raise ValueError(f"non-finite position for {n}")
            else:
                out[j] = math.degrees(p)
        if unknown:
            raise ValueError(f"unknown hand joints: {unknown}")
        return out

    def clamp_deg(self, joints: Mapping[str, float]) -> dict[str, float]:
        roms = self.hand.config.joint_roms_dict
        return {j: min(max(v, roms[j][0]), roms[j][1]) for j, v in joints.items()}

    # ------------------------------------------------------------ IO
    def read_deg(self) -> dict[str, float]:
        pos = self.hand.get_joint_position().as_dict()
        return {j: float(pos[j]) for j in self.joint_ids if pos.get(j) is not None}

    def read_rad(self) -> tuple[list[str], list[float]]:
        deg = self.read_deg()
        js = [j for j in self.joint_ids if j in deg]
        return [self.ros_name(j) for j in js], [math.radians(deg[j]) for j in js]

    def set_target_deg(self, joints: Mapping[str, float]) -> None:
        with self._lock:
            self._target.update(self.clamp_deg(joints))

    def hold_current(self) -> None:
        with self._lock:
            self._target = dict(self._commanded)

    def step(self, dt: float) -> dict[str, float] | None:
        """Advance the commanded pose toward the target by at most max_speed*dt.

        Returns the pose sent to the hand, or None when nothing was sent.
        """
        with self._lock:
            if not self._torque or self._estopped or not self._target:
                return None
            max_step = self.max_speed_deg_s * max(dt, 0.0)
            changed = {}
            for j, tgt in self._target.items():
                cur = self._commanded.get(j, tgt)
                d = tgt - cur
                if abs(d) > 1e-6:
                    nxt = cur + max(-max_step, min(max_step, d))
                    self._commanded[j] = nxt
                    changed[j] = nxt
            if not changed:
                return None
            self.hand.set_joint_positions(changed)
            return changed

    def at_target(self, tol_deg: float = 1e-3) -> bool:
        with self._lock:
            return all(abs(self._commanded.get(j, v) - v) <= tol_deg for j, v in self._target.items())

    # ------------------------------------------------------------ trajectories
    def make_trajectory(self, names: Sequence[str],
                        points: Iterable[tuple[float, Sequence[float]]]) -> TrajectorySample:
        """points: (time_from_start [s], positions [rad]) in ROS order."""
        joints = [self.core_name(n) for n in names]
        if any(j is None for j in joints):
            raise ValueError(f"unknown hand joints: {[n for n, j in zip(names, joints) if j is None]}")
        times, rows = [], []
        for t, pos in points:
            if len(pos) != len(joints):
                raise ValueError("trajectory point size does not match joint_names")
            if times and t <= times[-1]:
                raise ValueError("trajectory time_from_start must be strictly increasing")
            times.append(float(t))
            rows.append(list(self.clamp_deg(dict(zip(joints, (math.degrees(p) for p in pos)))).values()))
        if not times:
            raise ValueError("empty trajectory")
        start = self._commanded or self.read_deg()
        if times[0] > 0.0:  # start from where the hand is commanded now
            times.insert(0, 0.0)
            rows.insert(0, [start.get(j, rows[0][k]) for k, j in enumerate(joints)])
        return TrajectorySample(joints=list(joints), times=times, positions=rows)
