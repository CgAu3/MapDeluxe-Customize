#pragma once
#include "MapDataType.h"
#define MDXS_EXTEND_NAME "mdxs"

void WriteMdxsFile(CFile& file,
	STEP_HEADER *pstep_header,
	GRID_DATA* pmap0,
	GRID_DATA* pmap1,
	DOOR_DATA* pdoor,
	OBJ_DATA_EX* pobj,
	OBJ_DATA* pwind);
bool ReadMdxsFile(CFile& file,
	STEP_HEADER *pstep_header,
	GRID_DATA** ppmap0,
	GRID_DATA** ppmap1,
	DOOR_DATA** ppdoor,
	OBJ_DATA_EX** ppobj,
	OBJ_DATA* wind);