# RobotHand — AR4 MK5 + ORCA Hand v2 통합 (ROS 2 Jazzy)

AR4 MK5 로봇팔과 ORCA Hand v2(오른손)를 **ROS 2 Jazzy에서 하나의 로봇으로** 다루기 위한 패키지 묶음입니다.
하나의 통합 URDF 위에서 팔과 손 드라이버가 함께 실행되고, RViz 표시와 MoveIt 계획·실행을 지원합니다.
하드웨어가 없을 때는 mock(가상 하드웨어)으로 같은 코드를 그대로 실행합니다.

> 기준: 2026-10-24 · Ubuntu 24.04 · ROS 2 Jazzy · orca_core 0.8.0 · 워크스페이스 = 이 저장소 (`~/RobotHand`)
> 통합 패키지 위치: [`orcahand/ar4_orca_integration/ar4_orca_integration/`](orcahand/ar4_orca_integration/ar4_orca_integration/). 아래 문서의 패키지 경로(`ar4_orca_description/...` 등)는 이 폴더 기준입니다.

```
                        ar4_orca_bringup/bringup.launch.py
 ar4_orca_description ──robot_description──▶ robot_state_publisher ──TF──▶ RViz2 (MotionPlanning)
 (AR4 + hand_connector + ORCA)                     ▲ /joint_states                 │
                                                   │                               ▼
                        joint_state_broadcaster ───┤                       move_group (MoveIt)
                        (joint_1..6)               │                   ar4_orca_moveit_config
                                                   │                    │                │
 AR4 Teensy ◀── ARHardwareInterface ◀── joint_trajectory_controller ◀──┘ ar_manipulator  │ orca_hand
 (mock: GenericSystem)       ros2_control                                                  ▼
 Dynamixel ×17 ◀── orca_core ◀── orcahand_driver ◀── ~/follow_joint_trajectory ◀─────────────┘
 (mock: MockOrcaHand)            (hand_* → /joint_states)  ~/joint_command ◀── hand_pose · slider_relay
```

---

## 0. 빠른 시작

```bash
# 하드웨어 없이 (RViz에서 팔·손이 같이 움직임)
ros2 launch ar4_orca_bringup bringup.launch.py arm_mock:=true hand_mock:=true moveit:=true

# 슬라이더 한 창으로 팔 + 손 조작
ros2 launch ar4_orca_bringup bringup.launch.py arm_mock:=true hand_mock:=true gui:=true

# 실물 전체 (전원 투입 직후)
ros2 launch ar4_orca_bringup bringup.launch.py calibrate:=True moveit:=true
```

---

## 1. 패키지 구성

| 패키지 | 역할 |
|---|---|
| `orcahand_ros_description` | ORCA Hand v2 xacro 매크로 + 메시(DAE 시각 / 볼록껍질 STL 충돌). orca_ui 번들에서 생성. **관절 이름 = orca_core 관절 id, 값 = orca_core 각도(deg→rad)**. 오른손 벌림 관절 4개는 orca_core 부호 규칙(+ = 새끼손가락 쪽)에 맞춰 축이 반전되어 있음 |
| `ar4_orca_description` | `urdf/ar4_orca.urdf.xacro`: AR4 + 장착 파츠(`config/mount.yaml`) + 손 + AR4 `ros2_control`. 커넥터 메시 `meshes/hand_connector.STL`. 구조 검사 도구 `check_model.py`. 자세한 구조는 [`MODEL_STRUCTURE.md`](orcahand/ar4_orca_integration/ar4_orca_integration/MODEL_STRUCTURE.md) |
| `orcahand_driver` | orca_core를 감싼 rclpy 노드(`hand_driver_node.py` + ROS 없는 로직 `hand_backend.py`). `/joint_states` 발행, `~/joint_command`, `~/follow_joint_trajectory`, 토크/neutral/e-stop 서비스. 도구: `hand_pose`, `slider_relay` |
| `ar4_orca_bringup` | 팔 컨트롤러 + 손 드라이버 + RSP + RViz(+ MoveIt)를 한 번에 실행 |
| `ar4_orca_moveit_config` | MoveIt 설정: SRDF(`ar_manipulator`, `orca_hand`), 충돌 설정, 한계, OMPL/Pilz, 컨트롤러 매핑 |

관련 저장소 (같은 `~/RobotHand` 아래)

