#pragma once
#include "MapDataType.h"
#include "afxwin.h"

// CDlgUglTile 对话框

class CDlgUglTile : public CDialog
{
	DECLARE_DYNAMIC(CDlgUglTile)

public:
	CDlgUglTile(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgUglTile();

// 对话框数据
	enum { IDD = IDD_UGL_TILE };

	TILE m_tile;
	COLORREF m_pltline[16];

	bool drawing;
	u8 cur_color;

	void PresentTile(CDC* pDC);
	void PresentCurColor(CDC* pDC);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	CStatic m_StaticColor;
};
