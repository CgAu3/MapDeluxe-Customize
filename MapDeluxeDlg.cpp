//MapDeluxeDlg.cpp
//主窗口
//编写:wwylele



#include "stdafx.h"
#include "MapDeluxe.h"
#include "MapDeluxeDlg.h"
#include "CodeTran.h"
#include "DlgResize.h"
#include "DlgDoor.h"
#include "DlgRomImage.h"
#include "DlgObj.h"
#include "DlgAbout.h"
#include "MdxStepFile.h"
#include "DlgUgl.h"
#include "GraAssoc.h"
//#include "vector"//仅用于debug


#ifdef _DEBUG
#define new DEBUG_NEW
#define printf_debug printf
#else
#define printf_debug printf_dtr
#endif

#ifndef _DEBUG //DEBUG下无效，方便wwylele查看已成为最终版的游戏←w←
#define CHECK_ROM_MAGIC //打开游戏时会检查MAGIC
#endif

static UINT BASED_CODE StatusBar_indicators[] =
{
	ID_SEPARATOR,
	ID_SEPARATOR,
};


const char *MagicStr="ROM_REBUILD_V1";

// CMapDeluxeDlg 对话框

COLORREF BitColor[8]=
{
	RGB(255,0,0),
	RGB(255,128,0),	
	RGB(255,255,0),
	RGB(0,255,0),
	RGB(0,255,255),
	RGB(0,0,255),
	RGB(255,0,255),
	RGB(255,0,128)
};

HANDLE hConsole = NULL;

//Release下printf_debug跳转至此
void printf_dtr(char*,...)
{
	//这只是一个空函数而已:p

}

//打开控制台的函数，改写自DesMuME源代码
void OpenConsole()
{

	if (hConsole) return;

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD fileType = GetFileType(hConsole);

	bool shouldRedirectStdout = fileType == FILE_TYPE_UNKNOWN;

	bool attached = false;
	if(AttachConsole(-1))
		attached = true;
	if(!attached)
	{
		if (!AllocConsole()) return;

		SetConsoleCP(GetACP());
		SetConsoleOutputCP(GetACP());
	}
	SetConsoleTitle(_T("MapDeluxe"));

	if(shouldRedirectStdout)
	{
		freopen("CONOUT$", "w", stdout);
		freopen("CONOUT$", "w", stderr);
		freopen("CONIN$", "r", stdin);
	}

}

u8 TILE::Get(u8 x,u8 y)
{
	u8& k=dt[y*4+x/2];
	return x%2 ? k>>4:k&0xF;
}
void TILE::Set(u8 x,u8 y,u8 value)
{
	u8& k=dt[y*4+x/2];
	if(x%2)
	{
		k=(k&0xF)|(value<<4);
		
	}
	else
	{
		k=(k&0xF0)|(value&0xF);
	}
}
bool TILE::operator ==(TILE& value)
{
	for(int i=0;i<32;i++)
	{
		if(dt[i]!=value.dt[i])return false;
	}
	return true;
}

//这些是向导生成的
CMapDeluxeDlg::CMapDeluxeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMapDeluxeDlg::IDD, pParent)
{
	m_hIcon = (HICON)::LoadImage(AfxGetApp()->m_hInstance,MAKEINTRESOURCE(IDR_MAINFRAME),
		IMAGE_ICON,16,16,0);
}
void CMapDeluxeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_STEP_NUMBER, m_EditStepNumber);
	DDX_Control(pDX, IDC_CHECK_LZ77, m_CheckLz77);
	DDX_Control(pDX, IDC_COMBO_BGM, m_ComboBgm);
	DDX_Control(pDX, IDC_COMBO_SPCMAP, m_ComboSpcMap);
	DDX_Control(pDX, IDC_EDIT_CLIP_X, m_EditClipX);
	DDX_Control(pDX, IDC_EDIT_CLIP_Y, m_EditClipY);
	DDX_Control(pDX, IDC_EDIT_BEGIN_X, m_EditBeginX);
	DDX_Control(pDX, IDC_EDIT_BEGIN_Y, m_EditBeginY);
	DDX_Control(pDX, IDC_EDIT_BCK_MOV, m_EditBckMov);
	DDX_Control(pDX, IDC_EDIT_UNK36, m_EditX36);

	DDX_Control(pDX, IDC_CHECK_UNK55, m_CheckX55);
	DDX_Control(pDX, IDC_CHECK_BCKROLL, m_CheckBckRoll);
	DDX_Control(pDX, IDC_EDIT_PLT_FRT, m_EditPltFrt);
	DDX_Control(pDX, IDC_EDIT_TILE_FRT, m_EditTileFrt);

	DDX_Control(pDX, IDC_EDIT_PLT_BCK, m_EditPltBck);

	DDX_Control(pDX, IDC_EDIT_FILE, m_EditFileName);
	DDX_Control(pDX, IDC_TREE_FILE, m_Tree);
	DDX_Control(pDX, IDC_SCROLLBAR_MAPH, m_HScrollMap);
	DDX_Control(pDX, IDC_SCROLLBAR_MAPV, m_VScrollMap);
	DDX_Control(pDX, IDC_COMBO_MAPCHG, m_ComboMapChg);
	DDX_Control(pDX, IDC_SCROLLBAR_GRALIB, m_ScrollBarGraLib);
	DDX_Control(pDX, IDC_STATIC_LIB_INFO, m_StaticLibInfo);
	DDX_Control(pDX, IDC_CHECK_NEST, m_CheckNest);
	DDX_Control(pDX, IDC_PROGRESS, m_Progress);
	DDX_Control(pDX, IDC_CHECK_NEST_AUTO, m_CheckNestAuto);
	DDX_Control(pDX, IDC_CHECK_EDG, m_CheckEdg);
	DDX_Control(pDX, IDC_EDIT_EDG, m_EditEdg);
	DDX_Control(pDX, IDC_BUTTON_TILE_FRT_CHG, m_ButtonFrtTileChg);
	DDX_Control(pDX, IDC_BUTTON_PLT_FRT_CHG, m_ButtonFrtPltChg);
	DDX_Control(pDX, IDC_BUTTON_BCK_CHG, m_ButtonBckChg);
	DDX_Control(pDX, IDC_COMBO_GRA_ANI, m_ComboGraAni);
	DDX_Control(pDX, IDC_CHECK_MAP_OUT_BCK, m_CheckMapOutBck);
	DDX_Control(pDX, IDC_COMBO_WIND, m_ComboWind);
	DDX_Control(pDX, IDC_CHECK_GRA_ASSOC, m_CheckGraAssoc);

	DDX_Control(pDX, IDC_COMBO_SCRIPT_ID, m_ComboScriptId);
}

BEGIN_MESSAGE_MAP(CMapDeluxeDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_DESTROY()
	ON_COMMAND(ID_M_OPEN, &CMapDeluxeDlg::OnBnClickedButtonOpen)//ON_BN_CLICKED(IDC_BUTTON_OPEN, &CMapDeluxeDlg::OnBnClickedButtonOpen)
	ON_NOTIFY(NM_DBLCLK, IDC_TREE_FILE, &CMapDeluxeDlg::OnNMDblclkTreeFile)
	ON_COMMAND(ID_M_NEW, &CMapDeluxeDlg::OnBnClickedButtonNew)//ON_BN_CLICKED(IDC_BUTTON_NEW, &CMapDeluxeDlg::OnBnClickedButtonNew)
	ON_COMMAND(ID_M_SAVE, &CMapDeluxeDlg::OnBnClickedButtonSave)//ON_BN_CLICKED(IDC_BUTTON_SAVE, &CMapDeluxeDlg::OnBnClickedButtonSave)
	ON_BN_CLICKED(IDC_CHECK_LZ77, &CMapDeluxeDlg::OnBnClickedCheckLz77)
	ON_CBN_SELCHANGE(IDC_COMBO_BGM, &CMapDeluxeDlg::OnCbnSelchangeComboBgm)
	ON_CBN_SELCHANGE(IDC_COMBO_SPCMAP, &CMapDeluxeDlg::OnCbnSelchangeComboSpcmap)
	ON_EN_CHANGE(IDC_EDIT_CLIP_X, &CMapDeluxeDlg::OnEnChangeEditClipX)
	ON_EN_CHANGE(IDC_EDIT_CLIP_Y, &CMapDeluxeDlg::OnEnChangeEditClipY)
	ON_EN_CHANGE(IDC_EDIT_BEGIN_X, &CMapDeluxeDlg::OnEnChangeEditBeginX)
	ON_EN_CHANGE(IDC_EDIT_BEGIN_Y, &CMapDeluxeDlg::OnEnChangeEditBeginY)
	ON_EN_CHANGE(IDC_EDIT_BCK_MOV, &CMapDeluxeDlg::OnEnChangeEditBckMov)
	ON_EN_CHANGE(IDC_EDIT_UNK36, &CMapDeluxeDlg::OnEnChangeEditUnk36)
	ON_BN_CLICKED(IDC_CHECK_UNK55, &CMapDeluxeDlg::OnBnClickedCheckUnk55)
	ON_BN_CLICKED(IDC_CHECK_BCKROLL, &CMapDeluxeDlg::OnBnClickedCheckBckroll)
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	ON_WM_MOUSEMOVE()
	ON_CBN_SELCHANGE(IDC_COMBO_MAPCHG, &CMapDeluxeDlg::OnCbnSelchangeComboMapchg)
	ON_WM_LBUTTONDOWN()
	ON_COMMAND(ID_M_SAVE_TEST, &CMapDeluxeDlg::OnBnClickedButtonSaveTest)//ON_BN_CLICKED(IDC_BUTTON_SAVE_TEST, &CMapDeluxeDlg::OnBnClickedButtonSaveTest)
	ON_COMMAND(ID_M_SAVEAS, &CMapDeluxeDlg::OnBnClickedButtonSaveas)//ON_BN_CLICKED(IDC_BUTTON_SAVEAS, &CMapDeluxeDlg::OnBnClickedButtonSaveas)
	ON_BN_CLICKED(IDC_CHECK_NEST, &CMapDeluxeDlg::OnBnClickedCheckNest)
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_M_SAVE_FINAL, &CMapDeluxeDlg::OnBnClickedButtonSaveFinal)//ON_BN_CLICKED(IDC_BUTTON_SAVE_FINAL, &CMapDeluxeDlg::OnBnClickedButtonSaveFinal)
	ON_COMMAND(ID_M_RESIZE, &CMapDeluxeDlg::OnBnClickedButtonResize)//ON_BN_CLICKED(IDC_BUTTON_RESIZE, &CMapDeluxeDlg::OnBnClickedButtonResize)
	ON_COMMAND(ID_M_DOOR, &CMapDeluxeDlg::OnBnClickedButtonDoor)//ON_BN_CLICKED(IDC_BUTTON_DOOR, &CMapDeluxeDlg::OnBnClickedButtonDoor)
	ON_WM_LBUTTONUP()
	ON_COMMAND(ID_M_CLEAR_MAP, &CMapDeluxeDlg::OnBnClickedClearMap)//ON_BN_CLICKED(IDC_CLEAR_MAP, &CMapDeluxeDlg::OnBnClickedClearMap)
	ON_WM_MBUTTONDOWN()
	ON_WM_DROPFILES()
	ON_BN_CLICKED(IDC_CHECK_EDG, &CMapDeluxeDlg::OnBnClickedCheckEdg)
	ON_COMMAND(ID_M_ROM_IMAGE, &CMapDeluxeDlg::OnBnClickedButtonRomImage)//ON_BN_CLICKED(IDC_BUTTON_ROM_IMAGE, &CMapDeluxeDlg::OnBnClickedButtonRomImage)
	ON_COMMAND(ID_M_GAME_TEST, &CMapDeluxeDlg::OnBnClickedButtonGameTest)//ON_BN_CLICKED(IDC_BUTTON_GAME_TEST, &CMapDeluxeDlg::OnBnClickedButtonGameTest)
	ON_COMMAND(ID_M_OBJ, &CMapDeluxeDlg::OnBnClickedButtonObj)//ON_BN_CLICKED(IDC_BUTTON_OBJ, &CMapDeluxeDlg::OnBnClickedButtonObj)
	//ON_MESSAGE_VOID(WM_KICKIDLE,OnKickIdle)
	ON_COMMAND(ID_M_ABOUT, &CMapDeluxeDlg::OnBnClickedButtonAbout)//ON_BN_CLICKED(IDC_BUTTON_ABOUT, &CMapDeluxeDlg::OnBnClickedButtonAbout)
	ON_COMMAND(ID_M_STEP_EXPORT, &CMapDeluxeDlg::OnBnClickedButtonStepExport)//ON_BN_CLICKED(IDC_BUTTON_STEP_EXPORT, &CMapDeluxeDlg::OnBnClickedButtonStepExport)
	ON_COMMAND(ID_M_STEP_IMPORT, &CMapDeluxeDlg::OnBnClickedButtonStepImport)//ON_BN_CLICKED(IDC_BUTTON_STEP_IMPORT, &CMapDeluxeDlg::OnBnClickedButtonStepImport)
	ON_COMMAND(ID_M_UNDO, &CMapDeluxeDlg::OnBnClickedButtonUndo)//ON_BN_CLICKED(IDC_BUTTON_UNDO, &CMapDeluxeDlg::OnBnClickedButtonUndo)
	ON_COMMAND(ID_M_REDO, &CMapDeluxeDlg::OnBnClickedButtonRedo)
	ON_COMMAND(ID_M_RESET_MAP, &CMapDeluxeDlg::OnBnClickedButtonResetMap)//ON_BN_CLICKED(IDC_BUTTON_RESET_MAP, &CMapDeluxeDlg::OnBnClickedButtonResetMap)
	ON_COMMAND(ID_M_XZKBB, &CMapDeluxeDlg::OnXzkbb)
	ON_COMMAND(ID_M_TIEZI, &CMapDeluxeDlg::OnTiezi)
	ON_COMMAND(ID_M_EXIT, &CMapDeluxeDlg::OnBnClickedExit)
	ON_WM_INITMENU()
	ON_BN_CLICKED(IDC_BUTTON_TILE_FRT_CHG, &CMapDeluxeDlg::OnBnClickedButtonTileFrtChg)
	ON_COMMAND_RANGE(FTC_MENU_ID_BASE,FTC_MENU_ID_BASE+500,&CMapDeluxeDlg::OnFtcMenu)
	ON_BN_CLICKED(IDC_BUTTON_PLT_FRT_CHG, &CMapDeluxeDlg::OnBnClickedButtonPltFrtChg)
	ON_COMMAND_RANGE(FPC_MENU_ID_BASE,FPC_MENU_ID_BASE+100,&CMapDeluxeDlg::OnFpcMenu)
	ON_BN_CLICKED(IDC_BUTTON_BCK_CHG, &CMapDeluxeDlg::OnBnClickedButtonBckChg)
	ON_COMMAND_RANGE(BCC_MENU_ID_BASE,BCC_MENU_ID_BASE+100,&CMapDeluxeDlg::OnBccMenu)
	ON_CBN_SELCHANGE(IDC_COMBO_GRA_ANI, &CMapDeluxeDlg::OnCbnSelchangeComboGraAni)
	ON_COMMAND(ID_M_NEW_WHITE, &CMapDeluxeDlg::OnBnClickedNewWhite)
	ON_BN_CLICKED(IDC_CHECK_MAP_OUT_BCK, &CMapDeluxeDlg::OnBnClickedCheckMapOutBck)

	ON_WM_MENUSELECT()
	ON_WM_SETCURSOR()

	ON_COMMAND(ID_MAPCHG, &CMapDeluxeDlg::OnAccMapChg)
	ON_COMMAND(ID_NESTCHG, &CMapDeluxeDlg::OnAccNestChg)
	ON_CBN_SELCHANGE(IDC_COMBO_WIND, &CMapDeluxeDlg::OnCbnSelchangeComboWind)
	ON_BN_CLICKED(IDC_CHECK_NEST_AUTO, &CMapDeluxeDlg::OnBnClickedCheckNestAuto)
	ON_BN_CLICKED(IDC_CHECK_GRA_ASSOC, &CMapDeluxeDlg::OnBnClickedCheckGraAssoc)
	ON_CBN_SELCHANGE(IDC_COMBO_SCRIPT_ID, &CMapDeluxeDlg::OnCbnSelchangeComboScriptId)
END_MESSAGE_MAP()

//做一些实验用的函数
void cheatsDecryptGSACode(u32& address, u32& value, bool v3) 
{
  u32 rollingseed = 0xC6EF3720;
  u32 seeds_v1[] =  { 0x09F4FBBD, 0x9681884A, 0x352027E9, 0xF3DEE5A7 }; 
  u32 seeds_v3[] = { 0x7AA9648F, 0x7FAE6994, 0xC0EFAAD5, 0x42712C57 };
  u32 *seeds = v3 ? seeds_v3 : seeds_v1;
  
  int bitsleft = 32;
  while (bitsleft > 0) {
    value -= ((((address << 4) + seeds[2]) ^ (address + rollingseed)) ^
              ((address >> 5) + seeds[3]));
    address -= ((((value << 4) + seeds[0]) ^ (value + rollingseed)) ^
                ((value >> 5) + seeds[1]));
    rollingseed -= 0x9E3779B9;
    bitsleft--;
  }
}
void tst()
{
	/*CFile f(_T("D:\\Personal\\My Documents\\wwylele\\VC++编程\\DreamapDx\\MdxRomRebuild\\res\\RomRebuild_v3.gba"),CFile::modeRead);
	u8* pRomResource=new u8[0x1000000];//16MB//(u8*)mrrLockRomResource();
	f.Read(pRomResource,0x1000000);
	u8* tmp=new u8[0x800000];//8MB
	u32 clen;
	CFile of;
	clen=CompressLZ(pRomResource,0x800000,tmp);
	of.Open(_T("RomRebuild_A_LZ_v3.bin"),CFile::modeCreate|CFile::modeWrite);
	of.Write(tmp,clen);
	of.Close();
	clen=CompressLZ(pRomResource+0x800000,0x800000,tmp);
	of.Open(_T("RomRebuild_B_LZ_v3.bin"),CFile::modeCreate|CFile::modeWrite);
	of.Write(tmp,clen);
	of.Close();
	delete[] tmp;*/
	LoadGraAssocTable(0x123456);
}


