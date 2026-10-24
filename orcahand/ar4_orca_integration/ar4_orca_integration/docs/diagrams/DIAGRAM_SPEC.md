# AR4 MK5 + ORCA Hand — Claude Design용 다이어그램 설명서

> 사용법: **0장(공통 규칙)** + 그리고 싶은 다이어그램 장(D1~D4) 하나를 Claude Design에 붙여 넣고,
> 각 장 끝의 "Claude Design 프롬프트"를 함께 주면 된다. 한 번에 한 장씩 그리는 것을 권장.
> 모든 이름은 실제 코드/폴더/노드/토픽 이름이다(2026-10-22 코드 기준으로 확인).
> 기존 "로봇팔 다이어그램"이 있다면 그 스타일·배치를 우선하고, 여기의 블록 이름과 색 규칙만 맞추면 된다.

---

## 0. 공통 규칙 (모든 다이어그램에 적용)

### 0-1. 색 = 소속 서브시스템 (어느 저장소/어느 쪽 장치에 속하는가)
| 그룹 키 | 소속 | 테두리 | 채움 | 포함 예 |
|---|---|---|---|---|
| `AR4` | 로봇팔: `ar4_ros_driver` 코드 + **팔 하드웨어** | #2563EB | #DBEAFE | annin_ar4_description, annin_ar4_driver, annin_ar4_moveit_config, AR4_teensy.ino, **Teensy 4.1, stepper, encoder, limit switch** |
| `ORCA` | 로봇핸드: `orca_core`, `orca_ui`, `orcahand_description` + **핸드 하드웨어** | #16A34A | #DCFCE7 | hardware_hand.py, dynamixel_client.py, config.yaml, **USB 어댑터, Dynamixel ×17, 텐던** |
| `NEW` | `ar4_orca_integration` (이번에 새로 작성) | #EA580C | #FFEDD5 | ar4_orca_bringup, ar4_orca_description, orcahand_driver, orcahand_ros_description |
| `ROS` | ROS 2 / 프레임워크 (apt로 설치된 것) | #7C3AED | #EDE9FE | robot_state_publisher, controller_manager, joint_trajectory_controller, MoveIt(move_group), rviz2 |
| `USER` | 사람 / 명령 입력 | #111827 | #FFFFFF | 사용자, 터미널 CLI |

