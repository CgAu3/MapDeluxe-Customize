// DlgUgl.cpp : 实现文件
//

#include "stdafx.h"
#include "MapDeluxe.h"
#include "DlgUgl.h"
#include "CodeTran.h"
#include "DlgUglColor.h"
#include "DlgUglTile.h"
#include "DlgUglGmap.h"

#define PLT_OUT_X_OFF 40
#define PLT_OUT_Y_OFF 16



// CDlgUgl 对话框

IMPLEMENT_DYNAMIC(CDlgUgl, CDialog)

CDlgUgl::CDlgUgl(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgUgl::IDD, pParent)
{

}

CDlgUgl::~CDlgUgl()
{
}

void CDlgUgl::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER_UGL_PLT, m_SliderPlt);
	DDX_Control(pDX, IDC_STATIC_UGL_PLT, m_StaticPlt);
	DDX_Control(pDX, IDC_EDIT_UGL_TITLE, m_EditTitle);
	DDX_Control(pDX, IDC_STATIC_UGL_TILE, m_StaticTile);
	DDX_Control(pDX, IDC_STATIC_UGL_COLOR, m_StaticColor);
	DDX_Control(pDX, IDC_SLIDER_UGL_TILE_PLT, m_SliderTilePlt);
	DDX_Control(pDX, IDC_CHECK_UGL_PLT_EXT, m_CheckPltExt);
	DDX_Control(pDX, IDC_STATIC_UGL_TILE_INFO, m_StaticTileInfo);
	DDX_Control(pDX, IDC_SCROLLBAR_UGL_GMAP, m_ScrollGmap);
	DDX_Control(pDX, IDC_BUTTON_UGL_IMPORT_SYS, m_ButtonImportSys);
}


BEGIN_MESSAGE_MAP(CDlgUgl, CDialog)

	ON_WM_VSCROLL()
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_EN_CHANGE(IDC_EDIT_UGL_TITLE, &CDlgUgl::OnEnChangeEditUglTitle)
	ON_BN_CLICKED(IDOK, &CDlgUgl::OnBnClickedOk)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_CHECK_UGL_PLT_EXT, &CDlgUgl::OnBnClickedCheckUglPltExt)
	ON_BN_CLICKED(IDC_BUTTON_UGL_IMPORT_SYS, &CDlgUgl::OnBnClickedButtonUglImportSys)
	ON_COMMAND_RANGE(FTCI_MENU_ID_BASE,FTCI_MENU_ID_BASE+100,&CDlgUgl::OnFpciMenu)
END_MESSAGE_MAP()


// CDlgUgl 消息处理程序

BOOL CDlgUgl::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_Ugl=m_UglIO;

	m_curgmap=0xFFFF;

	m_EditTitle.SetWindowTextW(m_Ugl.title);
	m_EditTitle.SetLimitText(15);

	CDC* pDC=GetDC();
	m_TmpDC.CreateCompatibleDC(pDC);
	m_BmpTmpPlt.CreateCompatibleBitmap(pDC,300,200);
	m_BmpTmpTile.CreateCompatibleBitmap(pDC,128,256);
	m_BmpTmpGmap.CreateCompatibleBitmap(pDC,256,(UGL_GMAP_MAX_COUNT/16+1)*16);
	
	m_Font.CreateFont(16,0,0,0,0,0,0,0,
		DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,PROOF_QUALITY,DEFAULT_PITCH|FF_DONTCARE,
		_T("Consolas"));
	m_TmpDC.SelectObject(&m_Font);
	pDC->SelectObject(&m_Font);
	m_TmpDC.SetBkMode(TRANSPARENT);


	ReleaseDC(pDC);
	m_SliderPlt.SetRange(0,15);
	m_SliderPlt.SetPos(0);
	m_SliderTilePlt.SetRange(1,9);
	m_SliderTilePlt.SetPos(1);

	//设置滚动条
	RECT vsrc;
	m_ScrollGmap.GetWindowRect(&vsrc);

	SCROLLINFO scrinfo={0};
	scrinfo.cbSize=sizeof(SCROLLINFO);
	scrinfo.fMask=SIF_PAGE|SIF_RANGE|SIF_POS;
	scrinfo.nPage=vsrc.bottom-vsrc.top;
	scrinfo.nMin=0;
	scrinfo.nMax=(UGL_GMAP_MAX_COUNT/16+1)*16-scrinfo.nPage;
	scrinfo.nPos=0;
	m_ScrollGmap.SetScrollInfo(&scrinfo);

	PaintTile();
	PaintGmap();

	return TRUE;
}


