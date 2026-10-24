# ar4_orca_integration — 코드 동작 설명 (실행 순서대로)

> 대상: 이 패키지를 처음 보는 사람 / 다른 Claude 세션.
> 경로는 `ar4_orca_integration/` 기준. 줄 번호는 2026-10-21 시점 기준.
> 함께 볼 문서: `SYSTEM_OVERVIEW.md` (경로·구조·설치), `README.md` (사용법).

---

## 0. 큰 그림

```
ros2 launch ar4_orca_bringup bringup.launch.py ...
   │
   ├─(1) xacro 실행 → 통합 URDF 문자열 (팔 + 마운트 + 핸드 + AR4 ros2_control 태그)
   ├─(2) robot_state_publisher  ← URDF 보유, /joint_states → /tf
   ├─(3) ros2_control_node      ← URDF의 <ros2_control> 태그로 AR4 하드웨어 플러그인 로드 (60 Hz)
   ├─(4) spawner × 2            ← joint_state_broadcaster → (끝나면) joint_trajectory_controller
   ├─(5) orcahand_driver        ← orca_core로 핸드 연결, 50 Hz 루프
   ├─(6) rviz2                  ← /robot_description + /tf 로 하나의 로봇 표시
   └─(7) (선택) 슬라이더 GUI     ← 핸드 전용 URDF로 슬라이더, 출력은 핸드 명령 토픽으로
```
핵심 아이디어: **모델은 하나, 드라이버는 둘.** 두 드라이버는 서로를 모르고, 같은 `/joint_states`에
관절 이름이 겹치지 않게 각자 발행할 뿐이다. `robot_state_publisher`는 부분 메시지도 받아서 합친다.

---

## 1. 모델 만들기 (빌드 전에 이미 생성되어 들어 있음)

### 1-1. `orcahand_ros_description/tools/build_from_orca_ui.py` (한 번만 실행하는 생성기)
- 입력: `orca_ui/orca_ui/models/hand_v2/{right,left}/hand.urdf` + `.glb` 메쉬
  (orca_ui 웹 3D 뷰가 쓰는 모델. 관절 이름 = orca_core 관절 id, **각도는 deg→rad만 하면 부호 보정 불필요**)
- 하는 일
  1. `.glb` → `.dae` 변환 (`convert_mesh`): 부품별 색(흰 스킨/검은 몸체)을 collada material로 보존,
     `up_axis`를 `Z_UP`, 단위를 meter로 고정 (안 하면 RViz에서 90° 돌아가 보임)
  2. 같은 메쉬로 볼록껍질 `.stl` 생성 → 충돌용 (MoveIt 자기충돌 계산이 가벼움)
  3. URDF의 link/joint를 xacro 매크로로 다시 씀: 모든 이름 앞에 `${prefix}` (기본 `hand_`)
     - inertial은 버림 (원본 값이 SI 단위가 아니고, RViz/MoveIt엔 불필요)
     - 관절 limit은 orca_core `config.yaml`의 `joint_roms`를 사용 (현재 URDF 값과 동일함을 확인)
  4. 루트에 `${prefix}mount_joint` (fixed) 추가 → `parent` 링크에 붙일 수 있게
  5. `config/hand_joints.yaml`에 관절 목록과 neutral 자세 기록
- 출력: `urdf/orcahand_{right,left}_macro.xacro`, `meshes/{side}/{visual,collision}/`

### 1-2. `orcahand_ros_description/urdf/orcahand.xacro`
- `<xacro:orcahand side prefix parent><origin/></xacro:orcahand>` 매크로 하나로 좌/우 선택.
- `orcahand.urdf.xacro`: `world`에 핸드만 붙인 단독 모델 (`view_hand.launch.py`, 슬라이더 GUI용).

### 1-3. `ar4_orca_description/urdf/ar4_orca.urdf.xacro` — 통합 모델
1. `annin_ar4_description`의 `ar_macro.xacro`를 include → `world → base_link → … → link_6 → ee_link`
   (기존 AR4 코드를 그대로 불러씀, 복사 아님)
