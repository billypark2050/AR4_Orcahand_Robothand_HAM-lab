from svglib import Svg
def build():
    s = Svg("d1")
    OX = 150
    col = {"A": (0, 230), "B": (250, 230), "M": (570, 240), "C": (900, 220), "D": (1190, 220)}
    def X(c): return OX + col[c][0]
    def Wd(c): return col[c][1]
    span = lambda c1, c2: (X(c1), X(c2) + Wd(c2) - X(c1))
    H0 = 58
    # ---------- section A: launch & robot model
    s.text(OX, 40, "LAUNCH & ROBOT MODEL  ·  xacro가 launch 시점에 하나의 URDF로 조립", "sect")
    yA1, yA2, yA3 = 60, 160, 260
    s.box(X("M"), yA1, Wd("M"), H0, "bringup.launch.py", "ar4_orca_bringup/launch/", "new")
    s.box(X("B"), yA2, Wd("B"), H0, "annin_ar4_description", "ar_macro.xacro · meshes/ar4_mk5", "ar4")
    s.box(X("M"), yA2, Wd("M"), H0, "ar4_orca_description", "ar4_orca.urdf.xacro · mount.yaml", "new")
    s.box(X("C"), yA2, Wd("C"), H0, "orcahand_ros_description", "orcahand.xacro · meshes dae/stl", "new")
    s.box(X("D"), yA2, Wd("D"), H0, "hand_v2 bundle", "orca_ui/orca_ui/models/hand_v2", "orca")
    s.box(X("D"), yA3, Wd("D"), H0, "orcahand_description", "official URDF / MJCF (reference)", "orca", faded=True)
    mx = X("M") + Wd("M") / 2
    s.line([(mx, yA1 + H0), (mx, yA2)], "include", "runs xacro", mx + 8, (yA1 + H0 + yA2) / 2 + 4)
    y = yA2 + H0 / 2
    s.line([(X("B") + Wd("B"), y), (X("M"), y)], "include", "include", (X("B") + Wd("B") + X("M")) / 2, y - 8, "middle")
    s.line([(X("C"), y), (X("M") + Wd("M"), y)], "include", "include", (X("C") + X("M") + Wd("M")) / 2, y - 8, "middle")
    s.line([(X("D"), y), (X("C") + Wd("C"), y)], "include", "convert", (X("D") + X("C") + Wd("C")) / 2, y - 8, "middle")
    dx = X("D") + 34
    s.line([(dx, yA3), (dx, yA2 + H0)], "include", "orca_ui build_hand_bundle.py", dx + 8, (yA2 + H0 + yA3) / 2 + 4)
    s.line([(mx, yA2 + H0), (mx, 338)], "include", "robot_description (URDF 문자열) → robot_state_publisher, controller_manager",
           mx + 8, 330)
    s.hline(20, OX + 1410, 352, "divider")
    # ---------- runtime
    s.text(OX, 378, "RUNTIME  ·  ros2 launch ar4_orca_bringup bringup.launch.py", "sect")
    s.text(X("A"), 404, "ROBOT ARM · AR4 MK5", "col")
    s.text(X("D") + Wd("D"), 404, "ROBOT HAND · ORCA v2", "col", "end")
    L = {0: 420, 1: 520, 2: 620, 3: 730, 4: 870, 5: 970}
    h = 62
    labels = {0: "UI", 1: "Planning", 2: "ROS 2 nodes", 3: "HW interface / library", 4: "Firmware", 5: "Hardware"}
    for k, v in labels.items():
        s.text(OX - 16, L[k] + h / 2 + 4, v, "layer", "end")
    # where it runs
    s.vline(30, L[0], L[3] + h, "bracket"); s.vline(30, L[4], L[5] + h, "bracket")
    s.out.append(f'<text class="where" transform="translate(22 {(L[0]+L[3]+h)/2}) rotate(-90)" text-anchor="middle">Ubuntu PC · ROS 2</text>')
    s.out.append(f'<text class="where" transform="translate(22 {(L[4]+L[5]+h)/2}) rotate(-90)" text-anchor="middle">devices</text>')
    by1, by2 = L[3] + h + 22, L[4] - 22
    s.rect(OX - 10, by1, 1430, by2 - by1, "band")
    s.text(OX - 16, (by1 + by2) / 2 + 4, "USB cable", "layer usb", "end")
    # arm
    s.box(X("A"), L[0], Wd("A"), h, "rviz2 · MotionPlanning", "moveit_rviz_plugin", "ar4", "ROS")
    s.box(X("B"), L[0], Wd("B"), h, "terminal · ros2 CLI", "action · topic · service", "user")
    s.box(X("A"), L[1], Wd("A"), h, "move_group", "MoveIt · IK · OMPL", "ar4", "ROS")
    s.box(X("B"), L[1], Wd("B"), h, "annin_ar4_moveit_config", "srdf · kinematics · controllers", "ar4")
    x2, w2 = span("A", "B")
    s.box(x2, L[2], w2, h + 10, "controller_manager", "ros2_control_node · 60 Hz · AR4 plugin + controllers.yaml",
          "ar4", "ROS", sub2="joint_state_broadcaster · joint_trajectory_controller")
    s.box(X("A"), L[3], Wd("A"), h, "ARHardwareInterface", "ar_hardware_interface.cpp", "ar4")
    s.box(X("B"), L[3], Wd("B"), h, "TeensyDriver", "teensy_driver.cpp", "ar4")
    s.box(X("A"), L[4], Wd("A"), h, "AR4_nano.ino", "gripper (unused)", "ar4", "FW", faded=True)
    s.box(X("B"), L[4], Wd("B"), h, "AR4_teensy.ino", "on Teensy 4.1 · stateTRAJ()", "ar4", "FW")
    s.box(x2, L[5], w2, h, "AR4 MK5 arm", "stepper ×6 · encoder ×6 · limit switch ×6 · E-Stop", "ar4", "HW")
    ax = X("A") + 34
    s.line([(ax, L[0] + h), (ax, L[1])], "action", "/move_action", ax + 8, (L[0] + h + L[1]) / 2 + 4)
    s.line([(ax, L[1] + h), (ax, L[2])], "action", "follow_joint_trajectory", ax + 8, (L[1] + h + L[2]) / 2 + 4)
    s.line([(ax, L[2] + h + 10), (ax, L[3])], "call", "loads plugin", ax + 8, (L[2] + h + 10 + L[3]) / 2 + 4)
    yy = L[1] + h / 2
    s.line([(X("B"), yy), (X("A") + Wd("A"), yy)], "include", None)
    yy = L[3] + h / 2
    s.line([(X("A") + Wd("A"), yy), (X("B"), yy)], "call", None)
    bx = X("B") + 34
    s.line([(bx, L[3] + h), (bx, L[4])], "serial", "/dev/ttyACM0 · ASCII (MV, JP, JV)", bx + 8, (by1 + by2) / 2 + 4)
    s.line([(bx, L[4] + h), (bx, L[5])], "serial", "STEP/DIR · encoder A/B", bx + 8, (L[4] + h + L[5]) / 2 + 4)
    # centre
    s.box(X("M"), L[0], Wd("M"), h, "rviz2 · RobotModel", "ar4_orca_bringup/rviz/", "shared", "ROS")
    s.box(X("M"), L[2], Wd("M"), h + 10, "robot_state_publisher", "/joint_states + URDF → /tf", "shared", "ROS")
    s.box(X("M"), L[3], Wd("M"), h, "orca_ui (ROS 아님)", "ROS 끈 상태에서 캘리브레이션·텐셔닝", "orca", dashed=True)
    s.line([(mx, L[2]), (mx, L[0] + h)], "topic", "/tf", mx + 8, (L[0] + h + L[2]) / 2 + 4)
    yy = L[2] + (h + 10) / 2
    s.line([(x2 + w2, yy), (X("M"), yy)], "topic", "/joint_states", (x2 + w2 + X("M")) / 2, yy - 8, "middle")
    s.line([(X("C"), yy), (X("M") + Wd("M"), yy)], "topic", "/joint_states", (X("C") + X("M") + Wd("M")) / 2, yy - 8, "middle")
    yy = L[3] + h / 2
    s.line([(X("M") + Wd("M"), yy), (X("C"), yy)], "call", "imports", (X("C") + X("M") + Wd("M")) / 2, yy - 8, "middle")
    # mechanical link (hand mounted on arm)
    s.box(X("M"), L[5], Wd("M"), h, "flange → hand_adapter", "mount.yaml · bolted", "new", "HW", align="start")
    yy = L[5] + h / 2
    s.line([(x2 + w2, yy), (X("M"), yy)], "phys", "ee_link", (x2 + w2 + X("M")) / 2, yy - 8, "middle", end=False)
    s.line([(X("M") + Wd("M"), yy), (X("C"), yy)], "phys", "hand_forearm", (X("C") + X("M") + Wd("M")) / 2, yy - 8, "middle", end=False)
    # hand
    s.box(X("C"), L[0], Wd("C"), h, "hand_pose.py", "preset 1회 전송 → hand tracking 자리", "new")
    s.box(X("D"), L[0], Wd("D"), h, "joint_state_publisher_gui", "hand_gui:=true (sliders)", "orca", "ROS")
    s.box(X("D"), L[1], Wd("D"), h, "ar4_orca_moveit_config", "arm + hand groups (planned)", "new", dashed=True)
    x3, w3 = span("C", "D")
    s.box(x3, L[2], w3, h + 10, "orcahand_driver", "hand_driver_node.py · hand_backend.py · 50 Hz",
          "new", sub2="config/orcahand_driver.yaml")
    s.box(x3, L[3], w3, h, "orca_core", "load_hand · OrcaHand · DynamixelClient",
          "orca", sub2="models/v2/orcahand-right/config.yaml + calibration.yaml")
    s.box(X("C"), L[4], Wd("C"), h, "USB adapter", "U2D2 / OH board", "orca", "HW")
    s.box(X("D"), L[4], Wd("D"), h, "Dynamixel firmware", "position PID · current limit", "orca", "FW")
    s.box(x3, L[5], w3, h, "ORCA Hand v2 right", "Dynamixel ×17 → spool → tendon → finger", "orca", "HW")
    cx = X("C") + 34
    s.line([(cx, L[0] + h), (cx, L[2])], "topic", "/orcahand_driver/joint_command", cx + 8, (L[0] + h + L[2]) / 2 + 4)
    s.line([(cx, L[2] + h + 10), (cx, L[3])], "call", "Python calls", cx + 8, (L[2] + h + 10 + L[3]) / 2 + 4)
    s.line([(cx, L[3] + h), (cx, L[4])], "serial", "Dynamixel Protocol 2.0", cx + 8, (by1 + by2) / 2 + 4)
    s.line([(cx, L[4] + h), (cx, L[5])], "serial", "TTL bus · 1 Mbps", cx + 8, (L[4] + h + L[5]) / 2 + 4)
    dx2 = X("D") + 34
    s.line([(dx2, L[1] + h), (dx2, L[2])], "action", "follow_joint_trajectory", dx2 + 8, (L[1] + h + L[2]) / 2 + 4)
    return s.render(OX + 1430, L[5] + h + 20,
        "아키텍처: 위는 launch 시점에 조립되는 로봇 모델(description 계보), 아래는 실행 중 레이어. 왼쪽 팔(AR4)과 오른쪽 손(ORCA)이 같은 층에 나란히 있고, 가운데는 공통 블록. USB 케이블에서 ROS 2가 끝나고, 하드웨어 층에서 손이 어댑터로 팔 플랜지에 고정된다.")