void CDlgUgl::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	
	if((CSliderCtrl*)pScrollBar==&m_SliderPlt)
	{
		CDC *pDC=GetDC();
		PresentPlt(pDC);
		PaintTile();
		PresentTile(pDC);
		PaintGmap();
		PresentGmap(pDC);
		ReleaseDC(pDC);
	}
	else
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
	   CDC *pDC=GetDC();
		PresentGmap(pDC);
		ReleaseDC(pDC);
	}
	

	CDialog::OnVScroll(nSBCode, nPos, pScrollBar);
}


void CDlgUgl::PresentPlt(CDC *pDC)
{
	m_TmpDC.SelectObject(&m_BmpTmpPlt);
	CString str;
	str.Format(_T("调色面#%d"),m_SliderPlt.GetPos());
	m_StaticPlt.SetWindowText(str);

	m_CheckPltExt.SetCheck(m_Ugl.plt_p[m_SliderPlt.GetPos()].plt_count==0x100);

	m_TmpDC.FillRect((LPRECT)CRect(0,0,300,200),&CBrush(RGB(255,255,255)));
	for(int i=0;i<10;i++)
	{
		str.Format(_T("行#%d"),i);
		m_TmpDC.TextOut(0,i*16+PLT_OUT_Y_OFF,str,str.GetLength());
	}
	for(int i=0;i<16;i++)
	{
		str.Format(_T("%d"),i);
		m_TmpDC.TextOutW(PLT_OUT_X_OFF+i*16,0,str,str.GetLength());
		CBrush Brush;
		for(int line=0;line<11;line++)
		{
			if(line<2)Brush.CreateHatchBrush(HS_DIAGCROSS,0);
			else Brush.CreateSolidBrush(R5G5B5X1toR8G8B8X8(
				m_Ugl.plt_p[m_SliderPlt.GetPos()].plt[(line-2)*16+i]));
			m_TmpDC.FillRect((LPRECT)&CRect(PLT_OUT_X_OFF+i*16,PLT_OUT_Y_OFF+line*16,
				PLT_OUT_X_OFF+i*16+15,PLT_OUT_Y_OFF+line*16+15),&Brush);
			Brush.DeleteObject();
		}
	}
	

	RECT strc;
	m_StaticPlt.GetWindowRect(&strc);
	ScreenToClient(&strc);
	pDC->BitBlt(strc.left,strc.bottom,
		300,176,&m_TmpDC,
		0,0,SRCCOPY);
	
}
void CDlgUgl::OnPaint()
{
	CPaintDC dc(this);
	PresentPlt(&dc);
	PresentTile(&dc);
	PresentGmap(&dc);
}
void CDlgUgl::PaintTile()
{
	CBrush BrushNn;
	BrushNn.CreateHatchBrush(HS_DIAGCROSS,0);
	m_TmpDC.SelectObject(&m_BmpTmpTile);
	u16 tx,ty;
	for(u16 i=0;i<512;i++)
	{
		tx=i%16;
		ty=i/16;
		if(i<m_Ugl.tile_count)for(int px=0;px<8;px++)for(int py=0;py<8;py++)
		{
			COLORREF clr;
			if(m_SliderTilePlt.GetPos()==1)clr=m_Ugl.tile[i].Get(px,py)*0x00111111;
			else clr=R5G5B5X1toR8G8B8X8(
				m_Ugl.plt_p[m_SliderPlt.GetPos()].plt[
				(m_SliderTilePlt.GetPos()-2)*16
					+m_Ugl.tile[i].Get(px,py)]);
			m_TmpDC.SetPixel(tx*8+px,ty*8+py,clr);
		}
		else
		{
			m_TmpDC.FillRect((LPRECT)&CRect(tx*8,ty*8,tx*8+8,ty*8+8),&BrushNn);
		}
	}
}
void CDlgUgl::PresentTile(CDC *pDC)
{
	m_TmpDC.SelectObject(&m_BmpTmpTile);
	RECT strc;
	m_StaticTile.GetWindowRect(&strc);
	ScreenToClient(&strc);
	pDC->BitBlt(strc.left,strc.bottom,
		128,256,&m_TmpDC,
		0,0,SRCCOPY);
}
void CDlgUgl::PresentGmap(CDC *pDC)
{
	
	m_TmpDC.SelectObject(&m_BmpTmpGmap);
	RECT strc;
	m_ScrollGmap.GetWindowRect(&strc);
	ScreenToClient(&strc);
	pDC->BitBlt(strc.right,strc.top,
		256,strc.bottom-strc.top,&m_TmpDC,
		0,m_ScrollGmap.GetScrollPos(),SRCCOPY);
}
void CDlgUgl::PaintGmap()
{
	m_TmpDC.SelectObject(&m_BmpTmpGmap);
	u16 submapping;
	bool flipx,flipy;
	u8 pltcls;
	u8 pltidx;
	u32 drx,dry;
	for(u32 i=0;i<m_Ugl.gmap_count;i++)
	{
		for(int subb=0;subb<4;subb++)
		{
			submapping=m_Ugl.gmap[i].mapping[subb]&0x3FF;
			if(submapping>=m_Ugl.tile_count){
				//不存在对应的tile?!那就画上血红色~~~
				for(int by=0;by<8;by++)for(int bx=0;bx<8;bx++)
				{
					drx=(i%16)*16+(subb%2)*8+bx;
					dry=(i/16)*16+(subb/2)*8+by;
					if(bx==by || bx+by==7)
						m_TmpDC.SetPixel(drx,dry,RGB(255,255,0));
					else
						m_TmpDC.SetPixel(drx,dry,RGB(255,0,0));
				}
			}
			else{
				//有对应的tile，真乖~~~
				flipx=m_Ugl.gmap[i].mapping[subb]&1024 ? true:false;
				flipy=m_Ugl.gmap[i].mapping[subb]&2048 ? true:false;
				pltcls=m_Ugl.gmap[i].mapping[subb]>>12;
				
				for(int by=0;by<8;by++)for(int bx=0;bx<8;bx++)
				{
					pltidx=m_Ugl.tile[submapping].Get(flipx?7-bx:bx,flipy?7-by:by);
					drx=(i%16)*16+(subb%2)*8+bx;
					dry=(i/16)*16+(subb/2)*8+by;
					if(pltidx!=0){//非透明色
						if(pltcls>=8)
						{
							//纳尼?!竟然有用到奇怪的调色板?!那还是画上血红色~~~
							m_TmpDC.SetPixel(drx,dry,RGB(255,0,0));
						}
						else m_TmpDC.SetPixel(drx,dry,
								R5G5B5X1toR8G8B8X8(m_Ugl.plt_p[m_SliderPlt.GetPos()]
									.plt[(pltcls-2)*16+(pltidx)])
								);
					}
					else
					{//透明色
						m_TmpDC.SetPixel(drx,dry,
							(drx&4) ^ (dry&4) ? RGB(250,250,250):RGB(255,255,255)
							);
					}
				}
			}
		}
	}
}
void CDlgUgl::OnMouseMove(UINT nFlags, CPoint point)
{
	

	CRect sptrc;
	m_StaticPlt.GetWindowRect((LPRECT)&sptrc);
	ScreenToClient((LPRECT)&sptrc);
	sptrc.top=sptrc.bottom+PLT_OUT_Y_OFF+32;
	sptrc.bottom=sptrc.top+128;
	sptrc.left+=PLT_OUT_X_OFF;
	sptrc.right=sptrc.left+256;
	if(sptrc.PtInRect((POINT)point))
	{
		point-=sptrc.TopLeft();
		CDC *pDC=GetDC();
		PresentColor(pDC,(u16)point.x,(u16)point.y);
		ReleaseDC(pDC);
	}
	else
	{
		m_StaticTile.GetWindowRect((LPRECT)&sptrc);
		ScreenToClient((LPRECT)&sptrc);
		sptrc.top=sptrc.bottom;
		sptrc.bottom+=256;
		sptrc.right=sptrc.left+128;
		if(sptrc.PtInRect((POINT)point))
		{
			point-=sptrc.TopLeft();
			CString str;
			str.Format(_T("瓦图#%d"),point.x/8+point.y/8*16);
			m_StaticTileInfo.SetWindowText(str);

		}
		else
		{
			m_ScrollGmap.GetWindowRect((LPRECT)&sptrc);
			ScreenToClient((LPRECT)&sptrc);
			sptrc.left=sptrc.right;
			sptrc.right+=256;
			if(sptrc.PtInRect((POINT)point))//如果是单击映射区域
			{
				point-=sptrc.TopLeft();
				point.y+=m_ScrollGmap.GetScrollPos();
				m_curgmap=(u16)(point.y/16*16+point.x/16);
				CDC* pDC=GetDC();
				PresentGmap(pDC);
				ReleaseDC(pDC);
			}
			else
			{
				m_curgmap=0xFFFF;
			}
		}
	}

	

	CDialog::OnMouseMove(nFlags, point);
}
void CDlgUgl::PresentColor(CDC *pDC,u16 x,u16 y)
{
	CRect sptrc;
	m_StaticPlt.GetWindowRect((LPRECT)&sptrc);
	ScreenToClient((LPRECT)&sptrc);
	sptrc.top=sptrc.bottom+PLT_OUT_Y_OFF+32;
	sptrc.bottom=sptrc.top+128;
	sptrc.left+=PLT_OUT_X_OFF;
	sptrc.right=sptrc.left+256;

	CString str;
	u16 color=m_Ugl.plt_p[m_SliderPlt.GetPos()].plt[y/16*16+x/16];
	pDC->FillRect((LPRECT)&CRect(sptrc.left,sptrc.bottom+8,sptrc.left+48,sptrc.bottom+56),
		&CBrush(R5G5B5X1toR8G8B8X8(color)));
	str.Format(_T("面#%d,行#%d,#%d\nR:%d\nG:%d\nB:%d"),
		m_SliderPlt.GetPos(),y/16+2,x/16,
		color&31,
		(color>>5)&31,
		(color>>10)&31
		);
	m_StaticColor.SetWindowText(str);
}

