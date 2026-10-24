import d1, d2, d3, d4
css = open("style.css").read()
SECTIONS = [
 ("architecture", "D1 · 아키텍처", "어떤 코드가 어느 층에 있고 누가 누구를 쓰는가. 위는 launch 시점에 조립되는 로봇 모델(description 계보), 아래는 실행 중 레이어입니다. 같은 층에서 왼쪽이 팔, 오른쪽이 손이며 맨 아래에서 손이 어댑터로 팔 플랜지에 고정됩니다.",
  d1.build(), "왼쪽 괄호: Ubuntu PC에서 도는 ROS 2 영역과 장치(펌웨어·하드웨어) 영역. 회색 띠가 USB 케이블입니다.",
  ["<b>description 계보:</b> 공식 <code>orcahand_description</code> → orca_ui 번들 → <code>orcahand_ros_description</code> → <code>ar4_orca_description</code>. 실행 중에는 공식 저장소를 쓰지 않습니다(반투명).",
   "<b>코드 위치:</b> 파랑 = <code>ar4_ros_driver/</code>, 초록 = <code>orcahand/orca_core</code>·<code>orca_ui</code>·<code>orcahand_description</code>, 주황 = <code>orcahand/ar4_orca_integration/</code>. <span class='chip ros'>ROS</span> 배지는 apt로 설치된 ROS 2 패키지(ros2_control, MoveIt, rviz2 등)이고, 색은 그것을 쓰는 쪽(팔이면 파랑)입니다.",
   "<b>점선 블록</b> <code>ar4_orca_moveit_config</code>는 아직 없습니다(Phase 2). <code>orca_ui</code>는 ROS를 끈 상태에서 캘리브레이션·텐셔닝용으로만 씁니다."]),
 ("startup", "D2 · 시작 순서", "<code>ros2 launch ar4_orca_bringup bringup.launch.py</code> 한 줄 이후 무엇이 어떤 순서로 켜지는가. 오른쪽 열은 해당 코드 위치입니다.",
  d2.build(), "alt 상자는 arm_mock 값에 따른 분기입니다. hand_mock:=true이면 17~20의 Dynamixel 통신 대신 orca_core의 MockOrcaHand가 응답합니다.",
  ["4~23은 거의 동시에 시작합니다. launch 파일이 순서를 보장하는 곳은 JSB가 끝난 뒤 JTC를 켜는 14→15뿐입니다.",
   "19에서 캘리브레이션이 안 된 config이면 핸드 드라이버는 시작을 거부하고 종료합니다. 자동 캘리브레이션은 하지 않습니다."]),
 ("communication", "D3 · 통신 아키텍처", "실행 중 노드들이 어떤 이름과 방식(topic, service, action)으로 연결되는가, 그리고 USB 아래에서 쓰이는 장치 프로토콜.",
  d3.build(), "큰 테두리 = 하나의 프로세스. 같은 프로세스 안은 ROS 메시지가 아니라 함수 호출이나 공유 메모리(ros2_control interface)로 연결됩니다.",
  ["<code>/joint_states</code> 하나에 두 발행자가 있습니다: 팔(joint_1..6, 60 Hz)과 손(hand_* 17개, 50 Hz). robot_state_publisher가 둘을 합칩니다.",
   "<code>ARHardwareInterface</code>와 <code>TeensyDriver</code>는 별도 노드가 아니라 controller_manager 프로세스 안에서 플러그인으로 돕니다.",
   "<code>/joint_trajectory_controller/controller_state</code>, <code>/orcahand_driver/commanded_joint_states</code> 같은 모니터링 토픽은 그림에서 생략했습니다."]),
 ("signal-path", "D4 · 실행 추적 (Command ↓ / Feedback ↑)", "명령 하나가 모터까지 내려가는 길과 측정값이 RViz까지 올라오는 길. 팔과 손이 나란히 있고, 가운데 세 블록을 함께 씁니다.",
  d4.build(), "회색 띠 위는 Ubuntu PC의 ROS 2, 아래는 장치 쪽 펌웨어·하드웨어입니다.",
  ["<b>팔:</b> position+velocity 명령 설정이라 JTC가 PID 보정 없이 궤적 속도를 그대로 내려보내고(<code>MV…</code>), 엔코더 값은 표시와 허용오차 초과 시 중단에 쓰입니다.",
   "<b>손:</b> 위치를 실제로 맞추는 폐루프는 각 Dynamixel 안(PID loop)에 있고, 올라오는 손가락 각도는 모터 위치로 계산한 추정값입니다.",
   "<b>맨 아래:</b> 손은 어댑터로 팔 플랜지(<code>ee_link</code>)에 고정되어 팔이 움직이면 손 전체가 함께 움직입니다. 장착 위치는 <code>mount.yaml</code>에 있습니다."]),
]
nav = "".join(f'<a href="#{sid}">{t.split(" · ")[0]} {t.split(" · ")[1].split(" (")[0]}</a>' for sid, t, *_ in SECTIONS)
secs = []
for sid, title, intro, svg, cap, notes in SECTIONS:
    secs.append(f'''<section class="diagram" id="{sid}">
  <h2>{title}</h2><p>{intro}</p>
  <figure><div class="scroll">{svg}</div><figcaption>{cap}</figcaption></figure>
  <ul class="notes">{"".join(f"<li>{n}</li>" for n in notes)}</ul>
</section>''')
legend = '''<section class="legend-card" aria-label="범례">
  <h2 class="small">범례 · 네 그림 공통</h2>
  <div class="lg">
    <div class="row"><span class="sw ar4"></span>로봇팔 · <code>ar4_ros_driver</code> + 팔 하드웨어</div>
    <div class="row"><span class="sw orca"></span>로봇핸드 · <code>orca_core</code> · <code>orca_ui</code> · <code>orcahand_description</code> + 핸드 하드웨어</div>
    <div class="row"><span class="sw new"></span>새로 작성 · <code>ar4_orca_integration</code></div>
    <div class="row"><span class="sw shared"></span>팔·손 공용 (RViz, robot_state_publisher, /joint_states)</div>
    <div class="row"><span class="chip ros">ROS</span>apt로 설치된 ROS 2 패키지 (코드는 직접 안 씀) · 색은 쓰는 쪽</div>
    <div class="row"><span class="sw user"></span>사용자 · 터미널</div>
    <div class="row"><span class="chip">HW</span><span class="chip">FW</span>하드웨어 / 펌웨어 (소속 색 유지)</div>
    <div class="row"><span class="sw dash"></span>아직 없음 (planned) · 반투명 = 사용 안 함</div>
  </div>
  <div class="lg">
    <div class="row"><span class="ln"></span>topic</div>
    <div class="row"><span class="ln action"></span>action (goal → feedback · result)</div>
    <div class="row"><span class="ln call"></span>같은 프로세스 안 함수 호출</div>
    <div class="row"><span class="ln include"></span>파일 include · 변환 · 응답</div>
    <div class="row"><span class="ln iface"></span>ros2_control interface (공유 메모리)</div>
    <div class="row"><span class="ln serial"></span>USB 시리얼 · 버스 · 배선</div>
    <div class="row"><span class="ln cmd"></span>Command Path ↓ &nbsp; <span class="ln fb"></span>Feedback Path ↑ (D4)</div>
    <div class="row"><span class="ln phys"></span>물리적 연결 &nbsp; <span class="ln loop"></span>모터 내부 폐루프</div>
  </div>
</section>'''
page = f'''<title>AR4 + ORCA Diagrams</title>
<meta name="claude:viewport-fit-sides" content="cover">
<link rel="preconnect" href="https://fonts.googleapis.com">
<link rel="stylesheet" href="https://fonts.googleapis.com/css2?family=IBM+Plex+Sans:wght@400;500;600&family=IBM+Plex+Mono:wght@400;500;600&family=IBM+Plex+Sans+KR:wght@400;500;600&display=swap">
<style>{css}</style>
<div class="wrap">
  <header>
    <span class="eyebrow">ar4_orca_integration · ROS 2 Jazzy · 2026-10-22 코드 기준</span>
    <h1>AR4 MK5 + ORCA Hand 다이어그램</h1>
    <p class="lede">네 가지 관점으로 본 같은 시스템입니다. 블록 이름은 실제 노드·함수·파일 이름 그대로이고, 색은 그 코드나 장치가 속한 쪽(팔, 손, 새로 작성, 공용)이고, 보라 <code>ROS</code> 배지는 apt로 설치된 ROS 2 패키지입니다.</p>
  </header>
  <nav aria-label="다이어그램">{nav}</nav>
  {legend}
  {"".join(secs)}
</div>
<script>
try {{ const h = location.hash.slice(1); if (h) {{ const el = document.getElementById(h); if (el) el.scrollIntoView(); }} }} catch (e) {{}}
</script>'''
open("ar4_orca_diagrams.html", "w").write(page)
print("ok", len(page))
