#pragma once

#define CODETRAN_FORMAT _T("%d:%s")
#define CODETRAN_FORMAT_WIND _T("%04X,%02X,%s")
#define CODETRAN_FORMAT_WIND_POOR _T("%04X,%02X")

TCHAR* CodeTran_Bgm(u8 code);
TCHAR* CodeTran_SpcMap(u8 code);
TCHAR* CodeTran_Det(u8 code);
bool CodeTran_DetNset(u8 code);
u16 R8G8B8X8toR5G5B5X1(COLORREF value);
COLORREF R5G5B5X1toR8G8B8X8(u16 value);
TCHAR* CodeTran_Obj(u16 code);
TCHAR* CodeTran_FoeBeh(u16 objcode,u16 behcode);
TCHAR* CodeTran_FrtGraLib(u32 ptr_tile);
u32 CodeTran_FrtPlt(u32 ptr_tile,u32 ptr_plt);
u32 CodeTran_FrtGraLib_Index(u32 ptr_tile);
TCHAR* CodeTran_Bck(u32 ptr_plt,u32 ptr_tile,u32 ptr_gra_map);
TCHAR* CodeTran_GraAni(u32 code);
TCHAR* CodeTran_ScriptId(u8 code);

#define GRA_LIB_PLT_MAX_COUNT 16
struct GRA_LIB_FRT_DESC
{
	u32 ptr_tile;
	u32 ptr_gra_map;
	u32 ptr_plt[GRA_LIB_PLT_MAX_COUNT];
	TCHAR* desc;
};
struct GRA_LIB_BCK_DESC
{
	u32 ptr_plt;
	u32 ptr_tile;
	u32 ptr_gra_map;
	TCHAR* desc;
};
extern const GRA_LIB_FRT_DESC gra_lib_frt_desc[];
extern const GRA_LIB_BCK_DESC gra_lib_bck_desc[];

struct OBJ_TEX
{
	u16 obj_class;
	//贴图上的坐标
	u16 tex_x;
	u16 tex_y;
	//小贴图尺寸
	u16 tex_w;
	u16 tex_h;
	//焦点在小贴图上的坐标
	u16 fcs_x;
	u16 fcs_y;
};
extern const OBJ_TEX obj_tex[];
u32 CodeTran_ObjTex(u16 obj_class);