//初始化窗口，初始化一切功能
BOOL CMapDeluxeDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	tst();

	mos_header=ros_header=0;//操作历史初始化

	
	hAccel=::LoadAccelerators(AfxGetInstanceHandle(),MAKEINTRESOURCE(ID_MENU_MAIN));

	//窗口标题
	CString str;
	CString strVer=GetProductVersion();
	TCHAR auth[]=_T("vuvh`f^");
	for(int i=0;i<7;i++)auth[i]+=i+1;
	str.Format(_T("MapDeluxe | 主程序版本:%s | RomRebuild版本:%d | 作者:%s"),
		(const TCHAR*)strVer,mrrGetRomVersion(),auth);
	SetWindowText(str);

	drawing=false;

	m_SetCursorResp=true;

	m_NuKirbyLeft=true;

	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标


	SetWindowLong(m_Progress.m_hWnd,GWL_STYLE,(~WS_VISIBLE)&GetWindowLong(m_Progress.m_hWnd,GWL_STYLE));

	m_StatusBar.Create(this);
	m_StatusBar.SetIndicators(StatusBar_indicators,
		sizeof(StatusBar_indicators)/sizeof(UINT));
	m_StatusBar.SetPaneInfo(0,ID_SEPARATOR,SBPS_NORMAL,700);
	m_StatusBar.SetPaneInfo(1,ID_SEPARATOR,SBPS_NORMAL,100);
	m_StatusBar.SetPaneText(0,_T("就绪"));
	m_StatusBar.SetPaneText(1,_T("MapDeluxe"));
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST,AFX_IDW_CONTROLBAR_LAST,ID_SEPARATOR);

	//ToolTip初始化
	//暂时用不上了
	m_ToolTip.Create(this,TTS_BALLOON);
	m_ToolTip.Activate(TRUE); 
	m_ToolTip.SetMaxTipWidth(400);
	m_ToolTip.SetDelayTime(TTDT_AUTOPOP,30000);
	//InitToolTipText();

	//清空ROM数据
	ZeroMemory(map,sizeof(GRID_DATA*)*2*STEP_INDEXING_COUNT);
	ZeroMemory(door,sizeof(DOOR_DATA*)*STEP_INDEXING_COUNT);
	ZeroMemory(obj,sizeof(OBJ_DATA*)*STEP_INDEXING_COUNT);
	ZeroMemory(wind,sizeof(OBJ_DATA)*STEP_INDEXING_COUNT);

	//初始化光标信息
	cur_step=0xFFFF;
	cur_x=cur_y=0xFFFF;
	cur_sel=0xFFFF;
	cur_chg=0;

	//为一些ComboBox加上项
	for(u32 i=0;i<256;i++)if(CodeTran_Bgm((u8)i))
	{
		str.Format(CODETRAN_FORMAT,i,CodeTran_Bgm((u8)i));
		m_ComboBgm.AddString(str);
	}
	for(u8 i=0;i<10;i++)if(CodeTran_SpcMap(i))
	{
		str.Format(CODETRAN_FORMAT,i,CodeTran_SpcMap(i));
		m_ComboSpcMap.AddString(str);
	}
	for(u8 i=0;i<16;i++)if(CodeTran_GraAni(i))
	{
		str.Format(CODETRAN_FORMAT,i,CodeTran_GraAni(i));
		m_ComboGraAni.AddString(str);
	}
	for(u8 i=0;i<8;i++)if(CodeTran_ScriptId(i))
	{
		str.Format(CODETRAN_FORMAT,i,CodeTran_ScriptId(i));
		m_ComboScriptId.AddString(str);
	}
	str.Format(CODETRAN_FORMAT_WIND,0xFFFF,0x00,_T("无"));m_ComboWind.AddString(str);
	str.Format(CODETRAN_FORMAT_WIND,0x0000,0x00,_T("空?"));m_ComboWind.AddString(str);
	str.Format(CODETRAN_FORMAT_WIND,0x0706,0x00,_T("全屏风↑"));m_ComboWind.AddString(str);
	str.Format(CODETRAN_FORMAT_WIND,0x0706,0x01,_T("全屏风↓"));m_ComboWind.AddString(str);
	str.Format(CODETRAN_FORMAT_WIND,0x0706,0x02,_T("全屏风←"));m_ComboWind.AddString(str);
	str.Format(CODETRAN_FORMAT_WIND,0x0706,0x03,_T("全屏风→"));m_ComboWind.AddString(str);
	str.Format(CODETRAN_FORMAT_WIND,0x0806,0x00,_T("加强局部风力"));m_ComboWind.AddString(str);
	

	//滚动条
	SCROLLINFO scrinfo={0};
	RECT scrrc;
	scrinfo.cbSize=sizeof(SCROLLINFO);
	scrinfo.fMask=SIF_PAGE;
	m_HScrollMap.GetWindowRect(&scrrc);
	scrinfo.nPage=scrrc.right-scrrc.left;
	m_HScrollMap.SetScrollInfo(&scrinfo);
	m_VScrollMap.GetWindowRect(&scrrc);
	scrinfo.nPage=scrrc.bottom-scrrc.top;
	m_VScrollMap.SetScrollInfo(&scrinfo);

	//初始化各种图形及绘图设备
	CDC* pDC=GetDC();
	m_TmpDC.CreateCompatibleDC(pDC);
	m_TmpDC2.CreateCompatibleDC(pDC);
	m_BmpMap.CreateCompatibleBitmap(pDC,1,1);//No use
	m_BmpGra.CreateCompatibleBitmap(pDC,1,1);//No use
	m_BmpGraOut.CreateCompatibleBitmap(pDC,1,1);//No use
	m_BmpGraMask.CreateCompatibleBitmap(pDC,1,1);//No use
	m_BmpObjTex.LoadBitmap(IDB_OBJ_TEX);
	BITMAP BmpObjTex;
	m_BmpObjTex.GetBitmap(&BmpObjTex);
	m_BmpObjTexMask.CreateCompatibleBitmap(pDC,BmpObjTex.bmWidth,BmpObjTex.bmHeight);

	m_TmpDC.SelectObject(&m_BmpObjTex);
	m_TmpDC2.SelectObject(&m_BmpObjTexMask);
	COLORREF cbck=m_TmpDC.GetPixel(0,0);
	for(int y=0;y<BmpObjTex.bmHeight;y++)for(int x=0;x<BmpObjTex.bmWidth;x++)
	{
		m_TmpDC2.SetPixel(x,y,m_TmpDC.GetPixel(x,y)==cbck?
			RGB(255,255,255):0);
	}

	m_BmpDet.LoadBitmap(IDB_DET);
	m_BmpDetOut.CreateCompatibleBitmap(pDC,256,256);
	m_BmpDetMask.CreateCompatibleBitmap(pDC,256,256);
	//m_BmpDetMask.CreateBitmap(
	m_TmpDC.SelectObject(&m_BmpDet);
	m_TmpDC2.SelectObject(&m_BmpDetMask);cbck=m_TmpDC.GetPixel(0,0);
	for(int y=0;y<256;y++)for(int x=0;x<256;x++)
	{
		m_TmpDC2.SetPixel(x,y,m_TmpDC.GetPixel(x,y)==cbck?
			RGB(255,255,255):0);
	}
	m_BmpNest.LoadBitmap(IDB_NEST);

	ReleaseDC(pDC);

	m_ComboMapChg.AddString(_T("贴图"));
	m_ComboMapChg.AddString(_T("判定"));
	m_ComboMapChg.SelectString(0,_T("贴图"));

	m_CheckNestAuto.SetCheck(GetPrivateProfileInt(_T("MAP"),_T("NestAuto"),1,ProfilePath)?TRUE:FALSE);

	m_EditEdg.SetWindowText(_T("0"));
	m_EditEdg.EnableWindow(FALSE);
	m_CheckEdg.EnableWindow(FALSE);

	m_CheckMapOutBck.SetCheck(GetPrivateProfileInt(_T("MAP"),_T("MapOutBck"),0,ProfilePath)?TRUE:FALSE);
	m_CheckGraAssoc.SetCheck(GetPrivateProfileInt(_T("MAP"),_T("GraAssoc"),1,ProfilePath)?TRUE:FALSE);

	//为菜单加上图标
	CMenu *pMenu=GetMenu();
	m_mBmpNew.LoadBitmap(IDB_M_NEW);
	pMenu->SetMenuItemBitmaps(ID_M_NEW,MF_BYCOMMAND,&m_mBmpNew,&m_mBmpNew);
	m_mBmpOpen.LoadBitmap(IDB_M_OPEN);
	pMenu->SetMenuItemBitmaps(ID_M_OPEN,MF_BYCOMMAND,&m_mBmpOpen,&m_mBmpOpen);
	m_mBmpSave.LoadBitmap(IDB_M_SAVE);
	pMenu->SetMenuItemBitmaps(ID_M_SAVE,MF_BYCOMMAND,&m_mBmpSave,&m_mBmpSave);
	m_mBmpSaveas.LoadBitmap(IDB_M_SAVEAS);
	pMenu->SetMenuItemBitmaps(ID_M_SAVEAS,MF_BYCOMMAND,&m_mBmpSaveas,&m_mBmpSaveas);
	m_mBmpSaveFinal.LoadBitmap(IDB_M_SAVE_FINAL);
	pMenu->SetMenuItemBitmaps(ID_M_SAVE_FINAL,MF_BYCOMMAND,&m_mBmpSaveFinal,&m_mBmpSaveFinal);
	m_mBmpGameTest.LoadBitmap(IDB_M_GAME_TEST);
	pMenu->SetMenuItemBitmaps(ID_M_GAME_TEST,MF_BYCOMMAND,&m_mBmpGameTest,&m_mBmpGameTest);
	m_mBmpRomImage.LoadBitmap(IDB_M_ROM_IMAGE);
	pMenu->SetMenuItemBitmaps(ID_M_ROM_IMAGE,MF_BYCOMMAND,&m_mBmpRomImage,&m_mBmpRomImage);
	m_mBmpAbout.LoadBitmap(IDB_M_ABOUT);
	pMenu->SetMenuItemBitmaps(ID_M_ABOUT,MF_BYCOMMAND,&m_mBmpAbout,&m_mBmpAbout);
	m_mBmpXzkbb.LoadBitmap(IDB_M_XZKBB);
	pMenu->SetMenuItemBitmaps(ID_M_XZKBB,MF_BYCOMMAND,&m_mBmpXzkbb,&m_mBmpXzkbb);
	m_mBmpUndo.LoadBitmap(IDB_M_UNDO);
	pMenu->SetMenuItemBitmaps(ID_M_UNDO,MF_BYCOMMAND,&m_mBmpUndo,&m_mBmpUndo);
	m_mBmpRedo.LoadBitmap(IDB_M_REDO);
	pMenu->SetMenuItemBitmaps(ID_M_REDO,MF_BYCOMMAND,&m_mBmpRedo,&m_mBmpRedo);
	m_mBmpResize.LoadBitmap(IDB_M_RESIZE);
	pMenu->SetMenuItemBitmaps(ID_M_RESIZE,MF_BYCOMMAND,&m_mBmpResize,&m_mBmpResize);
	m_mBmpDoor.LoadBitmap(IDB_M_DOOR);
	pMenu->SetMenuItemBitmaps(ID_M_DOOR,MF_BYCOMMAND,&m_mBmpDoor,&m_mBmpDoor);
	m_mBmpObj.LoadBitmap(IDB_M_OBJ);
	pMenu->SetMenuItemBitmaps(ID_M_OBJ,MF_BYCOMMAND,&m_mBmpObj,&m_mBmpObj);
	m_mBmpStepImport.LoadBitmap(IDB_M_STEP_IMPORT);
	pMenu->SetMenuItemBitmaps(ID_M_STEP_IMPORT,MF_BYCOMMAND,&m_mBmpStepImport,&m_mBmpStepImport);
	m_mBmpStepExport.LoadBitmap(IDB_M_STEP_EXPORT);
	pMenu->SetMenuItemBitmaps(ID_M_STEP_EXPORT,MF_BYCOMMAND,&m_mBmpStepExport,&m_mBmpStepExport);
	m_mBmpSaveTest.LoadBitmap(IDB_M_SAVETEST);
	pMenu->SetMenuItemBitmaps(ID_M_SAVE_TEST,MF_BYCOMMAND,&m_mBmpSaveTest,&m_mBmpSaveTest);

	m_BmpKirby.LoadBitmap(IDB_KIRBY);
	m_BrushKirby.CreatePatternBrush(&m_BmpKirby);

#ifdef _DEBUG
	OpenConsole();
	printf_debug("MAPDELUXE - Console\n");
#endif

	//尝试打开命令行文件
	//MessageBox(AfxGetApp()->m_lpCmdLine);
	CString strFileName=AfxGetApp()->m_lpCmdLine;
	strFileName.Replace(_T("\""),_T(""));
	CFile file;
	if(!file.Open(strFileName,CFile::modeReadWrite))
	{
		//MessageBox(_T("未能打开文件！此文件可能正在被其它程序使用！"),_T("错误"),MB_ICONERROR);
		return TRUE;
	}


#ifdef CHECK_ROM_MAGIC
	char MagicTmp[16];
	file.Seek(0x7FFFF0,CFile::begin);
	file.Read(MagicTmp,16);
	if(strcmp(MagicTmp,MagicStr)!=0)
	{
		//MessageBox(_T("所选文件非可解析的梦之泉ROM。\n请选择本程序创建的ROM！"),_T("错误"),MB_ICONERROR);
		file.Close();
		return TRUE;
	}
#endif

	ReadRom(file);

	m_EditFileName.SetWindowText(strFileName);

	//这之后不要再写别的初始化代码

	return TRUE;  
}

//清空ROM数据的函数
void CMapDeluxeDlg::ClearData()
{
	for(int index=0;index<STEP_INDEXING_COUNT;index++)
	{
		if(map[0][index])
		{
			delete[] (u8*)(map[0][index]);
			map[0][index]=0;
		}
		if(map[1][index])
		{
			delete[] map[1][index];
			map[1][index]=0;
		}
		if(door[index])
		{
			delete[] door[index];
			door[index]=0;
		}
		if(obj[index])
		{
			delete[] obj[index];
			obj[index]=0;
		}
		ZeroMemory(&wind[index],sizeof(OBJ_DATA));
	}
}
//这些没用了，已转移到MdxRomRebuild.dll
/*void CMapDeluxeDlg::LockRomResource()
{
	HRSRC hResInfo=FindResource(AfxGetApp()->m_hInstance,MAKEINTRESOURCE(IDR_ROM),_T("ROM")); 
	hRomResData=LoadResource(AfxGetApp()->m_hInstance,hResInfo);
	pRomRebuild=LockResource(hRomResData);
}
void CMapDeluxeDlg::UnlockRomResource()
{
	UnlockResource(hRomResData);
	FreeResource(hRomResData);
}*/

//WM_PAINT响应
void CMapDeluxeDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CPaintDC DC(this);
		PresentMap(&DC);
		PresentGraLib(&DC);
		DrawNuKirby(&DC);
		CDialog::OnPaint();
	}
}
void CMapDeluxeDlg::DrawNuKirby(CDC* pDC)
{
	int dx,dy;
	dx=NU_KIRBY_X-12;
	dy=NU_KIRBY_Y-12;
	pDC->SetBrushOrg(m_NuKirbyLeft?dx+24:dx,dy);
	pDC->FillRect((LPRECT)&CRect(dx,dy,
			dx+24,dy+24),&m_BrushKirby);
	pDC->SetBrushOrg(0,0);
}

HCURSOR CMapDeluxeDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//重载PreTranslateMessage用于显示ToolTip
BOOL CMapDeluxeDlg::PreTranslateMessage(MSG* pMsg)
{
	m_ToolTip.RelayEvent(pMsg);
	if(::TranslateAccelerator(GetSafeHwnd(),hAccel,pMsg))return true;

	return CDialog::PreTranslateMessage(pMsg);
}

//WM_DESTROY响应，退出时清空地图数据
void CMapDeluxeDlg::OnDestroy()
{
	CDialog::OnDestroy();
	ClearData();
	cur_step=0xFFFF;
	Mos_Clear();
	if(GraAssocLa)
	{
		delete[] GraAssocLa;
		GraAssocLa=0;
	}

}

//“打开”按钮响应
void CMapDeluxeDlg::OnBnClickedButtonOpen()
{
	TCHAR strPath[1000]={0};
	GetPrivateProfileString(_T("FILE"),_T("Path"),0,strPath,999,ProfilePath);

	//打开文件
	CFileDialog filedlg(TRUE,0,0,OFN_HIDEREADONLY,
		_T("梦之泉ROM|*.gba||"),this);
	filedlg.GetOFN().lpstrInitialDir=strPath;
	if(filedlg.DoModal()==IDCANCEL)return;
	CFile file;
	CString strFileName=filedlg.GetPathName();
	WritePrivateProfileString(_T("FILE"),_T("Path"),strFileName,ProfilePath);
	if(!file.Open(strFileName,CFile::modeReadWrite))
	{
		MessageBox(_T("未能打开文件！此文件可能正在被其它程序使用！"),_T("错误"),MB_ICONERROR);
		return;
	}


#ifdef CHECK_ROM_MAGIC
	char MagicTmp[16];
	file.Seek(0x7FFFF0,CFile::begin);
	file.Read(MagicTmp,16);
	if(strcmp(MagicTmp,MagicStr)!=0)
	{
		MessageBox(_T("所选文件非可解析的梦之泉ROM。\n请选择本程序创建的ROM！"),_T("错误"),MB_ICONERROR);
		file.Close();
		return;
	}
#endif

	ReadRom(file);

	m_EditFileName.SetWindowText(strFileName);
	
	file.Close();
}

//此函数用于将地图Header信息搬运到各种文本框列表框中
void CMapDeluxeDlg::StepHeaderOut()
{
	CString str;
	str.Format(_T("Level%d.Stage%d.Step%02d $0x%08X"),
		step_header[cur_step].level+1,
		step_header[cur_step].stage+1,
		step_header[cur_step].step,
		0x08800000+cur_step*0x4000);
	m_EditStepNumber.SetWindowText(str);

	m_CheckLz77.SetCheck(step_header[cur_step].lz77?TRUE:FALSE);

	str.Format(_T("%d"),step_header[cur_step].clip_x);
	m_EditClipX.SetWindowTextW(str);
	str.Format(_T("%d"),step_header[cur_step].clip_y);
	m_EditClipY.SetWindowTextW(str);

	str.Format(_T("%d"),step_header[cur_step].begin_x);
	m_EditBeginX.SetWindowTextW(str);
	str.Format(_T("%d"),step_header[cur_step].begin_y);
	m_EditBeginY.SetWindowTextW(str);

	str.Format(_T("%d"),step_header[cur_step].bck_mov);
	m_EditBckMov.SetWindowTextW(str);

	str.Format(_T("%d"),step_header[cur_step].bck_dy);
	m_EditX36.SetWindowTextW(str);

	//str.Format(_T("%d"),step_header[cur_step].x54);
	//m_EditX54.SetWindowTextW(str);

	m_CheckX55.SetCheck(step_header[cur_step].x55?TRUE:FALSE);
	m_CheckBckRoll.SetCheck(step_header[cur_step].bck_roll?TRUE:FALSE);

	if(step_header[cur_step].ptr_tile_frt<0x08800000)
	{
		str.Format(_T("调色板#%d"),
			CodeTran_FrtPlt(step_header[cur_step].ptr_tile_frt,step_header[cur_step].ptr_plt_frt));
		m_EditPltFrt.SetWindowText(str);

		m_EditTileFrt.SetWindowText(CodeTran_FrtGraLib(step_header[cur_step].ptr_tile_frt));
	}
	else
	{
		str.Format(_T("调色板#%d"),
			((step_header[cur_step].ptr_plt_frt-ROM_UGL_OFFSET)%UGL_LEN-UGL_PLTS_OFFSET)/UGL_PLTS_LEN);
		m_EditPltFrt.SetWindowText(str);
		str.Format(_T("[#%d]%s"),
			(step_header[cur_step].ptr_tile_frt-ROM_UGL_OFFSET)/UGL_LEN,
			ugl_rgn+ (step_header[cur_step].ptr_tile_frt-ROM_UGL_OFFSET) +UGL_TITLE_OFFSET );
		m_EditTileFrt.SetWindowText(str);
	}


	m_EditPltBck.SetWindowText(CodeTran_Bck(
		step_header[cur_step].ptr_plt_bck,
		step_header[cur_step].ptr_tile_bck,
		step_header[cur_step].ptr_gra_map_bck));

	str.Format(CODETRAN_FORMAT,step_header[cur_step].gra_ani_index,CodeTran_GraAni(step_header[cur_step].gra_ani_index));
	m_ComboGraAni.SelectString(0,str);

	str.Format(CODETRAN_FORMAT,step_header[cur_step].bgm,CodeTran_Bgm(step_header[cur_step].bgm));
	m_ComboBgm.SelectString(0,str);

	str.Format(CODETRAN_FORMAT,step_header[cur_step].spc_map,CodeTran_SpcMap(step_header[cur_step].spc_map));
	m_ComboSpcMap.SelectString(0,str);

	str.Format(CODETRAN_FORMAT,step_header[cur_step].script_id,CodeTran_ScriptId(step_header[cur_step].script_id));
	m_ComboScriptId.SelectString(0,str);

	if(wind[cur_step].class_id!=0x0706)wind[cur_step].paramA=0;
	str.Format(CODETRAN_FORMAT_WIND,wind[cur_step].class_id,wind[cur_step].paramA,_T(""));
	m_ComboWind.SelectString(0,str);
}

