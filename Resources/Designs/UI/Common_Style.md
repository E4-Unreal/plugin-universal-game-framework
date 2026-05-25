# UI 스타일 가이드

## 개요

- **대상 플러그인**: `UniversalGameFramework`
- **버전**: v0.1.0
- **작성일**: 2026-05-17
- **설명**: `Common UI` 플러그인을 사용하여 구현된 위젯에서 사용되는 경계, 텍스트, 버튼 스타일 등을 정의한 문서입니다.

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
| **`Secondary 900`** | `#0F172A` ![](https://placehold.co/12x12/0F172A/0F172A.png) | 메인 캔버스 배경 및 패널 팝업의 기본 기저색 |
| **`Secondary 950`** | `#050811` ![](https://placehold.co/12x12/050811/050811.png) | 가장 깊고 어두운 칠흑색 (음각 입력창 및 슬롯 배경) |

### 그레이 색상 (Gray Color)

| 색상 이름 | Hex 코드 | 주 역할 |
| :--- | :--- | :--- |
| **`White`** | `#FFFFFF` ![](https://placehold.co/12x12/FFFFFF/FFFFFF.png) | 가장 밝은 텍스트 및 액션 유도 라벨 |
| **`Gray 50`** | `#F9FAFB` ![](https://placehold.co/12x12/F9FAFB/F9FAFB.png) | 화면 타이틀 및 주요 헤더 텍스트 |
| **`Gray 100`** | `#F3F4F6` ![](https://placehold.co/12x12/F3F4F6/F3F4F6.png) | 매우 밝은 배경 오버레이 및 옅은 경계선 |
| **`Gray 200`** | `#E5E7EB` ![](https://placehold.co/12x12/E5E7EB/E5E7EB.png) | 일반 정보 텍스트, 보조 버튼 라벨 |
| **`Gray 300`** | `#D1D5DB` ![](https://placehold.co/12x12/D1D5DB/D1D5DB.png) | 비활성화된 텍스트, 옅은 아이콘 및 경계선 |
| **`Gray 400`** | `#9CA3AF` ![](https://placehold.co/12x12/9CA3AF/9CA3AF.png) | 외곽선 버튼 라벨, 보조 설명 텍스트 |
| **`Gray 500`** | `#6B7280` ![](https://placehold.co/12x12/6B7280/6B7280.png) | 중간 톤의 텍스트, 비활성화된 아이콘 |
| **`Gray 600`** | `#4B5563` ![](https://placehold.co/12x12/4B5563/4B5563.png) | 상세 주석 정보, 서브 외곽선 윤곽선 |
| **`Gray 700`** | `#374151` ![](https://placehold.co/12x12/374151/374151.png) | 어두운 요소 테두리, 카드 윤곽선 |
| **`Gray 800`** | `#1F2937` ![](https://placehold.co/12x12/1F2937/1F2937.png) | 어두운 모달 패널 배경, 2차 배경색 |
| **`Gray 900`** | `#111827` ![](https://placehold.co/12x12/111827/111827.png) | 어두운 테마 기본 배경색 |
| **`Gray 950`** | `#030712` ![](https://placehold.co/12x12/030712/030712.png) | 칠흑같이 어두운 입력창 기저 배경색 |
| **`Black`** | `#000000` ![](https://placehold.co/12x12/000000/000000.png) | 가장 어두운 화면 암전 오버레이 및 배경 마스크 색상 |

### 언리얼 엔진 에디터 컬러 테마

```ini
# [ProjectName]/Saved/Config/EditorPerProjectUserSettings.ini

[ColorThemes]
Theme0=UGF_Primary
Theme0Color0=(R=204.578535,G=0.128633,B=1.000000,A=1.000000)
Theme0Label0=Primary 50
Theme0Color1=(R=205.196549,G=0.247904,B=0.991102,A=1.000000)
Theme0Label1=Primary 100
Theme0Color2=(R=203.323420,G=0.500106,B=0.982251,A=1.000000)
Theme0Label2=Primary 200
Theme0Color3=(R=205.147345,G=0.789327,B=0.973445,A=1.000000)
Theme0Label3=Primary 300
Theme0Color4=(R=208.681050,G=0.957871,B=0.938686,A=1.000000)
Theme0Label4=Primary 400
Theme0Color5=(R=212.469493,G=0.994611,B=0.814847,A=1.000000)
Theme0Label5=Primary 500
Theme0Color6=(R=215.797459,G=0.998937,B=0.571125,A=1.000000)
Theme0Label6=Primary 600
Theme0Color7=(R=216.311083,G=0.997445,B=0.356400,A=1.000000)
Theme0Label7=Primary 700
Theme0Color8=(R=214.759945,G=0.990941,B=0.234551,A=1.000000)
Theme0Label8=Primary 800
Theme0Color9=(R=214.462392,G=0.976422,B=0.155926,A=1.000000)
Theme0Label9=Primary 900
Theme0Color10=(R=215.702107,G=0.963554,B=0.066626,A=1.000000)
Theme0Label10=Primary 950
Theme1=UGF_Secondary
Theme1Color0=(R=210.159075,G=0.035708,B=0.973445,A=1.000000)
Theme1Label0=Secondary 50
Theme1Color1=(R=210.324284,G=0.071449,B=0.947307,A=1.000000)
Theme1Label1=Secondary 100
Theme1Color2=(R=214.868283,G=0.127205,B=0.871367,A=1.000000)
Theme1Label2=Secondary 200
Theme1Color3=(R=213.731095,G=0.206842,B=0.752942,A=1.000000)
Theme1Label3=Secondary 300
Theme1Color4=(R=217.034526,G=0.382170,B=0.479320,A=1.000000)
Theme1Label4=Secondary 400
Theme1Color5=(R=218.335082,G=0.506405,B=0.258183,A=1.000000)
Theme1Label5=Secondary 500
Theme1Color6=(R=218.660297,G=0.553953,B=0.141263,A=1.000000)
Theme1Label6=Secondary 600
Theme1Color7=(R=219.469769,G=0.635577,B=0.090842,A=1.000000)
Theme1Label7=Secondary 700
Theme1Color8=(R=222.067794,G=0.703143,B=0.043735,A=1.000000)
Theme1Label8=Secondary 800
Theme1Color9=(R=227.621614,G=0.793682,B=0.023153,A=1.000000)
Theme1Label9=Secondary 900
Theme1Color10=(R=226.634514,G=0.729254,B=0.005605,A=1.000000)
Theme1Label10=Secondary 950
Theme2=UGF_Gray
Theme2Color0=(R=0.000000,G=0.000000,B=1.000000,A=1.000000)
Theme2Label0=White
Theme2Color1=(R=210.079538,G=0.018016,B=0.964686,A=1.000000)
Theme2Label1=Gray 50
Theme2Color2=(R=220.108278,G=0.027466,B=0.921582,A=1.000000)
Theme2Label2=Gray 100
Theme2Color3=(R=220.227492,G=0.056853,B=0.830770,A=1.000000)
Theme2Label3=Gray 200
Theme2Color4=(R=216.441774,G=0.099917,B=0.708376,A=1.000000)
Theme2Label4=Gray 300
Theme2Color5=(R=218.926793,G=0.224495,B=0.428690,A=1.000000)
Theme2Label5=Gray 400
Theme2Color6=(R=221.483828,G=0.318878,B=0.215861,A=1.000000)
Theme2Label6=Gray 500
Theme2Color7=(R=217.414849,G=0.436090,B=0.124772,A=1.000000)
Theme2Label7=Gray 600
Theme2Color8=(R=220.049688,G=0.535694,B=0.082283,A=1.000000)
Theme2Label8=Gray 700
Theme2Color9=(R=219.254668,G=0.641348,B=0.038204,A=1.000000)
Theme2Label9=Gray 800
Theme2Color10=(R=225.580770,G=0.723717,B=0.020289,A=1.000000)
Theme2Label10=Gray 900
Theme2Color11=(R=225.822713,G=0.849462,B=0.006049,A=1.000000)
Theme2Label11=Gray 950
Theme2Color12=(R=0.000000,G=0.000000,B=0.000000,A=1.000000)
Theme2Label12=Black
```

## 2. 경계 스타일

| 경계 스타일 | 역할 | 적용 대상 | 이미지 | 배경 (색조) | 배경 (불투명도) | 배경 (16진 srgb) | 그리기 방식 | 코너 반경 | 윤곽선 (색조) | 윤곽선 (불투명도) | 윤곽선 (16진 srgb) |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| **Canvas** | 기본 배경 | 메인 캔버스, 전체 화면 배경 | None | `Secondary 900` | | `0F172AFF` | Rounded Box | 0.0 | | | |
| **Panel** | 패널 배경 | 팝업 창, 모달 패널, 다이얼로그 박스 내부 | None | `Secondary 800` | `0.95` | `1E293BF2` | Rounded Box | 6.0 | `Secondary 700` | `0.5` | `33415580` |
| **Floating** | 최상위 부유 | 툴팁, 컨텍스트 메뉴, 토스트 알림 등 최상위 임시 부유 패널 | None | `Secondary 700` | `0.90` | `334155E6` | Rounded Box | 4.0 | `Secondary 600` | `0.8` | `475569CC` |
| **Inset** | 음각 기저 배경 | 입력 필드, 아이템 슬롯 그리드, 스크롤 영역 등 안쪽 음각 영역 | None | `Secondary 950` | | `050811FF` | Rounded Box | 4.0 | `Secondary 700` | `0.8` | `334155CC` |
| **Overlay** | 배경 오버레이 | 모달 및 팝업창 뒤의 화면 암전 처리 및 클릭 차단 | None | Black | `0.30` | `0000004D` | Rounded Box | 0.0 | | | |

## 3. 텍스트 스타일

| 텍스트 스타일 | 역할 | 적용 대상 | 폰트 패밀리 | 타입페이스 | 크기 | 문자 간격 | 컬러 (색조) | 컬러 (불투명도) | 컬러 (16진 srgb) |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| **Game Title** | 게임 메인 타이틀 | 메인 메뉴 게임 제목 | Roboto | Bold | 64 | 1.0 | `Gray 50` | | `F9FAFBFF` |
| **Title** | 주요 타이틀 | 화면 타이틀, 모달 주요 제목 | Roboto | Bold | 32 | 1.0 | `Gray 50` | | `F9FAFBFF` |
| **Head** | 중간 타이틀 | 섹션 제목, 모달 서브 제목 | Roboto | Bold | 24 | 0.5 | `Gray 50` | | `F9FAFBFF` |
| **Body** | 기본 본문 | 일반 정보 텍스트, 설명 본문 | Roboto | Medium | 16 | 0.5 | `Gray 200` | | `E5E7EBFF` |
| **Caption** | 보조 본문 | 보조 설명 텍스트, 상세 주석 | Roboto | Medium | 13 | 0.5 | `Gray 400` | | `9CA3AFFF` |
| **Button** | 일반 버튼 본문 | 채우기 버튼 기본/눌림 라벨 | Roboto | Medium | 16 | 0.5 | `Gray 200` | | `E5E7EBFF` |
| **Button Hover** | 버튼 호버 상태 | 모든 버튼 호버 상태 라벨 | - | - | - | - | `White` | | `FFFFFFFF` |
| **Button Disabled** | 버튼 비활성화 | 일반 및 탭/텍스트 비활성화 라벨 | - | - | - | - | `White` | `0.3` | `FFFFFF4D` |
| **Button Primary** | 주조 외곽선 본문 | 주조 외곽선 버튼 기본 라벨 | - | - | - | - | `Primary 400` | | `38BDF8FF` |
| **Button Primary Disabled** | 주조 외곽선 비활성 | 주조 외곽선 버튼 비활성화 라벨 | - | - | - | - | `Primary 500` | `0.3` | `0EA5E94D` |
| **Button Secondary** | 보조 외곽선 본문 | 보조 외곽선 버튼 기본 라벨 | - | - | - | - | `Secondary 400` | | `94A3B8FF` |
| **Button Secondary Disabled**| 보조 외곽선 비활성 | 보조 외곽선 버튼 비활성화 라벨 | - | - | - | - | `Secondary 500` | `0.3` | `64748B4D` |

## 4. 버튼 스타일

| 버튼 종류 | 세부 설정 항목 | 배경색 (색조) | 배경색 (불투명도) | 배경색 (16진 srgb) | 윤곽선 (색조) | 윤곽선 (불투명도) | 윤곽선 (16진 srgb) | 연결할 텍스트 스타일 |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| **Primary Solid** | 노멀 베이스 | `Primary 600` | | `0284C7FF` | | | | `Button` |
| | 노멀 호버됨 | `Primary 500` | | `0EA5E9FF` | | | | `Button Hover` |
| | 노멀 눌림 | `Primary 700` | | `0369A1FF` | | | | |
| | 비활성화됨 | `Primary 600` | `0.3` | `0284C74D` | | | | `Button Disabled` |
| **Primary Outline** | 노멀 베이스 | 투명 | | | `Primary 500` | | `0EA5E9FF` | `Button Primary` |
| | 노멀 호버됨 | `Primary 500` | | `0EA5E9FF` | `Primary 400` | | `38BDF8FF` | `Button Hover` |
| | 노멀 눌림 | `Primary 700` | | `0369A1FF` | `Primary 600` | | `0284C7FF` | |
| | 비활성화됨 | 투명 | | | `Primary 500` | `0.3` | `0EA5E94D` | `Button Primary Disabled` |
| **Secondary Solid**| 노멀 베이스 | `Secondary 600` | | `475569FF` | | | | `Button` |
| | 노멀 호버됨 | `Secondary 500` | | `64748BFF` | | | | `Button Hover` |
| | 노멀 눌림 | `Secondary 700` | | `334155FF` | | | | |
| | 비활성화됨 | `Secondary 600` | `0.3` | `4755694D` | | | | `Button Disabled` |
| **Secondary Outline** | 노멀 베이스 | 투명 | | | `Secondary 500` | | `64748BFF` | `Button Secondary` |
| | 노멀 호버됨 | `Secondary 500` | | `64748BFF` | `Secondary 400` | | `94A3B8FF` | `Button Hover` |
| | 노멀 눌림 | `Secondary 700` | | `334155FF` | `Secondary 600` | | `475569FF` | |
| | 비활성화됨 | 투명 | | | `Secondary 500` | `0.3` | `64748B4D` | `Button Secondary Disabled` |
| **Tab** | 노멀 베이스 | 투명 | | | | | | `Button` |
| | 노멀 호버됨 | 투명 | | | | | | `Button Hover` |
| | 노멀 눌림 | 투명 | | | | | | |
| | 선택된 베이스 | `Primary 500` | | `0EA5E9FF` | | | | `Button Hover` |
| | 선택된 호버됨 | `Primary 500` | | `0EA5E9FF` | | | | `Button Hover` |
| | 선택된 눌림 | `Primary 700` | | `0369A1FF` | | | | |
| | 비활성화됨 | 투명 | | | | | | `Button Disabled` |
| **Text / Icon** | 노멀 베이스 | 투명 | | | | | | `Button` |
| | 노멀 호버됨 | `Secondary 700` | `0.3` | `33415540` | | | | `Button Hover` |
| | 노멀 눌림 | 투명 | | | | | | |
| | 비활성화됨 | 투명 | | | | | | `Button Disabled` |
