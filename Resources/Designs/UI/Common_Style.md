# Common Style

## 개요

- **대상 플러그인**: `UniversalGameFramework`
- **버전**: v0.1.0
- **작성일**: 2026-05-17
- **설명**: `Common UI` 플러그인을 사용하여 구현된 위젯에서 사용되는 배경, 텍스트, 버튼 스타일 등을 정의한 문서입니다.

## 1. 색상 팔레트

### 주조 색상 (Primary Color)

| 색상 이름 | Hex 코드 | 주 역할 |
| :--- | :--- | :--- |
| **`Primary 500`** | `#0EA5E9` ![](https://placehold.co/12x12/0EA5E9/0EA5E9.png) | 주 버튼(Primary)의 호버 상태 배경/테두리 |
| **`Primary 600`** | `#0284C7` ![](https://placehold.co/12x12/0284C7/0284C7.png) | 주 버튼(Primary)의 기본 활성 상태 배경/테두리 |
| **`Primary 700`** | `#0369A1` ![](https://placehold.co/12x12/0369A1/0369A1.png) | 주 버튼(Primary)의 클릭(Pressed) 상태 배경/테두리 |
| **`Primary 800`** | `#075985` ![](https://placehold.co/12x12/075985/075985.png) | 주 버튼(Primary)의 깊은 클릭 상태 배경/테두리 |

### 보조 색상 (Secondary Color)

| 색상 이름 | Hex 코드 | 주 역할 |
| :--- | :--- | :--- |
| **`Secondary 600`** | `#475569` ![](https://placehold.co/12x12/475569/475569.png) | 보조 버튼 호버 상태 테두리 등 미세 강조 |
| **`Secondary 700`** | `#334155` ![](https://placehold.co/12x12/334155/334155.png) | 팝업창 외곽선, 보조 버튼 호버 테두리 |
| **`Secondary 800`** | `#1E293B` ![](https://placehold.co/12x12/1E293B/1E293B.png) | 비활성화 상태 배경, 버튼 호버/선택 상태 보조색 |
| **`Secondary 900`** | `#0F172A` ![](https://placehold.co/12x12/0F172A/0F172A.png) | 메인 캔버스 배경 및 카드 팝업의 기본 기저색 |
| **`Secondary 950`** | `#050811` ![](https://placehold.co/12x12/050811/050811.png) | 가장 깊고 어두운 칠흑색 (음각 입력창 및 슬롯 배경) |

### 그레이 색상 (Gray Color)

| 색상 이름 | Hex 코드 | 주 역할 |
| :--- | :--- | :--- |
| **`White`** | `#FFFFFF` ![](https://placehold.co/12x12/FFFFFF/FFFFFF.png) | 가장 밝은 텍스트 및 액션 유도 라벨 |
| **`Gray 50`** | `#F9FAFB` ![](https://placehold.co/12x12/F9FAFB/F9FAFB.png) | 화면 타이틀 및 주요 헤더 텍스트 |
| **`Gray 200`** | `#E5E7EB` ![](https://placehold.co/12x12/E5E7EB/E5E7EB.png) | 일반 정보 텍스트, 보조 버튼 라벨 |
| **`Gray 400`** | `#9CA3AF` ![](https://placehold.co/12x12/9CA3AF/9CA3AF.png) | 외곽선 버튼 라벨, 보조 설명 텍스트 |
| **`Gray 600`** | `#4B5563` ![](https://placehold.co/12x12/4B5563/4B5563.png) | 상세 주석 정보, 서브 외곽선 테두리 |

## 2. 배경 스타일

| 배경 스타일 | 역할 | 적용 대상 | 이미지 | 배경 (색조) | 배경 (불투명도) | 배경 (16진 선형) | 그리기 방식 | 코너 반경 | 윤곽선 (색조) | 윤곽선 (불투명도) | 윤곽선 (16진 선형) |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| **Background** | 기본 배경 | 메인 캔버스, 전체 화면 배경 | None | `Secondary 900` | `1.0` | `0F172AFF` | Rounded Box | 0.0 | 투명 | `0.0` | `00000000` |
| **Card** | 카드 배경 | 팝업 창, 모달 카드, 다이얼로그 박스 내부 | None | `Secondary 800` | `0.95` | `1E293BF2` | Rounded Box | 6.0 | `Secondary 700` | `0.5` | `33415580` |
| **Overlay** | 최상위 오버레이 | 툴팁, 컨텍스트 메뉴, 토스트 알림 등 최상위 임시 부유 패널 | None | `Secondary 700` | `0.90` | `334155E6` | Rounded Box | 4.0 | `Secondary 600` | `0.8` | `475569CC` |
| **Inset** | 음각 기저 배경 | 입력 필드, 아이템 슬롯 그리드, 스크롤 영역 등 안쪽 음각 영역 | None | `Secondary 950` | `1.0` | `050811FF` | Rounded Box | 4.0 | `Secondary 700` | `0.8` | `334155CC` |

## 3. 텍스트 스타일

| 텍스트 스타일 | 역할 | 적용 대상 | 폰트 패밀리 | 타입페이스 | 크기 | 문자 간격 | 컬러 |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| **Title** | 주요 타이틀 | 화면 타이틀, 모달 주요 제목 | Roboto | Bold | 42 | 1.0 | `Gray 50` |
| **Primary** | 강조 텍스트 | 기본 버튼 라벨, 강조 본문 | Roboto | Medium | 14 | 0.5 | `White` |
| **Secondary**| 기본 본문 | 일반 정보 텍스트, 보조 버튼 라벨 | Roboto | Medium | 14 | 0.5 | `Gray 200` |
| **Outline** | 보조 본문 | 외곽선 버튼 라벨, 보조 설명 텍스트 | Roboto | Medium | 13 | 0.5 | `Gray 400` |
| **Detail** | SYSTEM 상세 | 빌드 버전, 주석 메타 정보 | Roboto | Regular | 13 | 0.0 | `Gray 600` |

## 4. 버튼 스타일

| 버튼 종류 | 세부 설정 항목 | 배경색 | 테두리색 | 연결할 텍스트 스타일 |
| :--- | :--- | :--- | :--- | :--- |
| **Primary** | 노멀 베이스 | `Primary 600` | | Primary |
| | 노멀 호버됨 | `Primary 500` | | Primary |
| | 노멀 눌림 | `Primary 800` | | - |
| | 선택된 베이스 | `Primary 600` | | Primary |
| | 선택된 호버됨 | `Primary 500` | | Primary |
| | 선택된 눌림 | `Primary 800` | | - |
| | 비활성화됨 | `Secondary 800` | | Detail |
| **Secondary**| 노멀 베이스 | `Secondary 800` | `Secondary 700` | Secondary |
| | 노멀 호버됨 | `Secondary 700` | `Secondary 600` | Primary |
| | 노멀 눌림 | `Secondary 900` | `Secondary 700` | - |
| | 선택된 베이스 | `Primary 600` | | Primary |
| | 선택된 호버됨 | `Primary 500` | | Primary |
| | 선택된 눌림 | `Primary 800` | | - |
| | 비활성화됨 | `Secondary 900` | `Secondary 800` | Detail |
| **Outline** | 노멀 베이스 | 투명 | `Secondary 700` | Outline |
| | 노멀 호버됨 | `Secondary 800` | `Secondary 600` | Secondary |
| | 노멀 눌림 | `Secondary 900` | `Secondary 700` | - |
| | 선택된 베이스 | `Secondary 900` | `Secondary 700` | Secondary |
| | 선택된 호버됨 | `Secondary 800` | `Secondary 600` | Secondary |
| | 선택된 눌림 | `Secondary 900` | `Secondary 700` | - |
| | 비활성화됨 | 투명 | `Secondary 800` | Detail |