2. `config/mount.yaml`(인자 `mount_config`로 교체 가능)을 `xacro.load_yaml`로 읽어서
   - `parts:` 목록 → `urdf/parts/fixed_parts.xacro`의 `fixed_parts` 매크로가 항목마다 고정 조인트+링크 생성
     (기본: `ee_link → hand_adapter(원판) → hand_adapter_top`). 새 파츠는 yaml 항목 추가만으로 붙음
   - `hand:` → `orcahand` 매크로를 `parent=hand.parent`, origin = `hand.xyz` / `hand.rpy`로 호출
     - 기본값 `[0,0,0.058]` / `[1.5707963,0,0]`: 핸드 모델은 손가락이 +Y 방향이므로 X축으로 90° 돌려
       플랜지 법선(+Z)에 맞추고, forearm 하단 반길이(0.058 m)만큼 띄움. **실제 어댑터 치수로 바꿔야 함**
   - 자세한 구조·검증·파츠 추가 방법: `MODEL_STRUCTURE.md`, 검사 도구: `scripts/check_model.py`
3. `include_ros2_control:=true`이면 AR4의 `ar.ros2_control.xacro`를 호출
   - `use_mock_hardware:=true` → 플러그인을 `mock_components/GenericSystem`로 (명령값을 그대로 상태로 돌려주는 가짜 하드웨어)
   - false → `annin_ar4_driver/ARHardwareInterface` (실제 Teensy)
   - **핸드 관절은 ros2_control에 넣지 않음** → controller_manager는 팔 6축만 관리
4. AR4 그리퍼는 넣지 않음.

---

## 2. 실행: `ar4_orca_bringup/launch/bringup.launch.py`

### 2-1. 인자 (L30-44)
`ar_model, arm_mock, calibrate, serial_port, tf_prefix, hand_mock, hand_config_path, hand_side,
hand_prefix, hand_auto_start, mount_config, rviz, hand_gui`

### 2-2. 통합 URDF 생성 (L91-100)
`xacro ar4_orca.urdf.xacro include_ros2_control:=true use_mock_hardware:=<arm_mock> ...` 명령을
조립해서 `robot_description` 파라미터로 만든다. `mount_config`가 비어 있으면 패키지의 `config/mount.yaml`을 사용.

### 2-3. 노드 기동 순서 (L126-136)
| 순서 | 노드 | 하는 일 |
|---|---|---|
| ① | `robot_state_publisher` | URDF를 `/robot_description`으로 발행, `/joint_states` → `/tf` 계산 |
| ② | `ros2_control_node` | URDF의 `<ros2_control>`로 AR4 하드웨어 플러그인 로드. 설정은 **기존** `annin_ar4_driver/config/controllers.yaml` (update_rate 60 Hz) |
| ③ | spawner `joint_state_broadcaster` | 팔 관절 상태를 `/joint_states`로 |
| ④ | spawner `joint_trajectory_controller` | ③이 끝난 뒤(`OnProcessExit`) 실행. `/joint_trajectory_controller/follow_joint_trajectory` 액션 제공 |
| ⑤ | `_hand_driver()` (L66-84) | `orcahand_driver` 노드 실행. 파라미터 = `config/orcahand_driver.yaml` + launch 인자로 덮어쓰기. `hand_mock:=true`이고 config 경로가 없으면 `model_name=orcahand-<side>`를 넘김(가짜 핸드는 자동탐지할 하드웨어가 없으므로) |
| ⑥ | `rviz2` | `rviz/ar4_orca.rviz` (Fixed Frame `world`, RobotModel은 `/robot_description` 토픽) |
| ⑦ | `_hand_gui()` (L47-63) | `hand_gui:=true`일 때만. 핸드 단독 URDF를 임시 파일로 만들어 `joint_state_publisher_gui`에 주고, 출력 토픽을 `/orcahand_driver/joint_command`로 리매핑 → 슬라이더가 곧 핸드 명령 |

---

## 3. 핸드 드라이버 상세 (`orcahand_driver/`)

구조: **`hand_backend.py` (ROS와 무관한 로직) + `hand_driver_node.py` (ROS 인터페이스)**.
백엔드를 분리한 이유: ROS 없이 orca_core의 MockOrcaHand로 단위 테스트 가능 (`test/test_hand_backend.py`, 5개 통과).

### 3-1. 시작 (`hand_driver_node.py` `__init__`, L39-93)
1. 파라미터 선언 (L41-55): `config_path, calibration_path, model_name, mock, joint_prefix, control_rate(50),
   max_joint_speed_deg_s(180), auto_start, move_to_neutral_on_start, disable_torque_on_shutdown,
   joint_states_topic(/joint_states), goal_tolerance_deg(15), strict_goal_check(false), goal_settle_time(0.5)`
