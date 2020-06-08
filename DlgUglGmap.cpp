// DlgUglGmap.cpp : 实现文件
//

#include "stdafx.h"
#include "MapDeluxe.h"
#include "DlgUglGmap.h"


// CDlgUglGmap 对话框

IMPLEMENT_DYNAMIC(CDlgUglGmap, CDialog)

CDlgUglGmap::CDlgUglGmap(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgUglGmap::IDD, pParent)
{

}

CDlgUglGmap::~CDlgUglGmap()
{
}

void CDlgUglGmap::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_UGL_GMAP_TILE0, m_EditTile0);
	DDX_Control(pDX, IDC_EDIT_UGL_GMAP_TILE1, m_EditTile1);
	DDX_Control(pDX, IDC_EDIT_UGL_GMAP_TILE2, m_EditTile2);
	DDX_Control(pDX, IDC_EDIT_UGL_GMAP_TILE3, m_EditTile3);
	DDX_Control(pDX, IDC_EDIT_UGL_GMAP_PLT0, m_EditPlt0);
	DDX_Control(pDX, IDC_EDIT_UGL_GMAP_PLT1, m_EditPlt1);
	DDX_Control(pDX, IDC_EDIT_UGL_GMAP_PLT2, m_EditPlt2);
	DDX_Control(pDX, IDC_EDIT_UGL_GMAP_PLT3, m_EditPlt3);
	DDX_Control(pDX, IDC_CHECK_UGL_GMAP_FLIP_X0, m_CheckFlipX0);
	DDX_Control(pDX, IDC_CHECK_UGL_GMAP_FLIP_X1, m_CheckFlipX1);
	DDX_Control(pDX, IDC_CHECK_UGL_GMAP_FLIP_X2, m_CheckFlipX2);
	DDX_Control(pDX, IDC_CHECK_UGL_GMAP_FLIP_X3, m_CheckFlipX3);
	DDX_Control(pDX, IDC_CHECK_UGL_GMAP_FLIP_Y0, m_CheckFlipY0);
	DDX_Control(pDX, IDC_CHECK_UGL_GMAP_FLIP_Y1, m_CheckFlipY1);
	DDX_Control(pDX, IDC_CHECK_UGL_GMAP_FLIP_Y2, m_CheckFlipY2);
	DDX_Control(pDX, IDC_CHECK_UGL_GMAP_FLIP_Y3, m_CheckFlipY3);
}


