from svglib import Svg
def build():
    s = Svg("d3")
    # top row
    s.box(40, 60, 260, 64, "move_group", "MoveIt (기존 팔 설정 실행 시)", "ar4", "ROS")
    s.box(600, 60, 240, 64, "rviz2", "RobotModel · MotionPlanning", "shared", "ROS")
    s.box(940, 60, 260, 64, "hand_pose · hand_slider_gui", "orcahand_driver · hand_gui:=true", "new")
    s.box(1240, 60, 220, 64, "terminal · ros2 CLI", "topic · service · action", "user")
    s.line([(600, 82), (302, 82)], "action", "/move_action  (MoveGroup)", 451, 74, "middle")
    s.line([(300, 106), (598, 106)], "topic", "/display_planned_path", 451, 122, "middle")
    # controller_manager process
    s.frame(40, 230, 480, 290, "controller_manager 프로세스 · ros2_control_node · 60 Hz", "ar4", pos="bottom")
    s.box(60, 265, 210, 60, "joint_trajectory_controller", "JTC · action server", "ar4", "ROS")
    s.box(310, 265, 190, 60, "ar4_hw_services_mk5", "srv /park · /calibrate_mask", "ar4")
    s.box(60, 420, 190, 64, "ARHardwareInterface", "→ TeensyDriver (C++)", "ar4")
    s.box(310, 420, 190, 64, "joint_state_broadcaster", "JSB", "ar4", "ROS")
    s.line([(165, 124), (165, 263)], "action", "follow_joint_trajectory", 173, 200)
    s.line([(165, 325), (165, 418)], "iface", "cmd iface: position, velocity", 173, 376)
    s.line([(250, 452), (308, 452)], "iface", "state", 279, 444, "middle")
    # centre column
    s.box(600, 230, 240, 60, "robot_state_publisher", "URDF + /joint_states → /tf", "shared", "ROS")
    s.box(600, 420, 240, 46, "/joint_states", "sensor_msgs/JointState", "topic", pill=True)
    s.line([(720, 420), (720, 292)], "topic", "subscribe", 728, 360)
    s.line([(720, 230), (720, 126)], "topic", "/tf · /robot_description", 728, 180)
    s.line([(600, 246), (522, 246)], "topic", "/robot_description", 596, 260, "end")
    s.line([(500, 452), (598, 443)], "topic", "joint_1..6 · 60 Hz", 549, 470, "middle")
    # orcahand_driver process
    s.frame(900, 230, 560, 290, "orcahand_driver 프로세스 · Python · 50 Hz", "new", pos="bottom")
    s.box(920, 265, 250, 60, "hand_driver_node.py", "topics · services · action", "new")
    s.box(1190, 265, 250, 60, "hand_backend.py", "rad↔deg · ≤180°/s · trajectory", "new")
    s.box(920, 420, 250, 64, "orca_core", "OrcaHand → DynamixelClient", "orca")
    s.box(1190, 420, 250, 64, "config.yaml + calibration.yaml", "models/v2/orcahand-right/", "orca")
    s.line([(1170, 295), (1188, 295)], "call", None)
    s.line([(1300, 325), (1300, 372), (1100, 372), (1100, 418)], "call", "Python call", 1200, 366, "middle")
    s.line([(1190, 452), (1172, 452)], "include", None)
    s.line([(1040, 124), (1040, 263)], "topic", "/orcahand_driver/joint_command", 1048, 160)
    s.line([(1350, 124), (1350, 200), (1110, 200), (1110, 263)], "action", "action follow_joint_trajectory · srv estop, neutral, torque",
           1230, 192, "middle")
    s.line([(920, 300), (870, 300), (870, 443), (842, 443)], "topic", "hand_* ×17 · 50 Hz", 878, 380)
    s.rect(30, 548, 1440, 30, "band")
    s.text(200, 568, "USB cable  ·  아래는 ROS 메시지가 아닌 장치 프로토콜", "bandl")
    s.line([(150, 484), (150, 618)], "serial", None)
    s.line([(1040, 484), (1040, 618)], "serial", None)
    # arm protocol panel
    s.frame(40, 620, 660, 250, "AR4 · TeensyDriver ⇄ AR4_teensy.ino", "ar4")
    s.text(56, 666, "/dev/ttyACM0 · USB CDC · 115200 · ASCII 한 줄 + \\n", "ptitle")
    left = ["PC → Teensy", "STA<ver>B<model>   시작 핸드셰이크", "JC<seq> / JM<mask>  캘리브레이션",
            "MV A<v>…F<v>       속도 명령 (기본)", "MT A<p>…F<p>       위치 명령", "JP / JV            위치·속도 요청",
            "PK / RE            park / e-stop 리셋"]
    right = ["Teensy → PC", "ST… / JC…     응답", "JP A…F…       엔코더 각도 (deg)", "JV A…F…       속도",
             "ES<0|1>       e-stop 상태", "ER… / WN… / DB…", "PK            park 완료"]
    for i, (a, b) in enumerate(zip(left, right)):
        s.text(56, 694 + i * 22, a, "ph" if i == 0 else "pl")
        s.text(390, 694 + i * 22, b, "ph" if i == 0 else "pl")
    s.text(56, 852, "매 60 Hz 주기: read() = JP, JV  ·  write() = MV → ES", "pfoot")
    # hand protocol panel
    s.frame(760, 620, 700, 250, "ORCA · DynamixelClient ⇄ Dynamixel ×17", "orca")
    s.text(776, 666, "USB 어댑터 (포트 자동탐지) · Dynamixel Protocol 2.0 · 1 Mbps", "ptitle")
    rows = [("쓰기", "GroupSyncWrite  Goal Position (addr 116)", "write_desired_pos()"),
            ("읽기", "GroupSyncRead   Present Pos/Vel/Cur (addr 126)", "read_position_velocity_current()"),
            ("시작", "Torque Enable · Operating Mode · Current Limit", "init_joints()"),
            ("모드", "current_based_position", "config.yaml control_mode")]
    s.text(776, 696, "구분", "ph"); s.text(830, 696, "패킷", "ph"); s.text(1210, 696, "orca_core 함수", "ph")
    for i, (a, b, c) in enumerate(rows):
        y = 720 + i * 24
        s.text(776, y, a, "pl"); s.text(830, y, b, "pl"); s.text(1210, y, c, "pl")
    s.text(776, 852, "매 50 Hz 주기: 쓰기 1회 + 읽기 1회 (같은 tick 안)", "pfoot")
    return s.render(1500, 890,
        "통신 아키텍처: controller_manager 프로세스(JTC, JSB, ARHardwareInterface)와 orcahand_driver 프로세스(hand_driver_node, hand_backend, orca_core)가 /joint_states를 함께 발행하고, robot_state_publisher가 /tf로 rviz2에 전달한다. move_group은 /move_action과 follow_joint_trajectory 액션으로 연결된다. USB 아래에서는 Teensy ASCII 프로토콜과 Dynamixel Protocol 2.0이 쓰인다.")
