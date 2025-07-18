# MFC_GLIM Assignment 1

## 📌 프로젝트 개요

본 프로젝트는 MFC (Microsoft Foundation Class)를 기반으로 구현된 Windows 데스크탑 애플리케이션으로,  
사용자가 클릭한 **3개의 점을 기준으로 외접원을 계산 및 그리기**합니다.  
외접원의 **반지름과 테두리 두께**는 사용자가 직접 입력할 수 있으며,  
드래그를 통해 점의 위치를 실시간으로 변경할 수 있습니다.

---

## 🛠 사용 기술

| 항목 | 설명 |
|------|------|
| 언어 | C++ |
| 프레임워크 | MFC (Microsoft Foundation Class) |
| UI 구성 | Dialog 기반 (Edit, Static, Button) |
| 렌더링 방식 | GDI 함수 `SetPixel()` 직접 사용 |
| 입력 이벤트 처리 | `OnLButtonDown`, `OnMouseMove`, `OnLButtonUp` |

---

## 💡 기능 요약

- 세 점 클릭 → 외접원 자동 계산 및 시각화
- 중심 좌표 실시간 출력
- 반지름, 테두리 두께 수치 입력 가능
- 점 드래그 → 원 실시간 재계산
- 초기화 및 랜덤 이동 버튼 제공

---

## 🧩 UI 구성 및 입력 방식

| 구성 요소 | 기능 | 예시 입력 | 단위 기준 |
|-----------|------|-----------|------------|
| **Edit 1** | 원의 테두리 두께 입력 | `10` | 10 픽셀 |
| **Edit 2** | 원의 반지름 직접 설정 | `100` | 100 픽셀 ≒ 100mm *(해상도 기준)* |
| **Static Text** | 원의 중심 좌표 출력 | 중심: (300, 250) | 픽셀 |
| **[초기화] 버튼** | 점 목록 초기화 및 화면 갱신 | - | - |
| **[랜덤 이동] 버튼** | 클릭된 점을 랜덤 위치로 재배치 | - | - |

> 📎 참고: 화면상의 픽셀 값은 사용 중인 모니터의 DPI 설정에 따라 실제 mm 단위와 다를 수 있습니다.

---

## 🧮 외접원 계산 방식

1. 세 점 A, B, C의 좌표를 기반으로 외접원의 중심 (cx, cy)을 계산  
2. `radius = sqrt((cx - Ax)^2 + (cy - Ay)^2)`  
3. 사용자가 입력한 반지름 값이 존재하면 이를 반영해 덮어씀  
4. `SetPixel()` 반복 호출로 외접원 테두리 픽셀 직접 출력  
   (두께도 입력값 기준 반복 적용)


