"""Send a named pose to the hand once.

ros2 run orcahand_driver hand_pose neutral|open|fist|pinch  [--prefix hand_]
"""
import argparse
import math
import time

import rclpy
from sensor_msgs.msg import JointState

FINGERS = ("index", "middle", "ring", "pinky")
POSES = {  # orca_core degrees; anything not listed keeps its current target
    "open": {**{f"{f}_mcp": 0.0 for f in FINGERS}, **{f"{f}_pip": 0.0 for f in FINGERS},
             **{f"{f}_abd": 0.0 for f in FINGERS},
             "thumb_cmc": 0.0, "thumb_abd": 30.0, "thumb_mcp": 0.0, "thumb_dip": 0.0},
    "fist": {**{f"{f}_mcp": 85.0 for f in FINGERS}, **{f"{f}_pip": 90.0 for f in FINGERS},
             **{f"{f}_abd": 0.0 for f in FINGERS},
             "thumb_cmc": 0.0, "thumb_abd": 45.0, "thumb_mcp": 50.0, "thumb_dip": 60.0},
    "pinch": {"index_abd": 0.0, "index_mcp": 55.0, "index_pip": 45.0,
              "thumb_cmc": -20.0, "thumb_abd": 50.0, "thumb_mcp": 35.0, "thumb_dip": 30.0},
}


def main() -> None:
    ap = argparse.ArgumentParser()
    ap.add_argument("pose", choices=["neutral", *POSES])
    ap.add_argument("--prefix", default="hand_")
    args, ros_args = ap.parse_known_args()
    rclpy.init(args=ros_args)
    node = rclpy.create_node("hand_pose")
    if args.pose == "neutral":
        from std_srvs.srv import Trigger
        cli = node.create_client(Trigger, "/orcahand_driver/neutral")
        cli.wait_for_service(timeout_sec=5.0)
        fut = cli.call_async(Trigger.Request())
        rclpy.spin_until_future_complete(node, fut, timeout_sec=5.0)
        print(fut.result())
    else:
        pub = node.create_publisher(JointState, "/orcahand_driver/joint_command", 10)
        pose = POSES[args.pose]
        msg = JointState(name=[args.prefix + j for j in pose],
                         position=[math.radians(v) for v in pose.values()])
        deadline = time.time() + 3.0
        while pub.get_subscription_count() == 0 and time.time() < deadline:
            rclpy.spin_once(node, timeout_sec=0.1)
        pub.publish(msg)
        rclpy.spin_once(node, timeout_sec=0.2)
        print(f"sent '{args.pose}' ({len(pose)} joints)")
    node.destroy_node()
    rclpy.shutdown()


if __name__ == "__main__":
    main()