BEGIN_MESSAGE_MAP(CDlgUglGmap, CDialog)

	ON_BN_CLICKED(IDOK, &CDlgUglGmap::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlgUglGmap 消息处理程序


BOOL CDlgUglGmap::OnInitDialog()
{
	CDialog::OnInitDialog();

	CString str;
	str.Format(_T("%d"),m_BlockMapping.mapping[0]&0x3FF);
	m_EditTile0.SetWindowTextW(str);
	m_EditTile0.SetLimitText(3);
	str.Format(_T("%d"),m_BlockMapping.mapping[1]&0x3FF);
	m_EditTile1.SetWindowTextW(str);
	m_EditTile1.SetLimitText(3);
	str.Format(_T("%d"),m_BlockMapping.mapping[2]&0x3FF);
	m_EditTile2.SetWindowTextW(str);
	m_EditTile2.SetLimitText(3);
	str.Format(_T("%d"),m_BlockMapping.mapping[3]&0x3FF);
	m_EditTile3.SetWindowTextW(str);
	m_EditTile3.SetLimitText(3);
	str.Format(_T("%d"),m_BlockMapping.mapping[0]>>12);
	m_EditPlt0.SetWindowTextW(str);
	m_EditPlt0.SetLimitText(1);
	str.Format(_T("%d"),m_BlockMapping.mapping[1]>>12);
	m_EditPlt1.SetWindowTextW(str);
	m_EditPlt1.SetLimitText(1);
	str.Format(_T("%d"),m_BlockMapping.mapping[2]>>12);
	m_EditPlt2.SetWindowTextW(str);
	m_EditPlt2.SetLimitText(1);
	str.Format(_T("%d"),m_BlockMapping.mapping[3]>>12);
	m_EditPlt3.SetWindowTextW(str);
	m_EditPlt3.SetLimitText(1);
	m_CheckFlipX0.SetCheck(m_BlockMapping.mapping[0]&1024?TRUE:FALSE);
	m_CheckFlipX1.SetCheck(m_BlockMapping.mapping[1]&1024?TRUE:FALSE);
	m_CheckFlipX2.SetCheck(m_BlockMapping.mapping[2]&1024?TRUE:FALSE);
	m_CheckFlipX3.SetCheck(m_BlockMapping.mapping[3]&1024?TRUE:FALSE);
	m_CheckFlipY0.SetCheck(m_BlockMapping.mapping[0]&2048?TRUE:FALSE);
	m_CheckFlipY1.SetCheck(m_BlockMapping.mapping[1]&2048?TRUE:FALSE);
	m_CheckFlipY2.SetCheck(m_BlockMapping.mapping[2]&2048?TRUE:FALSE);
	m_CheckFlipY3.SetCheck(m_BlockMapping.mapping[3]&2048?TRUE:FALSE);

	return TRUE;
}

void CDlgUglGmap::OnBnClickedOk()
{
	TCHAR str[5];
	u16 tile,plt;

	m_EditTile0.GetWindowText(str,4);
	tile=_ttoi(str);
	if(tile>511)
	{
		MessageBox(_T("瓦图编号只能取值在0~511之间"),_T("数据错误"),0);return;
	}
	m_EditPlt0.GetWindowText(str,4);
	plt=_ttoi(str);
	if(plt<2)
	{
		MessageBox(_T("调色行编号只能取值在2~9之间"),_T("数据错误"),0);return;
	}
	m_BlockMapping.mapping[0]=tile|(plt<<12)
		|(m_CheckFlipX0.GetCheck()?1024:0)
		|(m_CheckFlipY0.GetCheck()?2048:0);

	m_EditTile1.GetWindowText(str,4);
	tile=_ttoi(str);
	if(tile>511)
	{
		MessageBox(_T("瓦图编号只能取值在0~511之间"),_T("数据错误"),0);return;
	}
	m_EditPlt1.GetWindowText(str,4);
	plt=_ttoi(str);
	if(plt<2)
	{
		MessageBox(_T("调色行编号只能取值在2~9之间"),_T("数据错误"),0);return;
	}
	m_BlockMapping.mapping[1]=tile|(plt<<12)
		|(m_CheckFlipX1.GetCheck()?1024:0)
		|(m_CheckFlipY1.GetCheck()?2048:0);

	m_EditTile2.GetWindowText(str,4);
	tile=_ttoi(str);
	if(tile>511)
	{
		MessageBox(_T("瓦图编号只能取值在0~511之间"),_T("数据错误"),0);return;
	}
	m_EditPlt2.GetWindowText(str,4);
	plt=_ttoi(str);
	if(plt<2)
	{
		MessageBox(_T("调色行编号只能取值在2~9之间"),_T("数据错误"),0);return;
	}
	m_BlockMapping.mapping[2]=tile|(plt<<12)
		|(m_CheckFlipX2.GetCheck()?1024:0)
		|(m_CheckFlipY2.GetCheck()?2048:0);

	m_EditTile3.GetWindowText(str,4);
	tile=_ttoi(str);
	if(tile>511)
	{
		MessageBox(_T("瓦图编号只能取值在0~511之间"),_T("数据错误"),0);return;
	}
	m_EditPlt3.GetWindowText(str,4);
	plt=_ttoi(str);
	if(plt<2)
	{
		MessageBox(_T("调色行编号只能取值在2~9之间"),_T("数据错误"),0);return;
	}
	m_BlockMapping.mapping[3]=tile|(plt<<12)
		|(m_CheckFlipX3.GetCheck()?1024:0)
		|(m_CheckFlipY3.GetCheck()?2048:0);

	
	OnOK();
}
