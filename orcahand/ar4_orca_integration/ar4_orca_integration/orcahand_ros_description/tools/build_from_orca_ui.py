#!/usr/bin/env python3
"""Generate the orcahand_ros_description xacro + meshes from an orca_ui hand bundle.

orca_ui ships `orca_ui/models/hand_v2/{right,left}/hand.urdf` whose joint names
are exactly orca_core's joint ids. NOTE: the bundle's axes do NOT always follow
orca_core's sign convention (orca_core/kinematics/data/v2_kinematics.yaml has a
per-joint `sign`; e.g. right *_abd = -1). With --orca-core, each revolute axis is
multiplied by that sign so the URDF joint value == orca_core angle (deg -> rad). This tool turns that bundle into a ROS 2 friendly description:

  * .glb visual meshes  -> .dae (keeps the two-tone colours, RViz/assimp friendly)
  * convex-hull .stl collision meshes (cheap enough for MoveIt self-collision)
  * one xacro macro per side with `prefix`/`parent`/origin parameters
  * inertials are dropped (the bundle's values are not SI; not needed for RViz/MoveIt)

Usage (needs: pip install trimesh pycollada numpy pyyaml):
    python3 tools/build_from_orca_ui.py <path/to/orca_ui> [--out <pkg dir>]
"""
from __future__ import annotations

import argparse
import math
import os
import xml.etree.ElementTree as ET

import numpy as np
import trimesh
import yaml

SIDES = ("right", "left")
VEL_LIMIT = 3.0      # rad/s, conservative placeholder used by MoveIt time-parameterisation
EFFORT_LIMIT = 1.0


def _fmt(v: float) -> str:
    return f"{0.0 if abs(v) < 1e-12 else v:.9g}"


def _vec(s: str) -> str:
    return " ".join(_fmt(float(x)) for x in s.split())


def convert_mesh(glb_path: str, dae_out: str, stl_out: str) -> None:
    scene = trimesh.load(glb_path, force="scene")
    parts, hull_parts = [], []
    for geom in scene.dump(concatenate=False):
        rgba = [200, 200, 200, 255]
        mat = getattr(geom.visual, "material", None)
        base = getattr(mat, "baseColorFactor", None) if mat is not None else None
        if base is not None:
            rgba = [int(x) for x in base]
        g = trimesh.Trimesh(vertices=geom.vertices, faces=geom.faces, process=False)
        g.visual = trimesh.visual.ColorVisuals(g, face_colors=np.tile(rgba, (len(g.faces), 1)))
        parts.append(g)
        hull_parts.append(geom.vertices)
    dae = trimesh.exchange.dae.export_collada(parts).decode()
    # URDF meshes are Z-up metres; collada defaults to Y_UP, which assimp would rotate.
    dae = dae.replace("<up_axis>Y_UP</up_axis>",
                      '<unit name="meter" meter="1"/>\n    <up_axis>Z_UP</up_axis>', 1)
    with open(dae_out, "w") as f:
        f.write(dae)
    hull = trimesh.Trimesh(vertices=np.vstack(hull_parts)).convex_hull
    hull.export(stl_out)


