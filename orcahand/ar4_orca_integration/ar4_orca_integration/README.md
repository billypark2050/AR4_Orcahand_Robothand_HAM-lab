# ar4_orca_integration

AR4 MK5 로봇팔과 ORCA Hand v2를 **ROS 2 Jazzy에서 하나의 로봇으로 시각화(RViz2)하고 제어**하기 위한 패키지 묶음입니다.
드라이버 두 개(AR4: ros2_control / ORCA: orca_core)가 병행 실행되고, 하나의 통합 URDF를 사용합니다.

```
                    ┌───────── ar4_orca_bringup/bringup.launch.py ─────────┐
 ar4_orca_description (AR4 + 어댑터 + ORCA, xacro)                          │
        │ robot_description                                                │
        ▼                                                                  │
 robot_state_publisher ◀── /joint_states ──┬─ joint_state_broadcaster      │
        │ TF                               │     (joint_1..6, AR4)         │
        ▼                                  └─ orcahand_driver              │
      RViz2                                      (hand_wrist, hand_index_mcp …)
                                                                           │
 MoveIt/CLI ─▶ /joint_trajectory_controller/follow_joint_trajectory ─▶ AR4 Teensy
 CLI/GUI    ─▶ /orcahand_driver/joint_command | follow_joint_trajectory ─▶ orca_core ─▶ Dynamixel
```

| 패키지 | 역할 |
|---|---|
| `orcahand_ros_description` | ORCA Hand v2 xacro 매크로(`prefix`, `side`, `parent`, origin) + 메쉬(DAE 시각 / 볼록껍질 STL 충돌). orca_ui 번들의 `hand.urdf`에서 생성 → **관절 이름 = orca_core id, 각도 = deg→rad 1:1** |
| `ar4_orca_description` | `ar4_orca.urdf.xacro`: AR4(mk1~5) + 장착 파츠(어댑터 등, `config/mount.yaml`) + 손 + AR4 `ros2_control`(실물/mock). AR4 그리퍼는 제외. 구조 검사 도구 `check_model.py` 포함 → **`MODEL_STRUCTURE.md` 참고** |
| `orcahand_driver` | orca_core를 감싼 rclpy 노드. `/joint_states` 발행, 스트리밍 명령, FollowJointTrajectory 액션, torque/neutral/e-stop 서비스 |
| `ar4_orca_bringup` | 두 드라이버 + RSP + RViz를 한 번에 실행 (`arm_mock`, `hand_mock`로 각각 실물/가상 선택) |

> 공식 `orcahand_description`(GitHub)과 이름이 겹치지 않도록 `orcahand_ros_description`으로 명명했습니다. 공식 저장소는 같은 `src/`에 있어도 됩니다(참고용: MJCF, 원본 STL). 공식 v2 URDF는 관절명이 CAD 자동 이름이라 orca_core와 직접 매핑되지 않습니다.

---

## 1. 설치 (Ubuntu 24.04 + ROS 2 Jazzy PC)

### 1-1. 워크스페이스 배치
```
~/ros2_ws/src/
 ├── ar4_ros_driver/          # 기존 (annin_ar4_*)
 └── ar4_orca_integration/    # 이 폴더 (4개 패키지)
```
Z: 드라이브에서 복사해 오는 경우 Windows 줄바꿈(CRLF)이 섞일 수 있습니다. 특히 `.sh`, `.py`는 Linux에서 오류가 나므로 한 번 정리하세요.
```bash
sudo apt install -y dos2unix && find ~/ros2_ws/src -type f \( -name '*.py' -o -name '*.sh' -o -name '*.xacro' -o -name '*.yaml' \) -exec dos2unix -q {} +
```
(Z:의 `ar4_ros_driver` 사본은 git 기준으로 54개 파일이 CRLF 변환만 된 상태입니다.)

