#pragma once
#include "MapDataType.h"
#include "afxwin.h"

// CDlgUglTile �Ի���

class CDlgUglTile : public CDialog
{
	DECLARE_DYNAMIC(CDlgUglTile)

public:
	CDlgUglTile(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgUglTile();

// �Ի�������
	enum { IDD = IDD_UGL_TILE };

	TILE m_tile;
	COLORREF m_pltline[16];

	bool drawing;
	u8 cur_color;

	void PresentTile(CDC* pDC);
	void PresentCurColor(CDC* pDC);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	CStatic m_StaticColor;
};