2. `HandBackend.from_orca_core(...)` (backend L65) → 내부에서 **`orca_core.load_hand(...)`**
   - `config_path`가 비어 있으면 orca_core가 연결된 하드웨어를 탐지해서 모델 선택
   - `config_path`가 있으면 그 config.yaml + 옆의 calibration.yaml 사용
3. `backend.connect()` (backend L81) → `hand.connect(interactive=False)` (포트 자동탐지, 터미널 질문 없음)
4. `auto_start`이면 `backend.start()` (backend L94)
   - `ensure_calibrated()`: **캘리브레이션 안 됐으면 예외 → 노드 종료** (자동 캘리브레이션 절대 안 함)
   - `hand.init_joints(force_calibrate=False, move_to_neutral=True)`: 토크 ON, 제어모드/전류 설정, neutral 자세로 이동
   - 현재 각도를 읽어 "명령값(_commanded)"과 "목표값(_target)"을 같게 초기화 → 시작하자마자 튀지 않음
   - 여기서 실패하면 `shutdown()`으로 포트를 놓고 예외 전달 (L70-72)
5. 발행자/구독자/서비스/액션 생성 (L78-91), 50 Hz 타이머 등록 (L93)
   - 타이머는 전용 콜백 그룹(한 번에 하나씩), 나머지는 재진입 그룹 + `MultiThreadedExecutor(4)`
     → trajectory 실행이 오래 걸려도 루프와 서비스가 막히지 않음

### 3-2. 50 Hz 루프 `_tick()` (L96-111) — 드라이버의 심장
매 주기마다:
1. `dt` 계산, 최대 3주기로 제한 (L99) → 루프가 늦게 돌아도 한 번에 크게 움직이지 않음
2. `backend.step(dt)` (backend L196)
   - 토크 OFF / e-stop이면 아무것도 안 보냄
   - 관절별로 `목표 - 현재명령` 차이를 `max_speed × dt`(기본 180°/s × 0.02 s = 3.6°) 이내로 잘라 한 걸음 이동
   - 바뀐 관절만 **`hand.set_joint_positions({joint: deg})`** 호출
     → orca_core가 ROM 클램프 + 관절각→모터위치 변환(캘리브레이션 사용) + Dynamixel에 목표 위치 쓰기
3. `backend.read_rad()` (backend L183) → **`hand.get_joint_position()`**
   → orca_core가 모터 위치를 읽어 관절각(deg)으로 역변환 → 드라이버가 rad + `hand_` 접두어로 변환
4. `/joint_states` 발행 (17개 관절), 보낸 명령이 있으면 `~/commanded_joint_states`도 발행
5. 통신 오류가 나도 노드는 죽지 않고 2초에 한 번 에러 로그 (L102-104)

> 모터 전용 핸드이므로 3번 값은 **모터 위치로 추정한 관절각**이다. 물체를 쥐어 손가락이 막히면 실제와 다를 수 있다.

### 3-3. 명령 경로 A — 스트리밍 `~/joint_command` (`_on_command`, L118-130)
- 입력: `sensor_msgs/JointState` (rad). 이름은 `hand_index_mcp`/`index_mcp` 둘 다 허용, 일부 관절만 보내도 됨
- `to_core_deg()` (backend L160): 이름 확인(모르는 관절이면 거부), NaN/inf 거부, rad→deg
- 실행 중인 trajectory가 있으면 **취소(선점)**
- `set_target_deg()`: ROM으로 잘라 목표에 반영 → 실제 이동은 3-2의 루프가 속도 제한하며 수행
- 사용처: `hand_pose` CLI, 슬라이더 GUI, `ros2 topic pub`

### 3-4. 명령 경로 B — 액션 `~/follow_joint_trajectory` (`_execute_traj`, L138-195)
- 수락 조건 (`_on_goal`, L132): 토크 ON이고 e-stop 아님
- `make_trajectory()` (backend L223): 관절 이름 확인, 시간이 증가하는지 확인, rad→deg + ROM 클램프,
  첫 점이 0초가 아니면 **현재 명령 자세를 0초 점으로 추가** (점프 방지)
- 실행 루프: 50 Hz로 `traj.sample(t)`(선형 보간, `TrajectorySample.sample` backend L33) → `set_target_deg`
  - 취소 요청 → 현재 자세 유지 + canceled / 스트리밍 명령으로 선점 → abort
  - 도중 토크 OFF·e-stop → abort