### 1-2. ROS 의존성
```bash
sudo apt install -y ros-jazzy-joint-state-publisher-gui ros-jazzy-xacro \
  ros-jazzy-ros2-control ros-jazzy-ros2-controllers ros-jazzy-control-msgs \
  python3-serial python3-yaml
cd ~/ros2_ws && rosdep install --from-paths src --ignore-src -r -y
```

### 1-3. orca_core를 ROS의 Python에 설치 (중요)
orca_core 0.8.0은 `numpy>=2.2.6`을 요구하지만, ROS 2 Jazzy의 메시지 C 확장은 Ubuntu의 numpy 1.26으로 빌드되어 있습니다.
그래서 numpy 2가 설치되면 rclpy 메시지 import가 깨질 수 있으므로 **`--no-deps`로 설치**합니다.
(검증: orca_core 0.8.0 테스트 1,613개가 numpy 1.26에서 통과했습니다. Feetech 테스트 1개만 float32 반올림 차이(1e-9 rad)로 실패했고 동작에는 영향이 없습니다.)

```bash
# 캘리브레이션에 쓴 로컬 orca_core 체크아웃을 editable로 설치 → 같은 calibration.yaml을 사용
pip3 install --user --break-system-packages --no-deps -e ~/orcahand/orca_core
pip3 install --user --break-system-packages --no-deps "dynamixel-sdk>=3.7.31,<4"
python3 -c "import numpy, orca_core; print(numpy.__version__, orca_core.__file__)"   # numpy 1.26.x 여야 함
```

### 1-4. 빌드
```bash
cd ~/ros2_ws && colcon build --symlink-install
source install/setup.bash
```

---

## 2. 어떤 핸드 config를 쓰는가 (캘리브레이션 위치)

`calibration.yaml`은 **`config.yaml`과 같은 폴더**에 저장됩니다.

* orca_core 스크립트(`scripts/calibrate.py …/orcahand-right/config.yaml`)로 캘리브레이션 → `~/orcahand/orca_core/orca_core/models/v2/orcahand-right/calibration.yaml`
* orca_ui로 캘리브레이션 → orca_ui의 `.venv` 안에 설치된 orca_core 모델 폴더에 저장될 수 있습니다.

```bash
find ~ -name calibration.yaml -path '*orcahand-right*' 2>/dev/null
```
찾은 경로의 `config.yaml`을 `hand_config_path:=`로 넘겨 주세요. 드라이버는 **절대 자동으로 캘리브레이션하지 않으며**, 캘리브레이션이 안 된 config이면 시작을 거부합니다.
캘리브레이션과 텐셔닝은 ROS를 끈 상태에서 orca_ui 또는 orca_core 스크립트로 하세요. 시리얼 포트는 한 프로세스만 점유할 수 있습니다.

---

## 3. 단계별 실행/검증 순서

| 단계 | 명령 | 확인할 것 |
|---|---|---|
| ① 핸드 모델만 | `ros2 launch orcahand_ros_description view_hand.launch.py` | 슬라이더로 손가락이 굽혀지는 방향이 orca_ui 3D 뷰와 같은지 |
| ② 팔+핸드 모델 검사·마운트 조정 | `ros2 run ar4_orca_description check_model.py` → `ros2 launch ar4_orca_description view_ar4_orca.launch.py` | `[OK]` + 팔·손 전체 표시. 장착 위치/파츠는 `ar4_orca_description/config/mount.yaml`에서 수정 |
| ③ 하드웨어 없이 전체 | `ros2 launch ar4_orca_bringup bringup.launch.py arm_mock:=true hand_mock:=true` | `ros2 topic echo /joint_states`에 6+17 관절, RViz에서 하나의 로봇 |
| ④ 실제 팔 + 가상 핸드 | `… arm_mock:=false calibrate:=True hand_mock:=true` | 기존 AR4 튜토리얼과 같은 동작 |
| ⑤ 가상 팔 + 실제 핸드 | `… arm_mock:=true hand_config_path:=<config.yaml>` | 시작 시 neutral 이동, `hand_pose fist/open` |
| ⑥ 전체 실물 | `… calibrate:=True hand_config_path:=<config.yaml>` | |