- **하드웨어 블록**은 소속 색(팔 = 파랑, 손 = 초록)을 쓰고, 블록 안 왼쪽 위에 **회색 `HW` 배지**(#475569)를 붙여 코드와 구분한다.
  펌웨어(.ino, Dynamixel 내장 펌웨어)는 `FW` 배지.
- **계획(아직 없음)** 인 블록: 해당 색 + **점선 테두리** + 라벨 끝에 `(planned)`.
- **이번 구성에서 쓰지 않는** 기존 블록(예: AR4 그리퍼): 해당 색 + 50% 투명도 + `(unused)`.
- 범례(legend) 박스를 항상 오른쪽 아래에 둔다.

### 0-2. 선 = 통신 종류
| 선 키 | 의미 | 스타일 |
|---|---|---|
| `topic` | ROS topic (publish → subscribe) | 실선, 끝 화살표 1개 |
| `service` | ROS service (request ↔ response) | 파선, 양끝 화살표 |
| `action` | ROS action (goal → / ← feedback, result) | 굵은 실선, 양끝 화살표, 라벨에 `[action]` |
| `call` | 같은 프로세스 안의 함수 호출 / 라이브러리 import | 얇은 점선, 끝 화살표 |
| `iface` | ros2_control command/state interface (공유 메모리) | 이중선 |
| `include` | 파일 포함·로드 (xacro include, yaml load, launch 실행) | 점선 + 속이 빈 삼각 화살표 |
| `serial` | USB 시리얼 / 버스 (전선) | 굵은 회색선, 라벨에 포트·속도 |
| `feedback` | 상태가 되돌아오는 경로 | 청록 #0D9488 실선 (D4에서만 강조) |

### 0-3. 블록 라벨 형식
```
<굵게: 실행 단위 또는 클래스/노드 이름>
<작게: 파일 경로 (패키지 기준)>
```
예: **ARHardwareInterface** / `annin_ar4_driver/src/ar_hardware_interface.cpp`

---

## D1. 아키텍처 (정적 구조 · 레이어)

**목적:** "어떤 코드가 어느 층에 있고, 누가 누구를 쓰는가." 시간 순서는 없음.
**배치:** 위→아래 7개 가로 레이어(swimlane). 각 레이어 안에서 **왼쪽 = 팔(AR4), 오른쪽 = 손(ORCA)**, 가운데 = 공통.

### 레이어와 블록
**L0 사용자 · 응용 (USER/NEW/ROS)**
- `USER` 사용자 / 터미널
- `ROS` **rviz2** — `ar4_orca_bringup/rviz/ar4_orca.rviz` (RobotModel, TF 표시)
- `ROS` **MotionPlanning 패널** (moveit_rviz_plugin) — `annin_ar4_moveit_config/rviz/moveit.rviz`
- `NEW` **hand_pose** — `orcahand_driver/orcahand_driver/hand_pose.py` (open/fist/pinch/neutral)
- `ROS` **joint_state_publisher_gui** (hand_gui:=true) — 손가락 슬라이더
- `NEW` (planned) Python 시퀀스 노드 / 손 추적 텔레오퍼레이션

**L1 계획 (Planning)**
- `ROS` **move_group** (MoveIt) — 실행: `annin_ar4_moveit_config/launch/moveit.launch.py`
  - 하위 상자(설정 파일, `AR4` 색): `srdf/ar.srdf.xacro`(그룹 `ar_manipulator`), `config/kinematics.yaml`(KDL), `config/ompl_planning.yaml`, `config/pilz_planning.yaml`, `config/joint_limits.yaml`, `config/controllers.yaml`
  - 주석: "현재는 팔 단독(그리퍼 포함) 모델 기준"
- `NEW` (planned) **ar4_orca_moveit_config** — 그룹 `ar_manipulator` + `orca_hand`

**L2 시작 · 모델 (Bringup & Description)**
- `NEW` **bringup.launch.py** — `ar4_orca_bringup/launch/bringup.launch.py` (모든 노드를 실행)
- `NEW` **ar4_orca.urdf.xacro** — `ar4_orca_description/urdf/` (통합 모델의 조립 파일)
  - `include` ← `AR4` **ar_macro.xacro**, **ar.ros2_control.xacro**, `config/mk5.yaml`, `meshes/ar4_mk5/` (annin_ar4_description)
  - `include` ← `NEW` **fixed_parts.xacro** + **config/mount.yaml** (ar4_orca_description: 어댑터 등 파츠)
  - `include` ← `NEW` **orcahand.xacro** + `orcahand_right_macro.xacro`, `meshes/right/` (orcahand_ros_description)
  - `include` ← `AR4` `annin_ar4_driver/config/joint_offsets/mk5.yaml`, `config/driver.yaml`
- `NEW` **build_from_orca_ui.py** — `orcahand_ros_description/tools/` (오프라인 생성기)
  - `include`(점선, "빌드 전 1회 변환") ← `ORCA` `orca_ui/orca_ui/models/hand_v2/right/hand.urdf` + `.glb`
- `NEW` **check_model.py** — `ar4_orca_description/scripts/` (모델 검사 도구)
- `ROS` **robot_state_publisher**

**L3 제어 노드 (ROS nodes)**
- 왼쪽 큰 상자 `ROS` **controller_manager** (`ros2_control_node`, 60 Hz)
  - 내부: `ROS` **joint_state_broadcaster**, `ROS` **joint_trajectory_controller**
  - 설정 `AR4`: `annin_ar4_driver/config/controllers.yaml`
  - 내부 작은 노드 `AR4` **ar4_hw_services_mk5** (서비스 `/park`, `/calibrate_mask` 제공)
- 오른쪽 상자 `NEW` **orcahand_driver** (50 Hz)
  - `hand_driver_node.py` (ROS 인터페이스) → `call` → `hand_backend.py` (단위 변환·속도 제한·trajectory·e-stop)
  - 설정: `orcahand_driver/config/orcahand_driver.yaml`

**L4 하드웨어 추상화 · 라이브러리**
- 왼쪽 `AR4` **ARHardwareInterface** — `annin_ar4_driver/src/ar_hardware_interface.cpp` (pluginlib, `hardware_interface_plugin.xml`)
  - `call` → `AR4` **TeensyDriver** — `src/teensy_driver.cpp` (boost::asio serial)
  - 대체(mock): `ROS` **mock_components/GenericSystem** (`arm_mock:=true`)
  - (unused) `AR4` **ARServoGripperHWInterface** → **ArduinoNanoDriver** (그리퍼)
- 오른쪽 `ORCA` **orca_core**
  - **load_hand()** `hand_factory.py` → **OrcaHand** `hardware_hand.py`
  - **calibration / config** `hand_config.py`, `calibration.py`, `models/v2/orcahand-right/config.yaml` + `calibration.yaml`
  - **motor_factory.py** → **DynamixelClient** `hardware/dynamixel_client.py` (dynamixel_sdk, Protocol 2.0)
  - 대체(mock): **MockOrcaHand** (`hand_mock:=true`)

**L5 펌웨어**
- 왼쪽 `AR4` **AR4_teensy.ino** — `annin_ar4_firmware/AR4_teensy/` (`stateTRAJ()` 루프, AccelStepper, Encoder 라이브러리)
- (unused) `AR4` **AR4_nano.ino**
- 오른쪽 `ORCA`+FW **Dynamixel 내장 펌웨어** (current_based_position 모드, 내부 위치 PID)

**L6 하드웨어**
- 왼쪽 `AR4`+HW **Teensy 4.1** ─ **stepper driver ×6 → stepper ×6**, **encoder ×6**, **limit switch ×6**, **E-Stop 버튼**
- 왼쪽 (unused) `AR4`+HW Arduino Nano → 서보 그리퍼
- 오른쪽 `ORCA`+HW **USB 어댑터 (U2D2 / OH board)** ─ **Dynamixel ×17** → 텐던 → 손가락·손목

**옆 상자 (레이어 밖, 오른쪽)**: `ORCA` **orca_ui** — `orca_ui/server.py`(FastAPI), `orca_ui/hand/service.py`, 웹 UI
- `call` → orca_core. 주석: "캘리브레이션·텐셔닝용. **orcahand_driver와 동시 실행 불가** (시리얼 포트 1개)"

### 주요 연결 (D1)
| from | to | 선 | 라벨 |
|---|---|---|---|
| bringup.launch.py | robot_state_publisher, controller_manager, orcahand_driver, rviz2 | include | 실행 |
| bringup.launch.py | ar4_orca.urdf.xacro | include | xacro → robot_description |
| robot_state_publisher | rviz2 | topic | /tf, /robot_description |
| MotionPlanning 패널 | move_group | action | /move_action |
| move_group | joint_trajectory_controller | action | /joint_trajectory_controller/follow_joint_trajectory |
| hand_pose | orcahand_driver | topic | /orcahand_driver/joint_command |
| joint_trajectory_controller | ARHardwareInterface | iface | joint_N/position, joint_N/velocity |
| ARHardwareInterface | TeensyDriver | call | update(), getJointPositions() |
| TeensyDriver | AR4_teensy.ino | serial | /dev/ttyACM0 (USB CDC) |
| AR4_teensy.ino | stepper/encoder | serial(전선) | STEP/DIR, A/B 펄스 |
| orcahand_driver | OrcaHand | call | set_joint_positions(), get_joint_position() |
| DynamixelClient | Dynamixel ×17 | serial | Protocol 2.0, 1 Mbps |

### Claude Design 프롬프트 (D1)
> "0장 규칙으로 'AR4 MK5 + ORCA Hand ROS 2 시스템 아키텍처' 레이어 다이어그램을 그려줘. 위에서 아래로 L0~L6 가로 레이어, 각 레이어 왼쪽은 로봇팔(AR4), 오른쪽은 로봇핸드(ORCA), 가운데는 공통 블록. 블록은 '굵은 이름 + 작은 파일 경로' 두 줄 라벨. 색은 출처별(AR4 파랑, ORCA 초록, NEW 주황, ROS 보라, HW 회색). planned는 점선, unused는 반투명. 연결은 D1 표만 그리고, 오른쪽 아래에 색·선 범례. 가로 16:9."

---

## D2. 실행 순서 (시작 시퀀스)

**목적:** `ros2 launch ar4_orca_bringup bringup.launch.py ...` 한 줄이 실행된 뒤 무엇이 어떤 순서로 켜지는가.
**형식:** UML 시퀀스 다이어그램(세로 lifeline). 단계 번호를 화살표에 붙이고, 오른쪽 여백에 코드 위치.

### Lifeline (왼→오, 색)
`USER` 사용자 · `ROS` ros2 launch · `ROS` xacro · `ROS` robot_state_publisher · `ROS` controller_manager · `AR4` ARHardwareInterface/TeensyDriver · `AR4`+FW AR4_teensy.ino(Teensy) · `ROS` spawner(JSB) · `ROS` spawner(JTC) · `NEW` orcahand_driver · `ORCA` orca_core · `ORCA`+HW Dynamixel · `ROS` rviz2

### 단계
| # | from → to | 내용 | 코드 위치 |
|---|---|---|---|
| 1 | 사용자 → ros2 launch | `ros2 launch ar4_orca_bringup bringup.launch.py arm_mock:=… hand_mock:=… calibrate:=… hand_config_path:=…` | |
| 2 | ros2 launch → xacro | 인자 선언 후 xacro 실행: `ar4_orca.urdf.xacro` + `mount.yaml` + `ar_macro.xacro` + `fixed_parts.xacro` + `orcahand.xacro` + `ar.ros2_control.xacro` → **URDF 문자열 (robot_description)** | bringup.launch.py L30-44, L91-100 |
| 3 | ros2 launch → robot_state_publisher | robot_description 파라미터로 시작 → `/robot_description`, `/tf_static` 발행 | L102-103 |
| 4 | ros2 launch → controller_manager | `ros2_control_node` 시작, 설정 `annin_ar4_driver/config/controllers.yaml` (60 Hz) | L105-111 |
| 4a | controller_manager ← robot_state_publisher | `/robot_description` 토픽으로 URDF 수신 ("Received robot description from topic") | |
| 4b | controller_manager → ARHardwareInterface | `<ros2_control>` 태그의 플러그인 로드: 실물 `annin_ar4_driver/ARHardwareInterface`, mock `mock_components/GenericSystem` | ar4_orca.urdf.xacro |
| 4c | ARHardwareInterface → Teensy | `on_init`: TeensyDriver::init → 시리얼 열기 → 핸드셰이크 `STA<ver>B<model>` → (calibrate:=True면) `JC<calib_sequence>` 리밋스위치 홈잉 → 서비스 `/park`, `/calibrate_mask` 생성 | ar_hardware_interface.cpp L6-112, teensy_driver.cpp L13-55 |
| 4d | controller_manager | `on_activate` → 60 Hz 루프 시작 (`read()` → controllers `update()` → `write()`) | |
| 5 | ros2 launch → spawner(JSB) | `joint_state_broadcaster` load → configure → activate → `/joint_states`(팔) 발행 시작 | L113-119 |
| 6 | spawner(JSB) 종료 → spawner(JTC) | `OnProcessExit` 이벤트로 `joint_trajectory_controller` 활성화 → 액션 서버 `/joint_trajectory_controller/follow_joint_trajectory` | L132 |
| 7 | ros2 launch → orcahand_driver | (3~6과 동시 진행) 파라미터 = `orcahand_driver.yaml` + launch 인자 | L66-84 `_hand_driver()` |
| 7a | orcahand_driver → orca_core | `HandBackend.from_orca_core()` → `orca_core.load_hand(config_path / model_name / mock)` | hand_backend.py L65 |
| 7b | orca_core → Dynamixel | `connect(interactive=False)`: 포트 자동탐지·모터 종류·baud 탐지 | hardware_hand.py `connect()` |
| 7c | orcahand_driver | `ensure_calibrated()` — **캘리브레이션 안 됐으면 종료** | hand_backend.py L87 |
| 7d | orca_core → Dynamixel | `init_joints()`: 토크 ON, 제어모드 current_based_position, 최대 전류, neutral 자세로 이동 | hardware_hand.py `init_joints()` |
| 7e | orcahand_driver | publisher/subscriber/service/action 생성, **50 Hz 타이머** 시작 | hand_driver_node.py L78-93 |
| 8 | ros2 launch → rviz2 | `ar4_orca.rviz` 로드 → `/robot_description` + `/tf`로 로봇 표시 | L121-124 |
| 9 | (선택) ros2 launch → joint_state_publisher_gui | `hand_gui:=true`일 때 손 전용 URDF로 슬라이더 → `/orcahand_driver/joint_command` | L47-63 |
| 10 | 사용자 Ctrl-C | orcahand_driver `close()` → 토크 OFF → disconnect / controller_manager deactivate | hand_driver_node.py L224 |

**표시할 주석:** "3~8은 거의 동시에 시작한다. 순서가 보장되는 것은 5→6(JSB 후 JTC)뿐이다."
**분기 표시 (alt 박스):** 4b `arm_mock` true/false, 7a `hand_mock` true/false.

### Claude Design 프롬프트 (D2)
> "0장 규칙으로 'bringup.launch.py 시작 시퀀스' UML 시퀀스 다이어그램을 그려줘. lifeline은 D2 목록 순서와 색을 따르고, 단계 1~10을 번호 붙은 화살표로, 각 화살표 오른쪽에 회색 작은 글씨로 코드 위치. 4b와 7a는 alt 박스(mock/real), 3~8 옆에 '동시 시작' 괄호, 5→6 사이에 'OnProcessExit' 표시. 세로 A4."

---

## D3. 통신 아키텍처

**목적:** 실행 중에 노드들이 **어떤 이름으로, 어떤 방식(topic/service/action)으로, 얼마나 자주** 주고받는가 + 그 아래 **시리얼 구간 프로토콜**.
**배치:** 위 2/3 = ROS 그래프(노드 = 둥근 사각형, 토픽/액션/서비스 = 선 위 라벨), 아래 1/3 = 하드웨어 통신 2칸(팔 / 손).

### 노드 (둥근 사각형)
`ROS` /robot_state_publisher · `ROS` /controller_manager (내부에 /joint_state_broadcaster, /joint_trajectory_controller) · `AR4` /ar4_hw_services_mk5 (같은 프로세스) · `NEW` /orcahand_driver · `ROS` /rviz2 · `ROS` /move_group (기존 팔 MoveIt 실행 시) · `NEW` hand_pose (CLI) · `ROS` /hand_slider_gui (선택) · `USER` ros2 CLI

### 토픽
| 이름 | 타입 | 보내는 쪽 → 받는 쪽 | 주기 / 비고 |
|---|---|---|---|
| `/robot_description` | std_msgs/String | robot_state_publisher → controller_manager, rviz2 | 1회, transient local |
| `/joint_states` | sensor_msgs/JointState | joint_state_broadcaster (joint_1..6, pos+vel) **와** orcahand_driver (hand_* 17개, pos) → robot_state_publisher, move_group | 60 Hz / 50 Hz, **두 발행자가 한 토픽 공유** |
| `/tf`, `/tf_static` | tf2_msgs/TFMessage | robot_state_publisher → rviz2, move_group | /joint_states에 맞춰 |
| `/orcahand_driver/joint_command` | sensor_msgs/JointState | hand_pose, hand_slider_gui, CLI → orcahand_driver | 수시 (rad, 일부 관절만 가능) |
| `/orcahand_driver/commanded_joint_states` | sensor_msgs/JointState | orcahand_driver → (모니터링) | 명령 시 |
| `/joint_trajectory_controller/controller_state` | control_msgs/JointTrajectoryControllerState | JTC → (모니터링) | 60 Hz |
| `/display_planned_path`, `/monitored_planning_scene` | moveit_msgs | move_group → rviz2 | 계획 시 |

### 액션 (굵은 양방향)
| 이름 | 타입 | client → server |
|---|---|---|
| `/move_action` | moveit_msgs/action/MoveGroup | rviz2 MotionPlanning → move_group |
| `/joint_trajectory_controller/follow_joint_trajectory` | control_msgs/action/FollowJointTrajectory | move_group 또는 CLI → JTC |
| `/orcahand_driver/follow_joint_trajectory` | control_msgs/action/FollowJointTrajectory | CLI, (planned) move_group → orcahand_driver |

### 서비스 (파선 양방향)
| 이름 | 타입 | 제공 노드 |
|---|---|---|
| `/park` | std_srvs/Trigger | ar4_hw_services_mk5 |
| `/calibrate_mask` | annin_ar4_driver/srv/CalibrateMask | ar4_hw_services_mk5 |
| `/orcahand_driver/{enable_torque, disable_torque, neutral, estop, reset_estop}` | std_srvs/Trigger | orcahand_driver |
| `/controller_manager/{list_controllers, load_controller, switch_controller, …}` | controller_manager_msgs | controller_manager (spawner가 사용) |

### 프로세스 내부 인터페이스 (이중선, ROS 메시지가 아님)
- JTC ⇄ ARHardwareInterface: **command interface** `joint_N/position`, `joint_N/velocity` / **state interface** `joint_N/position`, `joint_N/velocity` (controller_manager 안의 공유 메모리)
- hand_driver_node ⇄ hand_backend ⇄ orca_core: Python 함수 호출

### 하드웨어 통신 — 팔 (아래 왼쪽 칸)
- **TeensyDriver** (`teensy_driver.cpp`) ⇄ **AR4_teensy.ino**: USB 가상 시리얼(USB CDC) `/dev/ttyACM0`, 코드상 115200 baud 설정, ASCII 한 줄 + `\n`
- 호스트 → Teensy 명령: `STA<ver>B<model>`(시작) · `JC<seq>`(캘리브레이션) · `JM<mask>`(부분 캘리브레이션) · **`MV A<v>B<v>…F<v>`**(속도 명령, 기본) / `MT A<p>…F<p>`(위치 명령, velocity_control_enabled=false일 때) · **`JP`**(위치 요청) · **`JV`**(속도 요청) · `PK`(park) · `RE`(e-stop 리셋)
- Teensy → 호스트 응답: `ST…` · `JC…` · **`JP A…F…`**(엔코더 각도) · **`JV A…F…`** · **`ES<0|1>`**(e-stop 상태) · `ER…`(에러) · `DB…`(디버그) · `WN…`(경고) · `PK`
- 한 주기(60 Hz)마다: `read()` = `JP`→`JP…`, `JV`→`JV…` / `write()` = `MV…`→`ES…`
- Teensy → 모터: STEP/DIR 펄스(AccelStepper), 엔코더 A/B 펄스(Encoder 라이브러리), 리밋스위치 입력

### 하드웨어 통신 — 손 (아래 오른쪽 칸)
- **DynamixelClient** (`orca_core/hardware/dynamixel_client.py`, dynamixel_sdk) ⇄ USB 어댑터(포트 자동탐지) ⇄ **Dynamixel ×17** 반이중 버스, **Protocol 2.0**, 1 Mbps(v2)
- 쓰기: `GroupSyncWrite` → Goal Position (주소 116), `write_desired_pos()`
- 읽기: `GroupSyncRead` → Present Position/Velocity/Current (주소 126), `read_position_velocity_current()`
- 한 주기(50 Hz)마다 쓰기 1회 + 읽기 1회

### 주기 표 (그림 구석)
| 루프 | 주기 | 위치 |
|---|---|---|
| controller_manager (read→update→write) | 60 Hz | annin controllers.yaml `update_rate` |
| JTC 액션 상태 점검 | 20 Hz | `action_monitor_rate` |
| orcahand_driver `_tick()` | 50 Hz | orcahand_driver.yaml `control_rate` |
| Dynamixel 내부 위치 제어 | 모터 내부 (kHz급) | 벤더 펌웨어 |

### Claude Design 프롬프트 (D3)
> "0장 규칙으로 'ROS 2 통신 아키텍처' 다이어그램을 그려줘. 위 2/3은 노드 그래프(둥근 사각형, 색은 출처별), 연결은 topic 실선·service 파선 양방향·action 굵은 양방향·process 내부 interface 이중선이고, 선 라벨에 정확한 이름과 Hz. `/joint_states`는 두 발행자가 합쳐지는 것을 강조. 아래 1/3은 '팔: TeensyDriver↔AR4_teensy.ino USB CDC ASCII 프로토콜(명령/응답 목록)'과 '손: DynamixelClient↔Dynamixel Protocol 2.0' 두 칸. 오른쪽 위에 주기 표, 오른쪽 아래에 범례. 가로 16:9."

---

## D4. 실행 추적 — "RViz에서 실제 로봇 움직임까지"

**목적:** 명령 하나가 어떤 코드를 거쳐 모터까지 내려가고(**Command Path, downward**), 측정값이 어떻게 화면까지 올라오는가(**Feedback Path, upward**).
**배치:** 세로 2개 열(왼쪽 = 팔, 오른쪽 = 손). 각 열은 위(사용자·RViz) → 아래(모터) 층 순서.
각 열 안에서 **왼쪽 반 = Command Path(아래로, 진한 색 화살표)**, **오른쪽 반 = Feedback Path(위로, 청록 화살표)**.
같은 층에 있는 명령 블록과 피드백 블록은 나란히 놓는다(예: `write()` ↔ `read()`). 단계 번호 원을 블록 옆에.

### 팔 레인 (기존 AR4 MoveIt 경로 · 통합 MoveIt이 생겨도 실행부는 동일)
| # | 블록 (색) | 하는 일 | 다음으로 |
|---|---|---|---|
| A1 | `USER`→`ROS` **rviz2 MotionPlanning 패널** | 인터랙티브 마커로 목표 자세 지정, Planning Group `ar_manipulator`, **Plan** 클릭 | action `/move_action` |
| A2 | `ROS` **move_group: IK** | 목표 자세 → 관절 목표 (KDLKinematicsPlugin, `kinematics.yaml`) | |
| A3 | `ROS` **move_group: planning pipeline** | OMPL로 경로 탐색(`ompl_planning.yaml`), planning scene으로 충돌 검사(URDF + SRDF `disable_collisions`), request adapters(CheckStartStateBounds 등) | |
| A4 | `ROS` **move_group: time parameterization** | response adapter `AddTimeOptimalParameterization` — 각 점에 시간·속도 부여(`joint_limits.yaml`) → RobotTrajectory | topic `/display_planned_path` → RViz 미리보기 |
| A5 | `ROS` **TrajectoryExecutionManager → MoveItSimpleControllerManager** | **Execute** 시 `config/controllers.yaml`에 적힌 컨트롤러로 전송 | action `/joint_trajectory_controller/follow_joint_trajectory` |
| A6 | `ROS` **joint_trajectory_controller** (60 Hz) | 궤적을 spline 보간 → 이번 주기의 **목표 위치·속도**를 command interface에 기록. ※ position+velocity 두 interface를 쓰는 설정이라 **PID 보정 없이 궤적 속도를 그대로 전달**(ros2_controllers 소스 기준; controllers.yaml의 gains는 이 조합에서 쓰이지 않음) | iface `joint_N/position`, `joint_N/velocity` |
| A7 | `AR4` **ARHardwareInterface::write()** | rad→deg, 관절 오프셋 적용 → `TeensyDriver::update()` | call |
| A8 | `AR4` **TeensyDriver::update()** | `velocity_control_enabled: true`(driver.yaml) → **`MVA<v>B<v>…F<v>\n`** 전송 | serial `/dev/ttyACM0` |
| A9 | `AR4` **AR4_teensy.ino `stateTRAJ()` → `MoveVelocity()`** | 관절 최대속도 제한(`JOINT_MAX_SPEED`) → deg/s를 steps/s로 변환(`MOTOR_STEPS_PER_DEG`) → AccelStepper `setSpeed()` → 응답 `ES<estop>` | STEP/DIR 펄스 |
| A10 | `AR4`+HW **stepper driver → stepper motor** | 관절 회전 | |
| **Feedback Path (upward, 청록)** | | | |
| F1 | `AR4`+HW **encoder ×6** | 회전을 A/B 펄스로 → Teensy가 계속 카운트(`encPos[i].read()`) | |
| F2 | `AR4` **ARHardwareInterface::read()** (다음 60 Hz 주기 시작) | `JP` 요청 → 펌웨어 `readMotorSteps()` → `encStepsToJointPos()`(CAL_OFFSET_DEG) → `JP A…F…` / `JV` → 속도 → deg→rad + 오프셋 → **state interface** | iface |
| F3 | `ROS` **joint_trajectory_controller** | 실제값 vs 목표값 오차 계산 → **허용오차 감시**(trajectory 0.2 rad, goal 0.02 rad) → 초과 시 중단(abort), 도착 시 액션 result SUCCESSFUL. 액션 feedback(desired/actual/error)을 move_group에 보냄 | action feedback/result |
| F4 | `ROS` **joint_state_broadcaster** | state interface → `/joint_states` (joint_1..6) | topic |
| F5 | `ROS` **robot_state_publisher** | `/joint_states` + URDF → `/tf` | topic |
| F6 | `ROS` **rviz2 RobotModel / move_group CurrentStateMonitor** | 화면 갱신, 다음 계획의 시작 상태로 사용 | |

### 손 레인
| # | 블록 (색) | 하는 일 | 다음으로 |
|---|---|---|---|
| H1 | `USER`/`NEW` **hand_pose fist** (또는 슬라이더 GUI, CLI action) | 미리 정한 각도를 rad로 발행 | topic `/orcahand_driver/joint_command` (또는 action `/orcahand_driver/follow_joint_trajectory`) |
| H1' | `NEW` (planned) **ar4_orca_moveit_config → move_group** | 손 그룹 `orca_hand` 계획 | action `/orcahand_driver/follow_joint_trajectory` (점선) |
| H2 | `NEW` **hand_driver_node._on_command** | → `HandBackend.to_core_deg()`(이름 확인, rad→deg) → `set_target_deg()`(ROM 클램프) | call |
| H3 | `NEW` **hand_driver_node._tick() (50 Hz) → HandBackend.step(dt)** | 관절당 최대 180°/s로 한 걸음씩 | call |
| H4 | `ORCA` **OrcaHand.set_joint_positions()** | `_joint_to_motor_pos()`: 캘리브레이션 데이터(관절↔모터 비율, 모터 한계, `joint_to_motor_map` 부호)로 관절각 → 모터 위치 → `_set_motor_pos()` | call |
| H5 | `ORCA` **DynamixelClient.write_desired_pos()** | `GroupSyncWrite` Goal Position(116) | serial Protocol 2.0 |
| H6 | `ORCA`+HW **Dynamixel ×17 (current_based_position)** | **모터 내부 위치 PID + 전류 제한** → 스풀이 텐던을 당김 → 손가락·손목 이동 | |
| **Feedback Path (upward, 청록)** | | | |
| G1 | `ORCA`+HW **Dynamixel 내장 엔코더** | 모터 축 위치 측정 (모터 내부 루프에 사용) | |
| G2 | `ORCA` **DynamixelClient.read_position_velocity_current()** | `GroupSyncRead`(126) — 같은 50 Hz tick 안에서 | serial |
| G3 | `ORCA` **OrcaHand.get_joint_position()** | `_motor_to_joint_pos()`: 모터 위치 → **추정 관절각** (관절 엔코더 없음) | call |
| G4 | `NEW` **HandBackend.read_rad()** → hand_driver_node | deg→rad, `hand_` 접두어 → `/joint_states` (hand_* 17) | topic |
| G5 | `ROS` **robot_state_publisher → rviz2** | 팔과 같은 경로로 화면 갱신 | |

### 루프 표시 (각각 다른 색 괄호로 감싸기)
| 루프 | 범위 | 성격 |
|---|---|---|
| **Loop A** (팔, 60 Hz) | A6 → A10 → F1 → F2 → F3 → A6 | 명령은 궤적 속도 그대로 전달, 엔코더 값으로 **오차 감시·중단 판단**(감시형 피드백) |
| **Loop B** (손 모터 내부) | H6 ↔ G1 | Dynamixel 안에서 위치를 실제로 맞추는 **폐루프 제어** |
| **Loop C** (손, 50 Hz) | H3 → H6 → G2 → G4 | 관절 단위로는 **개루프**(모터 위치로 관절각 추정) |
| **Loop D** (모니터링) | F4/G4 → F5 → F6 | 제어가 아니라 **표시·상태 추정** |

### Claude Design 프롬프트 (D4)
> "0장 규칙으로 '실행 추적: Command Path(downward) / Feedback Path(upward)' 다이어그램을 그려줘. 세로 2개 열(왼쪽 팔, 오른쪽 손), 위는 사용자·RViz, 아래는 모터. 각 열의 왼쪽 반은 아래로 내려가는 명령 경로, 오른쪽 반은 위로 올라오는 청록색 피드백 경로이며 같은 층의 블록(write↔read 등)은 나란히. 블록마다 단계 번호 원(A1…A10, F1…F6, H1…H6, G1…G5)과 '굵은 함수/노드 이름 + 작은 파일 경로'. 선 라벨에는 실제 토픽·액션·시리얼 명령(MVA…F…, JP, GroupSyncWrite 116 등). Loop A~D는 서로 다른 색 괄호로 감싸고 성격(감시형/폐루프/개루프/모니터링) 표시. planned(H1')는 점선. 가로 16:9, 글자 겹치지 않게."

---

## 부록 A. 사실 확인 출처 (다이어그램 검토용)
| 내용 | 파일 |
|---|---|
| 60 Hz, JTC position+velocity, gains, tolerance | `annin_ar4_driver/config/controllers.yaml` |
| velocity_control_enabled: true (MV 사용) | `annin_ar4_driver/config/driver.yaml` |
| read(): JP+JV / write(): rad→deg, offset, update() | `annin_ar4_driver/src/ar_hardware_interface.cpp` L210-275 |
| 시리얼 115200, STA/JC/JM/MV/MT/JP/JV/PK/RE, 응답 헤더 | `annin_ar4_driver/src/teensy_driver.cpp` |
| /park, /calibrate_mask (노드 ar4_hw_services_<model>) | `ar_hardware_interface.cpp` L55-112 |
| stateTRAJ, MoveVelocity, readMotorSteps(encPos.read), encStepsToJointPos | `annin_ar4_firmware/AR4_teensy/AR4_teensy.ino` L374-400, 449-466, 866-1033 |
| JTC: position+velocity면 PID 미사용 | ros2_controllers (jazzy) `joint_trajectory_controller.cpp` L926-929, L430-438 |
| MoveIt 컨트롤러 매핑, KDL, OMPL, AddTimeOptimalParameterization | `annin_ar4_moveit_config/config/{controllers,kinematics,ompl_planning}.yaml` |
| SRDF 그룹 ar_manipulator, group_state home/upright | `annin_ar4_moveit_config/srdf/ar_macro.srdf.xacro` |
| Protocol 2.0, Goal Position 116, Present Pos/Vel/Cur 126, GroupSyncWrite/Read | `orca_core/hardware/dynamixel_client.py` |
| get_joint_position → read_position_velocity_current, _joint_to_motor_pos | `orca_core/hardware_hand.py` L690-712, L1294-1410 |
| 통합 launch, 노드 순서 | `ar4_orca_bringup/launch/bringup.launch.py` |
| 핸드 드라이버 50 Hz, 180°/s, 토픽·액션·서비스 | `orcahand_driver/orcahand_driver/{hand_driver_node,hand_backend}.py` |

## 부록 B. 다음 단계 (그림 완성 후)
그림 D1~D4가 확정되면 각 블록을 하나씩 설명하는 기술 문서(Claude Docs)를 만든다:
다이어그램별 해설 · 용어집(ROS 2 / ros2_control / MoveIt / 제어 / 통신) · 코드 읽는 순서 · 공부 로드맵.
