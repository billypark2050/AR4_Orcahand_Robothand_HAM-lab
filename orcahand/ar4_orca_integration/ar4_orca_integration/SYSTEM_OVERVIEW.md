# AR4 MK5 + ORCA Hand — 시스템 개요 (경로 · 구조 · 실행)

작성일: 2026-10-20 · 대상: ROS 2 Jazzy / Ubuntu 24.04

---

## 1. 파일 경로

### 1-1. NAS (보관용, 여기서 실행하지 않음)
```
Z:\Lab Members\Current Members\Billy Park\02. Research\RobotHand\
 ├── ar4_ros_driver\                  # AR4 MK5 ROS 2 드라이버 (git: Annin-Robotics/ar4_ros_driver)
 │    ├── annin_ar4_description\      #   팔 URDF/xacro, 메쉬 (mk1~mk5)
 │    ├── annin_ar4_driver\           #   ros2_control 하드웨어 플러그인 (Teensy/Nano 시리얼)
 │    ├── annin_ar4_moveit_config\    #   MoveIt + RViz 설정 (팔 단독)
 │    ├── annin_ar4_gazebo\           #   시뮬레이션
 │    └── annin_ar4_firmware\         #   Teensy / Arduino Nano 펌웨어
 └── orcahand\
      ├── orca_core\                  # 핸드 제어 Python 라이브러리 (git: orcahand/orca_core, v0.8.0)
      ├── orca_ui\                    # 웹 UI: 캘리브레이션·텐셔닝·3D 뷰 (git: orcahand/orca_ui)
      ├── orcahand_description\       # 공식 URDF/MJCF (참고용, 이번 통합에서는 사용하지 않음)
      └── ar4_orca_integration\       # ★ 새로 만든 통합 ROS 2 패키지 4개 (이 문서 위치)
```

### 1-2. Ubuntu 작업 PC (실제 실행 위치)
```
~/ros2_ws/src/
 ├── ar4_ros_driver/                  # git clone (필수, 함께 빌드)
 └── ar4_orca_integration/            # NAS에서 복사 (필수, 함께 빌드)
~/orcahand/
 ├── orca_core/                       # git clone (필수) → pip install --no-deps -e 로 설치
 └── orca_ui/                         # git clone (선택) → ROS를 끈 상태에서 캘리브레이션/텐셔닝용
```
- `~/orcahand/orca_core` 는 예시 경로. **실제로 캘리브레이션을 수행한 orca_core 폴더**를 쓸 것
  (`calibration.yaml` 은 `config.yaml` 옆에 저장됨: `orca_core/models/v2/orcahand-right/`).
- NAS에서 복사한 파일은 CRLF 줄바꿈이 섞일 수 있으므로 `dos2unix` 정리 후 빌드.

### 1-3. 필수 / 선택 정리
| 구성 | 출처 | 필요 여부 |
|---|---|---|
| ar4_ros_driver | git clone | 필수 |
| orca_core | git clone + pip | 필수 |
| ar4_orca_integration | NAS 복사 | 필수 |
| orca_ui | git clone | 선택 (유지보수용) |
| orcahand_description (공식) | git clone | 불필요 |

---

## 2. ar4_orca_integration 구조 설명 (다이어그램 작성용)

> 이 절은 구조도(다이어그램)를 그리기 위한 사실 서술이다. 박스 = 패키지/노드/하드웨어, 화살표 = 데이터 흐름.

### 2-1. 한 줄 요약
두 개의 드라이버(AR4 = ros2_control, ORCA = orca_core 기반 Python 노드)가 **병행 실행**되고,
각자 자기 관절 상태를 같은 `/joint_states` 토픽에 발행한다. **하나의 통합 URDF**를 가진
`robot_state_publisher`가 이를 합쳐 TF를 만들고, **RViz2가 팔+핸드를 하나의 로봇으로 표시**한다.