| 경로 | 용도 |
|---|---|
| `~/RobotHand/ar4_ros_driver` | AR4 공식 드라이버 (팔 URDF, 하드웨어 플러그인, 원래 MoveIt 설정) |
| `~/RobotHand/orcahand/orca_core` | 손 제어 라이브러리. 캘리브레이션 결과도 여기 저장 |
| `~/RobotHand/orcahand/orca_ui` | 웹 UI (캘리브레이션·텐셔닝·3D 뷰). **ROS와 동시에 실행 금지** |
| `~/RobotHand/orcahand/orca_teleop` | 핸드 트래킹 + retargeting (아직 ROS와 연결 안 됨) |
| `~/RobotHand/orcahand/orcahand_description` | 공식 URDF/MJCF (참고용) |

빌드 제외: `orca_core`, `orca_ui`, `orcahand_description`에는 `COLCON_IGNORE`가 있습니다.

---

## 2. 설치

### 2-1. ROS 의존성

```bash
source /opt/ros/jazzy/setup.bash
sudo apt install -y ros-jazzy-joint-state-publisher-gui ros-jazzy-xacro ros-jazzy-ros2-control \
  ros-jazzy-ros2-controllers ros-jazzy-control-msgs ros-jazzy-moveit python3-serial python3-yaml python3-pip
cd ~/RobotHand && rosdep install --from-paths . --ignore-src -r -y
```

`sudo`가 들어간 줄은 **한 줄씩** 실행하세요. 여러 줄을 한꺼번에 붙여 넣으면 다음 줄이 비밀번호 입력으로 들어갑니다.

### 2-2. orca_core를 ROS용 Python에 설치

orca_core는 numpy 2.x를 요구하지만 ROS Jazzy는 numpy 1.26 기준입니다. 그래서 **`--no-deps`로** 설치합니다.

```bash
pip3 install --user --break-system-packages --no-deps -e ~/RobotHand/orcahand/orca_core
pip3 install --user --break-system-packages --no-deps "dynamixel-sdk>=3.7.31,<4"
python3 -c "import orca_core, numpy; print(orca_core.__file__, numpy.__version__)"
# → ~/RobotHand/orcahand/orca_core/orca_core/__init__.py 1.26.x
```

### 2-3. 빌드와 환경

```bash
cd ~/RobotHand && colcon build --symlink-install
```

`~/.bashrc`에는 아래 두 줄만 있어야 합니다. 예전 `~/ros2_ws`를 source하는 줄은 지우세요.

```bash
source /opt/ros/jazzy/setup.bash
source ~/RobotHand/install/setup.bash
```

시리얼 포트 권한이 없으면 `sudo usermod -aG dialout $USER`를 실행하고 다시 로그인하세요.

---

## 3. 하드웨어 준비

### 3-1. 손 (orca_core uv 환경, ROS를 끈 터미널에서)

orca_core 자체 도구는 uv 가상환경(numpy 2.x)에서 실행합니다. **이 터미널에서는 ros2 명령이 동작하지 않습니다.**

```bash
export PYTHONPATH=""                       # ROS 경로 분리
cd ~/RobotHand/orcahand/orca_core
uv sync                                    # 처음 한 번 (.venv 생성)
uv run pytest                              # 전부 통과 확인

# 전원이 꺼진 상태에서 손을 움직였다면: 텐션 → 캘리브레이션
uv run python scripts/tension.py   orca_core/models/v2/orcahand-right/config.yaml   # 정리 후 Ctrl+C
uv run python scripts/calibrate.py orca_core/models/v2/orcahand-right/config.yaml

# 확인
uv run python scripts/neutral.py        orca_core/models/v2/orcahand-right/config.yaml
uv run python scripts/manual_control.py orca_core/models/v2/orcahand-right/config.yaml
```

- 텐션을 실행할 때 `Motors [...] did not answer` 경고가 나오면 그 모터는 텐션이 걸리지 않은 것입니다. 전원과 케이블을 확인하고 다시 실행하세요.
- 캘리브레이션 결과는 `orca_core/models/v2/orcahand-right/calibration.yaml`에 저장되고, **ROS 드라이버가 자동으로 이 파일을 읽습니다.**
- 하드웨어 버전은 같은 폴더의 `local_config.yaml`(`hardware_version: 2`)로 v2.0에 고정되어 있습니다. 원본 `config.yaml`은 수정하지 않습니다.
- `.venv`가 깨졌다는 경고가 나오면(`VIRTUAL_ENV ... does not match`) `rm -rf .venv && uv sync`로 다시 만드세요.
- 확인이 끝나면 **이 터미널을 닫고** 새 터미널에서 ROS를 실행하세요. 손 USB 포트는 한 프로그램만 쓸 수 있습니다.