//此函数用于文本转换为整数
u32 CMapDeluxeDlg::StrToI(CString &str)
{
	u32 s;
	try{
		int x=str.Find(_T(":"));
		if(x!=-1)
		{
			str=str.Left(x);
		}
		x=str.Find(_T("0x"));
		if(x==-1)
		{
			//return _ttoi(str);
			_stscanf_s(str,_T("%u"),&s);
		}
		else
		{
			_stscanf_s(str,_T("0x%x"),&s);
		}
	}catch(...){
		s=0;
	}
	return s;
	
}

//从游戏中加载当前地图的贴图库，渲染到当前贴图库
void CMapDeluxeDlg::LoadGraLib()
{
	if(cur_step==0xFFFF)return;

	m_SetCursorResp=false;
	m_StatusBar.SetPaneText(0,_T("加载地图..."));
	


	void* pRomRebuild=mrrLockRomResource();

	//读取调色板
	u16* plt;
	if(step_header[cur_step].ptr_plt_frt<ROM_UGL_OFFSET)
		plt=(u16*)((u8*)pRomRebuild+(step_header[cur_step].ptr_plt_frt-0x08000000));
	else
		plt=(u16*)(ugl_rgn+(step_header[cur_step].ptr_plt_frt-ROM_UGL_OFFSET));
	if(*plt==0)
	{
		gralib_len=0;
		m_SetCursorResp=true;
		m_StatusBar.SetPaneText(0,_T("就绪"));
		return;
	}
	plt++;
	

	//读取瓦图
	u8* ptiledata;
	if(step_header[cur_step].ptr_tile_frt<ROM_UGL_OFFSET)
		ptiledata=(u8*)pRomRebuild+(step_header[cur_step].ptr_tile_frt-0x08000000);
	else
		ptiledata=ugl_rgn+(step_header[cur_step].ptr_tile_frt-ROM_UGL_OFFSET);
	u32 lz77len;
	lz77len=*(u32*)(ptiledata);
	if(lz77len==0)
	{
		gralib_len=0;
		m_SetCursorResp=true;
		m_StatusBar.SetPaneText(0,_T("就绪"));
		return;
	}
	lz77len>>=8;
	u8* tile_lz=new u8[lz77len+0x100];
	u32 tile_count=lz77len/sizeof(TILE);
	TILE *tile=(TILE *)tile_lz;
	AgbUncompressLZ(ptiledata,tile_lz);

	//读取映射
	u8 *pgmapdata;
	if(step_header[cur_step].ptr_gra_map_frt<ROM_UGL_OFFSET)
		pgmapdata=(u8*)pRomRebuild+(step_header[cur_step].ptr_gra_map_frt-0x08000000);
	else
		pgmapdata=ugl_rgn+(step_header[cur_step].ptr_gra_map_frt-ROM_UGL_OFFSET);
	lz77len=*(u32*)(pgmapdata);
	if(lz77len==0)
	{
		delete[] tile_lz;
		gralib_len=0;
		m_SetCursorResp=true;
		m_StatusBar.SetPaneText(0,_T("就绪"));
		return;
	}
	lz77len>>=8;
	u32 liblen=lz77len/8;
	u8* gmap_lz=new u8[lz77len+0x100];
	BLOCK_MAPPING* pMapping=(BLOCK_MAPPING*)gmap_lz;
	AgbUncompressLZ(pgmapdata,gmap_lz);

	m_Progress.SetRange(0,(short)(liblen-1));
	SetWindowLong(m_Progress.m_hWnd,GWL_STYLE,WS_VISIBLE|GetWindowLong(m_Progress.m_hWnd,GWL_STYLE));

	//渲染
	CDC *pDC=GetDC(); 
	m_BmpGra.DeleteObject();
	m_BmpGraOut.DeleteObject();
	m_BmpGraMask.DeleteObject();
	//m_BmpGra.CreateCompatibleBitmap(pDC,liblen*16,16);
	m_BmpGra.CreateCompatibleBitmap(pDC,256,(liblen/16+1)*16);
	m_BmpGraOut.CreateCompatibleBitmap(pDC,256,(liblen/16+1)*16);
	m_BmpGraMask.CreateCompatibleBitmap(pDC,256,(liblen/16+1)*16);
	u16 submapping;
	bool flipx,flipy;
	u8 pltcls;
	u8 pltidx;
	u32 drx,dry;
	for(u32 i=0;i<liblen;i++)
	{
		for(int subb=0;subb<4;subb++)
		{
			submapping=pMapping[i].mapping[subb]&0x3FF;
			if(submapping>=tile_count){
				//不存在对应的tile?!那就画上血红色~~~
				for(int by=0;by<8;by++)for(int bx=0;bx<8;bx++)
				{
					drx=(i%16)*16+(subb%2)*8+bx;
					dry=(i/16)*16+(subb/2)*8+by;

					m_TmpDC2.SelectObject(&m_BmpGra);
					if(bx==by || bx+by==7)
						m_TmpDC2.SetPixel(drx,dry,RGB(255,255,0));
					else
						m_TmpDC2.SetPixel(drx,dry,RGB(255,0,0));
					m_TmpDC2.SelectObject(&m_BmpGraMask);
					m_TmpDC2.SetPixel(drx,dry,RGB(0,0,0));
				}
			}
			else{
				//有对应的tile，真乖~~~
				flipx=pMapping[i].mapping[subb]&1024 ? true:false;
				flipy=pMapping[i].mapping[subb]&2048 ? true:false;
				pltcls=pMapping[i].mapping[subb]>>12;
				
				for(int by=0;by<8;by++)for(int bx=0;bx<8;bx++)
				{
					pltidx=tile[submapping].Get(flipx?7-bx:bx,flipy?7-by:by);
					drx=(i%16)*16+(subb%2)*8+bx;
					dry=(i/16)*16+(subb/2)*8+by;
					if(pltidx!=0){//非透明色
						m_TmpDC2.SelectObject(&m_BmpGra);
						if(pltcls>=8)
						{
							//纳尼?!竟然有用到奇怪的调色板?!那还是画上血红色~~~
							m_TmpDC2.SetPixel(drx,dry,RGB(255,0,0));
						}
						else m_TmpDC2.SetPixel(drx,dry,
								R5G5B5X1toR8G8B8X8(plt[(pltcls-2)*16+(pltidx)])
								);
						m_TmpDC2.SelectObject(&m_BmpGraMask);
						m_TmpDC2.SetPixel(drx,dry,RGB(0,0,0));
					}
					else
					{//透明色
						m_TmpDC2.SelectObject(&m_BmpGra);
						m_TmpDC2.SetPixel(drx,dry,
							(drx&4) ^ (dry&4) ? RGB(250,250,250):RGB(255,255,255)
							);
						m_TmpDC2.SelectObject(&m_BmpGraMask);
						m_TmpDC2.SetPixel(drx,dry,RGB(255,255,255));
					}
				}
			}
		}
		if(!(i&0x3F))
		{
			m_Progress.SetPos(i);
			UpdateData(FALSE);
		}
	}



	delete[] tile_lz;
	delete[] gmap_lz;
	mrrUnlockRomResource();

	gralib_len=liblen;
	
	ReleaseDC(pDC);

	LoadGraAssocTable(step_header[cur_step].ptr_gra_map_frt);

	m_Progress.SetPos(0);
	UpdateData(FALSE);
	m_SetCursorResp=true;
	SetWindowLong(m_Progress.m_hWnd,GWL_STYLE,(~WS_VISIBLE)&GetWindowLong(m_Progress.m_hWnd,GWL_STYLE));
	m_StatusBar.RedrawWindow();
	m_StatusBar.SetPaneText(0,_T("就绪"));

}
//响应树状图双击，同时充当重新加载地图函数（此时pNMHDR==pResult==0）
void CMapDeluxeDlg::OnNMDblclkTreeFile(NMHDR *pNMHDR, LRESULT *pResult)
{
	HTREEITEM tic=m_Tree.GetSelectedItem();
	CString str;
	for(int i=0;i<STEP_INDEXING_COUNT;i++)
	{
		if(ti_step[i]==tic || pNMHDR==0)
		{
			//将所选地图的各种信息搬运到当前地图上

			if(pNMHDR)cur_step=i;else i=cur_step;
			Mos_Clear();
			StepHeaderOut();

			LoadGraLib();

			//设置滚动条
			RECT hsrc,vsrc;
			int hsrg,vsrg;
			m_HScrollMap.GetWindowRect(&hsrc);
			m_VScrollMap.GetWindowRect(&vsrc);
			hsrg=step_header[i].width*16-(hsrc.right-hsrc.left);
			if(hsrg<1)hsrg=1;
			vsrg=step_header[i].height*16-(vsrc.bottom-vsrc.top);
			if(vsrg<1)vsrg=1;
			SCROLLINFO scrinfo={0};
			scrinfo.cbSize=sizeof(SCROLLINFO);
			scrinfo.fMask=SIF_PAGE|SIF_RANGE|SIF_POS;
			scrinfo.nPage=hsrc.right-hsrc.left;
			scrinfo.nMin=0;scrinfo.nMax=hsrg-1+scrinfo.nPage-1;
			scrinfo.nPos=0;
			m_HScrollMap.SetScrollInfo(&scrinfo);
			scrinfo.nPage=vsrc.bottom-vsrc.top;
			scrinfo.nMin=0;scrinfo.nMax=vsrg-1+scrinfo.nPage-1;
			scrinfo.nPos=0;
			m_VScrollMap.SetScrollInfo(&scrinfo);

			ResetGraLibScrollBar();
			cur_chg=0;

			CDC* pDC=GetDC();
			m_BmpMap.DeleteObject();
			m_BmpMap.CreateCompatibleBitmap(pDC,step_header[i].width*16,step_header[i].height*16);
			m_TmpDC.SelectObject(&m_BmpMap);
			ScreenToClient(&hsrc);
			ScreenToClient(&vsrc);
			pDC->FillRect((RECT*)&CRect(hsrc.left,vsrc.top,hsrc.right,vsrc.bottom),&CBrush(RGB(0,0,0)));
			PaintMap();
			PaintGraLib();
			PresentMap(pDC);
			PresentGraLib(pDC);
			ReleaseDC(pDC);


			if(pResult)*pResult=0;
			return;
		}
	}
	if(pNMHDR)for(int i=0;i<UGL_COUNT;i++)
	{
		if(tic==ti_ugl[i])
		{
			OnUglEdit(i);
			return;
		}
	}

	if(pResult)*pResult = 0;
}
void CMapDeluxeDlg::OnUglEdit(int ugl_index)
{
	CDlgUgl* pDlg=new CDlgUgl;//之所以要申请堆内存是因为它……太大了

	void* pRomRebuild=mrrLockRomResource();

	//读取标题
	memcpy(pDlg->m_UglIO.title,ugl_rgn +UGL_LEN*ugl_index +UGL_TITLE_OFFSET,32);

	//读取调色板
	for(int pltpln=0;pltpln<16;pltpln++)
	{
		pDlg->m_UglIO.plt_p[pltpln].plt_count=
			*(u16*)(ugl_rgn +UGL_LEN*ugl_index +UGL_PLTS_OFFSET +UGL_PLTS_LEN*pltpln);
		if(pDlg->m_UglIO.plt_p[pltpln].plt_count==0)pDlg->m_UglIO.plt_p[pltpln].plt_count=0x100;
		memcpy(pDlg->m_UglIO.plt_p[pltpln].plt,
			ugl_rgn +UGL_LEN*ugl_index +UGL_PLTS_OFFSET +UGL_PLTS_LEN*pltpln+2,0x100);
		//if(gra_lib_frt_desc[12].ptr_plt[pltpln])memcpy(pDlg->m_UglIO.plt_p[pltpln].plt,////////////////
		//	(u8*)pRomRebuild+(gra_lib_frt_desc[12].ptr_plt[pltpln]-0x08000000)+2,0x100);////////////////
		
	}
	//读取瓦图
	u8* ptiledata;
	ptiledata=ugl_rgn +UGL_LEN*ugl_index +UGL_TILE_OFFSET;
	//ptiledata=(u8*)pRomRebuild+0x0047FC00;////////////////
	u32 lz77len;
	lz77len=*(u32*)(ptiledata);
	if(lz77len==0)
	{
		pDlg->m_UglIO.tile_count=0;
	}
	else
	{
		lz77len>>=8;
		pDlg->m_UglIO.tile_count=(u16)(lz77len/sizeof(TILE));
		if(pDlg->m_UglIO.tile_count>512)throw;
		AgbUncompressLZ(ptiledata,(u8*)pDlg->m_UglIO.tile);
	}
	//读取映射
	u8* pmapdata;
	pmapdata=ugl_rgn +UGL_LEN*ugl_index +UGL_GMAP_OFFSET;
	//pmapdata=(u8*)pRomRebuild+0x003FE80C;////////////////
	lz77len=*(u32*)(pmapdata);
	if(lz77len==0)
	{
		pDlg->m_UglIO.gmap_count=0;
	}
	else
	{
		lz77len>>=8;
		pDlg->m_UglIO.gmap_count=(u16)(lz77len/sizeof(BLOCK_MAPPING));
		if(pDlg->m_UglIO.gmap_count>884)throw;
		AgbUncompressLZ(pmapdata,(u8*)pDlg->m_UglIO.gmap);
	}

	mrrUnlockRomResource();


	if(pDlg->DoModal()==IDOK)
	{
		//写入标题
		memcpy(ugl_rgn +UGL_LEN*ugl_index +UGL_TITLE_OFFSET,pDlg->m_UglIO.title,32);
		CString str;
		str.Format(_T("[#%d]%s"),ugl_index,(TCHAR*)(ugl_rgn +UGL_LEN*ugl_index +UGL_TITLE_OFFSET));
		m_Tree.SetItemText(ti_ugl[ugl_index],str);

		//写入调色板
		for(int pltpln=0;pltpln<16;pltpln++)
		{
			*(u16*)(ugl_rgn +UGL_LEN*ugl_index +UGL_PLTS_OFFSET +UGL_PLTS_LEN*pltpln)=
				pDlg->m_UglIO.plt_p[pltpln].plt_count;
			memcpy(ugl_rgn +UGL_LEN*ugl_index +UGL_PLTS_OFFSET +UGL_PLTS_LEN*pltpln+2,
				pDlg->m_UglIO.plt_p[pltpln].plt,0x100);
			
		}

		//写入瓦图
		AgbCompressLZ((const u8*)pDlg->m_UglIO.tile,pDlg->m_UglIO.tile_count*sizeof(TILE),
			ugl_rgn +UGL_LEN*ugl_index +UGL_TILE_OFFSET);

		//写入映射
		AgbCompressLZ((const u8*)pDlg->m_UglIO.gmap,pDlg->m_UglIO.gmap_count*sizeof(BLOCK_MAPPING),
			ugl_rgn +UGL_LEN*ugl_index +UGL_GMAP_OFFSET);


		if(cur_step!=0xFFFF && 
			step_header[cur_step].ptr_gra_map_frt==ROM_UGL_OFFSET + UGL_LEN*ugl_index +UGL_GMAP_OFFSET)
			OnNMDblclkTreeFile(0,0);
	}
	delete pDlg;
}
//偷懒了，以后再写
/*void CMapDeluxeDlg::PaintMapGrid(u16 x,u16 y)
{
}*/
//渲染地图的函数（仅向内存渲染，不呈现）
void CMapDeluxeDlg::PaintMap(u16 qqx,u16 qqy)
{
	if(cur_step==0xFFFF)return;

	int nestm=m_CheckNest.GetCheck()?2:1;

	static CPen PenCur(PS_SOLID,1,RGB(255,0,0));
	CBrush BrushNull;
	BrushNull.CreateStockObject(NULL_BRUSH);

	m_TmpDC.SelectObject(&m_BmpMap);

	u16 v;

	CString str;
	u16 xbegin=qqx==0xFFFF?0:qqx;
	u16 xend=qqx==0xFFFF?step_header[cur_step].width:qqx+1;
	u16 ybegin=qqy==0xFFFF?0:qqy;
	u16 yend=qqy==0xFFFF?step_header[cur_step].height:qqy+1;
	m_ComboMapChg.GetWindowText(str);
	bool drawdet=m_ComboMapChg.FindString(-1,str)==1;
	bool drawbck=m_CheckMapOutBck.GetCheck()?true:false;
	//三层循环依次是——[主地图/掀开地图][遍历纵格][遍历横格]
	for(int nest=0;nest<nestm;nest++)for(u16 y=ybegin;y<yend;y++)for(u16 x=xbegin;x<xend;x++)
	{
		if(*(u32*)&map[nest][cur_step][x+y*step_header[cur_step].width]!=0xFFFFFFFF)
		{
			//如果此格不为无效，就绘制出图形
			//此判断仅针对于掀开地图，因为主地图不存在无效的格

			//无透明贴图
			if((drawdet && drawbck) || (!drawdet && !drawbck))
			{
				m_TmpDC2.SelectObject(&m_BmpGra);
				v=map[nest][cur_step][x+y*step_header[cur_step].width].gra;
				if(v<gralib_len)
					m_TmpDC.BitBlt(x*16,y*16,16,16,&m_TmpDC2,(v&0xF)*16,(v>>4)*16,SRCCOPY);
				else
					//贴图编号竟然越界了?!
					m_TmpDC.FillRect((RECT*)&CRect(x*16,y*16,x*16+16,y*16+16),
						&CBrush(RGB(255,255,0)));
			}
			//透明判定图
			if(drawdet && drawbck)
			{
				//画上判定
				//下面的一串代码就是为了让判定图的一些地方透明
				v=map[nest][cur_step][x+y*step_header[cur_step].width].det;
				m_TmpDC2.SelectObject(&m_BmpDet);
				m_TmpDC.BitBlt(x*16,y*16,16,16,&m_TmpDC2,(v&0xF)*16,(v>>4)*16,SRCINVERT);
				m_TmpDC2.SelectObject(&m_BmpDetMask);
				m_TmpDC.BitBlt(x*16,y*16,16,16,&m_TmpDC2,(v&0xF)*16,(v>>4)*16,SRCAND);
				m_TmpDC2.SelectObject(&m_BmpDet);
				m_TmpDC.BitBlt(x*16,y*16,16,16,&m_TmpDC2,(v&0xF)*16,(v>>4)*16,SRCINVERT);

				//画上未知值“Edg”
				v=map[nest][cur_step][x+y*step_header[cur_step].width].edg;
				for(int biti=0;biti<8;biti++)
				{
					if((v>>biti)&1)
						for(int sx=1;sx<3;sx++)for(int sy=0;sy<2;sy++)
							m_TmpDC.SetPixel(x*16+biti*2+sx,y*16+8+sy,BitColor[biti]);
				}
			}

			
			//不透明判定图
			if((!drawdet && drawbck) || (drawdet && !drawbck))
			{
				v=map[nest][cur_step][x+y*step_header[cur_step].width].det;
				m_TmpDC2.SelectObject(&m_BmpDet);
				m_TmpDC.BitBlt(x*16,y*16,16,16,&m_TmpDC2,(v&0xF)*16,(v>>4)*16,SRCCOPY);
			}
			//透明贴图
			if(!drawdet && drawbck)
			{
				v=map[nest][cur_step][x+y*step_header[cur_step].width].gra;
				if(v<gralib_len)
				{
					//下面的一串代码就是为了让贴图图的一些地方透明
					m_TmpDC2.SelectObject(&m_BmpGra);
					m_TmpDC.BitBlt(x*16,y*16,16,16,&m_TmpDC2,(v&0xF)*16,(v>>4)*16,SRCINVERT);
					m_TmpDC2.SelectObject(&m_BmpGraMask);
					m_TmpDC.BitBlt(x*16,y*16,16,16,&m_TmpDC2,(v&0xF)*16,(v>>4)*16,SRCAND);
					m_TmpDC2.SelectObject(&m_BmpGra);
					m_TmpDC.BitBlt(x*16,y*16,16,16,&m_TmpDC2,(v&0xF)*16,(v>>4)*16,SRCINVERT);
				}
				else
				{
					m_TmpDC2.SelectObject(&m_BmpGra);
					//贴图编号竟然越界了?!
					m_TmpDC.FillRect((RECT*)&CRect(x*16,y*16,x*16+16,y*16+16),
						&CBrush(RGB(255,255,0)));
				}
			}

		}
		else
		{
			//对于掀开地图的无效的格，就画上网状线标识
			m_TmpDC2.SelectObject(&m_BmpNest);
			m_TmpDC.BitBlt(x*16,y*16,16,16,&m_TmpDC2,0,0,SRCAND);
		}
	}
	//如果有光标，就画上
	if(cur_x!=0xFFFF)
	{
		m_TmpDC.SelectObject(&BrushNull);
		m_TmpDC.SelectObject(&PenCur);
		m_TmpDC.Rectangle(cur_x*16,cur_y*16,cur_x*16+16,cur_y*16+16);
		
	}
}