### 2-2. 레이어 구성 (위 → 아래)
1. **사용자 / 상위 명령 레이어**
   - RViz2 (시각화), CLI (`ros2 action/topic/service`), `hand_pose` CLI, 슬라이더 GUI(`hand_gui`), (Phase 2) MoveIt
2. **ROS 2 노드 레이어**
   - `robot_state_publisher` (1개): 통합 URDF 보유 → `/tf`, `/tf_static`, `/robot_description` 발행
   - `controller_manager` (`ros2_control_node`, 60 Hz)
     - `joint_state_broadcaster` → `/joint_states` (joint_1..joint_6)
     - `joint_trajectory_controller` ← `/joint_trajectory_controller/follow_joint_trajectory` (액션)
     - 하드웨어 플러그인: `annin_ar4_driver/ARHardwareInterface` (실물) 또는 `mock_components/GenericSystem` (`arm_mock:=true`)
   - `orcahand_driver` (Python, 50 Hz)
     - 발행: `/joint_states` (hand_wrist, hand_thumb_*, hand_index_* … 17개, rad)
     - 발행: `/orcahand_driver/commanded_joint_states` (마지막으로 보낸 명령)
     - 구독: `/orcahand_driver/joint_command` (sensor_msgs/JointState, 일부 관절만 가능)
     - 액션: `/orcahand_driver/follow_joint_trajectory` (control_msgs/FollowJointTrajectory)
     - 서비스: `~/enable_torque`, `~/disable_torque`, `~/neutral`, `~/estop`, `~/reset_estop` (std_srvs/Trigger)
3. **라이브러리 레이어**
   - AR4: `annin_ar4_driver` C++ 플러그인 (Teensy 통신, 관절 오프셋, 리밋스위치 캘리브레이션)
   - ORCA: `orca_core` Python 라이브러리 (`load_hand → connect → init_joints → set_joint_positions / get_joint_position`),
     관절각(deg) ↔ 모터 위치 변환, ROM 클램프, `calibration.yaml` 적용
4. **하드웨어 레이어**
   - AR4 MK5: USB 시리얼 `/dev/ttyACM0` → Teensy 4.1 → 스테퍼 모터 6축 (+ 엔코더, 리밋스위치)
   - ORCA Hand v2 right (모터 전용): USB 시리얼(자동 탐지) → Dynamixel 17개 → 텐던 → 손가락/손목

### 2-3. 데이터 흐름 (화살표)
- [명령 · 팔] CLI/MoveIt → `joint_trajectory_controller` → ARHardwareInterface → Teensy → 팔 모터
- [명령 · 핸드] CLI/`hand_pose`/GUI → `/orcahand_driver/joint_command` 또는 trajectory 액션 → `orcahand_driver`
  → (속도 제한 180°/s) → `orca_core.set_joint_positions(deg)` → Dynamixel
- [상태 · 팔] 엔코더 → Teensy → ARHardwareInterface → `joint_state_broadcaster` → `/joint_states`
- [상태 · 핸드] Dynamixel 위치 → `orca_core.get_joint_position()` (모터 기반 추정 관절각) → `orcahand_driver` → `/joint_states`
- [시각화] `/joint_states` (팔 6 + 핸드 17, 부분 메시지 병합) → `robot_state_publisher` → `/tf` → RViz2 RobotModel

### 2-4. 통합 URDF 트리 (ar4_orca.urdf.xacro)
```
world
 └─ base_link ─ joint_1 ─ link_1 ─ joint_2 ─ link_2 ─ … ─ joint_6 ─ link_6
     └─ ee_link (플랜지 면)
         └─ hand_adapter_joint (fixed) ─ hand_adapter (어댑터 원판, 임시 치수) ─ hand_adapter_top
             └─ hand_mount_joint (fixed, config/mount.yaml 의 hand.xyz / hand.rpy, 기본 [0,0,0.058] / [1.5707963,0,0])
                 └─ hand_forearm ─ hand_tower ─ hand_wrist ─ hand_carpals
                 ├─ thumb : hand_thumb_cmc → hand_thumb_abd → hand_thumb_mcp → hand_thumb_dip
                 └─ index / middle / ring / pinky : *_abd → *_mcp → *_pip
```

