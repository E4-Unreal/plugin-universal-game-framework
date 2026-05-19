# UI 스타일 가이드

## 개요

- **대상 플러그인**: `UniversalGameFramework`
- **버전**: v0.1.0
- **작성일**: 2026-05-17
- **설명**: `Common UI` 플러그인을 사용하여 구현된 위젯에서 사용되는 배경, 텍스트, 버튼 스타일 등을 정의한 문서입니다.

## 1. 색상 팔레트

### 주조 색상 (Primary Color)

| 색상 이름 | Hex 코드 | 주 역할 |
| :--- | :--- | :--- |
| **`Primary 50`** | `#F0F9FF` ![](https://placehold.co/12x12/F0F9FF/F0F9FF.png) | 최상위 밝은 강조 배경, 라이트 테마 하이라이트 |
| **`Primary 100`** | `#E0F2FE` ![](https://placehold.co/12x12/E0F2FE/E0F2FE.png) | 주조 색조 계열의 옅은 칩/뱃지 배경 |
| **`Primary 200`** | `#BAE6FD` ![](https://placehold.co/12x12/BAE6FD/BAE6FD.png) | 주조 색조 계열의 연한 윤곽선 및 강조 요소 |
| **`Primary 300`** | `#7DD3FC` ![](https://placehold.co/12x12/7DD3FC/7DD3FC.png) | 서브 브랜딩 요소, 연한 파란색 강조 텍스트 |
| **`Primary 400`** | `#38BDF8` ![](https://placehold.co/12x12/38BDF8/38BDF8.png) | 밝은 블루 악센트 포인트 및 그라데이션 시작색 |
| **`Primary 500`** | `#0EA5E9` ![](https://placehold.co/12x12/0EA5E9/0EA5E9.png) | 주 버튼(Primary)의 호버 상태 배경/윤곽선 |
| **`Primary 600`** | `#0284C7` ![](https://placehold.co/12x12/0284C7/0284C7.png) | 주 버튼(Primary)의 기본 활성 상태 배경/윤곽선 |
| **`Primary 700`** | `#0369A1` ![](https://placehold.co/12x12/0369A1/0369A1.png) | 주 버튼(Primary)의 클릭(Pressed) 상태 배경/윤곽선 |
| **`Primary 800`** | `#075985` ![](https://placehold.co/12x12/075985/075985.png) | 주 버튼(Primary)의 깊은 클릭 상태 배경/윤곽선 |
| **`Primary 900`** | `#0C4A6E` ![](https://placehold.co/12x12/0C4A6E/0C4A6E.png) | 주 버튼(Primary)의 비활성화 상태 배경 |
| **`Primary 950`** | `#082F49` ![](https://placehold.co/12x12/082F49/082F49.png) | 주조 색조 계열의 가장 어두운 칠흑색 기저 배경 |

### 보조 색상 (Secondary Color)

| 색상 이름 | Hex 코드 | 주 역할 |
| :--- | :--- | :--- |
| **`Secondary 50`** | `#F8FAFC` ![](https://placehold.co/12x12/F8FAFC/F8FAFC.png) | 보조 계열의 매우 연한 오버레이 배경 |
| **`Secondary 100`** | `#F1F5F9` ![](https://placehold.co/12x12/F1F5F9/F1F5F9.png) | 보조 계열의 옅은 가이드/테두리 라인 |
| **`Secondary 200`** | `#E2E8F0` ![](https://placehold.co/12x12/E2E8F0/E2E8F0.png) | 비활성화 상태의 기본 탭/헤더 윤곽선 |
| **`Secondary 300`** | `#CBD5E1` ![](https://placehold.co/12x12/CBD5E1/CBD5E1.png) | 보조 계열의 옅은 텍스트 및 그리드 라인 |
| **`Secondary 400`** | `#94A3B8` ![](https://placehold.co/12x12/94A3B8/94A3B8.png) | 차분한 정보 알림 뱃지 및 설명 정보 |
| **`Secondary 500`** | `#64748B` ![](https://placehold.co/12x12/64748B/64748B.png) | 보조 버튼(Secondary)의 호버 상태 윤곽선 |
| **`Secondary 600`** | `#475569` ![](https://placehold.co/12x12/475569/475569.png) | 보조 버튼 기본 상태 윤곽선 등 미세 강조 |
| **`Secondary 700`** | `#334155` ![](https://placehold.co/12x12/334155/334155.png) | 보조 버튼 기본 상태 배경, 팝업창 외곽선 |
| **`Secondary 800`** | `#1E293B` ![](https://placehold.co/12x12/1E293B/1E293B.png) | 보조 버튼 눌림 상태 배경, 비활성화 상태 배경 |
| **`Secondary 900`** | `#0F172A` ![](https://placehold.co/12x12/0F172A/0F172A.png) | 메인 캔버스 배경 및 카드 팝업의 기본 기저색 |
| **`Secondary 950`** | `#050811` ![](https://placehold.co/12x12/050811/050811.png) | 가장 깊고 어두운 칠흑색 (음각 입력창 및 슬롯 배경) |

### 그레이 색상 (Gray Color)

| 색상 이름 | Hex 코드 | 주 역할 |
| :--- | :--- | :--- |
| **`White`** | `#FFFFFF` ![](https://placehold.co/12x12/FFFFFF/FFFFFF.png) | 가장 밝은 텍스트 및 액션 유도 라벨 |
| **`Gray 50`** | `#F9FAFB` ![](https://placehold.co/12x12/F9FAFB/F9FAFB.png) | 화면 타이틀 및 주요 헤더 텍스트 |
| **`Gray 200`** | `#E5E7EB` ![](https://placehold.co/12x12/E5E7EB/E5E7EB.png) | 일반 정보 텍스트, 보조 버튼 라벨 |
| **`Gray 400`** | `#9CA3AF` ![](https://placehold.co/12x12/9CA3AF/9CA3AF.png) | 외곽선 버튼 라벨, 보조 설명 텍스트 |
| **`Gray 600`** | `#4B5563` ![](https://placehold.co/12x12/4B5563/4B5563.png) | 상세 주석 정보, 서브 외곽선 윤곽선 |

## 2. 배경 스타일

| 배경 스타일 | 역할 | 적용 대상 | 이미지 | 배경 (색조) | 배경 (불투명도) | 배경 (16진 선형) | 그리기 방식 | 코너 반경 | 윤곽선 (색조) | 윤곽선 (불투명도) | 윤곽선 (16진 선형) |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| **Canvas** | 기본 배경 | 메인 캔버스, 전체 화면 배경 | None | `Secondary 900` | | `0F172AFF` | Rounded Box | 0.0 | | | |
| **Card** | 카드 배경 | 팝업 창, 모달 카드, 다이얼로그 박스 내부 | None | `Secondary 800` | `0.95` | `1E293BF2` | Rounded Box | 6.0 | `Secondary 700` | `0.5` | `33415580` |
| **Overlay** | 최상위 오버레이 | 툴팁, 컨텍스트 메뉴, 토스트 알림 등 최상위 임시 부유 패널 | None | `Secondary 700` | `0.90` | `334155E6` | Rounded Box | 4.0 | `Secondary 600` | `0.8` | `475569CC` |
| **Inset** | 음각 기저 배경 | 입력 필드, 아이템 슬롯 그리드, 스크롤 영역 등 안쪽 음각 영역 | None | `Secondary 950` | | `050811FF` | Rounded Box | 4.0 | `Secondary 700` | `0.8` | `334155CC` |

## 3. 텍스트 스타일

| 텍스트 스타일 | 역할 | 적용 대상 | 폰트 패밀리 | 타입페이스 | 크기 | 문자 간격 | 컬러 (색조) | 컬러 (불투명도) | 컬러 (16진 선형) |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| **Title** | 주요 타이틀 기본 | 화면 타이틀, 모달 주요 제목 | Roboto | Bold | 42 | 1.0 | `Gray 50` | | `F9FAFBFF` |
| **Title Highlight** | 주요 타이틀 강조 | 타이틀 호버/활성 상태 | - | - | - | - | `White` | | `FFFFFFFF` |
| **Title Primary** | 주요 타이틀 주조 | 주조 테마 타이틀 | - | - | - | - | `Primary 400` | | `38BDF8FF` |
| **Title Secondary** | 주요 타이틀 보조 | 보조 테마 타이틀 | - | - | - | - | `Secondary 400` | | `94A3B8FF` |
| **Head** | 중간 타이틀 기본 | 섹션 제목, 모달 서브 제목 | Roboto | Bold | 24 | 0.5 | `Gray 50` | | `F9FAFBFF` |
| **Head Highlight** | 중간 타이틀 강조 | 중간 타이틀 호버/활성 상태 | - | - | - | - | `White` | | `FFFFFFFF` |
| **Head Primary** | 중간 타이틀 주조 | 주조 테마 중간 타이틀 | - | - | - | - | `Primary 400` | | `38BDF8FF` |
| **Head Secondary** | 중간 타이틀 보조 | 보조 테마 중간 타이틀 | - | - | - | - | `Secondary 400` | | `94A3B8FF` |
| **Body**| 기본 본문 기본 | 일반 정보 텍스트, 보조 버튼 라벨 | Roboto | Medium | 16 | 0.5 | `Gray 200` | | `E5E7EBFF` |
| **Body Highlight** | 기본 본문 강조 | 기본 버튼 라벨, 강조 본문 | - | - | - | - | `White` | | `FFFFFFFF` |
| **Body Primary** | 기본 본문 주조 | 주조 테마 강조 텍스트 | - | - | - | - | `Primary 400` | | `38BDF8FF` |
| **Body Secondary** | 기본 본문 보조 | 보조 테마 강조 텍스트 | - | - | - | - | `Secondary 400` | | `94A3B8FF` |
| **Caption** | 보조 본문 기본 | 외곽선 버튼 라벨, 보조 설명 텍스트 | Roboto | Medium | 13 | 0.5 | `Gray 400` | | `9CA3AFFF` |
| **Caption Highlight** | 보조 본문 강조 | 외곽선 버튼 호버/활성 라벨 | - | - | - | - | `White` | | `FFFFFFFF` |
| **Caption Primary** | 보조 본문 주조 | 주조 외곽선 버튼 기본 라벨 | - | - | - | - | `Primary 400` | | `38BDF8FF` |
| **Caption Secondary** | 보조 본문 보조 | 보조 외곽선 버튼 기본 라벨 | - | - | - | - | `Secondary 400` | | `94A3B8FF` |
| **Muted** | 비활성화 기본 | 비활성화 버튼 라벨, 비활성화 안내 | Roboto | Regular | 13 | 0.0 | `White` | `0.3` | `FFFFFF4D` |
| **Muted Highlight** | 비활성화 강조 | 비활성화 강조 라벨 | - | - | - | - | `White` | `0.5` | `FFFFFF80` |
| **Muted Primary** | 비활성화 주조 | 주조 외곽선 버튼 비활성화 라벨 | - | - | - | - | `Primary 500` | `0.3` | `0EA5E94D` |
| **Muted Secondary** | 비활성화 보조 | 보조 외곽선 버튼 비활성화 라벨 | - | - | - | - | `Secondary 500` | `0.3` | `64748B4D` |

## 4. 버튼 스타일

| 버튼 종류 | 세부 설정 항목 | 배경색 (색조) | 배경색 (불투명도) | 배경색 (16진 선형) | 윤곽선 (색조) | 윤곽선 (불투명도) | 윤곽선 (16진 선형) | 연결할 텍스트 스타일 |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| **Primary Solid** | 노멀 베이스 | `Primary 600` | | `0284C7FF` | | | | `Body` |
| | 노멀 호버됨 | `Primary 500` | | `0EA5E9FF` | | | | `Body Highlight` |
| | 노멀 눌림 | `Primary 700` | | `0369A1FF` | | | | - |
| | 선택된 베이스 | `Primary 500` | | `0EA5E9FF` | | | | `Body Highlight` |
| | 선택된 호버됨 | `Primary 500` | | `0EA5E9FF` | | | | `Body Highlight` |
| | 선택된 눌림 | `Primary 700` | | `0369A1FF` | | | | - |
| | 비활성화됨 | `Primary 600` | `0.3` | `0284C74D` | | | | `Muted` |
| **Primary Outline** | 노멀 베이스 | 투명 | | | `Primary 500` | | `0EA5E9FF` | `Caption Primary` |
| | 노멀 호버됨 | `Primary 500` | | `0EA5E9FF` | `Primary 400` | | `38BDF8FF` | `Caption Highlight` |
| | 노멀 눌림 | `Primary 700` | | `0369A1FF` | `Primary 600` | | `0284C7FF` | - |
| | 선택된 베이스 | `Primary 500` | | `0EA5E9FF` | `Primary 400` | | `38BDF8FF` | `Caption Highlight` |
| | 선택된 호버됨 | `Primary 500` | | `0EA5E9FF` | `Primary 400` | | `38BDF8FF` | `Caption Highlight` |
| | 선택된 눌림 | `Primary 700` | | `0369A1FF` | `Primary 600` | | `0284C7FF` | - |
| | 비활성화됨 | 투명 | | | `Primary 500` | `0.3` | `0EA5E94D` | `Muted Primary` |
| **Secondary Solid**| 노멀 베이스 | `Secondary 600` | | `475569FF` | | | | `Body` |
| | 노멀 호버됨 | `Secondary 500` | | `64748BFF` | | | | `Body Highlight` |
| | 노멀 눌림 | `Secondary 700` | | `334155FF` | | | | - |
| | 선택된 베이스 | `Secondary 500` | | `64748BFF` | | | | `Body Highlight` |
| | 선택된 호버됨 | `Secondary 500` | | `64748BFF` | | | | `Body Highlight` |
| | 선택된 눌림 | `Secondary 700` | | `334155FF` | | | | - |
| | 비활성화됨 | `Secondary 600` | `0.3` | `4755694D` | | | | `Muted` |
| **Secondary Outline** | 노멀 베이스 | 투명 | | | `Secondary 500` | | `64748BFF` | `Caption Secondary` |
| | 노멀 호버됨 | `Secondary 500` | | `64748BFF` | `Secondary 400` | | `94A3B8FF` | `Caption Highlight` |
| | 노멀 눌림 | `Secondary 700` | | `334155FF` | `Secondary 600` | | `475569FF` | - |
| | 선택된 베이스 | `Secondary 500` | | `64748BFF` | `Secondary 400` | | `94A3B8FF` | `Caption Highlight` |
| | 선택된 호버됨 | `Secondary 500` | | `64748BFF` | `Secondary 400` | | `94A3B8FF` | `Caption Highlight` |
| | 선택된 눌림 | `Secondary 700` | | `334155FF` | `Secondary 600` | | `475569FF` | - |
| | 비활성화됨 | 투명 | | | `Secondary 500` | `0.3` | `64748B4D` | `Muted Secondary` |