### 핸드 명령 예
```bash
ros2 run orcahand_driver hand_pose fist        # open | fist | pinch | neutral
ros2 topic pub --once /orcahand_driver/joint_command sensor_msgs/msg/JointState \
  "{name: [hand_index_mcp, hand_index_pip], position: [1.2, 1.0]}"          # rad, 일부 관절만 가능
ros2 action send_goal /orcahand_driver/follow_joint_trajectory control_msgs/action/FollowJointTrajectory \
  "{trajectory: {joint_names: [hand_index_mcp], points: [{positions: [1.4], time_from_start: {sec: 2}}, {positions: [0.0], time_from_start: {sec: 4}}]}}"
ros2 service call /orcahand_driver/estop std_srvs/srv/Trigger          # 토크 OFF + 래치
ros2 service call /orcahand_driver/reset_estop std_srvs/srv/Trigger
ros2 service call /orcahand_driver/enable_torque std_srvs/srv/Trigger
```
손가락 슬라이더 GUI: `bringup.launch.py … hand_gui:=true`. GUI는 열려 있는 동안 계속 명령을 보내므로, trajectory를 실행할 때는 닫아 주세요.

### 팔 명령 예 (MoveIt 없이)
```bash
ros2 action send_goal /joint_trajectory_controller/follow_joint_trajectory control_msgs/action/FollowJointTrajectory \
  "{trajectory: {joint_names: [joint_1, joint_2, joint_3, joint_4, joint_5, joint_6], points: [{positions: [0, 0, 0, 0, 0.5, 0], time_from_start: {sec: 4}}]}}"
# 또는: sudo apt install ros-jazzy-rqt-joint-trajectory-controller && ros2 run rqt_joint_trajectory_controller rqt_joint_trajectory_controller
```

---

## 4. 핸드 드라이버 동작 요약
* 50 Hz 루프에서 다음을 반복합니다.
  1. 목표 각도로 이동합니다. 관절당 최대 `max_joint_speed_deg_s`(기본 180°/s)로 제한하고, orca_core가 ROM 클램프를 적용합니다.
  2. `get_joint_position()`으로 현재 각도를 읽어 `/joint_states`로 발행합니다.
* **모터 전용 핸드**는 `/joint_states`의 손가락 각도가 "모터 위치로 추정한 관절 각도"입니다. 물체를 쥐면 실제 손가락 각도와 차이가 날 수 있습니다. 그래서 trajectory 완료 판정은 기본적으로 관대하게 설정되어 있습니다(`goal_tolerance_deg: 15`, `strict_goal_check: false`).
* 종료(Ctrl-C) 시 토크를 끕니다(`disable_torque_on_shutdown`). 이때 손가락이 힘을 잃고 풀립니다.
* 주요 파라미터는 `orcahand_driver/config/orcahand_driver.yaml`에 있습니다.

## 5. 핸드 모델 재생성 (orca_ui 업데이트 시)
```bash
pip install trimesh pycollada numpy pyyaml
python3 orcahand_ros_description/tools/build_from_orca_ui.py ~/orcahand/orca_ui --orca-core ~/orcahand/orca_core
```

## 6. 다음 단계 (Phase 2)
* 통합 MoveIt config를 만듭니다.
  * SRDF: `ar_manipulator`, `orca_hand` 그룹, 충돌 비활성 쌍
  * `moveit_controllers.yaml`: 팔은 JTC, 핸드는 `/orcahand_driver/follow_joint_trajectory`
* 실제 어댑터 치수(또는 STL)를 `config/mount.yaml`에 반영합니다.
* (선택) 손목 카메라 등 센서 프레임을 추가합니다.
