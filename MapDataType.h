//游戏数据结构
#pragma once

struct STEP_HEADER
{
	u8 level;
	u8 stage;
	u16 step;
	u8 bgm;
	u8 lz77;
	u16 x06;//=0
	u32 ptr_map;
	u32 ptr_nestmap;

	u32 ptr_nestlist;
	u16 width;
	u16 height;
	u32 ptr_plt_frt;
	u32 ptr_tile_frt;

	u32 ptr_gra_map_frt;
	u16 clip_x;
	u16 clip_y;
	u32 ptr_plt_bck;
	u32 ptr_tile_bck;

	u32 ptr_gra_map_bck;
	u16 bck_mov;
	u16 bck_dy;//
	u16 wind_index;
	u16 door_count;
	u16 obj_count;
	u16 obj_vertical;

	u32 gra_ani_index;
	u32 ptr_door;
	u32 ptr_obj;
	u32 x4C;//=0

	u16 begin_x;
	u16 begin_y;
	u8 script_id;
	u8 x55;
	u8 bck_roll;
	u8 spc_map;

};
struct GRID_DATA
{
	u16 gra;
	u8 edg;
	u8 det;
};
/*struct DOOR_DATA
{
	u16 to_step;
	u16 from_x;
	u16 from_y;
	u16 to_x;
	u16 to_y;
	u16 x;
};*/
union DOOR_DATA
{
	struct{
		u16 to_step;
		u16 x;
		u16 y;
		u16 to_x;
		u16 to_y;
		u16 unk;
	}door;
	struct{
		u16 magic;//5555
		u16 x;
		u16 y;
		u16 unk1;
		u16 unk2;
		u16 unk3;
	}ret;
	struct{
		u16 magic;//6666
		u16 to_step;//0xFFFF mean end
		u16 x1;
		u16 x2;
		u16 x3;
		u16 unk2;
	}spc_rec;
	struct{
		u16 magic;//7777
		u16 to_step;
		u16 unk1;
		u16 x2;
		u16 x3;
		u16 unk2;
	}spc;
	struct{
		u16 magic;//8888
		u16 x;
		u16 y;
		u16 unk1;
		u16 unk2;
		u16 unk3;
	}goal;
};
struct OBJ_DATA
{
	u16 class_id;
	u8 paramA;
	u8 paramB;
	u16 x;
	u16 y;
};

struct OBJ_DATA_EX
{
	u16 is_folder;
	u16 len;
	u16 fx,fy;//Just use for folder
	OBJ_DATA o[3];// This is a waste of memory
	u32 GetPosCode(bool l2r,bool u2d,bool vert);
};

struct ROM_MDXINFO
{
	u8 auto_obj_bufidx;
	u8 rsv[100];
};
struct TILE
{
	u8 dt[32];
	u8 Get(u8 x,u8 y);
	
	void Set(u8 x,u8 y,u8 value);
	bool operator ==(TILE& value);
};


struct BLOCK_MAPPING
{
	u16 mapping[4];
};

#define ROM_IMAGE_OFFSET 0x00CC0000
#define ROM_IMAGE_CMD_OFFSET 0xEC
#define ROM_MDXINFO_OFFSET 0x00CD3000
#define ROM_UGL_OFFSET 0x08CE0000
#define UGL_COUNT 100
#define UGL_LEN 0x8000
#define UGL_TILE_OFFSET 0
#define UGL_GMAP_OFFSET 0x4000
#define UGL_GMAP_MAX_COUNT 884
#define UGL_PLTS_OFFSET 0x6000
#define UGL_PLTS_COUNT 16
#define UGL_PLTS_LEN 0x200
#define UGL_TITLE_OFFSET 0x6150