#!/usr/bin/env python3
"""Check the combined AR4 + ORCA model BEFORE starting any driver.

    ros2 run ar4_orca_description check_model.py                      # default mount.yaml
    ros2 run ar4_orca_description check_model.py --mount ~/my_mount.yaml --side left
    ros2 run ar4_orca_description check_model.py --out ~/ar4_orca.urdf # also save the URDF

Prints, in order:
  1. the kinematic tree (arm -> parts -> hand), mesh sub-links of the arm hidden
  2. a joint summary (arm 6 revolute, hand 17 revolute, fixed count)
  3. where each mounting part / the hand root sits relative to ee_link (all joints at 0)
  4. problems: missing meshes, unknown parents in mount.yaml, duplicate names
Exit code 0 = no problems.
"""
import argparse
import math
import os
import subprocess
import sys
import xml.etree.ElementTree as ET

import numpy as np

try:
    from ament_index_python.packages import get_package_share_directory
except ImportError:  # pragma: no cover
    get_package_share_directory = None

HIDDEN_SUFFIXES = ("_aluminum", "_motor", "_cover", "_logo", "_enclosure")
EXPECTED_HAND = 17
EXPECTED_ARM = 6


def rpy_matrix(r, p, y):
    cr, sr, cp, sp, cy, sy = math.cos(r), math.sin(r), math.cos(p), math.sin(p), math.cos(y), math.sin(y)
    return np.array([[cy * cp, cy * sp * sr - sy * cr, cy * sp * cr + sy * sr],
                     [sy * cp, sy * sp * sr + cy * cr, sy * sp * cr - cy * sr],
                     [-sp, cp * sr, cp * cr]])


def origin_tf(el):
    T = np.eye(4)
    o = el.find("origin")
    if o is not None:
        xyz = [float(v) for v in o.get("xyz", "0 0 0").split()]
        rpy = [float(v) for v in o.get("rpy", "0 0 0").split()]
        T[:3, :3] = rpy_matrix(*rpy)
        T[:3, 3] = xyz
    return T


def resolve_mesh(uri):
    if uri.startswith("file://"):
        return uri[len("file://"):]
    if uri.startswith("package://") and get_package_share_directory:
        pkg, rel = uri[len("package://"):].split("/", 1)
        try:
            return os.path.join(get_package_share_directory(pkg), rel)
        except Exception:
            return None
    return uri


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--mount", default="", help="mount yaml (default: package config/mount.yaml)")
    ap.add_argument("--side", default="right")
    ap.add_argument("--prefix", default="hand_")
    ap.add_argument("--ar-model", default="mk5")
    ap.add_argument("--out", default="", help="save the expanded URDF here")
    ap.add_argument("--show-all", action="store_true", help="also show AR4 mesh sub-links")
    a = ap.parse_args()

    share = get_package_share_directory("ar4_orca_description")
    mount = a.mount or os.path.join(share, "config", "mount.yaml")
    cmd = ["xacro", os.path.join(share, "urdf", "ar4_orca.urdf.xacro"), "include_ros2_control:=false",
           f"ar_model:={a.ar_model}", f"hand_side:={a.side}", f"hand_prefix:={a.prefix}",
           f"mount_config:={os.path.expanduser(mount)}"]
    print("$ " + " ".join(cmd))
    res = subprocess.run(cmd, capture_output=True, text=True)
    if res.returncode != 0:
        print("\n[FAIL] xacro error:\n" + res.stderr)
        sys.exit(2)
    urdf = res.stdout
    if a.out:
        with open(os.path.expanduser(a.out), "w") as f:
            f.write(urdf)
        print(f"saved -> {a.out}")

    root = ET.fromstring(urdf)
    links = {l.get("name"): l for l in root.findall("link")}
    joints = root.findall("joint")
    problems = []

    names = [l.get("name") for l in root.findall("link")]
    for n in set(names):
        if names.count(n) > 1:
            problems.append(f"duplicate link name: {n}")

    children = {}
    for j in joints:
        p, c = j.find("parent").get("link"), j.find("child").get("link")
        children.setdefault(p, []).append(j)
        if p not in links:
            problems.append(f"joint {j.get('name')}: parent link '{p}' does not exist")

    # 1. tree
    print("\n=== 1. kinematic tree ===")

    def walk(link, depth):
        for j in children.get(link, []):
            c = j.find("child").get("link")
            if not a.show_all and c.endswith(HIDDEN_SUFFIXES):
                continue
            tag = j.get("type")
            print(f"{'  ' * depth}{link} --[{j.get('name')} : {tag}]--> {c}")
            walk(c, depth + 1)
    walk("world", 0)

    # 2. joint summary
    rev = [j.get("name") for j in joints if j.get("type") in ("revolute", "continuous", "prismatic")]
    hand_rev = [n for n in rev if n.startswith(a.prefix)]
    arm_rev = [n for n in rev if not n.startswith(a.prefix)]
    print("\n=== 2. joints ===")
    print(f"arm  movable: {len(arm_rev)}  {arm_rev}")
    print(f"hand movable: {len(hand_rev)}")
    print(f"fixed       : {sum(1 for j in joints if j.get('type') == 'fixed')}")
    if len(arm_rev) != EXPECTED_ARM:
        problems.append(f"expected {EXPECTED_ARM} arm joints, found {len(arm_rev)}")
    if len(hand_rev) != EXPECTED_HAND:
        problems.append(f"expected {EXPECTED_HAND} hand joints, found {len(hand_rev)}")

    # 3. poses relative to ee_link (all joints at zero)
    print("\n=== 3. frames relative to ee_link (all joints = 0) ===")
    parent_of = {j.find("child").get("link"): j for j in joints}

    def tf_to(link, stop="ee_link"):
        T = np.eye(4)
        while link != stop:
            j = parent_of.get(link)
            if j is None:
                return None
            T = origin_tf(j) @ T
            link = j.find("parent").get("link")
        return T

    hand_root = f"{a.prefix}forearm"
    show = []
    stack = ["ee_link"]  # everything below the flange, stopping at the hand root
    while stack:
        l = stack.pop(0)
        for j in children.get(l, []):
            c = j.find("child").get("link")
            show.append(c)
            if c != hand_root:
                stack.append(c)
    if hand_root not in show:
        problems.append(f"hand root '{hand_root}' is not below ee_link")
    for l in show:
        T = tf_to(l)
        if T is None:
            continue
        xyz = np.round(T[:3, 3], 4)
        r = T[:3, :3]
        rpy = (math.atan2(r[2, 1], r[2, 2]), -math.asin(max(-1, min(1, r[2, 0]))), math.atan2(r[1, 0], r[0, 0]))
        print(f"{l:24s} xyz={xyz}  rpy(deg)={np.round(np.degrees(rpy), 1)}")

    # 4. meshes
    missing = []
    for l in links.values():
        for g in l.iter("mesh"):
            p = resolve_mesh(g.get("filename"))
            if p is None or not os.path.exists(p):
                missing.append(f"{l.get('name')}: {g.get('filename')}")
    print("\n=== 4. problems ===")
    known_upstream = [m for m in missing if "_Col.STL" in m]
    for m in known_upstream:
        print(f"[note] missing AR4 collision mesh (upstream ar4_ros_driver issue, visuals OK): {m}")
    for m in missing:
        if m not in known_upstream:
            problems.append(f"missing mesh: {m}")
    for p in problems:
        print(f"[FAIL] {p}")
    if not problems:
        print("[OK] no problems")
    sys.exit(1 if problems else 0)


if __name__ == "__main__":
    main()
