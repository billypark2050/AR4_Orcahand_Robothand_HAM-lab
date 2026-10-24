# 통합 모델 구조 · 검증 · 파츠 추가 방법

> 순서: **① 모델 구조 확인 → ② 화면으로 확인 → ③ 그다음에 드라이버 연결.**
> 모델 확인 단계에는 드라이버와 orca_core가 필요 없습니다.

---

## 1. 모델이 만들어지는 방식

통합 URDF는 파일 하나로 저장해 두지 않고, launch 시점에 `xacro`가 아래 3개 층을 조립해 만듭니다.

```
ar4_orca_description/urdf/ar4_orca.urdf.xacro
 ├─ ① 팔    : annin_ar4_description/urdf/ar_macro.xacro      (기존 AR4, 수정 없음)
 │            world → base_link → link_1 … link_6 → ee_link(플랜지 면)
 ├─ ② 파츠  : ar4_orca_description/config/mount.yaml 의 parts 목록
 │            (urdf/parts/fixed_parts.xacro 가 목록을 읽어 고정 링크로 만듦)
 │            기본값: ee_link → hand_adapter(원판, 임시 치수) → hand_adapter_top
 └─ ③ 손    : orcahand_ros_description/urdf/orcahand.xacro
              mount.yaml 의 hand.parent → hand_forearm → hand_tower → hand_wrist → …
```

**물리적인 장착 정보는 전부 `config/mount.yaml` 한 파일에 있습니다.** 코드(xacro)를 고치지 않고 yaml만 바꿉니다.

### 기본 트리 (확인된 실제 출력)
```
link_6 --[ee_joint : fixed]--> ee_link
  ee_link --[hand_adapter_joint : fixed]--> hand_adapter            ← 파츠 1 (원판 r=40mm, t=10mm)
    hand_adapter --[hand_adapter_top_joint : fixed]--> hand_adapter_top   ← 파츠 2 (프레임만)
      hand_adapter_top --[hand_mount_joint : fixed]--> hand_forearm       ← 손 시작
        hand_forearm --[hand_tower_fixed]--> hand_tower --[hand_wrist]--> hand_carpals → 손가락 5개
```
관절 수: 팔 6개(회전) + 손 17개(회전) + 고정 관절들.

### 기본 장착값의 의미
| 항목 | 값 | 의미 |
|---|---|---|
| `hand.parent` | `hand_adapter_top` | 어댑터 윗면에 손을 올림 |
| `hand.xyz` | `[0, 0, 0.058]` | 손 모델의 원점이 forearm 중간에 있으므로, 바닥면이 어댑터에 닿도록 반 길이(58 mm)만큼 띄움 |
| `hand.rpy` | `[1.5707963, 0, 0]` | 손 모델은 손가락 방향이 +Y이므로, X축으로 90° 돌려 플랜지 법선(+Z) 방향으로 세움. **세 번째 값(yaw)으로 손바닥 방향을 돌림** |

검증 결과(모든 관절 0): `hand_forearm`이 `ee_link` 기준 z = 0.068 m(어댑터 10 mm + 58 mm), 회전은 roll 90°.

---

## 2. 검증 절차 (Ubuntu, 드라이버 없이)

```bash
source ~/ros2_ws/install/setup.bash
```

### 2-1. 구조 검사 도구
```bash
ros2 run ar4_orca_description check_model.py
ros2 run ar4_orca_description check_model.py --out ~/ar4_orca.urdf     # 펼친 URDF를 파일로도 저장
ros2 run ar4_orca_description check_model.py --mount ~/my_mount.yaml   # 다른 장착 파일 검사
```
이 도구가 출력하는 내용은 아래 네 가지입니다.
1. 트리(팔 → 파츠 → 손). AR4의 메쉬용 보조 링크는 숨기며, 보려면 `--show-all`을 붙입니다.
2. 관절 수. 팔 6개, 손 17개가 아니면 FAIL입니다.
3. `ee_link` 기준 각 파츠와 손 시작점의 위치·자세(모든 관절 0일 때).
4. 문제 목록: 없는 parent, 이름 중복, 없는 메쉬 파일.
   - `Link_5_Col.STL`, `Link_6_Col.STL` 누락은 원래 AR4 저장소의 문제라서 `[note]`로만 표시됩니다. 화면 표시에는 영향이 없습니다.

종료 코드가 0(`[OK] no problems`)일 때만 다음 단계로 넘어갑니다.

### 2-2. 표준 도구로 교차 확인 (선택)
```bash
sudo apt install -y liburdfdom-tools
check_urdf ~/ar4_orca.urdf                 # "Successfully Parsed" + 트리
urdf_to_graphviz ~/ar4_orca.urdf && xdg-open ar4_orca.pdf   # 트리 그림
```

### 2-3. 화면으로 확인 (슬라이더)
```bash
ros2 launch ar4_orca_description view_ar4_orca.launch.py
ros2 launch ar4_orca_description view_ar4_orca.launch.py mount_config:=$HOME/my_mount.yaml
```
- `joint_state_publisher_gui`가 팔과 손 관절값을 모두 보내므로, 드라이버 없이도 **팔과 손 전체가 그려져야 정상**입니다.
- RViz의 TF 표시를 켜면 `ee_link`, `hand_adapter_top`, `hand_forearm` 축을 볼 수 있습니다.
- 장착 위치를 바꾸려면 yaml을 수정한 뒤 이 launch를 다시 실행합니다. `--symlink-install`로 빌드했다면 재빌드는 필요 없습니다.