//将内存中渲染好的地图呈现
void CMapDeluxeDlg::PresentMap(CDC* pDC)
{
	if(cur_step==0xFFFF)return;
	m_TmpDC.SelectObject(&m_BmpMap);
	//根据滚动条的位置计算呈现位置
	RECT hsrc,vsrc;
	int hsp=m_HScrollMap.GetScrollPos();
	int vsp=m_VScrollMap.GetScrollPos();
	m_HScrollMap.GetWindowRect(&hsrc);
	m_VScrollMap.GetWindowRect(&vsrc);
	ScreenToClient(&hsrc);
	ScreenToClient(&vsrc);
	pDC->BitBlt(hsrc.left,vsrc.top,
		hsrc.right-hsrc.left,vsrc.bottom-vsrc.top,&m_TmpDC,
		hsp,vsp,SRCCOPY);
}
//滚动条响应
void CMapDeluxeDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	int minpos;
   int maxpos;
   pScrollBar->GetScrollRange(&minpos, &maxpos); 
   maxpos = pScrollBar->GetScrollLimit();
   int curpos = pScrollBar->GetScrollPos();
   switch (nSBCode)
   {
   case SB_LEFT:curpos = minpos;break;
   case SB_RIGHT:curpos = maxpos;break;
   case SB_LINELEFT:
      if (curpos > minpos)
         curpos--;
      break;
   case SB_LINERIGHT:
      if (curpos < maxpos)
         curpos++;
      break;
   case SB_PAGELEFT:
   {
      SCROLLINFO   info;
      pScrollBar->GetScrollInfo(&info, SIF_ALL);
      if (curpos > minpos)
      curpos = max(minpos, curpos - (int) info.nPage);
   }
      break;
   case SB_PAGERIGHT:
   {
      SCROLLINFO   info;
      pScrollBar->GetScrollInfo(&info, SIF_ALL);
      if (curpos < maxpos)
         curpos = min(maxpos, curpos + (int) info.nPage);
   }
      break;
   case SB_THUMBPOSITION: 
      curpos = nPos;     
      break;
   case SB_THUMBTRACK:   
      curpos = nPos;     
      break;
   }
   pScrollBar->SetScrollPos(curpos);

	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);

	//PaintMap();
	CDC* pDC=GetDC();
	PresentMap(pDC);
	ReleaseDC(pDC);
}

void CMapDeluxeDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	int minpos;
   int maxpos;
   pScrollBar->GetScrollRange(&minpos, &maxpos); 
   maxpos = pScrollBar->GetScrollLimit();
   int curpos = pScrollBar->GetScrollPos();
   switch (nSBCode)
   {
   case SB_TOP:      
      curpos = minpos;
      break;
   case SB_BOTTOM:    
      curpos = maxpos;
      break;
   case SB_LINEUP:     
      if (curpos > minpos)
         curpos--;
      break;
   case SB_LINEDOWN:
      if (curpos < maxpos)
         curpos++;
      break;
   case SB_PAGEUP: 
   {
      SCROLLINFO   info;
      pScrollBar->GetScrollInfo(&info, SIF_ALL);
      if (curpos > minpos)
      curpos = max(minpos, curpos - (int) info.nPage);
   }
      break;
   case SB_PAGEDOWN: 
   {
      SCROLLINFO   info;
      pScrollBar->GetScrollInfo(&info, SIF_ALL);

      if (curpos < maxpos)
         curpos = min(maxpos, curpos + (int) info.nPage);
   }
      break;
   case SB_THUMBPOSITION: 
      curpos = nPos;
      break;
   case SB_THUMBTRACK:  
      curpos = nPos;
      break;
   }
   pScrollBar->SetScrollPos(curpos);

	CDialog::OnVScroll(nSBCode, nPos, pScrollBar);
	//PaintMap();
	PaintGraLib();
	CDC* pDC=GetDC();
	PresentMap(pDC);
	PresentGraLib(pDC);
	ReleaseDC(pDC);
}
//解码ROM数据至程序
void CMapDeluxeDlg::ReadRom(CFile& file)
{
	m_SetCursorResp=false;
	m_StatusBar.SetPaneText(0,_T("读取游戏..."));

	ClearData();
	cur_step=0xFFFF;
	CString str;
	m_Tree.DeleteAllItems();
	ti_rom=m_Tree.InsertItem(_T("地图"));
	for(u32 level=0;level<8;level++)
	{
		str.Format(_T("Level%d"),level+1);
		ti_level[level]=m_Tree.InsertItem(str,ti_rom);
	}
	
	ZeroMemory(ti_stage,sizeof(HTREEITEM)*8*8);

	printf_debug("ReadRom:\n");

	u32 lz77len;
	u8* lz77psrc;
	u8* lz77pdst;

	/*struct IMAGE_LIB_INFO{
		u32 ptr_plt_frt;
		u32 ptr_tile_frt;
		u32 ptr_gra_map_frt;
	}ilit;
	std::vector<IMAGE_LIB_INFO> ilil;
	bool ilib,iliq;*/
	for(int index=0;index<STEP_INDEXING_COUNT;index++)
	{
		//Header
		file.Seek(0x00800000+index*0x4000,CFile::begin);
		file.Read(&step_header[index],sizeof(STEP_HEADER));

		/*//图形库测试
		u16 pltlen;
		u32 tilelen,gmlen;
		file.Seek(step_header[index].ptr_plt_frt-0x08000000,CFile::begin);
		file.Read(&pltlen,2);
		file.Seek(step_header[index].ptr_tile_frt-0x08000000,CFile::begin);
		file.Read(&tilelen,4);
		tilelen>>=8;
		file.Seek(step_header[index].ptr_gra_map_frt-0x08000000,CFile::begin);
		file.Read(&gmlen,4);
		gmlen>>=8;
		printf_debug(
			"[%d-%d-%02d]%4X%8X%8X\n",
				step_header[index].level+1,
				step_header[index].stage+1,step_header[index].step,
				pltlen,tilelen,gmlen
				);*/


		/*ilit.ptr_plt_frt=step_header[index].ptr_plt_bck;
		ilit.ptr_tile_frt=step_header[index].ptr_tile_bck;
		ilit.ptr_gra_map_frt=step_header[index].ptr_gra_map_bck;

		ilib=false;
		iliq=false;
		
		for(u32 q=0;q<ilil.size();q++)
		{
			if(ilil[q].ptr_plt_frt==ilit.ptr_plt_frt &&
				ilil[q].ptr_tile_frt==ilit.ptr_tile_frt &&
				ilil[q].ptr_gra_map_frt==ilit.ptr_gra_map_frt
				//ilil[q].gra_ani_index==ilit.gra_ani_index
				)
			{
				ilib=true;
				break;
			}
			if(ilil[q].ptr_plt_frt==ilit.ptr_plt_frt ||
				ilil[q].ptr_tile_frt==ilit.ptr_tile_frt ||
				ilil[q].ptr_gra_map_frt==ilit.ptr_gra_map_frt //&&
				//ilil[q].gra_ani_index==ilit.gra_ani_index
				)
			{
				iliq=true;
			}
		}
		if(!ilib)
		{
			ilil.push_back(ilit);
			printf_debug(
				"[%d-%d-%02d]"
				"%08X\t%08X\t%08X"
				//" %08X "
				"%c"
				"\n",
				step_header[index].level+1,
				step_header[index].stage+1,step_header[index].step,
				ilit.ptr_plt_frt,
				ilit.ptr_tile_frt,
				ilit.ptr_gra_map_frt,
				//,ilit.gra_ani_index,
				iliq?'!':' '
				);
		}*/
		

		//顺便更新一下树状图
		if(ti_stage[step_header[index].level][step_header[index].stage]==0)
		{
			str.Format(_T("Stage%d"),step_header[index].stage+1);
			ti_stage[step_header[index].level][step_header[index].stage]=
				m_Tree.InsertItem(str,ti_level[step_header[index].level]);
		}
		str.Format(_T("Step%02d"),step_header[index].step);
		ti_step[index]=m_Tree.InsertItem(str,
			ti_stage[step_header[index].level][step_header[index].stage]);

		//主地图
		file.Seek(0x00800000+index*0x4000+0x00001000,CFile::begin);
		file.Read(&lz77len,4);
		lz77len>>=8;
		file.Seek(-4,CFile::current);
		lz77psrc=new u8[lz77len];
		lz77pdst=new u8[lz77len+0x100];
		file.Read(lz77psrc,lz77len);
		AgbUncompressLZ(lz77psrc,lz77pdst);
		delete[]lz77psrc;
		map[0][index]=(GRID_DATA*)lz77pdst;

		//嵌套地图
		file.Seek(0x00800000+index*0x4000+0x00002000,CFile::begin);
		file.Read(&lz77len,4);
		lz77len>>=8;
		file.Seek(-4,CFile::current);
		lz77psrc=new u8[lz77len];
		lz77pdst=new u8[lz77len+0x100];
		file.Read(lz77psrc,lz77len);
		AgbUncompressLZ(lz77psrc,lz77pdst);
		delete[]lz77psrc;
		map[1][index]=new GRID_DATA[step_header[index].width*step_header[index].height];
		u16* pnest=(u16*)lz77pdst;
		for(s32 k=0;k<step_header[index].width*step_header[index].height;k++)
		{
			if(pnest[k]==0)
			{
				*(u32*)&map[1][index][k]=0xFFFFFFFF;
			}
			else
			{
				file.Seek(0x00800000+index*0x4000+0x00003000+pnest[k]*4,CFile::begin);
				file.Read(&map[1][index][k],4);
			}
		}
		delete[]lz77pdst;

		//门
		if(step_header[index].door_count)
		{
			file.Seek(0x00800000+index*0x4000+0x00000100,CFile::begin);
			door[index]=new DOOR_DATA[step_header[index].door_count];
			file.Read(door[index],step_header[index].door_count*sizeof(DOOR_DATA));
		}

		//OBJ
		if(step_header[index].obj_count)
		{
			file.Seek(0x00800000+index*0x4000+0x00000800,CFile::begin);
			obj[index]=new OBJ_DATA_EX[step_header[index].obj_count];
			for(u16 i=0;i<step_header[index].obj_count;i++)
			{
				file.Read(&obj[index][i].o[0],sizeof(OBJ_DATA));
			}
			for(u16 i=0;i<step_header[index].obj_count;i++)
			{
				if(obj[index][i].o[0].class_id==0x0006)
				{
					//printf_debug("---\n");
					obj[index][i].is_folder=1;
					obj[index][i].len=obj[index][i].o[0].paramB;
					obj[index][i].fx=obj[index][i].o[0].x;
					obj[index][i].fy=obj[index][i].o[0].y;
					if(obj[index][i].len>3)throw;
					file.Seek(0x00800000+index*0x4000+0x00000800+
						obj[index][i].o[0].paramA*sizeof(OBJ_DATA),CFile::begin);
					for(u8 j=0;j<obj[index][i].len;j++)
					{
						file.Read(&obj[index][i].o[j],sizeof(OBJ_DATA));
					}
				}
				else
				{
					obj[index][i].is_folder=0;
					obj[index][i].len=0;
				}
			}
		}
		//风
		if(step_header[index].wind_index==0xFFFF)
		{
			wind[index].class_id=0xFFFF;
		}
		else
		{
			file.Seek(0x00800000+index*0x4000+0x00000800+
				step_header[index].wind_index*sizeof(OBJ_DATA),CFile::begin);
			file.Read(&wind[index],sizeof(OBJ_DATA));
			
		}

	}

	//起始页
	file.Seek(ROM_IMAGE_CMD_OFFSET,CFile::begin);
	u32 firstcmd;
	file.Read(&firstcmd,4);
	use_rom_image=(firstcmd==0xEA1FFFAD);
	file.Seek(ROM_IMAGE_OFFSET,CFile::begin);
	file.Read(rom_image,sizeof(u16)*160*240);

	//附加信息
	file.Seek(ROM_MDXINFO_OFFSET,CFile::begin);
	file.Read(&rom_mdxinfo,sizeof(ROM_MDXINFO));

	//UGL（自定义贴图库）
	file.Seek(ROM_UGL_OFFSET-0x08000000,CFile::begin);
	file.Read(ugl_rgn,UGL_COUNT*UGL_LEN);

	ti_ugl_head=m_Tree.InsertItem(_T("自定义贴图库"));
	for(int i=0;i<10;i++)
	{
		str.Format(_T("#%d~#%d"),i*10,i*10+9);
		ti_ugl_level[i]=m_Tree.InsertItem(str,ti_ugl_head);
		for(int j=0;j<10;j++)
		{
			str.Format(_T("[#%d]%s"),i*10+j,ugl_rgn+ UGL_LEN*(i*10+j) +UGL_TITLE_OFFSET);
			ti_ugl[i*10+j]=m_Tree.InsertItem(str,ti_ugl_level[i]);
		}
	}

	m_SetCursorResp=true;
	m_StatusBar.SetPaneText(0,_T("就绪"));

	
	
}

//“新建”按钮响应
void CMapDeluxeDlg::OnBnClickedButtonNew()
{
	//选择文件保存位置
	TCHAR strPath[1000]={0};
	GetPrivateProfileString(_T("FILE"),_T("Path"),0,strPath,999,ProfilePath);
	CFileDialog filedlg(FALSE,_T("gba"),_T("我的梦之泉.gba"),OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,
		_T("梦之泉ROM|*.gba||"),this);
	filedlg.GetOFN().lpstrInitialDir=strPath;
	filedlg.GetOFN().lpstrTitle=_T("选择新游戏的保存位置...");
	if(filedlg.DoModal()==IDCANCEL)return;
	CFile file;
	CString strFileName=filedlg.GetPathName();
	WritePrivateProfileString(_T("FILE"),_T("Path"),strFileName,ProfilePath);
	if(!file.Open(strFileName,CFile::modeCreate|CFile::modeWrite))
	{
		MessageBox(_T("未能创建文件，请重试"),_T("错误"),MB_ICONERROR);
		return;
	}

	//加载并写入初始ROM
	void* pRomRebuild=mrrLockRomResource();
	file.Write(pRomRebuild,0x01000000);
	mrrUnlockRomResource();
	file.Close();

	file.Open(strFileName,CFile::modeReadWrite);
	ReadRom(file);

	rom_mdxinfo.auto_obj_bufidx=1;

	m_EditFileName.SetWindowText(strFileName);

	file.Close();

	/////
	//CreateGraAssocTable();
}

//“保存”按钮响应
void CMapDeluxeDlg::OnBnClickedButtonSave()
{
	if(map[0][0]==0)return;
	CString strFileName;
	m_EditFileName.GetWindowText(strFileName);
	CFile file;
	if(!file.Open(strFileName,CFile::modeReadWrite))
	{
		MessageBox(_T("未能写入文件！此文件可能正在被其它程序使用！"),_T("错误"),MB_ICONERROR);
		return;
	}
	//重新写入一遍初始ROM以更新可能的RomRebuild更新
	void* pRomRebuild=mrrLockRomResource();
	file.Write(pRomRebuild,0x01000000);
	mrrUnlockRomResource();
	//写入所有数据
	WriteRom(file);

	file.Close();
}

