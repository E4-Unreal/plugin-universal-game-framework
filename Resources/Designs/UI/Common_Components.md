# Common Components

## 개요

- **대상 플러그인**: `UniversalGameFramework`
- **버전**: v0.1.0
- **작성일**: 2026-05-17
- **설명**: `Common_Style.md` 설정을 바탕으로 에디터에서 직접 위젯 블루프린트 에셋으로 구현할 재사용 가능 컴포넌트들의 에셋 정보와 상세 설정 사양을 정의합니다.

## 1. 배경

| 에셋 이름 | 분류 | 부모 클래스 | 기본 크기 | 배경 스타일 | 용도 |
| :--- | :--- | :--- | :--- | :--- | :--- |
| **FullscreenOverlay** | 풀스크린 오버레이 카드 | Common User Widget | `전체 화면` | Background | 메인 로비 배경 및 대형 캔버스 배경막 |
| **SidePanel** | 사이드 패널 카드 | Common User Widget | `350 x 세로 채우기` | Card | 화면 우측이나 좌측 고정형 상세 옵션 및 사이드 메뉴 배경막 |
| **PanelCard** | 정보 패널 카드 | Common User Widget | `600 x 450` | Card | 인게임 인벤토리 및 상세 설명판 배경막 |
| **DialogCard** | 기본 다이얼로그 카드 | Common User Widget | `400 x 250` | Card | 경고창 및 확인 요청 모달 배경막 |

## 2. 버튼

| 에셋 이름 | 분류 | 부모 클래스 | 기본 크기 | 버튼 스타일 | 용도 |
| :--- | :--- | :--- | :--- | :--- | :--- |
| **Primary** | 강조 버튼 | Common Button Base | `260 x 46` | Primary | 메인 화면의 시작, 확인, 진행 등 강조 액션 버튼 |
| **Secondary** | 기본 버튼 | Common Button Base | `260 x 46` | Secondary | 일반 설정, 메뉴 이동 등 표준 일반 동작 버튼 |
| **Confirm** | 확인 버튼 | Common Button Base | `110 x 34` | Secondary | 모달 팝업 및 대화 상자의 확인, 완료 결정 버튼 |
| **Cancel** | 취소 버튼 | Common Button Base | `110 x 34` | Outline | 모달 팝업 및 대화 상자의 취소, 복귀, 거절 버튼 |
| **Icon** | 아이콘 버튼 | Common Button Base | `40 x 40` | Outline | 상단 닫기 단추 혹은 유틸리티 툴팁 아이콘 전용 버튼 |
| **Tab** | 탭 버튼 | Common Button Base | `가변 x 46` | Secondary | 상단 네비게이션 메뉴 탭 전용 버튼 (선택 상태 지원) |