void CDlgUgl::OnLButtonDown(UINT nFlags, CPoint point)
{
	CRect sptrc;
	m_StaticPlt.GetWindowRect((LPRECT)&sptrc);
	ScreenToClient((LPRECT)&sptrc);
	sptrc.top=sptrc.bottom+PLT_OUT_Y_OFF+32;
	sptrc.bottom=sptrc.top+128;
	sptrc.left+=PLT_OUT_X_OFF;
	sptrc.right=sptrc.left+256;
	if(sptrc.PtInRect((POINT)point))//如果是单击调色板区域
	{
		point-=sptrc.TopLeft();
		CDlgUglColor dlg;
		dlg.m_pltcolor=m_Ugl.plt_p[m_SliderPlt.GetPos()].plt[point.y/16*16+point.x/16];
		if(dlg.DoModal()==IDOK)
		{
			m_Ugl.plt_p[m_SliderPlt.GetPos()].plt[point.y/16*16+point.x/16]=dlg.m_pltcolor;
			CDC *pDC=GetDC();
			PresentPlt(pDC);
			PresentColor(pDC,(u16)point.x,(u16)point.y);
			PaintTile();
			PresentTile(pDC);
			PaintGmap();
			PresentGmap(pDC);
			ReleaseDC(pDC);
		}
	}
	else
	{
		m_StaticTile.GetWindowRect((LPRECT)&sptrc);
		ScreenToClient((LPRECT)&sptrc);
		sptrc.top=sptrc.bottom;
		sptrc.bottom+=256;
		sptrc.right=sptrc.left+128;
		if(sptrc.PtInRect((POINT)point))//如果是单击瓦图区域
		{
			point-=sptrc.TopLeft();
			u16 tile_idx=(u16)(point.x/8+point.y/8*16);
			if(tile_idx<m_Ugl.tile_count)//如果瓦图有效
			{
				CDlgUglTile dlg;
				dlg.m_tile=m_Ugl.tile[tile_idx];
				//给Tile窗口传递调色板
				if(m_SliderTilePlt.GetPos()==1)for(int i=0;i<16;i++)
					dlg.m_pltline[i]=i*0x00111111;
				else for(int i=0;i<16;i++)
					dlg.m_pltline[i]=R5G5B5X1toR8G8B8X8(m_Ugl.plt_p[m_SliderPlt.GetPos()].plt
						[(m_SliderTilePlt.GetPos()-2)*16+i]);
				if(dlg.DoModal()==IDOK)
				{
					m_Ugl.tile[tile_idx]=dlg.m_tile;
					CDC *pDC=GetDC();
					PaintTile();
					PresentTile(pDC);
					PaintGmap();
					PresentGmap(pDC);
					ReleaseDC(pDC);
				}
			}
			else//如果瓦图无效
			{
				CString str;
				str.Format(_T("是否将瓦图扩展至%d个？"),tile_idx+1);
				if(MessageBox(str,_T("扩展瓦图"),MB_YESNO)==IDYES)
				{
					//新数据清零
					ZeroMemory(&m_Ugl.tile[m_Ugl.tile_count],
						(tile_idx+1-m_Ugl.tile_count)*sizeof(TILE));
					m_Ugl.tile_count=tile_idx+1;
					CDC *pDC=GetDC();
					PaintTile();
					PresentTile(pDC);
					PaintGmap();
					PresentGmap(pDC);
					ReleaseDC(pDC);
				}
			}
		}
		else
		{
			m_ScrollGmap.GetWindowRect((LPRECT)&sptrc);
			ScreenToClient((LPRECT)&sptrc);
			sptrc.left=sptrc.right;
			sptrc.right+=256;
			if(sptrc.PtInRect((POINT)point))//如果是单击映射区域
			{
				point-=sptrc.TopLeft();
				point.y+=m_ScrollGmap.GetScrollPos();
				u16 gmap_idx=(u16)(point.y/16*16+point.x/16);
				if(gmap_idx<m_Ugl.gmap_count)//如果映射有效
				{
					CDlgUglGmap dlg;
					dlg.m_BlockMapping=m_Ugl.gmap[gmap_idx];
					if(dlg.DoModal()==IDOK)
					{
						m_Ugl.gmap[gmap_idx]=dlg.m_BlockMapping;
						CDC *pDC=GetDC();
						PaintGmap();
						PresentGmap(pDC);
						ReleaseDC(pDC);
					}
				}
				else if(gmap_idx<UGL_GMAP_MAX_COUNT)//如果映射无效
				{
					CString str;
					str.Format(_T("是否将映射扩展至%d个？"),gmap_idx+1);
					if(MessageBox(str,_T("扩展映射"),MB_YESNO)==IDYES)
					{
						//新数据清零
						ZeroMemory(&m_Ugl.gmap[m_Ugl.gmap_count],
							(gmap_idx+1-m_Ugl.gmap_count)*sizeof(BLOCK_MAPPING));
						m_Ugl.gmap_count=gmap_idx+1;
						CDC *pDC=GetDC();
						PaintGmap();
						PresentGmap(pDC);
						ReleaseDC(pDC);
					}
				}
			}
		}
	}
	
	CDialog::OnLButtonDown(nFlags, point);
}

