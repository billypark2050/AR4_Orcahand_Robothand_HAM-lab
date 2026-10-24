from svglib import Svg
def build():
    s = Svg("d4")
    OX = 120
    LANES = {"acmd": 0, "afb": 350, "hfb": 630, "hcmd": 980}
    LW, BH = 260, 64
    ROW = [92, 202, 312, 422, 532, 672, 782]
    X = lambda l: OX + LANES[l]
    top = lambda r: ROW[r]; bot = lambda r: ROW[r] + BH
    s.text(X("acmd"), 26, "ROBOT ARM · AR4 MK5", "col")
    s.text(X("hcmd") + LW, 26, "ROBOT HAND · ORCA v2", "col", "end")
    for lane, lab, k in [("acmd", "COMMAND ↓", "cmdl"), ("afb", "FEEDBACK ↑", "fbl"), ("hfb", "FEEDBACK ↑", "fbl"), ("hcmd", "COMMAND ↓", "cmdl")]:
        s.text(X(lane) + LW / 2, 56, lab, f"lane {k}", "middle")
    for r, lab in enumerate(["UI", "Planning", "Control", "HW interface", "Driver", "Firmware", "Hardware"]):
        s.text(OX - 14, ROW[r] + BH / 2 + 4, lab, "layer", "end")
    by1, by2 = bot(4) + 18, top(5) - 18
    s.rect(OX, by1, 1240, by2 - by1, "band")
    s.text(OX - 14, (by1 + by2) / 2 - 2, "USB cable", "layer usb", "end")
    s.text(OX - 14, (by1 + by2) / 2 + 12, "ROS 2 ends", "layer small", "end")
    cx, cw = X("afb"), X("hfb") + LW - X("afb")
    s.box(cx, ROW[0], cw, BH, "rviz2 · RobotModel", "draws arm + hand from /tf", "shared", "ROS")
    s.box(cx, ROW[1], cw, BH, "robot_state_publisher", "/joint_states + URDF  →  /tf", "shared", "ROS")
    s.box(cx, ROW[2], cw, BH, "/joint_states", "joint_1..6 @60 Hz  +  hand_* ×17 @50 Hz", "topic", pill=True)
    mid = cx + cw / 2
    s.line([(mid, top(2)), (mid, bot(1))], "fb", "subscribe", mid + 9, (top(2) + bot(1)) / 2 + 4)
    s.line([(mid, top(1)), (mid, bot(0))], "fb", "/tf", mid + 9, (top(1) + bot(0)) / 2 + 4)
    def col(lane, items, labels, kind, up=False):
        for r, (t, sub, g, badge) in items.items():
            s.box(X(lane), ROW[r], LW, BH, t, sub, g, badge)
        ax = X(lane) + 36
        for (r1, r2), lab in labels.items():
            y1, y2 = (top(r1), bot(r2)) if up else (bot(r1), top(r2))
            ly = (by1 + by2) / 2 + 4 if {r1, r2} == {4, 5} else (y1 + y2) / 2 + 4
            s.line([(ax, y1), (ax, y2)], kind, lab, ax + 9, ly)
    col("acmd", {0: ("rviz2 · MotionPlanning", "Plan → Execute (ar_manipulator)", "ar4", "ROS"),
                 1: ("move_group (MoveIt)", "IK (KDL) → OMPL → timing", "ar4", "ROS"),
                 2: ("joint_trajectory_controller", "60 Hz · spline · tolerance check", "ar4", "ROS"),
                 3: ("ARHardwareInterface::write()", "ar_hardware_interface.cpp", "ar4", None),
                 4: ("TeensyDriver::update()", "teensy_driver.cpp · boost::asio", "ar4", None),
                 5: ("MoveVelocity()", "AR4_teensy.ino · deg/s→steps/s", "ar4", "FW"),
                 6: ("Stepper motor ×6", "via stepper drivers", "ar4", "HW")},
        {(0, 1): "/move_action", (1, 2): "…/follow_joint_trajectory", (2, 3): "cmd iface: position, velocity",
         (3, 4): "rad→deg, −joint offset", (4, 5): "MVA<v>B<v>…F<v>\\n", (5, 6): "STEP / DIR pulses"}, "cmd")
    col("afb", {3: ("joint_state_broadcaster", "state iface → /joint_states", "ar4", "ROS"),
                4: ("ARHardwareInterface::read()", "asks JP, JV · deg→rad + offset", "ar4", None),
                5: ("readMotorSteps()", "AR4_teensy.ino · encoder → deg", "ar4", "FW"),
                6: ("Encoder ×6", "quadrature A/B → Teensy", "ar4", "HW")},
        {(6, 5): "A/B pulses", (5, 4): "reply JP A…F… · JV A…F…", (4, 3): "state iface: position, velocity",
         (3, 2): "publish (60 Hz)"}, "fb", up=True)
    col("hcmd", {0: ("hand_pose · hand_gui", "→ 나중에 hand tracking 노드", "new", None),
                 1: ("hand_driver_node._on_command", "rad→deg · name check · ROM clamp", "new", None),
                 2: ("HandBackend.step(dt)", "50 Hz tick · ≤180°/s per joint", "new", None),
                 3: ("OrcaHand.set_joint_positions()", "hardware_hand.py · calibration", "orca", None),
                 4: ("DynamixelClient (write)", "write_desired_pos()", "orca", None),
                 5: ("Position PID", "current_based_position mode", "orca", "FW"),
                 6: ("Dynamixel ×17", "spool → tendon → finger", "orca", "HW")},
        {(0, 1): "/orcahand_driver/joint_command", (1, 2): "set_target_deg()", (2, 3): "set_joint_positions(deg)",
         (3, 4): "_joint_to_motor_pos()", (4, 5): "GroupSyncWrite · Goal Pos 116", (5, 6): "current-limited drive"}, "cmd")
    col("hfb", {3: ("OrcaHand.get_joint_position()", "hardware_hand.py → read_rad()", "orca", None),
                4: ("DynamixelClient (read)", "read_position_velocity_current()", "orca", None),
                5: ("Present Position", "Dynamixel control table · 126", "orca", "FW"),
                6: ("Motor encoder", "inside each Dynamixel", "orca", "HW")},
        {(6, 5): "position", (5, 4): "GroupSyncRead · addr 126", (4, 3): "_motor_to_joint_pos() (estimate)",
         (3, 2): "publish hand_* ×17 (50 Hz)"}, "fb", up=True)
    y6 = ROW[6] + BH / 2
    s.line([(X("acmd") + LW, y6), (X("afb"), y6)], "phys", "shaft turns", (X("acmd") + LW + X("afb")) / 2, y6 - 7, "middle")
    s.line([(X("hcmd"), y6), (X("hfb") + LW, y6)], "phys", "shaft turns", (X("hcmd") + X("hfb") + LW) / 2, y6 - 7, "middle")
    y5 = ROW[5] + BH / 2
    s.line([(X("hcmd"), y5), (X("hfb") + LW, y5)], "loop", "PID loop", (X("hcmd") + X("hfb") + LW) / 2, y5 - 7, "middle", both=True)
    # mechanical mount: the hand is bolted to the arm
    ym = 892
    s.box(cx, ym, cw, 54, "AR4 flange (ee_link) → hand_adapter → ORCA hand_forearm", "ar4_orca_description/config/mount.yaml", "new", "HW", align="middle")
    s.line([(X("acmd") + LW / 2, bot(6)), (X("acmd") + LW / 2, ym + 27), (cx, ym + 27)], "phys", "arm carries the hand", X("acmd") + LW / 2 + 9, ym + 10, end=False)
    s.line([(X("hcmd") + LW / 2, bot(6)), (X("hcmd") + LW / 2, ym + 27), (cx + cw, ym + 27)], "phys", None, end=False)
    return s.render(OX + 1260, 966,
        "실행 추적: 팔과 손 각각 명령은 RViz·MoveIt·컨트롤러·하드웨어 인터페이스·USB·펌웨어를 거쳐 모터로 내려가고(Command Path), 측정값은 반대로 올라와 /joint_states로 합쳐진 뒤 robot_state_publisher를 거쳐 RViz에 표시된다(Feedback Path). 맨 아래에서 손은 어댑터로 팔 플랜지에 고정되어 있다.")
