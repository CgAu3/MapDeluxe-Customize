//DlgBoss.cpp
//编辑小BOSS对话框
//编写:wwylele

#include "stdafx.h"
#include "MapDeluxe.h"
#include "DlgBoss.h"
#include "CodeTran.h"


// DlgBoss 对话框

IMPLEMENT_DYNAMIC(CDlgBoss, CDialog)

CDlgBoss::CDlgBoss(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgBoss::IDD, pParent)
{

}

CDlgBoss::~CDlgBoss()
{
}

void CDlgBoss::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_BOSS_LOCK, m_ComboBossLock);
	DDX_Control(pDX, IDC_COMBO_BOSS_CLASS1, m_ComboBoss1Class);
	DDX_Control(pDX, IDC_COMBO_BOSS_CLASS2, m_ComboBoss2Class);
	DDX_Control(pDX, IDC_EDIT_BOSS_PLT1, m_EditBoss1Plt);
	DDX_Control(pDX, IDC_EDIT_BOSS_PLT2, m_EditBoss2Plt);
	DDX_Control(pDX, IDC_CHECK_BOSS_HP1, m_CheckBoss1Hp);
	DDX_Control(pDX, IDC_CHECK_BOSS_HP2, m_CheckBoss2Hp);
	DDX_Control(pDX, IDC_CHECK_BOSS_BOOL1, m_CheckBoss1X);
	DDX_Control(pDX, IDC_CHECK_BOSS_BOOL2, m_CheckBoss2X);
	DDX_Control(pDX, IDC_CHECK_BOSS_SND, m_CheckBoss2);
}


BEGIN_MESSAGE_MAP(CDlgBoss, CDialog)
	ON_BN_CLICKED(IDC_CHECK_BOSS_SND, &CDlgBoss::OnBnClickedCheckBossSnd)
	ON_BN_CLICKED(IDOK, &CDlgBoss::OnBnClickedOk)
END_MESSAGE_MAP()


// DlgBoss 消息处理程序

BOOL CDlgBoss::OnInitDialog()
{
	CDialog::OnInitDialog();

	CString str;
	str=_T("[00-00]不设置");
	m_ComboBossLock.AddString(str);
	if(boss_lock==0)m_ComboBossLock.SelectString(-1,str);
	str=_T("[06-02]BOSS战时场景静止");
	m_ComboBossLock.AddString(str);
	if(boss_lock==0x0206)m_ComboBossLock.SelectString(-1,str);
	str=_T("[06-04]BOSS死后开启指定位置的传送门");
	m_ComboBossLock.AddString(str);
	if(boss_lock==0x0406)m_ComboBossLock.SelectString(-1,str);
	str=_T("[06-05]BOSS死后掀开指定位置的砖块");
	m_ComboBossLock.AddString(str);
	if(boss_lock==0x0506)m_ComboBossLock.SelectString(-1,str);

	for(u16 i=0;i<8;i++)
	{
		str.Format(_T("[07-%02X]%s"),i,CodeTran_Obj((i<<8)|7));
		m_ComboBoss1Class.AddString(str);
		if(boss1_class==((i<<8)|7))m_ComboBoss1Class.SelectString(-1,str);
		m_ComboBoss2Class.AddString(str);
		if(boss2_class==((i<<8)|7) && boss2)m_ComboBoss2Class.SelectString(-1,str);
	}

	str.Format(_T("%d"),boss1_plt);
	m_EditBoss1Plt.SetWindowText(str);
	m_CheckBoss1Hp.SetCheck(boss1_hp?TRUE:FALSE);
	m_CheckBoss1X.SetCheck(boss1_x?TRUE:FALSE);

	if(boss2)
	{
		str.Format(_T("%d"),boss2_plt);
		m_EditBoss2Plt.SetWindowText(str);
		m_CheckBoss2Hp.SetCheck(boss2_hp?TRUE:FALSE);
		m_CheckBoss2X.SetCheck(boss2_x?TRUE:FALSE);
	}

	m_CheckBoss2.SetCheck(boss2?TRUE:FALSE);
	OnBnClickedCheckBossSnd();
	return TRUE; 
}

void CDlgBoss::OnBnClickedCheckBossSnd()
{
	m_ComboBoss2Class.EnableWindow(m_CheckBoss2.GetCheck());
	m_EditBoss2Plt.EnableWindow(m_CheckBoss2.GetCheck());
	m_CheckBoss2Hp.EnableWindow(m_CheckBoss2.GetCheck());
	m_CheckBoss2X.EnableWindow(m_CheckBoss2.GetCheck());
	if(m_CheckBoss2.GetCheck())
	{
		CString str;
		m_ComboBoss2Class.GetWindowText(str);
		if(str==_T(""))
		{
			str.Format(_T("[07-%02X]%s"),0,CodeTran_Obj(7));
			m_ComboBoss2Class.SelectString(-1,str);
			m_EditBoss2Plt.SetWindowText(_T("0"));
		}
		
	}
}

void CDlgBoss::OnBnClickedOk()
{
	CString str;
	u32 ca,cb;
	try{
		m_ComboBossLock.GetWindowText(str);
		_stscanf_s(str,_T("[%X-%X]"),&ca,&cb);
		boss_lock=(u16)((cb<<8)|ca);

		m_ComboBoss1Class.GetWindowText(str);
		_stscanf_s(str,_T("[%X-%X]"),&ca,&cb);
		boss1_class=(u16)((cb<<8)|ca);

		m_EditBoss1Plt.GetWindowText(str);
		_stscanf_s(str,_T("%d"),&ca);
		boss1_plt=(u16)ca;

		boss1_hp=m_CheckBoss1Hp.GetCheck()?true:false;
		boss1_x=m_CheckBoss1X.GetCheck()?true:false;

		boss2=m_CheckBoss2.GetCheck()?true:false;
		if(boss2)
		{
			m_ComboBoss2Class.GetWindowText(str);
			_stscanf_s(str,_T("[%X-%X]"),&ca,&cb);
			boss2_class=(u16)((cb<<8)|ca);

			m_EditBoss2Plt.GetWindowText(str);
			_stscanf_s(str,_T("%d"),&ca);
			boss2_plt=(u16)ca;

			boss2_hp=m_CheckBoss2Hp.GetCheck()?true:false;
			boss2_x=m_CheckBoss2X.GetCheck()?true:false;
		}

		int a=1+1;
	}catch(...){
		MessageBox(_T("输入数据有误，修改失败"),_T("错误"),MB_ICONERROR);
		OnCancel();
	}

	OnOK();
}