//编码地图数据进入ROM文件
void CMapDeluxeDlg::WriteRom(CFile& file)
{
	m_SetCursorResp=false;
	m_StatusBar.SetPaneText(0,_T("保存游戏..."));

	m_Progress.SetRange(1,STEP_INDEXING_COUNT);
	SetWindowLong(m_Progress.m_hWnd,GWL_STYLE,WS_VISIBLE|GetWindowLong(m_Progress.m_hWnd,GWL_STYLE));
	u8 *buff;
	u16 *nestbuff;
	u32 len;
	CString str;
	const u32 zero32=0,F32=0xFFFFFFFF;
	CList<u32> nestlist;
	bool newstage=false;
	u16 prevstage=0xFFFF,currstage;
	///补给品缓存分配标记
	u8 o4buf=0;
	for(int index=0;index<STEP_INDEXING_COUNT;index++)
	{
		currstage=step_header[index].level<<8|step_header[index].stage;
		if(currstage!=prevstage)
		{
			prevstage=currstage;
			newstage=true;
		}else newstage=false;

		//写入主地图
		file.Seek(0x00800000+index*0x4000+0x00001000,CFile::begin);
		buff=new u8[step_header[index].width*step_header[index].height*4];
		len=AgbCompressLZ((u8*)(map[0][index]),
			step_header[index].width*step_header[index].height*4,
			buff);
		if(len>0x1000 || len==0)
		{
			delete[] buff;
			str.Format(_T("地图[Level%d.Stage%d.Step%02d]的主地图空间溢出！\n写入文件已中断"),
				step_header[index].level+1,step_header[index].stage+1,step_header[index].step);
			MessageBox(str);
			m_Progress.SetPos(0);
			SetWindowLong(m_Progress.m_hWnd,GWL_STYLE,(~WS_VISIBLE)&GetWindowLong(m_Progress.m_hWnd,GWL_STYLE));
			m_SetCursorResp=true;
			m_StatusBar.SetPaneText(0,_T("就绪"));
			return;
		}
		file.Write(buff,len);
		delete[] buff;

		//写入掀开地图表
		nestlist.RemoveAll();
		nestbuff=new u16[step_header[index].width*step_header[index].height];
		for(int k=0;k<step_header[index].width*step_header[index].height;k++)
		{
			if(*(u32*)&map[1][index][k]==0xFFFFFFFF)
			{
				nestbuff[k]=0;
			}
			//...导火索双重掀开写入
			else if(map[0][index][k].det<0x3E && map[0][index][k].det>0x37)
			{
				//我懒得查找相同项了，直接添加
				nestlist.AddTail(*(u32*)&map[1][index][k]);
				nestbuff[k]=nestlist.GetCount()-1+1;
				nestlist.AddTail(*(u32*)&map[0][index][k]);//双重掀开!!!
			}
			else
			{
				//查找相同项
				POSITION pos = nestlist.GetHeadPosition();
				int ki=0;
				while(1)   
				{
					if(pos==0)
					{
						ki=-1;
						break;
					}
					if(nestlist.GetNext(pos)==*(u32*)&map[1][index][k])
					{
						break;
					}
					ki++;
				}
				if(ki!=-1)//有相同项
				{
					nestbuff[k]=(u16)(ki+1);
				}
				else//没有相同项
				{
					nestlist.AddTail(*(u32*)&map[1][index][k]);
					nestbuff[k]=nestlist.GetCount()-1+1;
				}
			}
		}
		file.Seek(0x00800000+index*0x4000+0x00003000,CFile::begin);
		file.Write(&zero32,4);
		POSITION pos;
		pos=nestlist.GetHeadPosition();  
		if(nestlist.GetCount()+2>0x1000/4)
		{
			delete[] nestbuff;
			str.Format(_T("地图[Level%d.Stage%d.Step%02d]的掀开地图表溢出！\n写入文件已中断"),
				step_header[index].level+1,step_header[index].stage+1,step_header[index].step);
			MessageBox(str);
			m_Progress.SetPos(0);
			SetWindowLong(m_Progress.m_hWnd,GWL_STYLE,(~WS_VISIBLE)&GetWindowLong(m_Progress.m_hWnd,GWL_STYLE));
			m_SetCursorResp=true;
			m_StatusBar.SetPaneText(0,_T("就绪"));
			return;
		}
		while(pos)   
		{   
			file.Write(&nestlist.GetNext(pos),4);
		}
		file.Write(&F32,4);
		
		//写入掀开地图映射
		buff=new u8[step_header[index].width*step_header[index].height*2];
		len=AgbCompressLZ((u8*)(nestbuff),
			step_header[index].width*step_header[index].height*2,
			buff);
		if(len>0x1000 || len==0)
		{
			delete[] nestbuff;
			str.Format(_T("地图[Level%d.Stage%d.Step%02d]的掀开地图映射溢出！\n写入文件已中断"),
				step_header[index].level+1,step_header[index].stage+1,step_header[index].step);
			MessageBox(str);
			m_Progress.SetPos(0);
			SetWindowLong(m_Progress.m_hWnd,GWL_STYLE,(~WS_VISIBLE)&GetWindowLong(m_Progress.m_hWnd,GWL_STYLE));
			m_SetCursorResp=true;
			m_StatusBar.SetPaneText(0,_T("就绪"));
			return;
		}
		file.Seek(0x00800000+index*0x4000+0x00002000,CFile::begin);
		file.Write(buff,len);
		delete[]nestbuff;
		delete[]buff;

		//写入传送门
		file.Seek(0x00800000+index*0x4000+0x00000100,CFile::begin);
		file.Write(door[index],step_header[index].door_count*sizeof(DOOR_DATA));

		//写入OBJ+Wind
		u16 obj_top;
		obj_top=step_header[index].obj_count;
		OBJ_DATA odt;
		if(newstage)o4buf=0;
		for(u16 i=0;i<step_header[index].obj_count;i++)
		{
			file.Seek(0x00800000+index*0x4000+0x00000800+i*sizeof(OBJ_DATA),CFile::begin);
			if(obj_top>40)
			{
				str.Format(_T("地图[Level%d.Stage%d.Step%02d]物件数量数据溢出！\n写入文件已中断"),
				step_header[index].level+1,step_header[index].stage+1,step_header[index].step);
				MessageBox(str);
				m_Progress.SetPos(0);
				SetWindowLong(m_Progress.m_hWnd,GWL_STYLE,(~WS_VISIBLE)&GetWindowLong(m_Progress.m_hWnd,GWL_STYLE));
				m_SetCursorResp=true;
				m_StatusBar.SetPaneText(0,_T("就绪"));
				return;
			}
			if(obj[index][i].is_folder)
			{
				odt.class_id=0x0006;
				odt.paramA=(u8)obj_top;
				odt.paramB=(u8)obj[index][i].len;
				odt.x=obj[index][i].fx;
				odt.y=obj[index][i].fy;
				file.Write(&odt,sizeof(OBJ_DATA));
				file.Seek(0x00800000+index*0x4000+0x00000800+obj_top*sizeof(OBJ_DATA),CFile::begin);
				for(u16 j=0;j<obj[index][i].len;j++)
				{
					odt=obj[index][i].o[j];
					file.Write(&odt,sizeof(OBJ_DATA));
				}
				obj_top+=obj[index][i].len;
			}
			else
			{
				if((obj[index][i].o[0].class_id&0xF)==4)
				{
					//补给品缓存序号累加
					if(rom_mdxinfo.auto_obj_bufidx)obj[index][i].o[0].paramB=o4buf;
					o4buf++;
				}
				odt=obj[index][i].o[0];
				file.Write(&odt,sizeof(OBJ_DATA));
			}
		}
		if(wind[index].class_id==0xFFFF)
		{
			step_header[index].wind_index=0xFFFF;
		}
		else
		{
			step_header[index].wind_index=obj_top;
			file.Seek(0x00800000+index*0x4000+0x00000800+obj_top*sizeof(OBJ_DATA),CFile::begin);
			file.Write(&wind[index],sizeof(OBJ_DATA));

		}

		//写入头
		file.Seek(0x00800000+index*0x4000,CFile::begin);
		file.Write(&step_header[index],sizeof(STEP_HEADER));

		m_Progress.SetPos(index+1);
		UpdateData(FALSE);
	}

	//起始页
	file.Seek(ROM_IMAGE_CMD_OFFSET,CFile::begin);
	u32 firstcmd=use_rom_image?0xEA1FFFAD:0xE12FFF11;
	file.Write(&firstcmd,4);
	file.Seek(ROM_IMAGE_OFFSET,CFile::begin);
	file.Write(rom_image,sizeof(u16)*160*240);

	//附加信息
	file.Seek(ROM_MDXINFO_OFFSET,CFile::begin);
	file.Write(&rom_mdxinfo,sizeof(ROM_MDXINFO));

	//UGL（自定义贴图库）
	file.Seek(ROM_UGL_OFFSET-0x08000000,CFile::begin);
	file.Write(ugl_rgn,UGL_COUNT*UGL_LEN);

	MessageBox(_T("写入文件成功！"),_T("成功"));
	m_Progress.SetPos(0);
	SetWindowLong(m_Progress.m_hWnd,GWL_STYLE,(~WS_VISIBLE)&GetWindowLong(m_Progress.m_hWnd,GWL_STYLE));
	m_StatusBar.RedrawWindow();
	m_SetCursorResp=true;
	m_StatusBar.SetPaneText(0,_T("就绪"));
}

//下面的这些函数都是一些文本框等控件的响应
void CMapDeluxeDlg::OnBnClickedCheckLz77()
{
	if(cur_step==0xFFFF)return;
	step_header[cur_step].lz77=m_CheckLz77.GetCheck()?1:0;
}

void CMapDeluxeDlg::OnCbnSelchangeComboBgm()
{
	if(cur_step==0xFFFF)return;
	CString str;
	m_ComboBgm.GetWindowText(str);
	step_header[cur_step].bgm=(u8)StrToI(str);
}

void CMapDeluxeDlg::OnCbnSelchangeComboSpcmap()
{
	if(cur_step==0xFFFF)return;
	CString str;
	m_ComboSpcMap.GetWindowText(str);
	step_header[cur_step].spc_map=(u8)StrToI(str);
}
void CMapDeluxeDlg::OnCbnSelchangeComboGraAni()
{
	if(cur_step==0xFFFF)return;
	CString str;
	m_ComboGraAni.GetWindowText(str);
	step_header[cur_step].gra_ani_index=(u8)StrToI(str);
}

void CMapDeluxeDlg::OnEnChangeEditClipX()
{
	if(cur_step==0xFFFF)return;
	CString str;
	m_EditClipX.GetWindowText(str);
	step_header[cur_step].clip_x=(u16)StrToI(str);
}
void CMapDeluxeDlg::OnEnChangeEditClipY()
{
	if(cur_step==0xFFFF)return;
	CString str;
	m_EditClipY.GetWindowText(str);
	step_header[cur_step].clip_y=(u16)StrToI(str);
}


void CMapDeluxeDlg::OnEnChangeEditBeginX()
{
	if(cur_step==0xFFFF)return;
	CString str;
	m_EditBeginX.GetWindowText(str);
	step_header[cur_step].begin_x=(u16)StrToI(str);

}

void CMapDeluxeDlg::OnEnChangeEditBeginY()
{
	if(cur_step==0xFFFF)return;
	CString str;
	m_EditBeginY.GetWindowText(str);
	step_header[cur_step].begin_y=(u16)StrToI(str);
}

void CMapDeluxeDlg::OnEnChangeEditBckMov()
{
	if(cur_step==0xFFFF)return;
	CString str;
	m_EditBckMov.GetWindowText(str);
	step_header[cur_step].bck_mov=(u16)StrToI(str);
}

void CMapDeluxeDlg::OnEnChangeEditUnk36()
{
	if(cur_step==0xFFFF)return;
	CString str;
	m_EditX36.GetWindowText(str);
	step_header[cur_step].bck_dy=(u16)StrToI(str);

}




void CMapDeluxeDlg::OnBnClickedCheckUnk55()
{
	if(cur_step==0xFFFF)return;
	step_header[cur_step].x55=m_CheckX55.GetCheck()?1:0;
}

void CMapDeluxeDlg::OnBnClickedCheckBckroll()
{
	if(cur_step==0xFFFF)return;
	step_header[cur_step].bck_roll=m_CheckBckRoll.GetCheck()?1:0;
}

//鼠标的响应，用于地图光标移动和操作
void CMapDeluxeDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	bool NuKirbyLeftT=m_NuKirbyLeft;
	m_NuKirbyLeft=point.x<NU_KIRBY_X;
	if(m_NuKirbyLeft!=NuKirbyLeftT)
	{
		CDC *pDC=GetDC();
		DrawNuKirby(pDC);
		ReleaseDC(pDC);
	}
	if(cur_step!=0xFFFF)
	{

		RECT hsrc,vsrc,glsrc;
		int hsp=m_HScrollMap.GetScrollPos();
		int vsp=m_VScrollMap.GetScrollPos();
		int lsp=m_ScrollBarGraLib.GetScrollPos();
		m_HScrollMap.GetWindowRect(&hsrc);
		m_VScrollMap.GetWindowRect(&vsrc);
		m_ScrollBarGraLib.GetWindowRect(&glsrc);
		ScreenToClient(&hsrc);
		ScreenToClient(&vsrc);
		ScreenToClient(&glsrc);
		CRect rectmap;

		u16 tcur_x,tcur_y,tcur_sel;
		if(point.x<hsrc.right && point.x>hsrc.left &&
			point.y<vsrc.bottom && point.y>vsrc.top)
		{
			m_SetCursorResp=false;
			tcur_x=(u16)((point.x-hsrc.left+hsp)/16);
			tcur_y=(u16)((point.y-vsrc.top+vsp)/16);
			if(tcur_x>=step_header[cur_step].width ||
				tcur_y>=step_header[cur_step].height)
			{
				tcur_x=0xFFFF;
				tcur_y=0xFFFF;
			}
			tcur_sel=0xFFFF;
		}
		else if(point.y<glsrc.bottom && point.y>glsrc.top &&
			point.x>glsrc.right && point.x<glsrc.right+256)
		{
			m_SetCursorResp=false;
			tcur_x=0xFFFF;
			tcur_y=0xFFFF;
			tcur_sel=(u16)((point.x-glsrc.right)/16 + (point.y-glsrc.top+lsp)/16*16);
			int len;
			CString str;
			m_ComboMapChg.GetWindowText(str);
			switch(m_ComboMapChg.FindString(-1,str))
			{
			case 0:
				len=(gralib_len/16+1)*16;
				break;
			case 1:
				len=256;
				break;
			}
			if(tcur_sel>=len)tcur_sel=0xFFFF;
		}
		else
		{
			m_SetCursorResp=true;
			tcur_x=0xFFFF;
			tcur_y=0xFFFF;
			tcur_sel=0xFFFF;
		}

		if(tcur_x!=cur_x||tcur_y!=cur_y)
		{
			u16 lc_x=cur_x;
			u16 lc_y=cur_y;
			cur_x=tcur_x;
			cur_y=tcur_y;
			if(drawing&&cur_x!=0xFFFF)DrawGrid();
			PaintMap(lc_x,lc_y);
			PaintMap(cur_x,cur_y);
			CDC* pDC=GetDC();
			PresentMap(pDC);
			ReleaseDC(pDC);
			UpdateGridInfo();
			UpdateLibInfo();
		}
		if(tcur_sel!=cur_sel)
		{
			cur_sel=tcur_sel;
			if(drawing&&cur_x!=0xFFFF)DrawGrid();
			PaintGraLib();
			CDC* pDC=GetDC();
			PresentGraLib(pDC);
			ReleaseDC(pDC);
			UpdateGridInfo();
			UpdateLibInfo();
		}
	}

	CDialog::OnMouseMove(nFlags, point);
}

//更新选中格信息至状态栏
void CMapDeluxeDlg::UpdateGridInfo()
{
	if(cur_step==0xFFFF)return;
	CString str,str2;
	if(cur_x==0xFFFF)
	{
		str=_T("就绪");
	}
	else
	{
		str.Format(_T("(%u,%u)[主数据]判定=%u(%s) 图像=%u Edg=%u"),
			cur_x,cur_y,
			map[0][cur_step][cur_x+cur_y*step_header[cur_step].width].det,
			CodeTran_Det(map[0][cur_step][cur_x+cur_y*step_header[cur_step].width].det),
			map[0][cur_step][cur_x+cur_y*step_header[cur_step].width].gra,
			map[0][cur_step][cur_x+cur_y*step_header[cur_step].width].edg
			);
		if(*(u32*)&map[1][cur_step][cur_x+cur_y*step_header[cur_step].width]!=0xFFFFFFFF)
		{
			str2.Format(_T(" [掀开数据]判定=%u(%s) 图像=%u Edg=%u"),
				map[1][cur_step][cur_x+cur_y*step_header[cur_step].width].det,
				CodeTran_Det(map[1][cur_step][cur_x+cur_y*step_header[cur_step].width].det),
				map[1][cur_step][cur_x+cur_y*step_header[cur_step].width].gra,
				map[1][cur_step][cur_x+cur_y*step_header[cur_step].width].edg
				);
		}
		else
		{
			str2=_T(" [掀开数据]无");
		}
		str+=str2;
	}
	m_StatusBar.SetPaneText(0,str);
}
//更新选中图形库信息框
void CMapDeluxeDlg::UpdateLibInfo()
{
	if(cur_step==0xFFFF)return;
	CString str;
	if(cur_sel==0xFFFF)
	{

		CString str2;
		m_ComboMapChg.GetWindowText(str2);
		if(m_ComboMapChg.FindString(-1,str2)==1)
		{
			str.Format(_T("已选中编号:%d(%s)"),
				cur_chg,CodeTran_Det((u8)cur_chg)
			);
		}
		else
		{
			str.Format(_T("已选中编号:%d"),
				cur_chg
				);
		}
		m_StaticLibInfo.SetWindowText(str);
		return;
	}
	

	CString str2;
	m_ComboMapChg.GetWindowText(str2);
	if(m_ComboMapChg.FindString(-1,str2)==1)
	{
		str.Format(_T("已选中编号:%d(%s)\n当前编号:%d(%s)"),
			cur_chg,CodeTran_Det((u8)cur_chg),cur_sel,CodeTran_Det((u8)cur_sel)
		);
	}
	else
	{
		str.Format(_T("已选中编号:%d\n当前编号:%d"),
			cur_chg,cur_sel
			);
	}

	m_StaticLibInfo.SetWindowText(str);
}
//地图模式换挡响应
void CMapDeluxeDlg::OnCbnSelchangeComboMapchg()
{
	if(cur_step==0xFFFF)return;

	CString str;
	m_ComboMapChg.GetWindowText(str);
	bool EdgOpen=(m_ComboMapChg.FindString(-1,str)==1);
	m_CheckEdg.EnableWindow(EdgOpen);
	m_EditEdg.EnableWindow(EdgOpen && m_CheckEdg.GetCheck());

	ResetGraLibScrollBar();
	cur_chg=0;
	CDC* pDC=GetDC();
	PaintMap();
	PaintGraLib();
	PresentMap(pDC);
	PresentGraLib(pDC);
	ReleaseDC(pDC);
}

//重置图形库滚动条
void CMapDeluxeDlg::ResetGraLibScrollBar()
{
	int len;
	CString str;
	m_ComboMapChg.GetWindowText(str);
	switch(m_ComboMapChg.FindString(-1,str))
	{
	case 0:
		len=(gralib_len/16+1)*16;
		break;
	case 1:
		len=256;
		break;
	}

	RECT vsrc;
	int vsrg;
	m_ScrollBarGraLib.GetWindowRect(&vsrc);
	vsrg=len-(vsrc.bottom-vsrc.top);
	if(vsrg<1)vsrg=1;
	SCROLLINFO scrinfo={0};
	scrinfo.cbSize=sizeof(SCROLLINFO);
	scrinfo.fMask=SIF_PAGE|SIF_RANGE|SIF_POS;
	scrinfo.nPage=vsrc.bottom-vsrc.top;
	scrinfo.nMin=0;scrinfo.nMax=vsrg-1+scrinfo.nPage-1;
	scrinfo.nPos=0;
	m_ScrollBarGraLib.SetScrollInfo(&scrinfo);
}

