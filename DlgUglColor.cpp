// DlgUglColor.cpp : 实现文件
//

#include "stdafx.h"
#include "MapDeluxe.h"
#include "DlgUglColor.h"
#include "CodeTran.h"

// CDlgUglColor 对话框

IMPLEMENT_DYNAMIC(CDlgUglColor, CDialog)

CDlgUglColor::CDlgUglColor(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgUglColor::IDD, pParent)
{

}

CDlgUglColor::~CDlgUglColor()
{
}

void CDlgUglColor::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER_UGL_COLOR_R, m_SliderR);
	DDX_Control(pDX, IDC_SLIDER_UGL_COLOR_G, m_SliderG);
	DDX_Control(pDX, IDC_SLIDER_UGL_COLOR_B, m_SliderB);
	DDX_Control(pDX, IDC_STATIC_UGL_COLOR_R, m_StaticR);
	DDX_Control(pDX, IDC_STATIC_UGL_COLOR_G, m_StaticG);
	DDX_Control(pDX, IDC_STATIC_UGL_COLOR_B, m_StaticB);
}


BEGIN_MESSAGE_MAP(CDlgUglColor, CDialog)
	ON_WM_VSCROLL()
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CDlgUglColor 消息处理程序

BOOL CDlgUglColor::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_SliderR.SetRange(0,31);
	m_SliderG.SetRange(0,31);
	m_SliderB.SetRange(0,31);

	m_SliderR.SetPos(31-(m_pltcolor&31));
	m_SliderG.SetPos(31-((m_pltcolor>>5)&31));
	m_SliderB.SetPos(31-((m_pltcolor>>10)&31));

	UpdateColor();

	return TRUE;
}
void CDlgUglColor::PresentColor(CDC* pDC)
{
	RECT rc;
	m_StaticR.GetWindowRect(&rc);
	ScreenToClient(&rc);
	rc.top=rc.bottom;
	rc.bottom+=48;
	rc.right=rc.left+192;
	pDC->FillRect(&rc,&CBrush(R5G5B5X1toR8G8B8X8(
		(31-(m_SliderR.GetPos()))|
		((31-(m_SliderG.GetPos()))<<5)|
		((31-(m_SliderB.GetPos()))<<10))));
}
void CDlgUglColor::UpdateColor()
{
	CString str;
	str.Format(_T("R:%d"),31-(m_SliderR.GetPos()));
	m_StaticR.SetWindowText(str);
	str.Format(_T("G:%d"),31-(m_SliderG.GetPos()));
	m_StaticG.SetWindowText(str);
	str.Format(_T("B:%d"),31-(m_SliderB.GetPos()));
	m_StaticB.SetWindowText(str);

	CDC *pDC=GetDC();
	PresentColor(pDC);
	ReleaseDC(pDC);
}
void CDlgUglColor::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	UpdateColor();
	CDialog::OnVScroll(nSBCode, nPos, pScrollBar);
}

void CDlgUglColor::OnPaint()
{
	CPaintDC dc(this);
	PresentColor(&dc);
}

void CDlgUglColor::OnOK()
{
	m_pltcolor=(31-(m_SliderR.GetPos()))|
		((31-(m_SliderG.GetPos()))<<5)|
		((31-(m_SliderB.GetPos()))<<10);

	CDialog::OnOK();
}
