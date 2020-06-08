// DlgUglTile.cpp : 实现文件
//

#include "stdafx.h"
#include "MapDeluxe.h"
#include "DlgUglTile.h"
#include "CodeTran.h"

#define SCALE_R 16
#define PLT_SQ_Y SCALE_R*8+8
#define PLT_SQ_WIDTH 8
#define PLT_SQ_HEIGHT 24

// CDlgUglTile 对话框

IMPLEMENT_DYNAMIC(CDlgUglTile, CDialog)

CDlgUglTile::CDlgUglTile(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgUglTile::IDD, pParent)
{

}

CDlgUglTile::~CDlgUglTile()
{
}

void CDlgUglTile::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_UGL_TILL_CHOOSE_COLOR, m_StaticColor);
}


BEGIN_MESSAGE_MAP(CDlgUglTile, CDialog)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


void CDlgUglTile::PresentTile(CDC* pDC)
{
	for(u8 y=0;y<8;y++)for(u8 x=0;x<8;x++)
	{
		pDC->FillRect((LPRECT)&CRect(SCALE_R*x,SCALE_R*y,SCALE_R*(x+1),SCALE_R*(y+1)),
			&CBrush(m_pltline[m_tile.Get(x,y)]));
	}
}
void CDlgUglTile::PresentCurColor(CDC* pDC)
{
	CString str;
	str.Format(_T("当前颜色:#%d"),cur_color);
	m_StaticColor.SetWindowText(str);
	RECT rc;
	m_StaticColor.GetWindowRect(&rc);
	ScreenToClient(&rc);
	rc.bottom=rc.top;
	rc.top-=24;
	pDC->FillRect(&rc,&CBrush(m_pltline[cur_color]));
}

// CDlgUglTile 消息处理程序

void CDlgUglTile::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	PresentTile(&dc);
	PresentCurColor(&dc);
	for(int i=0;i<16;i++)
	{
		dc.FillRect((LPRECT)&CRect(i*PLT_SQ_WIDTH,PLT_SQ_Y,
			(i+1)*PLT_SQ_WIDTH,PLT_SQ_Y+PLT_SQ_HEIGHT),
			&CBrush(m_pltline[i]));
	}
}

BOOL CDlgUglTile::OnInitDialog()
{
	CDialog::OnInitDialog();

	drawing=false;
	cur_color=0;

	return TRUE;
}

void CDlgUglTile::OnLButtonDown(UINT nFlags, CPoint point)
{
	if(point.x<SCALE_R*8 && point.y<SCALE_R*8)
	{
		drawing=true;
		SetCapture();
		OnMouseMove(0,point);
	}
	else if(point.x<PLT_SQ_WIDTH*16 && point.y>PLT_SQ_Y && point.y<PLT_SQ_Y+PLT_SQ_HEIGHT)
	{
		cur_color=(u8)(point.x/PLT_SQ_WIDTH);
		CDC* pDC=GetDC();
		PresentCurColor(pDC);
		ReleaseDC(pDC);
	}

	CDialog::OnLButtonDown(nFlags, point);
}

void CDlgUglTile::OnLButtonUp(UINT nFlags, CPoint point)
{
	drawing=false;
	ReleaseCapture();

	CDialog::OnLButtonUp(nFlags, point);
}

void CDlgUglTile::OnMouseMove(UINT nFlags, CPoint point)
{
	if(drawing && point.x<SCALE_R*8 && point.y<SCALE_R*8)
	{
		u8 x=(u8)(point.x/SCALE_R);
		u8 y=(u8)(point.y/SCALE_R);
		m_tile.Set(x,y,cur_color);
		CDC* pDC=GetDC();
		pDC->FillRect((LPRECT)&CRect(SCALE_R*x,SCALE_R*y,SCALE_R*(x+1),SCALE_R*(y+1)),
			&CBrush(m_pltline[m_tile.Get(x,y)]));
		ReleaseDC(pDC);

	}

	CDialog::OnMouseMove(nFlags, point);
}