//绘制图形库
void CMapDeluxeDlg::PaintGraLib()
{
	if(cur_step==0xFFFF)return;
	static CPen PenCur(PS_SOLID,1,RGB(255,0,0)),PenChg(PS_SOLID,2,RGB(255,0,0)),
		PenAssocUp(PS_SOLID,2,RGB(255,255,0)),
		PenAssocDown(PS_SOLID,2,RGB(0,255,255)),
		PenAssocLeft(PS_SOLID,2,RGB(0,255,0)),
		PenAssocRight(PS_SOLID,2,RGB(0,0,255));
	CBrush BrushNull;
	BrushNull.CreateStockObject(NULL_BRUSH);

	int len;
	CString str;
	m_ComboMapChg.GetWindowText(str);
	bool pgra;
	switch(m_ComboMapChg.FindString(-1,str))
	{
	case 0:
		len=(gralib_len/16+1)*16;
		m_TmpDC2.SelectObject(&m_BmpGra);
		m_TmpDC.SelectObject(&m_BmpGraOut);
		pgra=true;
		break;
	case 1:
		len=256;
		m_TmpDC2.SelectObject(&m_BmpDet);
		m_TmpDC.SelectObject(&m_BmpDetOut);
		pgra=false;
		break;
	}
	
	m_TmpDC.BitBlt(0,0,256,len,&m_TmpDC2,0,0,SRCCOPY);
	if(cur_sel!=0xFFFF)
	{
		m_TmpDC.SelectObject(&BrushNull);
		m_TmpDC.SelectObject(&PenCur);
		m_TmpDC.Rectangle((cur_sel%16)*16,cur_sel/16*16,(cur_sel%16)*16+16,cur_sel/16*16+16);
		
	}

	if(cur_chg<gralib_len)
	{
		if(GraAssocLa && pgra && m_CheckGraAssoc.GetCheck())
		{
			POSITION pst;
			u16 assoc;
			m_TmpDC.SelectObject(&PenAssocLeft);
			pst=GraAssocLa[cur_chg].left.GetHeadPosition();
			while(pst)
			{
				assoc=GraAssocLa[cur_chg].left.GetNext(pst);
				m_TmpDC.Rectangle((assoc%16)*16,assoc/16*16,(assoc%16)*16+16,assoc/16*16+16);
			}
			m_TmpDC.SelectObject(&PenAssocRight);
			pst=GraAssocLa[cur_chg].right.GetHeadPosition();
			while(pst)
			{
				assoc=GraAssocLa[cur_chg].right.GetNext(pst);
				m_TmpDC.Rectangle((assoc%16)*16,assoc/16*16,(assoc%16)*16+16,assoc/16*16+16);
			}
			m_TmpDC.SelectObject(&PenAssocUp);
			pst=GraAssocLa[cur_chg].up.GetHeadPosition();
			while(pst)
			{
				assoc=GraAssocLa[cur_chg].up.GetNext(pst);
				m_TmpDC.Rectangle((assoc%16)*16,assoc/16*16,(assoc%16)*16+16,assoc/16*16+16);
			}
			m_TmpDC.SelectObject(&PenAssocDown);
			pst=GraAssocLa[cur_chg].down.GetHeadPosition();
			while(pst)
			{
				assoc=GraAssocLa[cur_chg].down.GetNext(pst);
				m_TmpDC.Rectangle((assoc%16)*16,assoc/16*16,(assoc%16)*16+16,assoc/16*16+16);
			}
		}
		m_TmpDC.SelectObject(&PenChg);
		m_TmpDC.Rectangle((cur_chg%16)*16,cur_chg/16*16,(cur_chg%16)*16+16,cur_chg/16*16+16);
	}

}
//呈现图形库
void CMapDeluxeDlg::PresentGraLib(CDC* pDC)
{
	if(cur_step==0xFFFF)return;

	RECT vsrc;
	int vsp=m_ScrollBarGraLib.GetScrollPos();
	m_ScrollBarGraLib.GetWindowRect(&vsrc);
	ScreenToClient(&vsrc);
	CString str;
	m_ComboMapChg.GetWindowText(str);
	switch(m_ComboMapChg.FindString(-1,str))
	{
	case 0:
		if(gralib_len==0)
		{
			pDC->FillRect((RECT*)&CRect(vsrc.right,vsrc.top,vsrc.right+256,vsrc.bottom),
				&CBrush(RGB(0,0,0)));
			return;
		}
		m_TmpDC.SelectObject(&m_BmpGraOut);
		break;
	case 1:

		m_TmpDC.SelectObject(&m_BmpDetOut);
		break;
	}
	
	pDC->BitBlt(vsrc.right,vsrc.top,
		256,vsrc.bottom-vsrc.top,&m_TmpDC,
		0,vsp,SRCCOPY);
}
//左键抬起响应，用于连续绘图
void CMapDeluxeDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	drawing=false;

	CDialog::OnLButtonUp(nFlags, point);
}

//修改格子
void CMapDeluxeDlg::DrawGrid()
{
	if(cur_step==0xFFFF)return;
	if(cur_x==0xFFFF)return;
	MAPOPT_INFO moi;
	moi.x=cur_x;
	moi.y=cur_y;
	moi.prev[0]=map[0][cur_step][cur_x+cur_y*step_header[cur_step].width];
	moi.prev[1]=map[1][cur_step][cur_x+cur_y*step_header[cur_step].width];

	int nest=m_CheckNest.GetCheck()?1:0;
	CString str;
	m_ComboMapChg.GetWindowText(str);
	
	if(*(u32*)&map[nest][cur_step][cur_x+cur_y*step_header[cur_step].width]==0xFFFFFFFF)
	{
		*(u32*)&map[nest][cur_step][cur_x+cur_y*step_header[cur_step].width]=0;
	}
	switch(m_ComboMapChg.FindString(-1,str))
	{
	case 0:
		map[nest][cur_step][cur_x+cur_y*step_header[cur_step].width].gra=cur_chg;
		break;
	case 1:
		map[nest][cur_step][cur_x+cur_y*step_header[cur_step].width].det=(u8)cur_chg;
		if(m_CheckEdg.GetCheck())
		{
			m_EditEdg.GetWindowText(str);
			map[nest][cur_step][cur_x+cur_y*step_header[cur_step].width].edg=(u8)StrToI(str);
		}
		if(nest==0 && m_CheckNestAuto.GetCheck())
		{
			*(u32*)&map[1][cur_step][cur_x+cur_y*step_header[cur_step].width]=
				CodeTran_DetNset((u8)cur_chg)?0:0xFFFFFFFF;
		}
		break;
	}
	moi.curr[0]=map[0][cur_step][cur_x+cur_y*step_header[cur_step].width];
	moi.curr[1]=map[1][cur_step][cur_x+cur_y*step_header[cur_step].width];

	if(*(u32*)&moi.prev[0]!=*(u32*)&moi.curr[0]||
		*(u32*)&moi.prev[1]!=*(u32*)&moi.curr[1])
		Mos_Push(moi);
}
//吸管响应
void CMapDeluxeDlg::OnMButtonDown(UINT nFlags, CPoint point)
{
	int nest=m_CheckNest.GetCheck()?1:0;
	if(cur_step!=0xFFFF && !drawing)
	{
		if(cur_x!=0xFFFF)
		{
			if(*(u32*)&map[nest][cur_step][cur_x+cur_y*step_header[cur_step].width]==0xFFFFFFFF)return;
			CString str;
			m_ComboMapChg.GetWindowText(str);
			switch(m_ComboMapChg.FindString(-1,str))
			{
			case 0:
				cur_chg=map[nest][cur_step][cur_x+cur_y*step_header[cur_step].width].gra;
				break;
			case 1:
				cur_chg=map[nest][cur_step][cur_x+cur_y*step_header[cur_step].width].det;
				
				break;
			}

		}
		CDC* pDC=GetDC();
		PaintGraLib();
		PresentGraLib(pDC);
		UpdateLibInfo();
		ReleaseDC(pDC);
	}
	
	CDialog::OnMButtonDown(nFlags, point);
}

//左键响应
void CMapDeluxeDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	if(cur_step!=0xFFFF)
	{

		int nest=m_CheckNest.GetCheck()?1:0;

		if(cur_x!=0xFFFF)
		{
			drawing=true;
			DrawGrid();

		}
		else if(cur_sel!=0xFFFF && cur_sel<gralib_len)
		{
			cur_chg=cur_sel;
		}
		CDC* pDC=GetDC();
		PaintMap(cur_x,cur_y);
		PaintGraLib();
		PresentMap(pDC);
		PresentGraLib(pDC);
		ReleaseDC(pDC);
		UpdateGridInfo();
		UpdateLibInfo();
	}
	CDialog::OnLButtonDown(nFlags, point);
}

//测试占用空间按钮
void CMapDeluxeDlg::OnBnClickedButtonSaveTest()
{
	if(cur_step==0xFFFF)return;

	bool lhe=true,lok=true;

	u32 mmlen,nmlen;
	u8* buff;
	buff=new u8[step_header[cur_step].width*step_header[cur_step].height*4];
	mmlen=AgbCompressLZ((u8*)(map[0][cur_step]),
		step_header[cur_step].width*step_header[cur_step].height*4,
		buff);
	delete[] buff;
	if(mmlen>0x1000 || mmlen==0)lok=false;
	if(mmlen>0xC00)lhe=false;

	u16 nestcount;
	u16* nestbuff;
	nestbuff=new u16[step_header[cur_step].width*step_header[cur_step].height];
	CList<u32> nestlist;
	nestlist.RemoveAll();
	for(int k=0;k<step_header[cur_step].width*step_header[cur_step].height;k++)
	{
		if(*(u32*)&map[1][cur_step][k]==0xFFFFFFFF)
		{
			nestbuff[k]=0;
		}
		//...导火索双重掀开写入
		else if(map[0][cur_step][k].det<0x3E && map[0][cur_step][k].det>0x37)
		{
			//我懒得查找相同项了，直接添加
			nestlist.AddTail(*(u32*)&map[1][cur_step][k]);
			nestbuff[k]=nestlist.GetCount()-1+1;
			nestlist.AddTail(*(u32*)&map[0][cur_step][k]);//双重掀开!!!
		}
		else
		{
			POSITION pos = nestlist.GetHeadPosition();
			int ki=0;
			while(1)   
			{
				if(pos==0)
				{
					ki=-1;
					break;
				}
				if(nestlist.GetNext(pos)==*(u32*)&map[1][cur_step][k])
				{
					break;
				}
				ki++;
			}
			if(ki!=-1)
			{
				nestbuff[k]=(u16)(ki+1);
			}
			else
			{
				nestlist.AddTail(*(u32*)&map[1][cur_step][k]);
				nestbuff[k]=nestlist.GetCount()-1+1;
			}
		}
	}
	/*for(int k=0;k<step_header[cur_step].width*step_header[cur_step].height;k++)
	{
		if(*(u32*)&map[1][cur_step][k]==0xFFFFFFFF)
		{
			nestbuff[k]=0;
		}
		else
		{
			nestbuff[k]=nestcount;
			nestcount++;
		}
	}*/

	nestcount=nestlist.GetCount()+2;
	if(nestcount*4>0x1000)lok=false;
	if(nestcount*4>0xC00)lhe=false;

	buff=new u8[step_header[cur_step].width*step_header[cur_step].height*2];
	nmlen=AgbCompressLZ((u8*)(nestbuff),
		step_header[cur_step].width*step_header[cur_step].height*2,
		buff);
	if(nmlen>0x1000 || nmlen==0)lok=false;
	if(nmlen>0xC00)lhe=false;
	delete[]nestbuff;
	delete[]buff;

	CString str;
	str.Format(_T("主地图占用空间:%.3fKB / 4.000KB\n")
		_T("掀开地图映射占用空间:%.3fKB / 4.000KB\n")
		_T("掀开地图表占用空间:%.3fKB / 4.000KB\n")
		_T("空间占用情况:%s"),
		mmlen/1024.0f,nmlen/1024.0f,nestcount*4/1024.0f,
		lok?(lhe?_T("良好 ^_^"):_T("危险 -_-")):_T("溢出 ×_×"));
	MessageBox(str,_T("测试结果"));
}

//另存为
void CMapDeluxeDlg::OnBnClickedButtonSaveas()
{
	if(map[0][0]==0)return;
	TCHAR strPath[1000]={0};
	GetPrivateProfileString(_T("FILE"),_T("Path"),0,strPath,999,ProfilePath);
	//打开文件
	CFileDialog filedlg(FALSE,_T("gba"),_T("我的梦之泉.gba"),OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,
		_T("梦之泉ROM|*.gba||"),this);
	filedlg.GetOFN().lpstrInitialDir=strPath;
	filedlg.GetOFN().lpstrTitle=_T("另存为...");
	if(filedlg.DoModal()==IDCANCEL)return;
	CFile file;
	CString strFileName=filedlg.GetPathName();
	WritePrivateProfileString(_T("FILE"),_T("Path"),strFileName,ProfilePath);
	if(!file.Open(strFileName,CFile::modeCreate|CFile::modeWrite))
	{
		MessageBox(_T("未能创建文件，请重试"),_T("错误"),MB_ICONERROR);
		return;
	}
	void* pRomRebuild=mrrLockRomResource();
	file.Write(pRomRebuild,0x01000000);
	mrrUnlockRomResource();
	WriteRom(file);
	m_EditFileName.SetWindowText(strFileName);
	file.Close();
}

//掀开按钮
void CMapDeluxeDlg::OnBnClickedCheckNest()
{
	CDC* pDC=GetDC();
	PaintMap();
	PresentMap(pDC);
	ReleaseDC(pDC);
}

//右键响应
void CMapDeluxeDlg::OnRButtonDown(UINT nFlags, CPoint point)
{
	if(cur_step!=0xFFFF && cur_x!=0xFFFF)
	{
		MAPOPT_INFO moi;
		moi.x=cur_x;
		moi.y=cur_y;
		moi.prev[0]=map[0][cur_step][cur_x+cur_y*step_header[cur_step].width];
		moi.prev[1]=map[1][cur_step][cur_x+cur_y*step_header[cur_step].width];

		if(m_CheckNest.GetCheck())
		{
			*(u32*)&map[1][cur_step][cur_x+cur_y*step_header[cur_step].width]=0xFFFFFFFF;
		}
		else
		{
			*(u32*)&map[0][cur_step][cur_x+cur_y*step_header[cur_step].width]=0;
		}
		CDC* pDC=GetDC();
		PaintMap(cur_x,cur_y);
		PresentMap(pDC);
		ReleaseDC(pDC);

		moi.curr[0]=map[0][cur_step][cur_x+cur_y*step_header[cur_step].width];
		moi.curr[1]=map[1][cur_step][cur_x+cur_y*step_header[cur_step].width];

		if(*(u32*)&moi.prev[0]!=*(u32*)&moi.curr[0]||
			*(u32*)&moi.prev[1]!=*(u32*)&moi.curr[1])
			Mos_Push(moi);
	}

	CDialog::OnRButtonDown(nFlags, point);
}

//存储为最终版
void CMapDeluxeDlg::OnBnClickedButtonSaveFinal()
{
	if(map[0][0]==0)return;
	char MagicErase[]="FINAL_PLAY_ONLY";
	TCHAR strPath[1000]={0};
	GetPrivateProfileString(_T("FILE"),_T("Path"),0,strPath,999,ProfilePath);
	//打开文件
	CFileDialog filedlg(FALSE,_T("gba"),_T("我的梦之泉.gba"),OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,
		_T("梦之泉ROM|*.gba||"),this);
	filedlg.GetOFN().lpstrTitle=_T("另存为最终版游戏...");
	filedlg.GetOFN().lpstrInitialDir=strPath;
	if(filedlg.DoModal()==IDCANCEL)return;
	CFile file;
	CString strFileName=filedlg.GetPathName();
	WritePrivateProfileString(_T("FILE"),_T("Path"),strFileName,ProfilePath);
	if(!file.Open(strFileName,CFile::modeCreate|CFile::modeWrite))
	{
		MessageBox(_T("未能创建文件，请重试"),_T("错误"),MB_ICONERROR);
		return;
	}
	void* pRomRebuild=mrrLockRomResource();
	file.Write(pRomRebuild,0x01000000);
	mrrUnlockRomResource();
	file.Seek(0x7FFFF0,CFile::begin);//
	file.Write(MagicErase,16);//Rewrite the magic text which is the flag of editing
	WriteRom(file);
	file.Close();
}

//修改尺寸
void CMapDeluxeDlg::OnBnClickedButtonResize()
{
	if(cur_step==0xFFFF)return;
	CDlgResize dlg;
	dlg.width=step_header[cur_step].width;
	dlg.height=step_header[cur_step].height;
	if(dlg.DoModal()==IDCANCEL)return;

	//复制地图判定、图像
	GRID_DATA* newmap[2];
	for(int n=0;n<2;n++)
	{
		newmap[n]=new GRID_DATA[dlg.width*dlg.height];
		for(u16 y=0;y<dlg.height;y++)for(u16 x=0;x<dlg.width;x++)
		{
			if(x+dlg.dx>-1 && x+dlg.dx<step_header[cur_step].width &&
				y+dlg.dy>-1 && y+dlg.dy<step_header[cur_step].height)
			{
				newmap[n][x+y*dlg.width]=
					map[n][cur_step][x+dlg.dx+(y+dlg.dy)*step_header[cur_step].width];
			}
			else
			{
				*(u32*)&newmap[n][x+y*dlg.width]=n?0xFFFFFFFF:0;
			}
		}
		delete[] map[n][cur_step];
		map[n][cur_step]=newmap[n];
	}
	step_header[cur_step].width=dlg.width;
	step_header[cur_step].height=dlg.height;

	//移动所有物件的位置
	int ctmp;
	if(obj[cur_step])for(u16 i=0;i<step_header[cur_step].obj_count;i++)
	{
		if(obj[cur_step][i].is_folder)
		{
			ctmp=obj[cur_step][i].fx-dlg.dx*16;
			if(ctmp<0)ctmp=0;
			else if(ctmp>step_header[cur_step].width*16)ctmp=step_header[cur_step].width*16-16;
			obj[cur_step][i].fx=(u16)ctmp;

			ctmp=obj[cur_step][i].fy-dlg.dy*16;
			if(ctmp<0)ctmp=0;
			else if(ctmp>step_header[cur_step].height*16)ctmp=step_header[cur_step].height*16-16;
			obj[cur_step][i].fy=(u16)ctmp;
			for(u16 j=0;j<obj[cur_step][i].len;j++)
			{
				ctmp=obj[cur_step][i].o[j].x-dlg.dx*16;
				if(ctmp<0)ctmp=0;
				else if(ctmp>step_header[cur_step].width*16)ctmp=step_header[cur_step].width*16-16;
				obj[cur_step][i].o[j].x=(u16)ctmp;

				ctmp=obj[cur_step][i].o[j].y-dlg.dy*16;
				if(ctmp<0)ctmp=0;
				else if(ctmp>step_header[cur_step].height*16)ctmp=step_header[cur_step].height*16-16;
				obj[cur_step][i].o[j].y=(u16)ctmp;
			}
		}
		else
		{
			ctmp=obj[cur_step][i].o[0].x-dlg.dx*16;
			if(ctmp<0)ctmp=0;
			else if(ctmp>step_header[cur_step].width*16)ctmp=step_header[cur_step].width*16-16;
			obj[cur_step][i].o[0].x=(u16)ctmp;

			ctmp=obj[cur_step][i].o[0].y-dlg.dy*16;
			if(ctmp<0)ctmp=0;
			else if(ctmp>step_header[cur_step].height*16)ctmp=step_header[cur_step].height*16-16;
			obj[cur_step][i].o[0].y=(u16)ctmp;
		}
	}
	
	OnNMDblclkTreeFile(0,0);//重新加载地图
	
}