void CDlgUgl::OnEnChangeEditUglTitle()
{
	m_EditTitle.GetWindowText(m_Ugl.title,16);
}

void CDlgUgl::OnBnClickedOk()
{
	m_UglIO=m_Ugl;
	OnOK();
}

void CDlgUgl::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	
	if((CSliderCtrl*)pScrollBar==&m_SliderTilePlt)
	{
		CDC *pDC=GetDC();
		PaintTile();
		PresentTile(pDC);
		ReleaseDC(pDC);
	}
	else
	{
	}
	

	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CDlgUgl::OnBnClickedCheckUglPltExt()
{
	m_Ugl.plt_p[m_SliderPlt.GetPos()].plt_count=m_CheckPltExt.GetCheck()?0x100:0xC0;
}


void CDlgUgl::OnBnClickedButtonUglImportSys()
{
	CString str;
	CMenu menu;
	menu.CreatePopupMenu();
	for(int i=0;gra_lib_frt_desc[i].ptr_tile;i++)
	{
		str.Format(_T("[Sys]%s"),gra_lib_frt_desc[i].desc);
		menu.AppendMenu(MF_STRING,FTCI_MENU_ID_BASE+i,str);
	}
	RECT brect;
	m_ButtonImportSys.GetWindowRect(&brect);
	menu.TrackPopupMenu(0,brect.right,brect.top,this);
	menu.DestroyMenu();
}

