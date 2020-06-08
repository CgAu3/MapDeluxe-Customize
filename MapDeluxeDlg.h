//主窗口类
//编写:wwylele

#pragma once
#include "afxwin.h"
#include "MapDataType.h"
#include "afxcmn.h"
#include "afxole.h"


#define FTC_MENU_ID_BASE 4001
#define FTC_MENU_ID_SHIFT 100 //自定义贴图库的菜单项的ID的换挡值
#define FPC_MENU_ID_BASE 4801
#define BCC_MENU_ID_BASE 5001

// CMapDeluxeDlg 对话框
class CMapDeluxeDlg : public CDialog
{
// 构造
public:
	CMapDeluxeDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MAIN };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

	
	STEP_HEADER step_header[STEP_INDEXING_COUNT];
	GRID_DATA* map[2][STEP_INDEXING_COUNT];//map[0][]=mainmap[],map[1][]=nestmap[]
	DOOR_DATA* door[STEP_INDEXING_COUNT];
	OBJ_DATA_EX* obj[STEP_INDEXING_COUNT];
	OBJ_DATA wind[STEP_INDEXING_COUNT];
	bool use_rom_image;
	u16 rom_image[240*160];
	ROM_MDXINFO rom_mdxinfo;
	u8 ugl_rgn[UGL_COUNT*UGL_LEN];

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CToolTipCtrl m_ToolTip;
	CStatusBar m_StatusBar;
	CEdit m_EditStepNumber;
	CButton m_CheckLz77;
	CComboBox m_ComboBgm;
	CComboBox m_ComboSpcMap;
	CEdit m_EditClipX;
	CEdit m_EditClipY;
	CEdit m_EditBeginX;
	CEdit m_EditBeginY;
	CEdit m_EditBckMov;
	CEdit m_EditX36;
	//CComboBox m_ComboGraAni;
	//CButton m_CheckX3E;
	CButton m_CheckX55;
	CButton m_CheckBckRoll;
	CEdit m_EditPltFrt;
	CEdit m_EditTileFrt;
	CEdit m_EditPltBck;

	CDC m_TmpDC,m_TmpDC2;
	CBitmap m_BmpMap;
	CBitmap m_BmpDet;
	CBitmap m_BmpDetMask;
	CBitmap m_BmpDetOut;
	CBitmap m_BmpGra;
	CBitmap m_BmpGraMask;
	CBitmap m_BmpGraOut; 
	CBitmap m_BmpNest;
	CBitmap m_BmpObjTex;
	CBitmap m_BmpObjTexMask;

	CBitmap m_mBmpNew;
	CBitmap m_mBmpOpen;
	CBitmap m_mBmpSave;
	CBitmap m_mBmpSaveas;
	CBitmap m_mBmpSaveFinal;
	CBitmap m_mBmpGameTest;
	CBitmap m_mBmpRomImage;
	CBitmap m_mBmpAbout;
	CBitmap m_mBmpXzkbb;
	CBitmap m_mBmpUndo;
	CBitmap m_mBmpRedo;
	CBitmap m_mBmpResize;
	CBitmap m_mBmpDoor;
	CBitmap m_mBmpObj;
	CBitmap m_mBmpStepImport;
	CBitmap m_mBmpStepExport;
	CBitmap m_mBmpWind;
	CBitmap m_mBmpSaveTest;
	

	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnDestroy();

	/*HGLOBAL hRomResData;
	void *pRomRebuild;
	void LockRomResource();
	void UnlockRomResource();*/

	void ClearData();
	afx_msg void OnBnClickedButtonOpen();
	afx_msg void OnBnClickedButtonNew();
	afx_msg void OnBnClickedButtonSave();
	void ReadRom(CFile& file);
	void WriteRom(CFile& file);
	CEdit m_EditFileName;
	CTreeCtrl m_Tree;
	HTREEITEM ti_rom;
	HTREEITEM ti_level[8];
	HTREEITEM ti_stage[8][8];
	HTREEITEM ti_step[STEP_INDEXING_COUNT];
	HTREEITEM ti_ugl[UGL_COUNT];
	HTREEITEM ti_ugl_level[10];
	HTREEITEM ti_ugl_head;
	afx_msg void OnNMDblclkTreeFile(NMHDR *pNMHDR, LRESULT *pResult);
	u32 cur_step;
	void StepHeaderOut();
	void LoadGraLib();
	u32 gralib_len;
	void ResetGraLibScrollBar();
	CScrollBar m_ScrollBarGraLib;
	
	u32 StrToI(CString &str);
	
	afx_msg void OnBnClickedCheckLz77();
	afx_msg void OnCbnSelchangeComboBgm();
	afx_msg void OnCbnSelchangeComboSpcmap();
	afx_msg void OnEnChangeEditClipX();
	afx_msg void OnEnChangeEditClipY();
	afx_msg void OnEnChangeEditBeginX();
	afx_msg void OnEnChangeEditBeginY();
	afx_msg void OnEnChangeEditBckMov();
	afx_msg void OnEnChangeEditUnk36();
	afx_msg void OnBnClickedCheckUnk55();
	afx_msg void OnBnClickedCheckBckroll();
	CScrollBar m_HScrollMap;
	CScrollBar m_VScrollMap;

	void PaintMapGrid(u16 x,u16 y);
	void PaintMap(u16 x=0xFFFF,u16 y=0xFFFF);
	void PresentMap(CDC* pDC);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	CComboBox m_ComboMapChg;

	u16 cur_x,cur_y;
	u16 cur_sel;
	u16 cur_chg;

	bool drawing;

	afx_msg void OnCbnSelchangeComboMapchg();
	void UpdateGridInfo();
	void UpdateLibInfo();

	void PaintGraLib();
	void PresentGraLib(CDC* pDC);
	
	CStatic m_StaticLibInfo;
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//CButton m_ButtonNew;
	//CButton m_ButtonOpen;
	//CButton m_ButtonSave;
	//CButton m_ButtonSaveAs;
	afx_msg void OnBnClickedButtonSaveTest();
	afx_msg void OnBnClickedButtonSaveas();
	CButton m_CheckNest;
	afx_msg void OnBnClickedCheckNest();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	CProgressCtrl m_Progress;
	afx_msg void OnBnClickedButtonSaveFinal();
	afx_msg void OnBnClickedButtonResize();
	//CButton m_ButtonResize;
	//CButton m_ButtonSaveFinal;
	CButton m_CheckNestAuto;
	afx_msg void OnBnClickedButtonDoor();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	void DrawGrid();
	afx_msg void OnBnClickedClearMap();
	afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnDropFiles(HDROP hDropInfo);
	CButton m_CheckEdg;
	CEdit m_EditEdg;
	afx_msg void OnBnClickedCheckEdg();
	afx_msg void OnBnClickedButtonRomImage();
	afx_msg void OnBnClickedButtonGameTest();
	//CButton m_ButtonRomImage;
	//CButton m_ButtonGameTest;
	afx_msg void OnBnClickedButtonObj();
	afx_msg void OnKickIdle();
	afx_msg void OnBnClickedButtonAbout();
	afx_msg void OnBnClickedButtonStepExport();
	afx_msg void OnBnClickedButtonStepImport();

	//操作历史子模块
	struct MAPOPT_INFO
	{
		u16 x,y;
		GRID_DATA prev[2];
		GRID_DATA curr[2];
	};
	struct MAPOPT_STACK_NOTE
	{
		MAPOPT_INFO info;
		MAPOPT_STACK_NOTE* pnext;
	} *mos_header,*ros_header;
	void Mos_Clear();
	void Mos_Push(MAPOPT_INFO& moi);
	void Mos_Push_(MAPOPT_INFO& moi);//仅内部调用
	bool Mos_Pop(MAPOPT_INFO& moi);
	void Mos_Dump();
	void Ros_Clear();//仅内部调用
	void Ros_Push(MAPOPT_INFO& moi);//仅内部调用
	bool Ros_Pop(MAPOPT_INFO& moi);
	void Ros_Dump();//仅内部调用

	afx_msg void OnBnClickedButtonUndo();
	afx_msg void OnBnClickedButtonRedo();
	afx_msg void OnBnClickedButtonResetMap();

	afx_msg void OnXzkbb();
	afx_msg void OnTiezi();
	afx_msg void OnInitMenu(CMenu* pMenu);

	afx_msg void OnBnClickedExit();


	CButton m_ButtonFrtTileChg;
	CButton m_ButtonFrtPltChg;
	CButton m_ButtonBckChg;
	afx_msg void OnBnClickedButtonTileFrtChg();
	afx_msg void OnFtcMenu(UINT id);
	afx_msg void OnBnClickedButtonPltFrtChg();
	afx_msg void OnFpcMenu(UINT id);
	afx_msg void OnBnClickedButtonBckChg();
	afx_msg void OnBccMenu(UINT id);
	CComboBox m_ComboGraAni;
	afx_msg void OnCbnSelchangeComboGraAni();

	HACCEL hAccel;

	void OnUglEdit(int ugl_index);

	afx_msg void OnBnClickedNewWhite();
	CButton m_CheckMapOutBck;
	afx_msg void OnBnClickedCheckMapOutBck();

	afx_msg void OnMenuSelect(UINT nItemID,UINT nFlags,HMENU hSysMenu);

	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	bool m_SetCursorResp;

	void OnAccMapChg();
	void OnAccNestChg();

	CComboBox m_ComboWind;
	afx_msg void OnCbnSelchangeComboWind();
	afx_msg void OnBnClickedCheckNestAuto();

	void CreateGraAssocTable();///
	
	CButton m_CheckGraAssoc;
	afx_msg void OnBnClickedCheckGraAssoc();

	CBitmap m_BmpKirby;
	CBrush m_BrushKirby;
	void DrawNuKirby(CDC* pDC);
	bool m_NuKirbyLeft;
#define NU_KIRBY_X 532
#define NU_KIRBY_Y 144

	CComboBox m_ComboScriptId;
	afx_msg void OnCbnSelchangeComboScriptId();
};