### 3-2. 팔

1. 케이블을 연결합니다.
2. **리밋 스위치가 모두 OFF인지** 확인합니다. 특히 J2, J3을 봅니다. ON이면 손으로 옮겨서 해제합니다.
3. 전원을 켭니다.
4. 팔 캘리브레이션은 `bringup.launch.py`의 `calibrate:=True`(기본값)가 대신합니다. 원래 `annin_ar4_driver/driver.launch.py`를 따로 실행하지 않습니다.
   - 캘리브레이션 중에는 각 관절이 리밋 스위치까지 실제로 움직입니다. 손과 케이블이 걸리지 않는지 확인하세요. 특히 J6 회전 시 손 케이블 감김에 주의하세요.
   - 전원을 끄지 않고 다시 실행할 때는 `calibrate:=False`로 해도 됩니다.

---

## 4. 실행

### 4-1. bringup 인자

| 인자 | 기본값 | 설명 |
|---|---|---|
| `arm_mock` | `false` | `true`: Teensy 대신 ros2_control 가상 하드웨어 |
| `hand_mock` | `false` | `true`: Dynamixel 대신 orca_core 가상 손 (실제 calibration.yaml은 무시하고 가상 캘리브레이션 사용) |
| `calibrate` | `True` | AR4 리밋 스위치 캘리브레이션 (전원 투입 직후 필요) |
| `serial_port` | `/dev/ttyACM0` | AR4 Teensy 포트 |
| `hand_config_path` | `''` | 비우면 `orca_core/models/v2/orcahand-<side>/config.yaml`을 사용 (캘리브레이션 완료된 경우). 시작 로그 `[hand] REAL: using calibrated config ...`로 확인 |
| `moveit` | `false` | `true`: move_group + MotionPlanning RViz |
| `gui` | `false` | `true`: 팔+손 슬라이더 한 창 (`slider_relay`가 팔→컨트롤러, 손→드라이버로 나눠 보냄) |
| `arm_move_time` | `0.5` | `gui:=true`에서 팔이 슬라이더 한 칸을 따라가는 시간 [s]. 실기에서는 크게 |
| `hand_gui` | `false` | 손 슬라이더만 (`gui`와 동시 사용 불가) |
| `rviz` | `true` | RViz 실행 |
| `mount_config` | `''` | 장착 yaml (`''` = `ar4_orca_description/config/mount.yaml`) |
| `hand_side`, `hand_prefix`, `ar_model`, `tf_prefix` | `right`, `hand_`, `mk5`, `''` | |

### 4-2. 단계별 진행 (한 번에 하나씩 실물로)

| 단계 | 명령 | 확인할 것 |
|---|---|---|
| 모델 검사 | `ros2 run ar4_orca_description check_model.py` → `ros2 launch ar4_orca_description view_ar4_orca.launch.py` | `[OK] no problems`, 팔·커넥터·손 표시 |
| A. 둘 다 mock | `... arm_mock:=true hand_mock:=true moveit:=true` | Plan & Execute로 팔·손 동작 |
| B. 손만 실물 | `... arm_mock:=true hand_mock:=false gui:=true` | `hand initialised, torque ON` 뒤 neutral 자세. 슬라이더 방향이 RViz와 실제가 같은지 |
| C. 팔만 실물 | `... arm_mock:=false hand_mock:=true calibrate:=True gui:=true arm_move_time:=2.0` | 캘리브레이션 완료, `/park` 동작 |
| D. 전체 실물 | `... calibrate:=True moveit:=true` | 처음에는 속도 비율을 낮게 |

`ros2 launch`는 터미널을 계속 차지합니다. 명령은 **다른 터미널**에서 보내세요.

---

## 5. 조작 방법

### 5-1. MoveIt (RViz MotionPlanning, `moveit:=true`)

| Planning Group | 관절 | 실행 경로 |
|---|---|---|
| `ar_manipulator` | joint_1~6. IK 끝점 = `hand_tower`(손 베이스) | `/joint_trajectory_controller/follow_joint_trajectory` |
| `orca_hand` | 손 17관절 | `/orcahand_driver/follow_joint_trajectory` |

