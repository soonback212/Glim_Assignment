#include "pch.h"
#include "framework.h"
#include "MFC_GLIM.h"
#include "MFC_GLIMDlg.h"
#include "afxdialogex.h"
#include <cmath>
#include <cstdlib>
#include <ctime>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CMFCGLIMDlg::CMFCGLIMDlg(CWnd* pParent)
    : CDialogEx(IDD_MFC_GLIM_DIALOG, pParent)
{
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCGLIMDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDIT1, m_radiusInput);
    DDX_Control(pDX, IDC_EDIT2, m_thicknessInput);
    // Static 텍스트는 멤버 바인딩 없이 SetDlgItemText로 처리
}

BEGIN_MESSAGE_MAP(CMFCGLIMDlg, CDialogEx)
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
    ON_BN_CLICKED(IDC_BUTTON1, &CMFCGLIMDlg::OnBnClickedButton1)
    ON_BN_CLICKED(IDC_BUTTON2, &CMFCGLIMDlg::OnBnClickedButton2)
    ON_WM_LBUTTONDOWN()
    ON_WM_MOUSEMOVE()
    ON_WM_LBUTTONUP()
END_MESSAGE_MAP()

BOOL CMFCGLIMDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();
    SetIcon(m_hIcon, TRUE);
    SetIcon(m_hIcon, FALSE);
    srand((unsigned)time(NULL));
    return TRUE;
}

void CMFCGLIMDlg::OnPaint()
{
    CPaintDC dc(this);

    for (const auto& pt : clickedPoints)
    {
        dc.Ellipse(pt.x - pointRadius, pt.y - pointRadius, pt.x + pointRadius, pt.y + pointRadius);
    }

    if (clickedPoints.size() == 3)
    {
        DrawCircleFromPoints(&dc);
    }
}

HCURSOR CMFCGLIMDlg::OnQueryDragIcon()
{
    return static_cast<HCURSOR>(m_hIcon);
}

void CMFCGLIMDlg::OnBnClickedButton1()
{
    clickedPoints.clear();
    draggingPointIndex = -1;
    radius = 0;
    UpdateCenterLabel();
    Invalidate();
}

void CMFCGLIMDlg::OnBnClickedButton2()
{
    CRect rect;
    GetClientRect(&rect);
    for (auto& pt : clickedPoints)
    {
        pt.x = rand() % rect.Width();
        pt.y = rand() % rect.Height();
    }
    Invalidate();
}

void CMFCGLIMDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
    if (clickedPoints.size() < 3)
    {
        clickedPoints.push_back(point);
        Invalidate();
    }
    else
    {
        for (int i = 0; i < 3; ++i)
        {
            if (abs(clickedPoints[i].x - point.x) < 10 && abs(clickedPoints[i].y - point.y) < 10)
            {
                draggingPointIndex = i;
                break;
            }
        }
    }

    CDialogEx::OnLButtonDown(nFlags, point);
}

void CMFCGLIMDlg::OnMouseMove(UINT nFlags, CPoint point)
{
    if (draggingPointIndex != -1 && (nFlags & MK_LBUTTON))
    {
        clickedPoints[draggingPointIndex] = point;
        Invalidate();
    }

    CDialogEx::OnMouseMove(nFlags, point);
}

void CMFCGLIMDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
    draggingPointIndex = -1;
    CDialogEx::OnLButtonUp(nFlags, point);
}

void CMFCGLIMDlg::DrawCircleFromPoints(CDC* pDC)
{
    CPoint A = clickedPoints[0];
    CPoint B = clickedPoints[1];
    CPoint C = clickedPoints[2];

    double a = A.x * (B.y - C.y) - A.y * (B.x - C.x) + B.x * C.y - C.x * B.y;
    if (fabs(a) < 1e-6) return;  // 세 점이 일직선

    double bx = ((A.x * A.x + A.y * A.y) * (B.y - C.y)
        + (B.x * B.x + B.y * B.y) * (C.y - A.y)
        + (C.x * C.x + C.y * C.y) * (A.y - B.y)) / (2 * a);

    double by = ((A.x * A.x + A.y * A.y) * (C.x - B.x)
        + (B.x * B.x + B.y * B.y) * (A.x - C.x)
        + (C.x * C.x + C.y * C.y) * (B.x - A.x)) / (2 * a);

    center = CPoint((int)bx, (int)by);

    // 반지름 기본값 계산
    int calcRadius = (int)sqrt((center.x - A.x) * (center.x - A.x) + (center.y - A.y) * (center.y - A.y));

    // 🔹 입력값 반영
    CString rStr, tStr;
    m_radiusInput.GetWindowTextW(rStr);
    m_thicknessInput.GetWindowTextW(tStr);

    int inputRadius = _ttoi(rStr);
    int thickness = _ttoi(tStr);

    if (inputRadius > 0) calcRadius = inputRadius;
    if (thickness <= 0) thickness = 1;  // 최소 두께 보장

    radius = calcRadius;
    UpdateCenterLabel();

    // 🔹 두께 적용하여 원 테두리 그리기
    for (double angle = 0; angle <= 360.0; angle += 0.5)
    {
        for (int t = 0; t < thickness; ++t)
        {
            int r = radius - thickness / 2 + t;
            int x = center.x + (int)(r * cos(angle * 3.141592 / 180.0));
            int y = center.y + (int)(r * sin(angle * 3.141592 / 180.0));
            pDC->SetPixel(x, y, RGB(0, 0, 255));
        }
    }
}

void CMFCGLIMDlg::UpdateCenterLabel()
{
    CString str;
    if (clickedPoints.size() == 3)
        str.Format(_T("중심: (%d, %d)"), center.x, center.y);
    else
        str = _T("중심: (미정)");

    SetDlgItemText(IDC_STATIC, str);
}
