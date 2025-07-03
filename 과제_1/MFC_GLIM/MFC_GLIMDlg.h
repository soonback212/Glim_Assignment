#pragma once
#include "pch.h"
#include "framework.h"  
#include "resource.h"
#include <vector>
#include <afxwin.h>
#include <afxext.h>
#include <afxcmn.h>
#include <afxdlgs.h>
#include <cmath>
#include <ctime>
#include <cstdlib>

class CMFCGLIMDlg : public CDialogEx
{
public:
    CMFCGLIMDlg(CWnd* pParent = nullptr);

#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_MFC_GLIM_DIALOG };
#endif

protected:
    virtual void DoDataExchange(CDataExchange* pDX);
    HICON m_hIcon;

    // 사용자 정의 변수
    std::vector<CPoint> clickedPoints;
    int draggingPointIndex = -1;
    CPoint center;
    int radius = 0;
    int pointRadius = 5;

    // Edit Control
    CEdit m_radiusInput;     // IDC_EDIT1
    CEdit m_thicknessInput;  // IDC_EDIT2

    // 헬퍼 함수
    void DrawCircleFromPoints(CDC* pDC);
    void UpdateCenterLabel();

protected:
    virtual BOOL OnInitDialog();
    afx_msg void OnPaint();
    afx_msg HCURSOR OnQueryDragIcon();
    afx_msg void OnBnClickedButton1();
    afx_msg void OnBnClickedButton2();
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    DECLARE_MESSAGE_MAP()
};