def build_side(orca_ui: str, out_pkg: str, side: str, core_cfg: dict | None,
               core_signs: dict | None = None) -> list[str]:
    bundle = os.path.join(orca_ui, "orca_ui", "models", "hand_v2", side)
    tree = ET.parse(os.path.join(bundle, "hand.urdf"))
    robot = tree.getroot()

    vis_dir = os.path.join(out_pkg, "meshes", side, "visual")
    col_dir = os.path.join(out_pkg, "meshes", side, "collision")
    os.makedirs(vis_dir, exist_ok=True)
    os.makedirs(col_dir, exist_ok=True)

    lines = [
        f'  <xacro:macro name="orcahand_{side}" params="prefix parent *origin">',
        f'    <joint name="${{prefix}}mount_joint" type="fixed">',
        f'      <parent link="${{parent}}"/>',
        f'      <child link="${{prefix}}forearm"/>',
        f'      <xacro:insert_block name="origin"/>',
        f'    </joint>',
    ]

    for link in robot.iter("link"):
        name = link.get("name")
        vis = link.find("visual")
        if vis is None:
            lines.append(f'    <link name="${{prefix}}{name}"/>')
            continue
        org = vis.find("origin")
        xyz, rpy = _vec(org.get("xyz", "0 0 0")), _vec(org.get("rpy", "0 0 0"))
        glb = vis.find("geometry/mesh").get("filename")
        stem = os.path.splitext(os.path.basename(glb))[0]
        convert_mesh(os.path.join(bundle, glb),
                     os.path.join(vis_dir, stem + ".dae"),
                     os.path.join(col_dir, stem + ".stl"))
        mesh_uri = f"package://orcahand_ros_description/meshes/{side}"
        lines += [
            f'    <link name="${{prefix}}{name}">',
            f'      <visual>',
            f'        <origin xyz="{xyz}" rpy="{rpy}"/>',
            f'        <geometry><mesh filename="{mesh_uri}/visual/{stem}.dae"/></geometry>',
            f'      </visual>',
            f'      <collision>',
            f'        <origin xyz="{xyz}" rpy="{rpy}"/>',
            f'        <geometry><mesh filename="{mesh_uri}/collision/{stem}.stl"/></geometry>',
            f'      </collision>',
            f'    </link>',
        ]

    joints = []
    roms = (core_cfg or {}).get("joint_roms", {})
    for j in robot.iter("joint"):
        name, jtype = j.get("name"), j.get("type")
        org = j.find("origin")
        xyz = _vec(org.get("xyz", "0 0 0")) if org is not None else "0 0 0"
        rpy = _vec(org.get("rpy", "0 0 0")) if org is not None else "0 0 0"
        lines += [
            f'    <joint name="${{prefix}}{name}" type="{jtype}">',
            f'      <parent link="${{prefix}}{j.find("parent").get("link")}"/>',
            f'      <child link="${{prefix}}{j.find("child").get("link")}"/>',
            f'      <origin xyz="{xyz}" rpy="{rpy}"/>',
        ]
        if jtype == "revolute":
            joints.append(name)
            axis = _vec(j.find("axis").get("xyz"))
            sign = (core_signs or {}).get(name, 1)
            if sign == -1:
                axis = " ".join(_fmt(-float(v)) for v in axis.split())
                print(f"[{side}] {name}: axis flipped (orca_core sign = -1)")
            lim = j.find("limit")
            lo, hi = float(lim.get("lower")), float(lim.get("upper"))
            if name in roms:
                rlo, rhi = (math.radians(float(v)) for v in roms[name])
                if abs(rlo - lo) > 1e-6 or abs(rhi - hi) > 1e-6:
                    print(f"[{side}] {name}: URDF limit differs from orca_core ROM, using ROM")
                lo, hi = rlo, rhi
            lines += [
                f'      <axis xyz="{axis}"/>',
                f'      <limit lower="{_fmt(lo)}" upper="{_fmt(hi)}" '
                f'effort="{EFFORT_LIMIT}" velocity="{VEL_LIMIT}"/>',
            ]
        lines.append("    </joint>")
    lines.append("  </xacro:macro>")

    with open(os.path.join(out_pkg, "urdf", f"orcahand_{side}_macro.xacro"), "w") as f:
        f.write('<?xml version="1.0"?>\n<!-- GENERATED by tools/build_from_orca_ui.py - do not edit -->\n')
        f.write('<robot xmlns:xacro="http://wiki.ros.org/xacro">\n')
        f.write("\n".join(lines) + "\n</robot>\n")
    return joints


def main() -> None:
    ap = argparse.ArgumentParser()
    ap.add_argument("orca_ui", help="path to an orca_ui checkout")
    ap.add_argument("--orca-core", help="path to an orca_core checkout (ROM cross-check)")
    ap.add_argument("--out", default=os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
    args = ap.parse_args()

    summary = {}
    for side in SIDES:
        cfg = None
        if args.orca_core:
            p = os.path.join(args.orca_core, "orca_core", "models", "v2", f"orcahand-{side}", "config.yaml")
            if os.path.exists(p):
                with open(p) as f:
                    cfg = yaml.safe_load(f)
        signs = None
        if args.orca_core:
            kp = os.path.join(args.orca_core, "orca_core", "kinematics", "data", "v2_kinematics.yaml")
            if os.path.exists(kp):
                with open(kp) as f:
                    ch = yaml.safe_load(f)[side]["chains"]
                ents = [e for e in ch["base_chain"] if "joint" in e] + \
                       [e for fl in ch["fingers"].values() for e in fl if "joint" in e]
                if side == "right":
                    signs = {e["joint"]: int(e.get("sign", 1)) for e in ents}
                else:
                    # orca_core's left chain is a mirror with its own frames, so its signs
                    # don't apply 1:1 to the bundle's left axes. Not verified -> untouched.
                    print(f"[{side}] WARNING: orca_core sign convention NOT checked for this side")
        joints = build_side(args.orca_ui, args.out, side, cfg, signs)
        summary[side] = {"joints": joints}
        if cfg:
            summary[side]["neutral_deg"] = {k: float(v) for k, v in cfg["neutral_position"].items()}
    with open(os.path.join(args.out, "config", "hand_joints.yaml"), "w") as f:
        f.write("# GENERATED by tools/build_from_orca_ui.py - orca_core joint ids per side\n")
        yaml.safe_dump(summary, f, sort_keys=False)
    print("done:", {s: len(v["joints"]) for s, v in summary.items()})


if __name__ == "__main__":
    main()