void CDlgUgl::OnFpciMenu(UINT id)
{
	id-=FTCI_MENU_ID_BASE;
	void* pRomRebuild=mrrLockRomResource();

	//读取调色板
	ZeroMemory(&m_Ugl,sizeof(m_Ugl));
	u16* plt;
	for(int i=0;i<GRA_LIB_PLT_MAX_COUNT;i++)if(gra_lib_frt_desc[id].ptr_plt[i])
	{
		plt=(u16*)((u8*)pRomRebuild+(gra_lib_frt_desc[id].ptr_plt[i]-0x08000000));
		m_Ugl.plt_p[i].plt_count=*(plt++);
		memcpy(m_Ugl.plt_p[i].plt,plt,m_Ugl.plt_p[i].plt_count);
	}

	//读取瓦图
	u8* ptiledata;
	ptiledata=(u8*)pRomRebuild+(gra_lib_frt_desc[id].ptr_tile-0x08000000);
	u32 lz77len;
	lz77len=*(u32*)(ptiledata);
	if(lz77len==0)
	{
		m_Ugl.tile_count=0;
	}
	else
	{
		lz77len>>=8;
		m_Ugl.tile_count=(u16)(lz77len/sizeof(TILE));
		if(m_Ugl.tile_count>512)throw;
		AgbUncompressLZ(ptiledata,(u8*)m_Ugl.tile);
	}
	//读取映射
	u8* pmapdata;
	pmapdata=(u8*)pRomRebuild+(gra_lib_frt_desc[id].ptr_gra_map-0x08000000);
	lz77len=*(u32*)(pmapdata);
	if(lz77len==0)
	{
		m_Ugl.gmap_count=0;
	}
	else
	{
		lz77len>>=8;
		m_Ugl.gmap_count=(u16)(lz77len/sizeof(BLOCK_MAPPING));
		if(m_Ugl.gmap_count>884)throw;
		AgbUncompressLZ(pmapdata,(u8*)m_Ugl.gmap);
	}
	CDC *pDC=GetDC();
	PresentPlt(pDC);
	PaintTile();
	PresentTile(pDC);
	PaintGmap();
	PresentGmap(pDC);
	ReleaseDC(pDC);
}