//编辑传送装置
void CMapDeluxeDlg::OnBnClickedButtonDoor()
{
	if(cur_step==0xFFFF)return;
	u16 tcount=step_header[cur_step].door_count;
	DOOR_DATA *tdata;
	if(tcount)
	{
		tdata=new DOOR_DATA[tcount];
		memcpy(tdata,door[cur_step],tcount*sizeof(DOOR_DATA));
	}
	else
	{
		tdata=0;
	}
	CDlgDoor dlg;
	dlg.pcount=&tcount;
	dlg.ppdata=&tdata;
	//添加坐标预设菜单
	CString str;
	u8 det0,det1;
	int menuidx=0;
	for(u16 y=0;y<step_header[cur_step].height;y++)for(u16 x=0;x<step_header[cur_step].width;x++)
	{
		det0=map[0][cur_step][x+y*step_header[cur_step].width].det;
		det1=map[1][cur_step][x+y*step_header[cur_step].width].det;
		if(det0==0x10||det0==0x36||det0==0x37||det0==0x90||det0==0xB6||det0==0xB7)
		{
			str.Format(_T("(%d,%d)%s"),x,y,CodeTran_Det(det0));
			dlg.m_MenuXY.AppendMenu(MF_STRING,DOOR_XY_MENU_ID_BASE+menuidx,str);
			menuidx++;
		}
		else if(det1==0x10||det1==0x36||det1==0x37||det1==0x90||det1==0xB6||det1==0xB7)
		{
			str.Format(_T("(%d,%d)(掀开)%s"),x,y,CodeTran_Det(det1));
			dlg.m_MenuXY.AppendMenu(MF_STRING,DOOR_XY_MENU_ID_BASE+menuidx,str);
			menuidx++;
		}
	}
	if(dlg.DoModal()==IDOK)
	{
		if(step_header[cur_step].door_count)
		{
			delete[] door[cur_step];
		}
		step_header[cur_step].door_count=tcount;
		door[cur_step]=tdata;
	}
	else
	{
		if(tcount)delete[] tdata;
	}
}


//清空地图
void CMapDeluxeDlg::OnBnClickedClearMap()
{
	if(cur_step==0xFFFF)return;
	if(MessageBox(_T("会将本地图完全清空，就和新的一样，数据不可恢复（当然SL大法除外）。\n是否继续?"),
		_T("警告"),MB_YESNO)==IDYES)
	{
		for(s32 z=0;z<step_header[cur_step].width*step_header[cur_step].height;z++)
		{
			*(u32*)&map[0][cur_step][z]=0;
			*(u32*)&map[1][cur_step][z]=0xFFFFFFFF;

		}
		Mos_Clear();
		CDC* pDC=GetDC();
		PaintMap();
		PresentMap(pDC);
		ReleaseDC(pDC);
	}

}

//响应从外部拖入的文件
void CMapDeluxeDlg::OnDropFiles(HDROP hDropInfo)
{
	TCHAR fname[256]={0};
	DragQueryFile(hDropInfo,0,fname,255);
	DragFinish(hDropInfo);

	CString strFileName=fname;
	CFile file;
	
	if(file.Open(strFileName,CFile::modeReadWrite))
	{
#ifdef CHECK_ROM_MAGIC
		char MagicTmp[16];
		file.Seek(0x7FFFF0,CFile::begin);
		file.Read(MagicTmp,16);
		if(strcmp(MagicTmp,MagicStr)!=0)
		{
			MessageBox(_T("所选文件非可解析的梦之泉ROM。\n请选择本程序创建的ROM！"),_T("错误"),MB_ICONERROR);
			file.Close();
			return;
		}
#endif
		ReadRom(file);
		m_EditFileName.SetWindowText(strFileName);
	}
	else
	{
		MessageBox(_T("未能打开文件！此文件可能正在被其它程序使用！"),_T("错误"),MB_ICONERROR);
	}



	CDialog::OnDropFiles(hDropInfo);
}

//Edg启动
void CMapDeluxeDlg::OnBnClickedCheckEdg()
{
	m_EditEdg.EnableWindow(m_CheckEdg.GetCheck());
}

//编辑起始画面
void CMapDeluxeDlg::OnBnClickedButtonRomImage()
{
	if(map[0][0]==0)return;
	CDlgRomImage dlg;
	dlg.use_rom_image=use_rom_image;
	memcpy(dlg.rom_image,rom_image,sizeof(u16)*240*160);
	if(dlg.DoModal()==IDOK){
		memcpy(rom_image,dlg.rom_image,sizeof(u16)*240*160);
		use_rom_image=dlg.use_rom_image;
	}
}

//测试游戏
void CMapDeluxeDlg::OnBnClickedButtonGameTest()
{
	if(map[0][0]==0)return;
	OnBnClickedButtonSave();
	
	CString str;
	m_EditFileName.GetWindowText(str);
	str=_T("VisualBoyAdvance.exe \"")+str+_T("\"");
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	ZeroMemory(&pi,sizeof(pi));
	ZeroMemory(&si,sizeof(si));
	si.cb=sizeof(si);
	TCHAR *str_t=new TCHAR[str.GetLength()+1];
	_tcscpy(str_t,str);
	if(!CreateProcess(0,str_t,0,0,0,0,0,0,&si,&pi))
	{
		MessageBox(_T("未找到程序VisualBoyAdvance.exe\n请将模拟器命名为\"VisualBoyAdvance.exe\"并放到与编辑器相同目录下"),_T("未找到模拟器"));
	}
	delete[] str_t;
}

//编辑Obj
void CMapDeluxeDlg::OnBnClickedButtonObj()
{
	if(cur_step==0xFFFF)return;
	CDlgObj dlg;
	PaintMap();

	dlg.width=step_header[cur_step].width*16;
	dlg.height=step_header[cur_step].height*16;
	CDC* pDC=GetDC();
	dlg.m_BmpBck.CreateCompatibleBitmap(pDC,dlg.width,dlg.height);
	dlg.m_BmpOut.CreateCompatibleBitmap(pDC,dlg.width,dlg.height);
	
	/*CDC newDC,newDC2;
	newDC.CreateCompatibleDC(pDC);
	newDC2.CreateCompatibleDC(pDC);*/

	m_TmpDC.SelectObject(&m_BmpMap);
	m_TmpDC2.SelectObject(&dlg.m_BmpBck);
	m_TmpDC2.BitBlt(0,0,dlg.width,dlg.height,&m_TmpDC,0,0,SRCCOPY);


	ReleaseDC(pDC);

	dlg.m_pTmpDC=&m_TmpDC;
	dlg.m_pTmpDC2=&m_TmpDC2;
	dlg.m_pBmpObjTex=&m_BmpObjTex;
	dlg.m_pBmpObjTexMask=&m_BmpObjTexMask;
	dlg.pobjlist=&obj[cur_step];
	dlg.pcount=&step_header[cur_step].obj_count;
	dlg.pobj_vertical=&step_header[cur_step].obj_vertical;
	dlg.auto_bufidx=&rom_mdxinfo.auto_obj_bufidx;
	
	dlg.DoModal();

	//newDC.DeleteDC();
	//newDC2.DeleteDC();
}

//也许以后会用，空闲响应
void CMapDeluxeDlg::OnKickIdle()
{
}

//关于
void CMapDeluxeDlg::OnBnClickedButtonAbout()
{
	CDlgAbout dlg;
	dlg.DoModal();
}

//导出地图
void CMapDeluxeDlg::OnBnClickedButtonStepExport()
{
	if(cur_step==0xFFFF)return;

	CString str;
	str.Format(_T("地图Level%d_Stage%d_Step%02d.")_T(MDXS_EXTEND_NAME),
		step_header[cur_step].level+1,
		step_header[cur_step].stage+1,
		step_header[cur_step].step);

	//打开文件
	CFileDialog filedlg(FALSE,_T(MDXS_EXTEND_NAME),str,
		OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,
		_T("MapDeluxe地图文件|*.")_T(MDXS_EXTEND_NAME)_T("||"),this);
	filedlg.m_ofn.lpstrTitle=_T("导出地图文件...");
	if(filedlg.DoModal()==IDCANCEL)return;
	CFile file;
	CString strFileName=filedlg.GetPathName();
	if(!file.Open(strFileName,CFile::modeCreate|CFile::modeWrite))
	{
		MessageBox(_T("未能创建文件，请重试"),_T("错误"),MB_ICONERROR);
		return;
	}
	WriteMdxsFile(file,
		&step_header[cur_step],
		map[0][cur_step],
		map[1][cur_step],
		door[cur_step],
		obj[cur_step],
		&wind[cur_step]);
	file.Close();
}

//导入地图
void CMapDeluxeDlg::OnBnClickedButtonStepImport()
{
	if(cur_step==0xFFFF)return;
	//打开文件
	CFileDialog filedlg(TRUE,0,0,OFN_HIDEREADONLY,
		_T("MapDeluxe地图文件|*.")_T(MDXS_EXTEND_NAME)_T("||"),this);
	if(filedlg.DoModal()==IDCANCEL)return;
	CFile file;
	CString strFileName=filedlg.GetPathName();
	if(!file.Open(strFileName,CFile::modeReadWrite))
	{
		MessageBox(_T("未能打开文件！此文件可能正在被其它程序使用！"),_T("错误"),MB_ICONERROR);
		return;
	}
	STEP_HEADER nstep_header;
	GRID_DATA* pmap0;
	GRID_DATA* pmap1;
	DOOR_DATA* pdoor;
	OBJ_DATA_EX* pobj;
	OBJ_DATA nwind;
	if(!ReadMdxsFile(file,&nstep_header,&pmap0,&pmap1,&pdoor,&pobj,&nwind))
	{
		MessageBox(_T("未能读取此文件！"),_T("错误"),MB_ICONERROR);
		file.Close();
		return;
	}
	file.Close();
	if(nstep_header.level!=step_header[cur_step].level||
		nstep_header.stage!=step_header[cur_step].stage||
		nstep_header.step!=step_header[cur_step].step)
	{
		if(MessageBox(_T("导入的地图与当前地图关卡号不同，是否继续？"),
			_T("警告"),MB_ICONWARNING|MB_YESNO)==IDNO)
		{
			delete[] pmap0;
			delete[] pmap1;
			delete[] pdoor;
			delete[] pobj;
			return;
		}
	}

	//游戏用基础信息保留
	nstep_header.level=step_header[cur_step].level;
	nstep_header.stage=step_header[cur_step].stage;
	nstep_header.step=step_header[cur_step].step;
	nstep_header.ptr_map=step_header[cur_step].ptr_map;
	nstep_header.ptr_nestmap=step_header[cur_step].ptr_nestmap;
	nstep_header.ptr_nestlist=step_header[cur_step].ptr_nestlist;
	nstep_header.ptr_door=step_header[cur_step].ptr_door;
	nstep_header.ptr_obj=step_header[cur_step].ptr_obj;

	step_header[cur_step]=nstep_header;
	wind[cur_step]=nwind;
	if(map[0][cur_step])delete[] map[0][cur_step];
	map[0][cur_step]=pmap0;
	if(map[1][cur_step])delete[] map[1][cur_step];
	map[1][cur_step]=pmap1;
	if(door[cur_step])delete[] door[cur_step];
	door[cur_step]=pdoor;
	if(obj[cur_step])delete[] obj[cur_step];
	obj[cur_step]=pobj;

	OnNMDblclkTreeFile(0,0);//重新加载地图
}

//操作历史子模块相关
void CMapDeluxeDlg::Mos_Push_(MAPOPT_INFO& moi)
{
	MAPOPT_STACK_NOTE* pnote=new MAPOPT_STACK_NOTE;
	pnote->info=moi;
	pnote->pnext=mos_header;
	mos_header=pnote;
}
void CMapDeluxeDlg::Mos_Push(MAPOPT_INFO& moi)
{
	Mos_Push_(moi);
	Ros_Clear();
	Mos_Dump();
}
bool CMapDeluxeDlg::Mos_Pop(MAPOPT_INFO& moi)
{
	if(!mos_header)return false;
	MAPOPT_STACK_NOTE* pnote=mos_header;
	moi=pnote->info;
	mos_header=mos_header->pnext;
	delete pnote;
	Ros_Push(moi);
	Mos_Dump();
	return true;
}
void CMapDeluxeDlg::Mos_Clear()
{
	Ros_Clear();
	MAPOPT_STACK_NOTE* pnote=mos_header;
	while(pnote){
		mos_header=mos_header->pnext;
		delete pnote;
		pnote=mos_header;
	}
	Ros_Clear();
	Mos_Dump();
}
void CMapDeluxeDlg::Mos_Dump()
{
	printf_debug("\n**************\nMos_Dump:\n");
	MAPOPT_STACK_NOTE* pnote=mos_header;
	while(pnote){
		printf_debug("(%3d,%3d)prev:%08X-%08X|curr:%08X-%08X\n",
			pnote->info.x,pnote->info.y,
			pnote->info.prev[0],pnote->info.prev[1],
			pnote->info.curr[0],pnote->info.curr[1]);
		pnote=pnote->pnext;
	}
	Ros_Dump();
}
void CMapDeluxeDlg::Ros_Push(MAPOPT_INFO& moi)
{
	MAPOPT_STACK_NOTE* pnote=new MAPOPT_STACK_NOTE;
	pnote->info=moi;
	pnote->pnext=ros_header;
	ros_header=pnote;
}
bool CMapDeluxeDlg::Ros_Pop(MAPOPT_INFO& moi)
{
	if(!ros_header)return false;
	MAPOPT_STACK_NOTE* pnote=ros_header;
	moi=pnote->info;
	ros_header=ros_header->pnext;
	delete pnote;
	Mos_Push_(moi);
	Mos_Dump();
	return true;
}
void CMapDeluxeDlg::Ros_Clear()
{
	MAPOPT_STACK_NOTE* pnote=ros_header;
	while(pnote){
		ros_header=ros_header->pnext;
		delete pnote;
		pnote=ros_header;
	}
}
void CMapDeluxeDlg::Ros_Dump()
{
	printf_debug("\n**************\nRos_Dump:\n");
	MAPOPT_STACK_NOTE* pnote=ros_header;
	while(pnote){
		printf_debug("(%3d,%3d)prev:%08X-%08X|curr:%08X-%08X\n",
			pnote->info.x,pnote->info.y,
			pnote->info.prev[0],pnote->info.prev[1],
			pnote->info.curr[0],pnote->info.curr[1]);
		pnote=pnote->pnext;
	}
}
void CMapDeluxeDlg::OnBnClickedButtonUndo()
{
	if(cur_step==0xFFFF)return;
	MAPOPT_INFO moi;
	if(!Mos_Pop(moi))
	{
		MessageBox(_T("已没有可撤销的操作"),_T("MapDeluxe"),0);
		return;
	}
	cur_x=moi.x;
	cur_y=moi.y;

	//验证
	if(*(u32*)&map[0][cur_step][cur_x+cur_y*step_header[cur_step].width] != *(u32*)&moi.curr[0]||
		*(u32*)&map[1][cur_step][cur_x+cur_y*step_header[cur_step].width] != *(u32*)&moi.curr[1])
	{
		MessageBox(_T("Error!\n发生诡异的错误！如果你看见这个对话框请立即联系作者"),_T("Error"),MB_ICONERROR);
	}
	map[0][cur_step][cur_x+cur_y*step_header[cur_step].width]=moi.prev[0];
	map[1][cur_step][cur_x+cur_y*step_header[cur_step].width]=moi.prev[1];
	CDC* pDC=GetDC();
	PaintMap();
	PresentMap(pDC);
	ReleaseDC(pDC);
}
void CMapDeluxeDlg::OnBnClickedButtonRedo()
{
	if(cur_step==0xFFFF)return;
	MAPOPT_INFO moi;
	if(!Ros_Pop(moi))
	{
		MessageBox(_T("已没有可重复的操作"),_T("MapDeluxe"),0);
		return;
	}
	cur_x=moi.x;
	cur_y=moi.y;

	//验证
	if(*(u32*)&map[0][cur_step][cur_x+cur_y*step_header[cur_step].width] != *(u32*)&moi.prev[0]||
		*(u32*)&map[1][cur_step][cur_x+cur_y*step_header[cur_step].width] != *(u32*)&moi.prev[1])
	{
		MessageBox(_T("Error!\n发生诡异的错误！如果你看见这个对话框请立即联系作者"),_T("Error"),MB_ICONERROR);
	}
	map[0][cur_step][cur_x+cur_y*step_header[cur_step].width]=moi.curr[0];
	map[1][cur_step][cur_x+cur_y*step_header[cur_step].width]=moi.curr[1];
	CDC* pDC=GetDC();
	PaintMap();
	PresentMap(pDC);
	ReleaseDC(pDC);
}
void CMapDeluxeDlg::OnBnClickedButtonResetMap()
{
	if(cur_step==0xFFFF)return;

	if(MessageBox(_T("将会将现在的地图恢复到原版游戏中的样子，不能反悔，是否继续？"),
		_T("警告"),MB_ICONWARNING|MB_YESNO)==IDNO)return;

	delete[] map[0][cur_step];map[0][cur_step]=0;
	delete[] map[1][cur_step];map[1][cur_step]=0;
	if(door[cur_step]){delete[] door[cur_step];door[cur_step]=0;}
	if(obj[cur_step]){delete[] obj[cur_step];obj[cur_step]=0;}


	u8* pRomRebuild=(u8*)mrrLockRomResource();
	u8* ptr;

	u32 lz77len;
	u8* lz77psrc;
	u8* lz77pdst;

	//Header
	///file.Seek(0x00800000+cur_step*0x4000,CFile::begin);
	ptr=pRomRebuild+0x00800000+cur_step*0x4000;
	///file.Read(&step_header[cur_step],sizeof(STEP_HEADER));
	memcpy(&step_header[cur_step],ptr,sizeof(STEP_HEADER));ptr+=sizeof(STEP_HEADER);

	//主地图
	///file.Seek(0x00800000+cur_step*0x4000+0x00001000,CFile::begin);
	ptr=pRomRebuild+0x00800000+cur_step*0x4000+0x00001000;
	///file.Read(&lz77len,4);
	memcpy(&lz77len,ptr,4);ptr+=4;
	lz77len>>=8;
	///file.Seek(-4,CFile::current);
	ptr-=4;
	lz77psrc=new u8[lz77len];
	lz77pdst=new u8[lz77len+0x100];
	///file.Read(lz77psrc,lz77len);
	memcpy(lz77psrc,ptr,lz77len);ptr+=lz77len;
	AgbUncompressLZ(lz77psrc,lz77pdst);
	delete[]lz77psrc;
	map[0][cur_step]=(GRID_DATA*)lz77pdst;

	//嵌套地图
	///file.Seek(0x00800000+cur_step*0x4000+0x00002000,CFile::begin);
	ptr=pRomRebuild+0x00800000+cur_step*0x4000+0x00002000;
	///file.Read(&lz77len,4);
	memcpy(&lz77len,ptr,4);ptr+=4;
	lz77len>>=8;
	///file.Seek(-4,CFile::current);
	ptr-=4;
	lz77psrc=new u8[lz77len];
	lz77pdst=new u8[lz77len+0x100];
	///file.Read(lz77psrc,lz77len);
	memcpy(lz77psrc,ptr,lz77len);ptr+=lz77len;
	AgbUncompressLZ(lz77psrc,lz77pdst);
	delete[]lz77psrc;
	map[1][cur_step]=new GRID_DATA[step_header[cur_step].width*step_header[cur_step].height];
	u16* pnest=(u16*)lz77pdst;
	for(s32 k=0;k<step_header[cur_step].width*step_header[cur_step].height;k++)
	{
		if(pnest[k]==0)
		{
			*(u32*)&map[1][cur_step][k]=0xFFFFFFFF;
		}
		else
		{
			///file.Seek(0x00800000+cur_step*0x4000+0x00003000+pnest[k]*4,CFile::begin);
			ptr=pRomRebuild+0x00800000+cur_step*0x4000+0x00003000+pnest[k]*4;
			///file.Read(&map[1][cur_step][k],4);
			memcpy(&map[1][cur_step][k],ptr,4);ptr+=4;
		}
	}
	delete[]lz77pdst;

	//门
	if(step_header[cur_step].door_count)
	{
		///file.Seek(0x00800000+cur_step*0x4000+0x00000100,CFile::begin);
		ptr=pRomRebuild+0x00800000+cur_step*0x4000+0x00000100;
		door[cur_step]=new DOOR_DATA[step_header[cur_step].door_count];
		///file.Read(door[cur_step],step_header[cur_step].door_count*sizeof(DOOR_DATA));
		memcpy(door[cur_step],ptr,step_header[cur_step].door_count*sizeof(DOOR_DATA));ptr+=step_header[cur_step].door_count*sizeof(DOOR_DATA);
	}

	//OBJ
	if(step_header[cur_step].obj_count)
	{
		///file.Seek(0x00800000+cur_step*0x4000+0x00000800,CFile::begin);
		ptr=pRomRebuild+0x00800000+cur_step*0x4000+0x00000800;
		obj[cur_step]=new OBJ_DATA_EX[step_header[cur_step].obj_count];
		for(u16 i=0;i<step_header[cur_step].obj_count;i++)
		{
			///file.Read(&obj[cur_step][i].o[0],sizeof(OBJ_DATA));
			memcpy(&obj[cur_step][i].o[0],ptr,sizeof(OBJ_DATA));ptr+=sizeof(OBJ_DATA);
		}
		for(u16 i=0;i<step_header[cur_step].obj_count;i++)
		{
			if(obj[cur_step][i].o[0].class_id==0x0006)
			{
				printf_debug("---\n");
				obj[cur_step][i].is_folder=1;
				obj[cur_step][i].len=obj[cur_step][i].o[0].paramB;
				obj[cur_step][i].fx=obj[cur_step][i].o[0].x;
				obj[cur_step][i].fy=obj[cur_step][i].o[0].y;
				if(obj[cur_step][i].len>3)throw;
				///file.Seek(0x00800000+cur_step*0x4000+0x00000800+
				///	obj[cur_step][i].o[0].paramA*sizeof(OBJ_DATA),CFile::begin);
				ptr=pRomRebuild+ 0x00800000+cur_step*0x4000+0x00000800+
					obj[cur_step][i].o[0].paramA*sizeof(OBJ_DATA);
				for(u8 j=0;j<obj[cur_step][i].len;j++)
				{
					///file.Read(&obj[cur_step][i].o[j],sizeof(OBJ_DATA));
					memcpy(&obj[cur_step][i].o[j],ptr,sizeof(OBJ_DATA));ptr+=sizeof(OBJ_DATA);
				}
			}
			else
			{
				obj[cur_step][i].is_folder=0;
				obj[cur_step][i].len=0;
			}
		}
	}
	//风
	if(step_header[cur_step].wind_index==0xFFFF)
	{
		wind[cur_step].class_id=0xFFFF;
	}
	else
	{
		///file.Seek(0x00800000+cur_step*0x4000+0x00000800+
		///	step_header[cur_step].wind_cur_step*sizeof(OBJ_DATA),CFile::begin);
		ptr=pRomRebuild+ 0x00800000+cur_step*0x4000+0x00000800+
			step_header[cur_step].wind_index*sizeof(OBJ_DATA);
		///file.Read(&wind[cur_step],sizeof(OBJ_DATA));
		memcpy(&wind[cur_step],ptr,sizeof(OBJ_DATA));ptr+=sizeof(OBJ_DATA);
		
	}


	mrrUnlockRomResource();

	OnNMDblclkTreeFile(0,0);//重新加载地图

}
void CMapDeluxeDlg::OnXzkbb()
{
	ShellExecute(0,_T("open"),_T("http://tieba.baidu.com/%D0%C7%D6%AE%BF%A8%B1%C8"),0,0,SW_SHOWNORMAL);
}
void CMapDeluxeDlg::OnTiezi()
{
	ShellExecute(0,_T("open"),_T("http://tieba.baidu.com/p/1816594640"),0,0,SW_SHOWNORMAL);
}
void CMapDeluxeDlg::OnInitMenu(CMenu* pMenu)
{

	CDialog::OnInitMenu(pMenu);

	MENUITEMINFO mii={0};
	mii.cbSize=sizeof(MENUITEMINFO);
	mii.fMask=MIIM_STATE;

	mii.fState=map[0][0]!=0?MFS_ENABLED:MFS_DISABLED;
	pMenu->SetMenuItemInfo(ID_M_SAVE,&mii);
	pMenu->SetMenuItemInfo(ID_M_SAVEAS,&mii);
	pMenu->SetMenuItemInfo(ID_M_SAVE_FINAL,&mii);
	pMenu->SetMenuItemInfo(ID_M_GAME_TEST,&mii);
	pMenu->SetMenuItemInfo(ID_M_ROM_IMAGE,&mii);

	mii.fState=mos_header!=0?MFS_ENABLED:MFS_DISABLED;
	pMenu->SetMenuItemInfo(ID_M_UNDO,&mii);

	mii.fState=ros_header!=0?MFS_ENABLED:MFS_DISABLED;
	pMenu->SetMenuItemInfo(ID_M_REDO,&mii);

	mii.fState=cur_step!=0xFFFF?MFS_ENABLED:MFS_DISABLED;
	pMenu->SetMenuItemInfo(ID_M_RESIZE,&mii);
	pMenu->SetMenuItemInfo(ID_M_DOOR,&mii);
	pMenu->SetMenuItemInfo(ID_M_OBJ,&mii);
	pMenu->SetMenuItemInfo(ID_M_WIND,&mii);
	pMenu->SetMenuItemInfo(ID_M_CLEAR_MAP,&mii);
	pMenu->SetMenuItemInfo(ID_M_RESET_MAP,&mii);
	pMenu->SetMenuItemInfo(ID_M_STEP_IMPORT,&mii);
	pMenu->SetMenuItemInfo(ID_M_STEP_EXPORT,&mii);
	pMenu->SetMenuItemInfo(ID_M_SAVE_TEST,&mii);
	
}

