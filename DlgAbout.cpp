// DlgAbout.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MapDeluxe.h"
#include "DlgAbout.h"

#include "time.h"

// CDlgAbout �Ի���

IMPLEMENT_DYNAMIC(CDlgAbout, CDialog)

CDlgAbout::CDlgAbout(CWnd* pParent)
	: CDialog(CDlgAbout::IDD, pParent)
{
	static bool sranded=false;
	if(!sranded){
		srand((unsigned int)time(0));
		sranded=true;
	}
}

CDlgAbout::~CDlgAbout()
{
}

void CDlgAbout::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_EditAbout);
}


BEGIN_MESSAGE_MAP(CDlgAbout, CDialog)
	ON_WM_MOUSEMOVE()
	ON_BN_CLICKED(IDC_COMMAND_BAIDU, &CDlgAbout::OnBnClickedCommandBaidu)
	ON_BN_CLICKED(IDC_COMMAND_TIEZE, &CDlgAbout::OnBnClickedCommandTieze)
END_MESSAGE_MAP()



void CDlgAbout::OnMouseMove(UINT nFlags, CPoint point)
{
	CDC *pDC=GetDC();
	int x,y;
	COLORREF dcl;
	int r,g,b;
	double wgh=0.3;
	for(int i=1;i<1000;i++)
	{
		x=rand()%200;
		y=rand()%80;
		dcl=m_TmpDC.GetPixel(x,y);
		r=GetRValue(dcl);
		g=GetGValue(dcl);
		b=GetBValue(dcl);
		r=(int)((r*wgh+rand()%256)/(wgh+1));
		g=(int)((g*wgh+rand()%256)/(wgh+1));
		b=(int)((b*wgh+rand()%256)/(wgh+1));
		pDC->SetPixel(x,y,RGB(r,g,b));
	}

	ReleaseDC(pDC);

	CDialog::OnMouseMove(nFlags, point);
}

BOOL CDlgAbout::OnInitDialog()
{
	CDialog::OnInitDialog();

	CDC* pDC=GetDC();
	m_TmpDC.CreateCompatibleDC(pDC);
	m_BmpLogo.LoadBitmap(IDB_LOGO);
	m_TmpDC.SelectObject(&m_BmpLogo);

	CString str;
	str.Format(
		_T("MapDeluxe\r\n")
		_T("������汾 %s\r\n")
		_T("RomRebuild�汾 %d\r\n")
		_T("���� wwylele\r\n")
		_T(__DATE__)_T(" ")_T(__TIME__)_T("����\r\n\r\n")
		_T("��л:(���¾�Ϊ�ٶ�ID,�������Ⱥ�)\r\n")
		_T("��������\r\n")
		_T("����_����\r\n")
		_T("���Ձ|����\r\n")
		_T("�ڰ�����X\r\n")
		_T("����ָ����\r\n")
		_T("С�κ�СĪ\r\n")
		_T("1159500890\r\n")
		_T("759631498\r\n")
		_T("ɢ��ҿ���\r\n")
		_T("������֮��\r\n")
		_T("mfgujhgh\r\n")
		_T("���Ƶİ��ư�\r\n")
		_T("1019630574\r\n")
		_T("��ˮϵ֮��\r\n")
		_T("cypwxy\r\n")
		_T("�Լ�����������д������֧���ҵ���\r\n")
		_T("������������ǰٶ�ID\r\n\r\n")
		_T("�����ڰٶ�:http://www.baidu.com/p/wwylele\r\n")
		_T("��ӭ���ʰٶ�����-��֮���Ȱ�(http://tieba.baidu.com/%s)")
		,(const TCHAR*)GetProductVersion(),mrrGetRomVersion(),_T("%E6%98%9F%E4%B9%8B%E5%8D%A1%E6%AF%94")
		);
	m_EditAbout.SetWindowText(str);
	

	//�õ�ϵͳ�汾�����û��vista�ͰѰ�ť��ʽ�ĳ���ͨ
	int dwMajor;
    int dwMinor;
	_asm
	{
		pushad
		mov ebx,fs:[0x18]  ; get self pointer from TEB
		mov eax,fs:[0x30]  ; get pointer to PEB / database
		mov ebx,[eax+0A8h] ; get OSMinorVersion
		mov eax,[eax+0A4h] ; get OSMajorVersion
		mov dwMinor,ebx
		mov dwMajor,eax
        popad
	}
	if(dwMajor<6)
	{
		SetWindowLong(GetDlgItem(IDC_COMMAND_BAIDU)->m_hWnd,GWL_STYLE,WS_TABSTOP|WS_VISIBLE|WS_CHILD);
		SetWindowLong(GetDlgItem(IDC_COMMAND_TIEZE)->m_hWnd,GWL_STYLE,WS_TABSTOP|WS_VISIBLE|WS_CHILD);
	}

	return TRUE;
}

void CDlgAbout::OnBnClickedCommandBaidu()
{
	ShellExecute(0,_T("open"),_T("http://tieba.baidu.com/%D0%C7%D6%AE%BF%A8%B1%C8"),0,0,SW_SHOWNORMAL);
}

void CDlgAbout::OnBnClickedCommandTieze()
{
	ShellExecute(0,_T("open"),_T("http://tieba.baidu.com/p/1816594640"),0,0,SW_SHOWNORMAL);
}
