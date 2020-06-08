#pragma once
#include "afxwin.h"
#include "MapDataType.h"

// CDlgUglGmap 对话框

class CDlgUglGmap : public CDialog
{
	DECLARE_DYNAMIC(CDlgUglGmap)

public:
	CDlgUglGmap(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgUglGmap();

// 对话框数据
	enum { IDD = IDD_UGL_GMAP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_EditTile0;
	CEdit m_EditTile1;
	CEdit m_EditTile2;
	CEdit m_EditTile3;
	CEdit m_EditPlt0;
	CEdit m_EditPlt1;
	CEdit m_EditPlt2;
	CEdit m_EditPlt3;
	CButton m_CheckFlipX0;
	CButton m_CheckFlipX1;
	CButton m_CheckFlipX2;
	CButton m_CheckFlipX3;
	CButton m_CheckFlipY0;
	CButton m_CheckFlipY1;
	CButton m_CheckFlipY2;
	CButton m_CheckFlipY3;
	BLOCK_MAPPING m_BlockMapping;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
};
