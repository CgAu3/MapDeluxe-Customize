#pragma once
#include "afxwin.h"


// CDlgAbout 对话框

class CDlgAbout : public CDialog
{
	DECLARE_DYNAMIC(CDlgAbout)

public:
	CDlgAbout(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgAbout();

// 对话框数据
	enum { IDD = IDD_ABOUT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	CDC m_TmpDC;
	CBitmap m_BmpLogo;

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	virtual BOOL OnInitDialog();
	CEdit m_EditAbout;
	afx_msg void OnBnClickedCommandBaidu();
	afx_msg void OnBnClickedCommandTieze();
};
