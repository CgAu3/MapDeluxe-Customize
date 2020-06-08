

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号

#define STEP_INDEXING_COUNT 292
#define DOOR_XY_MENU_ID_BASE 3001



class CMapDeluxeApp : public CWinApp
{
public:
	CMapDeluxeApp();

	virtual BOOL InitInstance();
	virtual void OnHelp();

	

	

	DECLARE_MESSAGE_MAP()
};


CString GetProductVersion();

extern CString ProfilePath;

//MdxRomRebuild.dll
typedef void* (__cdecl* FTmrrLockRomResource)();
extern FTmrrLockRomResource mrrLockRomResource;
typedef void (__cdecl* FTmrrUnlockRomResource)();
extern FTmrrUnlockRomResource mrrUnlockRomResource;
typedef int (__cdecl* FTmrrGetRomVersion)();
extern FTmrrGetRomVersion mrrGetRomVersion;

//AgbLz77.dll
typedef u32 (__cdecl* FTAgbCompressLZ)(const u8 *srcp,u32 size,u8 *dstp);
extern FTAgbCompressLZ AgbCompressLZ;
typedef u32 (__cdecl* FTAgbUncompressLZ)(const u8 *srcp,u8 *destp);
extern FTAgbUncompressLZ AgbUncompressLZ;



#define DreamapDx
#define DREAMAPDX
#define MapDeluxe
#define MAPDELUXE
#define wwylele
#define WWYLELE
#define SOLUTION_NAME "DreamapDx"
#define PROJECT_NAME "MapDeluxe"
#define PROJECT_AUTHOR "wwylele"
#define PROJECT_GUID "{47813AD7-6F62-4597-B3E6-A6503FDBD4BA}"