#pragma once
#include "MapDataType.h"
#include "afxcmn.h"
#include "afxwin.h"
struct UGL_PACKAGE
{
	TCHAR title[16];
	struct PLT_P{
		u16 plt[128];
		u16 plt_count;
	}plt_p[16];
	TILE tile[512];
	u16 tile_count;
	BLOCK_MAPPING gmap[UGL_GMAP_MAX_COUNT];
	u16 gmap_count;
};

#define FTCI_MENU_ID_BASE 6001

// CDlgUgl 对话框

class CDlgUgl : public CDialog
{
	DECLARE_DYNAMIC(CDlgUgl)

public:
	CDlgUgl(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgUgl();

// 对话框数据
	enum { IDD = IDD_UGL };

	UGL_PACKAGE m_UglIO;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	UGL_PACKAGE m_Ugl;

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CDC m_TmpDC;
	CBitmap m_BmpTmpPlt,m_BmpTmpTile,m_BmpTmpGmap;
	CFont m_Font;

	CSliderCtrl m_SliderPlt;
	CStatic m_StaticPlt;
	CEdit m_EditTitle;
	CStatic m_StaticTile;

	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	void PresentPlt(CDC *pDC);
	void PresentColor(CDC *pDC,u16 line,u16 i);
	void PaintTile();
	void PresentTile(CDC *pDC);
	void PaintGmap();
	void PresentGmap(CDC *pDC);
	afx_msg void OnPaint();
	
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	CStatic m_StaticColor;
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnEnChangeEditUglTitle();
	afx_msg void OnBnClickedOk();
	CSliderCtrl m_SliderTilePlt;
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	CButton m_CheckPltExt;
	afx_msg void OnBnClickedCheckUglPltExt();
	CStatic m_StaticTileInfo;
	CScrollBar m_ScrollGmap;

	u16 m_curgmap;
	
	afx_msg void OnBnClickedButtonUglImportSys();
	CButton m_ButtonImportSys;
	void OnFpciMenu(UINT id);
};
