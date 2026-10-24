from svglib import Svg
LIFE = [  # key, title, sub, group, badge
    ("user", "사용자", "terminal", "user", None),
    ("launch", "ros2 launch", "bringup.launch.py", "new", None),
    ("xacro", "xacro", "ar4_orca.urdf.xacro", "new", None),
    ("rsp", "robot_state_publisher", "", "shared", None),
    ("cm", "controller_manager", "ros2_control_node", "ar4", None),
    ("hw", "ARHardwareInterface", "+ TeensyDriver", "ar4", None),
    ("fw", "AR4_teensy.ino", "Teensy 4.1", "ar4", "FW"),
    ("sp", "spawner ×2", "JSB → JTC", "ar4", None),
    ("drv", "orcahand_driver", "hand_driver_node.py", "new", None),
    ("core", "orca_core", "hardware_hand.py", "orca", None),
    ("dxl", "Dynamixel ×17", "", "orca", "HW"),
    ("rviz", "rviz2", "ar4_orca.rviz", "shared", None),
]
STEPS = [  # (num, from, to, label, kind, ref) ; kind 'self' for self-call; 'alt' rows handled separately
    (1, "user", "launch", "ros2 launch … arm_mock hand_mock calibrate hand_config_path", "call", ""),
    (2, "launch", "xacro", "ar4_orca.urdf.xacro + mount.yaml", "call", "bringup L91-100"),
    (3, "xacro", "launch", "robot_description (URDF 문자열)", "ret", ""),
    (4, "launch", "rsp", "start (robot_description)", "call", "L102"),
    (5, "rsp", "rsp", "/robot_description, /tf_static 발행", "self", ""),
    (6, "launch", "cm", "start + annin controllers.yaml (60 Hz)", "call", "L105-111"),
    (7, "rsp", "cm", "/robot_description (topic)", "topic", ""),
    ("ALT", "arm_mock:=false"),
    (8, "cm", "hw", "load plugin · on_init()", "call", "ar_hardware_interface.cpp L6"),
    (9, "hw", "fw", "STA<ver>B<model>  (USB 115200)", "serial", "teensy_driver.cpp L36"),
    (10, "fw", "hw", "ST… handshake OK", "ret", ""),
    (11, "hw", "fw", "JC<calib_sequence>  (calibrate:=True)", "serial", "L68-70"),
    ("ELSE", "arm_mock:=true → mock_components/GenericSystem (시리얼 없음)"),
    ("END", ""),
    (12, "cm", "cm", "on_activate · read → update → write @60 Hz", "self", ""),
    (13, "launch", "sp", "spawner joint_state_broadcaster", "call", "L118"),
    (14, "sp", "cm", "load · configure · activate JSB → /joint_states", "service", ""),
    (15, "sp", "cm", "OnProcessExit → activate JTC (action server)", "service", "L132"),
    (16, "launch", "drv", "start (orcahand_driver.yaml + args)", "call", "_hand_driver L66"),
    (17, "drv", "core", "load_hand(config_path | model_name | mock)", "call", "hand_backend.py L65"),
    (18, "core", "dxl", "connect(): port · baud · motor type", "serial", ""),
    (19, "drv", "drv", "ensure_calibrated()  ✗ → 종료", "self", "L87"),
    (20, "core", "dxl", "init_joints(): torque on · mode · neutral", "serial", ""),
    (21, "drv", "drv", "pub/sub/srv/action 생성 · 50 Hz timer", "self", "node L78-93"),
    (22, "launch", "rviz", "start (ar4_orca.rviz)", "call", "L121-124"),
    (23, "rsp", "rviz", "/robot_description, /tf", "topic", ""),
]
def build():
    s = Svg("d2")
    X0, DX, HEADY, HEADH = 30, 132, 20, 52
    xs = {k: X0 + 50 + i * DX for i, (k, *_ ) in enumerate(LIFE)}
    REFX = X0 + 50 + (len(LIFE) - 1) * DX + 90
    W = REFX + 200
    for k, t, sub, g, badge in LIFE:
        s.box(xs[k] - 63, HEADY, 126, HEADH, t, sub or None, g, align="middle")
    y = HEADY + HEADH + 34
    rows = []
    for st in STEPS:
        rows.append((y, st))
        y += 46 if st[0] not in ("END",) else 18
    H = y + 20
    for k in xs:
        s.vline(xs[k], HEADY + HEADH, H - 10, "life")
    s.text(REFX, HEADY + 30, "코드 위치", "sect")
    alt_top = None
    for y, st in rows:
        if st[0] == "ALT":
            alt_top = y - 22
            altx1, altx2 = xs["cm"] - 40, xs["fw"] + 60
            s.text(altx1 + 8, y - 6, "alt  [" + st[1] + "]", "altl")
            continue
        if st[0] == "ELSE":
            s.out.append(f'<line class="altsep" x1="{altx1}" y1="{y-20}" x2="{altx2}" y2="{y-20}"/>')
            s.text(altx1 + 8, y - 2, "[" + st[1] + "]", "altl")
            continue
        if st[0] == "END":
            s.out.append(f'<rect class="altbox" x="{altx1}" y="{alt_top}" width="{altx2-altx1}" height="{y-alt_top-4}" rx="4"/>')
            continue
        n, a, b, lab, kind, ref = st
        if kind == "self":
            x = xs[a]
            s.line([(x, y - 8), (x + 34, y - 8), (x + 34, y + 6), (x + 2, y + 6)], "call")
            s.text(x + 42, y + 2, lab, "msg")
        else:
            x1, x2 = xs[a], xs[b]
            d = 1 if x2 > x1 else -1
            k2 = {"call": "seq", "serial": "seqs"}.get(kind, kind)
            s.line([(x1 + 3 * d, y), (x2 - 3 * d, y)], k2)
            s.text(min(x1, x2) + 10, y - 7, lab, "msg")
        s.out.append(f'<circle class="num" cx="{min(xs[a], xs[b]) - 16 if kind != "self" else xs[a] - 16}" cy="{y}" r="9"/>')
        s.text((min(xs[a], xs[b]) if kind != "self" else xs[a]) - 16, y + 3.5, str(n), "numt", "middle")
        if ref:
            s.text(REFX, y + 4, ref, "ref")
    # concurrency bracket for 4..23
    y4 = [r for r in rows if r[1][0] == 4][0][0]
    yl = rows[-1][0]
    bxp = REFX - 22
    s.line([(bxp, y4), (bxp - 8, y4), (bxp - 8, yl), (bxp, yl)], "phys", None, end=False)
    s.out.append(f'<text class="where" transform="translate({bxp - 14} {(y4+yl)/2}) rotate(-90)" text-anchor="middle">4–23 거의 동시에 시작 · 순서 보장은 14→15뿐</text>')
    return s.render(W, H, "시작 시퀀스: ros2 launch가 xacro로 URDF를 만들고, robot_state_publisher, controller_manager(AR4 하드웨어 초기화와 Teensy 핸드셰이크·캘리브레이션), 컨트롤러 spawner, orcahand_driver(orca_core 연결·캘리브레이션 확인·neutral 이동), rviz2를 띄운다.")