- **팔:** 손 끝 마커를 끌거나 Goal State `home` / `upright`를 고른 뒤 Plan & Execute를 누릅니다. IK 끝점이 손 베이스라서 커넥터와 forearm 오프셋이 자동으로 역산됩니다.
- **손:** Planning Group을 `orca_hand`로 바꾸고 Goal State `open` / `fist` / `neutral`을 고릅니다.
- **실기에서는** Velocity Scaling을 0.1~0.2로 시작하세요.
- **AR4 base_link에는 충돌 메시가 없습니다.** 손이 로봇 바닥이나 책상에 닿는 것은 검사되지 않습니다.
- MoveIt만 따로 실행하려면 `ros2 launch ar4_orca_moveit_config moveit.launch.py`를 쓰세요 (bringup은 `rviz:=false`).

### 5-2. 손 명령

```bash
ros2 run orcahand_driver hand_pose fist          # open | fist | pinch | neutral
ros2 topic pub --once /orcahand_driver/joint_command sensor_msgs/msg/JointState \
  "{name: [hand_index_mcp, hand_index_pip], position: [1.2, 1.0]}"            # rad, 일부 관절만 가능
ros2 action send_goal /orcahand_driver/follow_joint_trajectory control_msgs/action/FollowJointTrajectory \
  "{trajectory: {joint_names: [hand_index_mcp], points: [{positions: [1.4], time_from_start: {sec: 2}}]}}"
ros2 service call /orcahand_driver/estop std_srvs/srv/Trigger          # 토크 OFF + 래치
ros2 service call /orcahand_driver/reset_estop std_srvs/srv/Trigger
ros2 service call /orcahand_driver/enable_torque std_srvs/srv/Trigger
```

### 5-3. 팔 명령

```bash
ros2 action send_goal /joint_trajectory_controller/follow_joint_trajectory control_msgs/action/FollowJointTrajectory \
  "{trajectory: {joint_names: [joint_1, joint_2, joint_3, joint_4, joint_5, joint_6], points: [{positions: [0.5, 0.3, -0.3, 0, 0.5, 0], time_from_start: {sec: 4}}]}}"
ros2 service call /park std_srvs/srv/Trigger "{}"      # 실물 모드에서만 (하드웨어 플러그인이 제공)
```

---

## 6. 구조와 동작 요약

- **명령과 실행의 분리 (손):** 토픽·액션·서비스 콜백은 목표값만 바꿉니다. 모터 쓰기는 50 Hz 루프 한 곳에서만 일어나고, 관절당 최대 180°/s(`max_joint_speed_deg_s`)와 orca_core ROM 클램프가 항상 적용됩니다.
- **손가락 각도는 추정값:** 관절 엔코더가 아니라 모터 위치를 캘리브레이션 값으로 환산한 값입니다. 그래서 궤적 완료 판정은 관대하게 설정되어 있습니다(`goal_tolerance_deg: 15`).
- **캘리브레이션 보호:** orca_core의 `init_joints()`는 미캘리브레이션 상태면 스스로 캘리브레이션을 시작합니다. 드라이버는 그 전에 `ensure_calibrated()`로 막고 시작을 거부합니다.
- **종료:** Ctrl-C로 끄면 손 토크가 꺼지면서 손가락이 힘을 잃습니다.
- **mock:** 팔은 `mock_components/GenericSystem`, 손은 `MockOrcaHand`를 씁니다. 명령값을 그대로 현재값으로 돌려주며, 물리 계산은 없습니다.
- 파일별 호출 순서는 [`docs/diagrams/ar4_orca_diagrams_d5.html`](orcahand/ar4_orca_integration/ar4_orca_integration/docs/diagrams/ar4_orca_diagrams_d5.html)의 D5를 참고하세요.

---

## 7. 장착 (팔 ↔ 손)

[`ar4_orca_description/config/mount.yaml`](orcahand/ar4_orca_integration/ar4_orca_integration/ar4_orca_description/config/mount.yaml) 한 파일에서 관리합니다.