### 2-5. 패키지별 역할과 주요 파일
| 패키지 | 역할 | 주요 파일 |
|---|---|---|
| `orcahand_ros_description` | ORCA 핸드 모델 (관절 이름 = orca_core id, deg↔rad 1:1) | `urdf/orcahand.xacro`, `urdf/orcahand_{right,left}_macro.xacro`, `meshes/{right,left}/{visual(.dae),collision(.stl)}`, `tools/build_from_orca_ui.py`, `launch/view_hand.launch.py` |
| `ar4_orca_description` | 팔 + 어댑터 + 핸드 통합 모델 (AR4 그리퍼 제외) | `urdf/ar4_orca.urdf.xacro`, `urdf/parts/fixed_parts.xacro`, `config/mount.yaml`(장착 파츠·손 위치), `scripts/check_model.py`(구조 검사), `launch/view_ar4_orca.launch.py` |
| `orcahand_driver` | orca_core를 감싼 ROS 2 핸드 드라이버 | `orcahand_driver/hand_driver_node.py` (ROS 인터페이스), `hand_backend.py` (단위/이름 변환·속도 제한·trajectory·e-stop), `hand_pose.py` (CLI), `config/orcahand_driver.yaml` |
| `ar4_orca_bringup` | 전체 동시 실행 | `launch/bringup.launch.py`, `rviz/ar4_orca.rviz` |

### 2-6. 외부 의존 (화살표: 통합 패키지 → 기존 코드)
- `ar4_orca_description` → `annin_ar4_description` (팔 xacro·메쉬), `annin_ar4_driver` (ros2_control 태그, 관절 오프셋, driver.yaml)
- `ar4_orca_bringup` → `annin_ar4_driver/config/controllers.yaml` (60 Hz, JTC 설정)
- `orcahand_driver` → `orca_core` (pip 설치, import)
- `orcahand_ros_description` ⇠ `orca_ui/orca_ui/models/hand_v2` (빌드 시 1회 변환한 원본, 실행 시엔 불필요)

### 2-7. 주기 · 안전
| 항목 | 값 |
|---|---|
| AR4 제어/상태 주기 | 60 Hz (controller_manager `update_rate`) |
| AR4 액션 모니터 | 20 Hz |
| ORCA 제어/상태 주기 | 50 Hz (`control_rate`) |
| ORCA 관절 속도 제한 | 180 °/s (`max_joint_speed_deg_s`) |
| ORCA 안전 | 자동 캘리브레이션 금지(미캘리브레이션 시 시작 거부), ROM 클램프, e-stop 래치, 종료 시 토크 OFF |
| AR4 안전 | 하드웨어 E-Stop 버튼 → `ros2 run annin_ar4_driver reset_estop.sh mk5` |

---

## 3. 최초 1회 준비 (Ubuntu PC)

> 전제: Ubuntu 24.04 + ROS 2 Jazzy 설치 완료, AR4 튜토리얼(`ar4_ros_driver`)을 이미 이 PC에서 돌려 본 상태.
> 이미 끝난 단계는 건너뛰어도 됨.

### 요약 (4단계)
| # | 할 일 | 완료 확인 |
|---|---|---|
| 1 | `~/ros2_ws/src/`에 `ar4_ros_driver`(git clone)와 `ar4_orca_integration`(NAS에서 복사)을 나란히 배치 | `ls ~/ros2_ws/src` 에 두 폴더 |
| 2 | `dos2unix`로 줄바꿈 정리 | `file` 결과에 `CRLF` 없음 |
| 3 | orca_core를 `--no-deps`로 설치 (+ dynamixel-sdk) | numpy 1.26.x, orca_core 경로 출력 |
| 4 | `colcon build --symlink-install` → `source install/setup.bash` | `ros2 pkg list` 에 패키지 4개 |