- 끝난 뒤 `goal_settle_time`(0.5 s) 기다렸다가 최종 오차 계산
  - 오차 > `goal_tolerance_deg`(15°): `strict_goal_check:=true`면 실패, 기본은 경고만 하고 성공
  - (텐던 핸드는 부하가 걸리면 정확히 따라가지 못하므로 기본을 관대하게 둠)
- 나중에 MoveIt의 핸드 그룹 컨트롤러가 이 액션을 쓰게 된다 (Phase 2)

### 3-5. 서비스 (L197-222, 모두 `std_srvs/Trigger`)
| 서비스 | 동작 |
|---|---|
| `~/enable_torque` | e-stop 걸려 있으면 거부. 캘리브레이션 확인 → 토크 ON → 목표를 현재 자세로 맞춤(튀지 않게) |
| `~/disable_torque` | 토크 OFF (손가락이 힘 풀림) |
| `~/estop` | trajectory 취소 + 토크 OFF + **래치** (reset 전까지 토크 ON 불가) |
| `~/reset_estop` | 래치 해제 (토크는 여전히 OFF → enable_torque 필요) |
| `~/neutral` | config의 neutral 자세를 목표로 설정 (루프가 천천히 이동) |

### 3-6. 종료 (`close` L224, `main` L231)
- Ctrl-C → `backend.shutdown()`: `disable_torque_on_shutdown`이면 토크 OFF → 포트 닫기
- 시작 단계에서 `HandNotReadyError`(미캘리브레이션 등)면 FATAL 로그만 남기고 종료

### 3-7. `hand_pose.py` (CLI)
`ros2 run orcahand_driver hand_pose fist|open|pinch|neutral`
- open/fist/pinch: 미리 정한 deg 값을 rad로 바꿔 `~/joint_command`에 한 번 발행 (값은 ROM 안임을 확인함)
- neutral: `~/neutral` 서비스 호출

---

## 4. 팔(AR4) 쪽은 무엇을 새로 했나?
**코드는 새로 쓰지 않았다.** 기존 `annin_ar4_driver`를 그대로 쓴다.
- 다른 점은 (1) 팔 단독 URDF 대신 통합 URDF를 넘긴다는 것, (2) 그리퍼 컨트롤러를 띄우지 않는다는 것뿐.
- 팔 명령: `/joint_trajectory_controller/follow_joint_trajectory` (기존 튜토리얼과 동일)
- 캘리브레이션: `calibrate:=True` (전원 켠 뒤 첫 실행), E-Stop 해제: `reset_estop.sh mk5`

---

## 5. 데이터가 한 바퀴 도는 예시 — "주먹 쥐기"
1. `ros2 run orcahand_driver hand_pose fist`
2. → `/orcahand_driver/joint_command`에 `hand_index_mcp=1.48 rad ...` 발행
3. → `_on_command`: deg로 변환(85°), ROM 확인, 목표 갱신
4. → 다음 50 Hz tick: `step()`이 한 번에 최대 3.6°씩 → `orca_core.set_joint_positions` → Dynamixel
5. → 같은 tick: `get_joint_position()` → rad → `/joint_states`
6. → `robot_state_publisher`가 `hand_index_pp` 등의 TF 갱신 → RViz에서 손가락이 굽음
7. 약 0.5초(85° ÷ 180°/s) 후 목표 도달

---

## 6. 알려진 한계 / 주의
- **ROS 실기 실행은 아직 검증 전** (작성 환경에 ROS 런타임이 없었음). 검증된 것: xacro 전개(좌/우·mock/실물),
  URDF 기구학 렌더, 백엔드 단위테스트(MockOrcaHand), 정적 분석.
- orca_core는 `pip install --no-deps`로 설치해야 함 (numpy 2 vs ROS Jazzy numpy 1.26 충돌 방지).
- 핸드 시리얼 포트는 한 프로세스만 사용 가능 → orca_ui와 ROS 드라이버를 동시에 켜지 말 것.
- 슬라이더 GUI는 열려 있는 동안 계속 명령을 보내므로 trajectory와 함께 쓰면 trajectory가 계속 선점됨.
- 팔(60 Hz)과 핸드(50 Hz)는 시간 동기화되지 않음. 동시 동작 조율은 Phase 2(MoveIt)에서.
- 마운트 기본값은 임시값. 실제 어댑터 치수 반영 필요.