| 항목 | 값 | 의미 |
|---|---|---|
| `arm.link6_flange` | `false` | AR4 기본 J6 플랜지 제거 (실물에 없음) |
| `hand_connector` | parent `ee_link`, z = −0.017 | SolidWorks 커넥터. 기존 플랜지 안착면에 위치. 축 구멍 방향을 기존 플랜지에 맞춤 |
| `hand_connector_top` | z = +0.02425 | 커넥터 윗면 (ee_link 기준 +7.25 mm) |
| `hand` | xyz (0.010, 0, 0.058), rpy (π/2, 0, 0) | forearm 바닥면 중심을 J6 축에 맞춤 (forearm 메시 원점이 바닥 중심에서 −10 mm 떨어져 있음) |

실측으로 확인할 가정은 세 가지입니다: 커넥터 안착 높이, forearm 중앙 체결, 손바닥 방향(`hand.rpy`의 yaw, 90° 단위).
커넥터나 장착을 바꾸면 `ar4_orca_moveit_config/srdf`의 충돌 설정도 다시 만들어야 합니다.

---

## 8. 외부 저장소를 수정한 부분

`ar4_ros_driver`나 `orca_core`를 업데이트하면 아래 항목을 다시 확인하세요.

| 파일 | 변경 |
|---|---|
| `ar4_ros_driver/annin_ar4_description/urdf/ar_macro.xacro` | `ar_robot` 매크로에 `include_link6_flange:=true` 파라미터 추가 (기본값이라 원래 AR4 런치에는 영향 없음) |
| `ar4_ros_driver/annin_ar4_description/meshes/ar4_mk5/Link_5_Col.STL` | 업스트림 누락 파일. `Link_5_Aluminum.STL` 복사본 |
| `orca_core/orca_core/models/v2/orcahand-right/local_config.yaml` | `hardware_version: 2` 고정 |

---

## 9. 문제 해결

| 증상 | 원인 / 해결 |
|---|---|
| `PackageNotFoundError: ... ros2cli` | `PYTHONPATH=""` 또는 uv 환경이 켜진 터미널. 새 터미널을 여세요 |
| `ModuleNotFoundError: orca_core` (드라이버 종료) | 2-2절 pip 설치가 안 됨 |
| `No executable found` (`check_model.py` 등) | 실행 권한 없음 → `chmod +x <파일>` 후 재빌드 |
| RViz `Error loading geometries ... _Col.STL` | AR4 충돌 메시 누락 → 8절 참고, 해당 패키지 재빌드 |
| mock에서 손가락이 비정상적으로 꺾임 | 실제 calibration.yaml을 mock이 읽은 경우. 현재 launch는 자동으로 피함 |
| `joint_command rejected: unknown hand joints: ['joint_1' ...]` | 손 드라이버에 팔 관절이 섞여 들어감. 손 슬라이더는 `hand_gui`, 팔+손은 `gui`를 쓰세요 |
| `Waiting for an action server...` | bringup이 꺼져 있음. 다른 터미널에서 bringup을 실행한 채로 두세요 |
| `already built in one or more underlay workspaces` | 예전 `~/ros2_ws`가 source된 터미널. bashrc 정리 후 새 터미널 |
| `pytest: error: unrecognized arguments: -n` | 시스템 pytest가 실행됨 → orca_core 폴더에서 `rm -rf .venv && uv sync` 후 `uv run pytest` |
| 손 실물에서 `not fully calibrated` 경고 | 캘리브레이션 필요. ROS를 끄고 3-1절 진행 (mock에서는 정상 메시지) |

---

## 10. 손 모델 재생성 (orca_ui 업데이트 시)

```bash
pip install trimesh pycollada numpy pyyaml
python3 ~/RobotHand/orcahand/ar4_orca_integration/ar4_orca_integration/orcahand_ros_description/tools/build_from_orca_ui.py ~/RobotHand/orcahand/orca_ui \
  --orca-core ~/RobotHand/orcahand/orca_core
```

`--orca-core`를 주면 orca_core 운동학 파일의 부호 규칙이 오른손 축에 반영됩니다. 왼손은 검증되지 않았습니다.

---

## 11. 다음 단계

1. 실물 B~D단계 검증, 장착 가정 실측.
2. 손목 pose 입력 → 팔 IK (MoveIt Servo 또는 전용 IK 노드). ORCA `hand_wrist`와 J5·J6의 역할 분담 결정.
3. `orca_teleop` retargeter → `/orcahand_driver/joint_command` ROS 출력 단계.
4. 입력 장치 공통 형식 정의 (키포인트 21개 + 손목 pose, 좌표계, 주기).