### 3-1. 소스 배치
```bash
mkdir -p ~/ros2_ws/src && cd ~/ros2_ws/src

# AR4 드라이버 (이미 있으면 생략)
git clone https://github.com/Annin-Robotics/ar4_ros_driver.git

# 통합 패키지: NAS의 RobotHand\orcahand\ar4_orca_integration 폴더를 통째로 복사
#   (예: NAS를 /mnt/nas 로 마운트한 경우)
cp -r "/mnt/nas/Lab Members/Current Members/Billy Park/02. Research/RobotHand/orcahand/ar4_orca_integration" ~/ros2_ws/src/

# 핸드 제어 라이브러리 (이미 캘리브레이션에 쓴 체크아웃이 있으면 그걸 사용, 새로 받지 말 것)
mkdir -p ~/orcahand && cd ~/orcahand
git clone https://github.com/orcahand/orca_core.git      # 없을 때만
git clone https://github.com/orcahand/orca_ui.git        # 선택 (캘리브레이션 UI)
```
확인:
```bash
ls ~/ros2_ws/src
# ar4_orca_integration  ar4_ros_driver
ls ~/ros2_ws/src/ar4_orca_integration
# README.md  SYSTEM_OVERVIEW.md  ar4_orca_bringup  ar4_orca_description  orcahand_driver  orcahand_ros_description
```

### 3-2. 줄바꿈(CRLF) 정리
NAS(Windows)를 거친 파일은 줄바꿈이 CRLF일 수 있음 → `.py`/`.sh` 실행 오류(`/usr/bin/env: 'python3\r'` 등)의 원인.
```bash
sudo apt install -y dos2unix
find ~/ros2_ws/src -type f \( -name '*.py' -o -name '*.sh' -o -name '*.xacro' -o -name '*.yaml' \
  -o -name '*.xml' -o -name '*.txt' -o -name '*.cfg' -o -name '*.rviz' \) -exec dos2unix -q {} +
```
확인: `file ~/ros2_ws/src/ar4_ros_driver/annin_ar4_driver/scripts/reset_estop.sh` → `CRLF` 문구가 없어야 함.

### 3-3. ROS 의존 패키지
```bash
sudo apt update
sudo apt install -y ros-jazzy-joint-state-publisher-gui ros-jazzy-xacro \
  ros-jazzy-ros2-control ros-jazzy-ros2-controllers ros-jazzy-control-msgs \
  python3-serial python3-yaml
cd ~/ros2_ws && rosdep install --from-paths src --ignore-src -r -y
```

### 3-4. orca_core 설치 (중요: `--no-deps`)
- 이유: orca_core 0.8.0은 `numpy>=2`를 요구하지만, ROS 2 Jazzy의 메시지 모듈은 Ubuntu의 numpy 1.26으로 빌드됨.
  numpy 2가 깔리면 rclpy 메시지 import가 깨질 수 있음. (orca_core는 numpy 1.26에서 테스트 1,613개 통과 확인)
- `-e`(editable)로 **캘리브레이션에 사용한 그 orca_core 폴더**를 설치 → 같은 `calibration.yaml`을 사용.
```bash
pip3 install --user --break-system-packages --no-deps -e ~/orcahand/orca_core
pip3 install --user --break-system-packages --no-deps "dynamixel-sdk>=3.7.31,<4"
```
확인:
```bash
python3 -c "import numpy, orca_core; print(numpy.__version__, orca_core.__file__)"
# 1.26.x  /home/<user>/orcahand/orca_core/orca_core/__init__.py   ← numpy 2.x 가 나오면 안 됨
find ~ -name calibration.yaml -path '*orcahand-right*' 2>/dev/null
# 실행 시 hand_config_path 로 넘길 config.yaml 위치 확인 (calibration.yaml 과 같은 폴더)
```
- 시리얼 권한(이미 AR4 튜토리얼에서 했으면 생략): `sudo usermod -aG dialout $USER` 후 재로그인.