### 2-4. 두 프레임 사이 변환 직접 보기 (위 launch 실행 중, 다른 터미널)
```bash
ros2 run tf2_ros tf2_echo ee_link hand_forearm
```

---

## 3. 새 파츠 추가 방법

`config/mount.yaml`의 `parts:` 목록에 항목을 추가합니다. 항목 하나가 **고정 조인트 1개와 링크 1개**가 됩니다. 목록 순서대로 붙으므로, 앞에서 만든 파츠를 parent로 쓸 수 있습니다.

### 3-1. 항목 형식
```yaml
- name: wrist_camera            # 링크 이름 (조인트는 wrist_camera_joint)
  parent: hand_adapter          # 붙일 대상: ee_link, link_6, 앞의 파츠, 손 링크(hand_carpals 등)
  xyz: [0.05, 0, 0.005]         # parent 기준 위치 [m]
  rpy: [0, 1.5707963, 0]        # parent 기준 회전 [rad] (roll, pitch, yaw)
  geometry: {type: box, size: [0.025, 0.09, 0.025]}   # 생략하면 형상 없는 좌표계만 생김
  visual_xyz: [0, 0, 0]         # (선택) 형상을 파츠 좌표계 안에서 이동
  visual_rpy: [0, 0, 0]
  color: [0.1, 0.1, 0.1, 1.0]   # (선택)
  collision: true               # (선택) 충돌 형상 포함 여부, 기본 true
```
| geometry 종류 | 예 |
|---|---|
| 상자 | `{type: box, size: [x, y, z]}` |
| 원기둥 | `{type: cylinder, radius: r, length: l}` (중심 기준 → 바닥을 붙이려면 `visual_xyz: [0,0,l/2]`) |
| 구 | `{type: sphere, radius: r}` |
| CAD 메쉬 | `{type: mesh, filename: "package://ar4_orca_description/meshes/my_part.stl", scale: [0.001, 0.001, 0.001]}` (mm 단위 STL이면 0.001) |

### 3-2. 예시 A — 실제 어댑터 치수 반영
어댑터 두께가 12 mm, 지름이 80 mm라면 아래처럼 바꿉니다.
```yaml
parts:
  - name: hand_adapter
    parent: ee_link
    geometry: {type: cylinder, radius: 0.04, length: 0.012}
    visual_xyz: [0, 0, 0.006]
  - name: hand_adapter_top
    parent: hand_adapter
    xyz: [0, 0, 0.012]
```

### 3-3. 예시 B — 어댑터 CAD(STL) 사용
1. STL을 `ar4_orca_description/meshes/adapter.stl`에 넣습니다.
2. `CMakeLists.txt`의 `install(DIRECTORY urdf launch rviz config ...)`에 `meshes`를 추가하고, `colcon build`를 다시 실행합니다. 새 폴더라서 재빌드가 필요합니다.
3. yaml에 아래처럼 적습니다.
   ```yaml
   - name: hand_adapter
     parent: ee_link
     geometry: {type: mesh, filename: "package://ar4_orca_description/meshes/adapter.stl", scale: [0.001, 0.001, 0.001]}
   ```
   STL의 원점과 축이 플랜지 면에 맞게 설계돼 있어야 합니다. 안 맞으면 `visual_xyz`/`visual_rpy`로 보정합니다.

### 3-4. 예시 C — 손목 카메라 (yaml에 주석으로 들어 있음)
`mount.yaml` 아래쪽 `wrist_camera` 항목의 주석을 풀면 바로 확인할 수 있습니다. 카메라 드라이버를 붙일 때는 카메라 노드의 `frame_id`를 이 링크 이름으로 맞추면, 영상과 점군이 로봇 위 올바른 위치에 표시됩니다.

### 3-5. 손 장착 위치 바꾸기
- 손바닥 방향: `hand.rpy`의 세 번째 값. 예: `[1.5707963, 0, 1.5707963]` → 90° 회전
- 높이: `hand.xyz`의 z 값
- 어댑터 없이 플랜지에 바로: `hand.parent: ee_link` (parts 비워 두기 가능)

### 3-6. 파츠 추가 후 꼭 할 것
1. `check_model.py` → `[OK]` 확인
2. `view_ar4_orca.launch.py`로 눈으로 확인
3. (MoveIt 도입 후) 새 파츠와 인접 링크 사이의 충돌 비활성 설정을 SRDF에 추가

---

## 4. 파일 위치 요약
| 파일 | 역할 | 수정 빈도 |
|---|---|---|
| `ar4_orca_description/config/mount.yaml` | 파츠 목록 + 손 장착 위치 | **자주** (장착·파츠 변경 시) |
| `ar4_orca_description/urdf/ar4_orca.urdf.xacro` | 팔·파츠·손 조립 순서 | 거의 없음 |
| `ar4_orca_description/urdf/parts/fixed_parts.xacro` | yaml → 링크/조인트 변환기 | 없음 |
| `ar4_orca_description/scripts/check_model.py` | 구조 검사 도구 | 없음 |
| `orcahand_ros_description/urdf/*` | 손 모델 (생성기로 생성) | 직접 수정 금지 |
| `annin_ar4_description/*` | 팔 모델 (기존 저장소) | 수정 금지 |
