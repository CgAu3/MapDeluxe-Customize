#pragma once
#include "afxwin.h"


// DlgBoss 对话框

class CDlgBoss : public CDialog
{
	DECLARE_DYNAMIC(CDlgBoss)

public:
	CDlgBoss(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgBoss();

// 对话框数据
	enum { IDD = IDD_BOSS };

	u16 boss_lock;
	u16 boss1_class;
	u16 boss1_plt;
	bool boss1_hp;
	bool boss1_x;
	bool boss2;
	u16 boss2_class;
	u16 boss2_plt;
	bool boss2_hp;
	bool boss2_x;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_ComboBossLock;
	CComboBox m_ComboBoss1Class;
	CComboBox m_ComboBoss2Class;
	CEdit m_EditBoss1Plt;
	CEdit m_EditBoss2Plt;
	CButton m_CheckBoss1Hp;
	CButton m_CheckBoss2Hp;
	CButton m_CheckBoss1X;
	CButton m_CheckBoss2X;
	CButton m_CheckBoss2;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedCheckBossSnd();
	afx_msg void OnBnClickedOk();
};
