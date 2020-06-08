#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CDlgUglColor 对话框

class CDlgUglColor : public CDialog
{
	DECLARE_DYNAMIC(CDlgUglColor)

public:
	CDlgUglColor(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgUglColor();

// 对话框数据
	enum { IDD = IDD_UGL_COLOR };

	u16 m_pltcolor;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CSliderCtrl m_SliderR;
	CSliderCtrl m_SliderG;
	CSliderCtrl m_SliderB;
	CStatic m_StaticR;
	CStatic m_StaticG;
	CStatic m_StaticB;
	void UpdateColor();
	void PresentColor(CDC* pDC);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnPaint();
protected:
	virtual void OnOK();
};
