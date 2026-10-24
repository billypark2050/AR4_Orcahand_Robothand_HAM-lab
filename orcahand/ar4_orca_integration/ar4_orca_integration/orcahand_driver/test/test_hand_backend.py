"""Backend tests against orca_core's in-memory MockOrcaHand (no ROS, no hardware)."""
import math

import pytest

orca_core = pytest.importorskip("orca_core")

from orcahand_driver.hand_backend import HandBackend, HandNotReadyError  # noqa: E402


@pytest.fixture
def hb():
    b = HandBackend.from_orca_core(mock=True, prefix="hand_", max_speed_deg_s=100.0)
    b.connect()
    b.start(move_to_neutral=True)
    yield b
    b.shutdown()


def test_names_and_units(hb):
    names, pos = hb.read_rad()
    assert len(names) == 17 and all(n.startswith("hand_") for n in names)
    neutral = hb.hand.config.neutral_position
    got = dict(zip(names, pos))
    assert got["hand_wrist"] == pytest.approx(math.radians(neutral["wrist"]), abs=1e-3)
    assert hb.to_core_deg(["hand_index_mcp", "index_pip"], [math.pi / 2, 0.0]) == {
        "index_mcp": pytest.approx(90.0), "index_pip": 0.0}


def test_rejects_unknown_and_nan(hb):
    with pytest.raises(ValueError):
        hb.to_core_deg(["joint_1"], [0.0])
    with pytest.raises(ValueError):
        hb.to_core_deg(["hand_index_mcp"], [float("nan")])


def test_speed_limited_and_clamped(hb):
    start = hb.read_deg()["index_mcp"]
    hb.set_target_deg({"index_mcp": 500.0})          # beyond ROM -> clamped
    sent = hb.step(0.1)                               # 100 deg/s * 0.1 s = 10 deg max
    assert sent["index_mcp"] == pytest.approx(start + 10.0)
    for _ in range(100):
        hb.step(0.1)
    assert hb.read_deg()["index_mcp"] == pytest.approx(hb.hand.config.joint_roms_dict["index_mcp"][1], abs=0.5)


def test_no_motion_when_torque_off_or_estop(hb):
    hb.set_torque(False)
    hb.set_target_deg({"index_mcp": 50.0})
    assert hb.step(1.0) is None
    hb.set_torque(True)
    hb.estop()
    assert hb.step(1.0) is None
    with pytest.raises(HandNotReadyError):
        hb.set_torque(True)
    hb.reset_estop()
    hb.set_torque(True)


def test_trajectory_sampling(hb):
    tr = hb.make_trajectory(["hand_index_mcp", "hand_index_pip"],
                            [(1.0, [math.radians(40), math.radians(20)]),
                             (2.0, [math.radians(80), math.radians(60)])])
    assert tr.times[0] == 0.0                         # current pose prepended
    assert tr.sample(1.5)["index_mcp"] == pytest.approx(60.0)
    assert tr.sample(10.0)["index_pip"] == pytest.approx(60.0)
    with pytest.raises(ValueError):
        hb.make_trajectory(["hand_index_mcp"], [(1.0, [0.0]), (0.5, [0.0])])
