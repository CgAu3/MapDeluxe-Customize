#pragma once
#include "afxwin.h"


// CDlgAbout �Ի���

class CDlgAbout : public CDialog
{
	DECLARE_DYNAMIC(CDlgAbout)

public:
	CDlgAbout(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgAbout();

// �Ի�������
	enum { IDD = IDD_ABOUT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
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
