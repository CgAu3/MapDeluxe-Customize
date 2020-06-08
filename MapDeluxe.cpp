//MapDeluxe.cpp
//主入口
//编写:wwylele

#include "stdafx.h"
#include "MapDeluxe.h"
#include "MapDeluxeDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#pragma comment(lib,"Version.lib")

#define WANT_MRR_VERSION 4001

CString ProfilePath;

FTmrrLockRomResource mrrLockRomResource;
FTmrrUnlockRomResource mrrUnlockRomResource;
FTmrrGetRomVersion mrrGetRomVersion;
FTAgbCompressLZ AgbCompressLZ;
FTAgbUncompressLZ AgbUncompressLZ;

// CMapDeluxeApp

BEGIN_MESSAGE_MAP(CMapDeluxeApp, CWinApp)
	ON_COMMAND(ID_HELP, &CMapDeluxeApp::OnHelp)
END_MESSAGE_MAP()


// CMapDeluxeApp 构造

CMapDeluxeApp::CMapDeluxeApp()
{
}


// 唯一的一个 CMapDeluxeApp 对象

CMapDeluxeApp theApp_MapDeluxe_by_wwylele_Why_do_I_write_such_a_fucking_long_name;


// CMapDeluxeApp 初始化

BOOL CMapDeluxeApp::InitInstance()
{
	//加载额外dll
	HMODULE hMdlRR=LoadLibrary(_T("MdxRomRebuild.dll"));
	if(!hMdlRR)
	{
		MessageBox(0,_T("未找到或无法加载MdxRomRebuild.dll\n程序将终止\n")
			_T("请到相关网站下载最新完整程序包，或在百度上联系作者：wwylele"),_T("启动失败"),MB_ICONERROR);
		return FALSE;
	}
	mrrLockRomResource=(FTmrrLockRomResource)GetProcAddress(hMdlRR,"LockRomResource");
	mrrUnlockRomResource=(FTmrrUnlockRomResource)GetProcAddress(hMdlRR,"UnlockRomResource");
	mrrGetRomVersion=(FTmrrGetRomVersion)GetProcAddress(hMdlRR,"GetRomVersion");
	if(mrrGetRomVersion()!=WANT_MRR_VERSION)
	{
		CString str;
		str.Format(_T("找到MdxRomRebuild.dll但版本不对应\n")
			_T("程序所需MdxRomRebuild.dll版本:%d\n")
			_T("现找到的MdxRomRebuild.dll版本:%d\n程序将终止\n")
			_T("请到相关网站下载最新完整程序包，或在百度上联系作者：wwylele"),WANT_MRR_VERSION,mrrGetRomVersion());
		MessageBox(0,str,_T("启动失败"),MB_ICONERROR);
		return FALSE;
	}

	HMODULE hMdlAL=LoadLibrary(_T("AgbLz77.dll"));
	if(!hMdlAL)
	{
		MessageBox(0,_T("未找到或无法加载AgbLz77.dll\n程序将终止\n")
			_T("请到相关网站下载最新完整程序包，或在百度上联系作者：wwylele"),_T("启动失败"),MB_ICONERROR);
		return FALSE;
	}
	AgbCompressLZ=(FTAgbCompressLZ)GetProcAddress(hMdlAL,"AgbCompressLZ");
	AgbUncompressLZ=(FTAgbUncompressLZ)GetProcAddress(hMdlAL,"AgbUncompressLZ");

	//ini路径
	//TCHAR fp[MAX_PATH];
	//::GetModuleFileName(NULL,fp,MAX_PATH);
	//ProfilePath=fp;
	//ProfilePath+=_T(".ini");
	ProfilePath=_T(".\\MapDeluxe.ini");

	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);

	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	AfxEnableControlContainer();


	CMapDeluxeDlg* dlg=new CMapDeluxeDlg;
	m_pMainWnd = dlg;
	dlg->DoModal();
	delete dlg;


	return FALSE;
}

void CMapDeluxeApp::OnHelp()
{
	MessageBox(0,_T("作者偷懒，还没有来得及写帮助-_-|||"),_T("启动帮助失败"),0);
}
CString GetProductVersion()  
 {  
    int nMaxPathName = 4096; // Max length of file name/path  
     TCHAR *pBuffer;  
     UINT nItemLength;  
    void* pData, *lpBuffer;  
    CString sVersion;  
     DWORD dwInfoSize, dwHandle;  
    VS_FIXEDFILEINFO *pFileInfo;  
     // Get the file path and name  
    pBuffer = new TCHAR[nMaxPathName];  
    GetModuleFileName(NULL, pBuffer, nMaxPathName-1);  
  
     // Get File Version Info size  
     dwInfoSize = GetFileVersionInfoSize(pBuffer,  &dwHandle);  
     if(dwInfoSize > 0)  
    {  
       pData = new TCHAR[dwInfoSize];  
         if(GetFileVersionInfo(pBuffer, dwHandle,  dwInfoSize, pData))  
             if(VerQueryValue(pData,  _T("\\"), &lpBuffer,  &nItemLength))  
             {  
                pFileInfo = (VS_FIXEDFILEINFO*)lpBuffer;  
                sVersion.Format(_T("%d.%d.%d.%d"),   
                  pFileInfo->dwProductVersionMS >> 16,   
                 pFileInfo->dwProductVersionMS & 0xFFFF,   
                 pFileInfo->dwProductVersionLS >> 16,  
                  pFileInfo->dwProductVersionLS & 0xFFFF);      
                 // Calculate the product version as a number, you can delete the next statement if you don't need it.  
                 DWORD dwProductVersion =    (pFileInfo->dwProductVersionMS >> 16)   * 1000 +  
                                            (pFileInfo->dwProductVersionMS & 0xFFFF) * 100 +  
                                             (pFileInfo->dwProductVersionLS >> 16)   * 10 +  
                                             (pFileInfo->dwProductVersionLS & 0xFFFF) * 1;  
    
            }  
         // Delete the data buffer  
        delete [] pData;  
     }  
     // Get rid of the allocated string buffer  
     delete [] pBuffer;  
     return sVersion;  
}  