void CMapDeluxeDlg::OnBnClickedExit()
{
	DestroyWindow();
}
void CMapDeluxeDlg::OnBnClickedButtonTileFrtChg()
{
	if(cur_step==0xFFFF)return;
	CMenu m_MenuFrtTileChg,m_MenuUgl,m_MenuUglSub[10];
	CString str;
	m_MenuFrtTileChg.CreatePopupMenu();

	for(int i=0;gra_lib_frt_desc[i].ptr_tile;i++)
	{
		str.Format(_T("[Sys]%s"),gra_lib_frt_desc[i].desc);
		m_MenuFrtTileChg.AppendMenu(MF_STRING,FTC_MENU_ID_BASE+i,str);
	}
	for(int i=0;i<10;i++)
	{
		m_MenuUglSub[i].CreatePopupMenu();
	}
	for(int i=0;i<UGL_COUNT;i++)
	{
		str.Format(_T("[User#%d]%s"),i,ugl_rgn+ UGL_LEN*i +UGL_TITLE_OFFSET);
		m_MenuUglSub[i/10].AppendMenu(MF_STRING,FTC_MENU_ID_BASE+FTC_MENU_ID_SHIFT+i,str);
	}
	m_MenuUgl.CreatePopupMenu();
	for(int i=0;i<10;i++)
	{
		str.Format(_T("#%d~#%d"),i*10,i*10+9);
		m_MenuUgl.AppendMenu(MF_POPUP,(UINT)m_MenuUglSub[i].GetSafeHmenu(),str);
	}
	
	
	m_MenuFrtTileChg.AppendMenu(MF_POPUP,(UINT)m_MenuUgl.GetSafeHmenu(),_T("自定义贴图库"));

	RECT brect;
	m_ButtonFrtTileChg.GetWindowRect(&brect);
	m_MenuFrtTileChg.TrackPopupMenu(0,brect.right,brect.top,this);
	m_MenuFrtTileChg.DestroyMenu();
}
void CMapDeluxeDlg::OnFtcMenu(UINT id)
{
	if(cur_step==0xFFFF)return;
	id-=FTC_MENU_ID_BASE;
	if(id<FTC_MENU_ID_SHIFT)
	{
		step_header[cur_step].ptr_tile_frt=gra_lib_frt_desc[id].ptr_tile;
		step_header[cur_step].ptr_gra_map_frt=gra_lib_frt_desc[id].ptr_gra_map;
		step_header[cur_step].ptr_plt_frt=gra_lib_frt_desc[id].ptr_plt[0];
	}
	else
	{
		id-=FTC_MENU_ID_SHIFT;
		step_header[cur_step].ptr_tile_frt=ROM_UGL_OFFSET + UGL_LEN*id + UGL_TILE_OFFSET;
		step_header[cur_step].ptr_gra_map_frt=ROM_UGL_OFFSET + UGL_LEN*id + UGL_GMAP_OFFSET;
		step_header[cur_step].ptr_plt_frt=ROM_UGL_OFFSET + UGL_LEN*id + UGL_PLTS_OFFSET + UGL_PLTS_LEN*0;
	}
	OnNMDblclkTreeFile(0,0);
}
void CMapDeluxeDlg::OnBnClickedButtonPltFrtChg()
{
	if(cur_step==0xFFFF)return;
	CMenu m_MenuFrtPltChg;
	CString str;
	m_MenuFrtPltChg.CreatePopupMenu();
	u32 glidx=CodeTran_FrtGraLib_Index(step_header[cur_step].ptr_tile_frt);
	if(glidx!=0xFFFFFFFF)for(int i=0;gra_lib_frt_desc[glidx].ptr_plt[i];i++)
	{
		str.Format(_T("调色板#%d"),i);
		m_MenuFrtPltChg.AppendMenu(MF_STRING,FPC_MENU_ID_BASE+i,str);
	}
	else for(int i=0;i<UGL_PLTS_COUNT;i++)
	{
		str.Format(_T("调色板#%d"),i);
		m_MenuFrtPltChg.AppendMenu(MF_STRING,FPC_MENU_ID_BASE+i,str);
	}


	RECT brect;
	m_ButtonFrtPltChg.GetWindowRect(&brect);
	m_MenuFrtPltChg.TrackPopupMenu(0,brect.right,brect.top,this);
	m_MenuFrtPltChg.DestroyMenu();
}
void CMapDeluxeDlg::OnFpcMenu(UINT id)
{
	if(cur_step==0xFFFF)return;
	id-=FPC_MENU_ID_BASE;
	u32 glidx=CodeTran_FrtGraLib_Index(step_header[cur_step].ptr_tile_frt);
	if(glidx!=0xFFFFFFFF)
		step_header[cur_step].ptr_plt_frt=gra_lib_frt_desc[glidx].ptr_plt[id];
	else
		step_header[cur_step].ptr_plt_frt=step_header[cur_step].ptr_tile_frt+
			UGL_PLTS_OFFSET+UGL_PLTS_LEN*id;
	OnNMDblclkTreeFile(0,0);
}
void CMapDeluxeDlg::OnBnClickedButtonBckChg()
{
	if(cur_step==0xFFFF)return;
	CMenu m_Menu;
	CString str;
	m_Menu.CreatePopupMenu();

	for(int i=0;gra_lib_bck_desc[i].ptr_tile;i++)
	{
		str.Format(_T("[Sys]%s"),gra_lib_bck_desc[i].desc);
		m_Menu.AppendMenu(MF_STRING,BCC_MENU_ID_BASE+i,str);
	}

	RECT brect;
	m_ButtonBckChg.GetWindowRect(&brect);
	m_Menu.TrackPopupMenu(0,brect.right,brect.top,this);
	m_Menu.DestroyMenu();
}

void CMapDeluxeDlg::OnBccMenu(UINT id)
{
	if(cur_step==0xFFFF)return;
	id-=BCC_MENU_ID_BASE;
	step_header[cur_step].ptr_plt_bck=gra_lib_bck_desc[id].ptr_plt;
	step_header[cur_step].ptr_tile_bck=gra_lib_bck_desc[id].ptr_tile;
	step_header[cur_step].ptr_gra_map_bck=gra_lib_bck_desc[id].ptr_gra_map;
	StepHeaderOut();
}

const STEP_HEADER DEF_STEP_HEADER=
{
	0,//u8 level;//will change
	0,//u8 stage;//will change
	0,//u16 step;//will change
	0,//u8 bgm;
	1,//u8 lz77;
	0,//u16 x06;//=0
	0,//u32 ptr_map;//will change
	0,//u32 ptr_nestmap;//will change
	0,//u32 ptr_nestlist;//will change
	16,//u16 width;
	16,//u16 height;
	139379584,//u32 ptr_plt_frt;
	139020632,//u32 ptr_tile_frt;
	138427540,//u32 ptr_gra_map_frt;
	8,//u16 clip_x;
	8,//u16 clip_y;
	140048192,//u32 ptr_plt_bck;
	139033564,//u32 ptr_tile_bck;
	138529152,//u32 ptr_gra_map_bck;
	8,//u16 bck_mov;
	0,//u16 bck_dy;//
	0xFFFF,//u16 wind_index;
	0,//u16 door_count;
	0,//u16 obj_count;
	0,//u16 obj_vertical;

	0,//u32 gra_ani_index;
	0,//u32 ptr_door;//will change
	0,//u32 ptr_obj;//will change
	0,//u32 x4C;//=0

	0,//u16 begin_x;
	0,//u16 begin_y;
	0,//u8 x54;
	0,//u8 x55;
	0,//u8 bck_roll;
	0,//u8 spc_map;

};

void CMapDeluxeDlg::OnBnClickedNewWhite()
{
	//选择文件保存位置
	CFileDialog filedlg(FALSE,_T("gba"),_T("我的梦之泉.gba"),OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,
		_T("梦之泉ROM|*.gba||"),this);
	filedlg.m_ofn.lpstrTitle=_T("选择新游戏的保存位置...");
	if(filedlg.DoModal()==IDCANCEL)return;
	CFile file;
	CString strFileName=filedlg.GetPathName();
	if(!file.Open(strFileName,CFile::modeCreate|CFile::modeWrite))
	{
		MessageBox(_T("未能创建文件，请重试"),_T("错误"),MB_ICONERROR);
		return;
	}

	//加载并写入初始ROM
	void* pRomRebuild=mrrLockRomResource();
	file.Write(pRomRebuild,0x01000000);
	mrrUnlockRomResource();
	file.Close();

	file.Open(strFileName,CFile::modeReadWrite);
	ReadRom(file);

	rom_mdxinfo.auto_obj_bufidx=1;

	//清空地图
	STEP_HEADER step_header_tmp;
	for(int i=0;i<STEP_INDEXING_COUNT;i++)
	{
		step_header_tmp=step_header[i];
		step_header[i]=DEF_STEP_HEADER;
		step_header[i].level=step_header_tmp.level;
		step_header[i].stage=step_header_tmp.stage;
		step_header[i].step=step_header_tmp.step;
		step_header[i].ptr_map=step_header_tmp.ptr_map;
		step_header[i].ptr_nestmap=step_header_tmp.ptr_nestmap;
		step_header[i].ptr_nestlist=step_header_tmp.ptr_nestlist;
		step_header[i].ptr_door=step_header_tmp.ptr_door;
		step_header[i].ptr_obj=step_header_tmp.ptr_obj;
		delete[] map[0][i];
		map[0][i]=new GRID_DATA[DEF_STEP_HEADER.width*DEF_STEP_HEADER.height];
		ZeroMemory(map[0][i],sizeof(GRID_DATA)*DEF_STEP_HEADER.width*DEF_STEP_HEADER.height);
		delete[] map[1][i];
		map[1][i]=new GRID_DATA[DEF_STEP_HEADER.width*DEF_STEP_HEADER.height];
		ZeroMemory(map[1][i],sizeof(GRID_DATA)*DEF_STEP_HEADER.width*DEF_STEP_HEADER.height);
		delete[] door[i];
		door[i]=0;
		delete[] obj[i];
		obj[i]=0;
	}

	m_EditFileName.SetWindowText(strFileName);
	
	file.Close();
}

void CMapDeluxeDlg::OnBnClickedCheckMapOutBck()
{
	WritePrivateProfileString(_T("MAP"),_T("MapOutBck"),m_CheckMapOutBck.GetCheck()?
		_T("1"):_T("0"),ProfilePath);
	CDC* pDC=GetDC();
	PaintMap();
	PresentMap(pDC);
	ReleaseDC(pDC);
}

void CMapDeluxeDlg::OnAccMapChg()
{
	if(cur_step==0xFFFF)return;
	CString str;
	m_ComboMapChg.GetWindowText(str);
	int a=m_ComboMapChg.FindString(-1,str);
	if(a)
		m_ComboMapChg.SelectString(0,_T("贴图"));
	else
		m_ComboMapChg.SelectString(0,_T("判定"));

	OnCbnSelchangeComboMapchg();
	
}



void CMapDeluxeDlg::OnAccNestChg()
{
	if(cur_step==0xFFFF)return;
	m_CheckNest.SetCheck(m_CheckNest.GetCheck()?FALSE:TRUE);
	OnBnClickedCheckNest();
	
}

void CMapDeluxeDlg::OnCbnSelchangeComboWind()
{
	if(cur_step==0xFFFF)return;
	CString str;
	m_ComboWind.GetWindowText(str);
	//step_header[cur_step].spc_map=(u8)StrToI(str);
	u32 a,b;
	_stscanf(str,CODETRAN_FORMAT_WIND_POOR,&a,&b);
	wind[cur_step].class_id=(u16)a;
	wind[cur_step].paramA=(u8)b;
}

void CMapDeluxeDlg::OnBnClickedCheckNestAuto()
{
	WritePrivateProfileString(_T("MAP"),_T("NestAuto"),m_CheckNestAuto.GetCheck()?
		_T("1"):_T("0"),ProfilePath);
}

void CMapDeluxeDlg::OnBnClickedCheckGraAssoc()
{
	CDC *pDC=GetDC();
	PaintGraLib();
	PresentGraLib(pDC);
	ReleaseDC(pDC);
	WritePrivateProfileString(_T("MAP"),_T("GraAssoc"),m_CheckGraAssoc.GetCheck()?
		_T("1"):_T("0"),ProfilePath);
}


void CMapDeluxeDlg::OnCbnSelchangeComboScriptId()
{
	if(cur_step==0xFFFF)return;
	CString str;
	m_ComboScriptId.GetWindowText(str);
	step_header[cur_step].script_id=(u8)StrToI(str);
}
