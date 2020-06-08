//MdxStepFile.cpp
//地图文件读写
//编写:wwylele

#include "stdafx.h"
#include "MdxStepFile.h"




#define MDXS_MAGIC 0x5358444D //"MDXS"
#define MDXS_CURRENT_VERSION 5001

struct MDXS_HEADER{
	u32 magic;
	u32 version;
	OBJ_DATA wind;
	u32 offset_map0;
	u32 offset_map1;
	u32 offset_door;
	u32 offset_obj;
	STEP_HEADER step_header;
	u8 reserve[0x80];
};

void WriteMdxsFile(CFile& file,
	STEP_HEADER *pstep_header,
	GRID_DATA* pmap0,
	GRID_DATA* pmap1,
	DOOR_DATA* pdoor,
	OBJ_DATA_EX* pobj,
	OBJ_DATA* pwind)
{
	MDXS_HEADER mdxs_header={0};
	file.Seek(sizeof(MDXS_HEADER),CFile::begin);
	
	//写入map0
	mdxs_header.offset_map0=(u32)file.GetPosition();
	file.Write(pmap0,pstep_header->width*pstep_header->height*sizeof(GRID_DATA));

	//写入map1
	mdxs_header.offset_map1=(u32)file.GetPosition();
	file.Write(pmap1,pstep_header->width*pstep_header->height*sizeof(GRID_DATA));

	//写入door
	mdxs_header.offset_door=(u32)file.GetPosition();
	file.Write(pdoor,pstep_header->door_count*sizeof(DOOR_DATA));

	//写入obj
	mdxs_header.offset_obj=(u32)file.GetPosition();
	file.Write(pobj,pstep_header->obj_count*sizeof(OBJ_DATA_EX));

	//写入Header
	mdxs_header.magic=MDXS_MAGIC;
	mdxs_header.version=MDXS_CURRENT_VERSION;
	mdxs_header.wind=*pwind;
	mdxs_header.step_header=*pstep_header;
	file.Seek(0,CFile::begin);
	file.Write(&mdxs_header,sizeof(MDXS_HEADER));

}
bool ReadMdxsFile(CFile& file,
	STEP_HEADER *pstep_header,
	GRID_DATA** ppmap0,
	GRID_DATA** ppmap1,
	DOOR_DATA** ppdoor,
	OBJ_DATA_EX** ppobj,
	OBJ_DATA* wind)
{
	MDXS_HEADER mdxs_header;
	file.Seek(0,CFile::begin);
	file.Read(&mdxs_header,sizeof(MDXS_HEADER));
	if(mdxs_header.magic!=MDXS_MAGIC || 
		mdxs_header.version!=MDXS_CURRENT_VERSION)return false;
	*wind=mdxs_header.wind;
	*pstep_header=mdxs_header.step_header;

	//读取map0
	*ppmap0=new GRID_DATA[pstep_header->width*pstep_header->height];
	file.Seek(mdxs_header.offset_map0,CFile::begin);
	file.Read(*ppmap0,pstep_header->width*pstep_header->height*sizeof(GRID_DATA));

	//读取map1
	*ppmap1=new GRID_DATA[pstep_header->width*pstep_header->height];
	file.Seek(mdxs_header.offset_map1,CFile::begin);
	file.Read(*ppmap1,pstep_header->width*pstep_header->height*sizeof(GRID_DATA));

	//读取door
	*ppdoor=new DOOR_DATA[pstep_header->door_count];
	file.Seek(mdxs_header.offset_door,CFile::begin);
	file.Read(*ppdoor,pstep_header->door_count*sizeof(DOOR_DATA));

	//读取obj
	*ppobj=new OBJ_DATA_EX[pstep_header->obj_count];
	file.Seek(mdxs_header.offset_obj,CFile::begin);
	file.Read(*ppobj,pstep_header->obj_count*sizeof(OBJ_DATA_EX));

	return true;
}