### 3-5. 빌드
```bash
source /opt/ros/jazzy/setup.bash
cd ~/ros2_ws
colcon build --symlink-install
source install/setup.bash
```
확인:
```bash
ros2 pkg list | grep -E 'ar4_orca|orcahand'
# ar4_orca_bringup / ar4_orca_description / orcahand_driver / orcahand_ros_description
```
- 매번 source가 번거로우면 `~/.bashrc`에 `source ~/ros2_ws/install/setup.bash` 추가.
- 통합 패키지 파일을 수정했을 때: Python/launch/yaml은 `--symlink-install` 덕분에 재빌드 불필요,
  새 파일 추가나 `package.xml`/`setup.py` 변경 시에는 `colcon build` 다시 실행.

## 4. 실행 (단계별)
3장 준비가 끝난 뒤, 매 터미널마다 `source ~/ros2_ws/install/setup.bash` 필요.

| 단계 | 명령 | 하드웨어 |
|---|---|---|
| ① 핸드 모델 확인 | `ros2 launch orcahand_ros_description view_hand.launch.py` | 없음 |
| ② 통합 모델 검사·마운트 조정 | `ros2 run ar4_orca_description check_model.py` → `ros2 launch ar4_orca_description view_ar4_orca.launch.py` (장착은 `config/mount.yaml` 수정, `MODEL_STRUCTURE.md` 참고) | 없음 |
| ③ 전체 가상 실행 | `ros2 launch ar4_orca_bringup bringup.launch.py arm_mock:=true hand_mock:=true` | 없음 |
| ④ 실제 팔 + 가상 핸드 | `ros2 launch ar4_orca_bringup bringup.launch.py calibrate:=True hand_mock:=true` | AR4 |
| ⑤ 가상 팔 + 실제 핸드 | `ros2 launch ar4_orca_bringup bringup.launch.py arm_mock:=true hand_config_path:=<config.yaml>` | ORCA |
| ⑥ 전체 실물 | `ros2 launch ar4_orca_bringup bringup.launch.py calibrate:=True hand_config_path:=<config.yaml>` | 둘 다 |

- `calibrate:=True` 는 AR4 전원을 켠 뒤 처음 한 번. 이후 재실행은 `calibrate:=False`.
- `<config.yaml>` 예: `~/orcahand/orca_core/orca_core/models/v2/orcahand-right/config.yaml` (캘리브레이션한 것)
- 핸드 캘리브레이션/텐셔닝은 **ROS를 끈 상태**에서 orca_ui 또는 orca_core 스크립트로.

### 동작 확인 명령
```bash
ros2 topic echo /joint_states --once                      # 팔 6 + 핸드 17 관절
ros2 run orcahand_driver hand_pose fist                   # open | fist | pinch | neutral
ros2 service call /orcahand_driver/estop std_srvs/srv/Trigger
ros2 action send_goal /joint_trajectory_controller/follow_joint_trajectory control_msgs/action/FollowJointTrajectory \
  "{trajectory: {joint_names: [joint_1, joint_2, joint_3, joint_4, joint_5, joint_6], points: [{positions: [0, 0, 0, 0, 0.5, 0], time_from_start: {sec: 4}}]}}"
```

## 5. 현재 상태 / 다음 단계
- 완료: 통합 URDF, 핸드 드라이버, 통합 launch. (클라우드 검증: xacro 전개·FK 렌더·백엔드 테스트 5개 통과)
- 미검증: 실제 ROS 실행 (Ubuntu PC에서 ③부터 확인 필요)
- 다음: 통합 MoveIt config (arm + hand 그룹), 실제 어댑터 치수 반영
