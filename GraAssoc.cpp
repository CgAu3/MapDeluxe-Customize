#include "stdafx.h"
#include "MapDeluxe.h"
#include "MapDeluxeDlg.h"
#include "CodeTran.h"
#include "GraAssoc.h"

void CMapDeluxeDlg::CreateGraAssocTable()
{
	void* pRomRebuild=mrrLockRomResource();
	CFile outfile(_T("GraAssocTable.bin"),CFile::modeCreate|CFile::modeWrite);
	CList<u16> *pListArray;
	u8 *pgmapdata;
	u32 lz77len;
	u32 mapcount;
	GRID_DATA grid,grid2;

	u32 ptr_gra_map_FF;
	u16 u16FFFF=0xFFFF,u16wv,u16FEDC=0xFEDC;
	POSITION pst;
	for(int i=0;gra_lib_frt_desc[i].ptr_tile;++i)//遍历所有图库
	{
		pgmapdata=(u8*)pRomRebuild+(gra_lib_frt_desc[i].ptr_gra_map-0x08000000);
		lz77len=*(u32*)(pgmapdata);
		lz77len>>=8;
		mapcount=lz77len/8;
		pListArray=new CList<u16>[mapcount*4];
		for(int step=0;step<STEP_INDEXING_COUNT;++step)
		if(step_header[step].ptr_gra_map_frt==gra_lib_frt_desc[i].ptr_gra_map)//遍历所有关卡寻找匹配图库
		{
			for(int coor=0;coor<step_header[step].width*step_header[step].height;++coor)//遍历所有格
			{
				grid=map[1][step][coor];if(*(u32*)&grid==0xFFFFFFFF)grid=map[0][step][coor];
				if(grid.gra)//如果此格图像不是空的
				{
					
					//上侧的格
					if(coor>=step_header[step].width)
					{
						grid2=map[1][step][coor-step_header[step].width];if(*(u32*)&grid2==0xFFFFFFFF)grid2=map[0][step][coor-step_header[step].width];
						if(!pListArray[grid.gra*4].Find(grid2.gra,0))pListArray[grid.gra*4].AddHead(grid2.gra);
					}
					//下侧的格
					if(coor<step_header[step].width*(step_header[step].height-1))
					{
						grid2=map[1][step][coor+step_header[step].width];if(*(u32*)&grid2==0xFFFFFFFF)grid2=map[0][step][coor+step_header[step].width];
						if(!pListArray[grid.gra*4+1].Find(grid2.gra,0))pListArray[grid.gra*4+1].AddHead(grid2.gra);
					}
					//左侧的格
					if(coor%step_header[step].width!=0)
					{
						grid2=map[1][step][coor-1];if(*(u32*)&grid2==0xFFFFFFFF)grid2=map[0][step][coor-1];
						if(!pListArray[grid.gra*4+2].Find(grid2.gra,0))pListArray[grid.gra*4+2].AddHead(grid2.gra);
					}
					//右侧的格
					if((coor+1)%step_header[step].width!=0)
					{
						grid2=map[1][step][coor+1];if(*(u32*)&grid2==0xFFFFFFFF)grid2=map[0][step][coor+1];
						if(!pListArray[grid.gra*4+3].Find(grid2.gra,0))pListArray[grid.gra*4+3].AddHead(grid2.gra);
					}
				}
			}
		}
		//写入文件
		ptr_gra_map_FF=gra_lib_frt_desc[i].ptr_gra_map|0xFF000000;
		if(outfile.GetPosition()%4)outfile.Write(&u16FFFF,2);
		outfile.Write(&ptr_gra_map_FF,4);

		for(u32 j=0;j<mapcount*4;j++)
		{
			pst=pListArray[j].GetHeadPosition();
			while(pst)
			{
				u16wv=pListArray[j].GetNext(pst);
				outfile.Write(&u16wv,2);
			}
			outfile.Write(&u16FFFF,2);
		}
		outfile.Write(&u16FEDC,2);
		delete[] pListArray;
	}
	mrrUnlockRomResource();
	outfile.Close();
}

/*
GraAssocTable.bin文件描述：
每个贴图库数据的开头都会写上该贴图库的映射地址（但最高字节会被改成0xFF），此开头已对齐位置到4字节
开头之后就是数据，两字节为单位的数组，0xFFFF为一个贴图块数据的结束符，然后进入下一个数组。
数组依次排列是上、下、左、右……
整个贴图库的结束符是0xFEDC，然后进入下一个贴图库（如果字节不对齐则再补一个0xFFFF）
*/

GRA_ASSOC_LIST* GraAssocLa=0;
HRSRC hResInfo=0;
HGLOBAL hResGraAssocTable=0;
void LoadGraAssocTable(u32 gra_map)
{

	if(GraAssocLa)
	{
		delete[] GraAssocLa;
		GraAssocLa=0;
	}

	//CFile gaf;
	//gaf.Open(_T("GraAssocTable.bin"),CFile::modeRead);
	
	if(!hResInfo)
	{
		hResInfo=FindResource(AfxGetApp()->m_hInstance,MAKEINTRESOURCE(IDR_GRAASSOCTABLE),TEXT("BIN")); 
		hResGraAssocTable=LoadResource(AfxGetApp()->m_hInstance,hResInfo);
	}
	int gafsize=SizeofResource(AfxGetApp()->m_hInstance,hResInfo);
	u8* pgafb=(u8*)LockResource(hResGraAssocTable);
	u8* pgaf=pgafb;


	//查找文件中位置
	u32 gra_map_FF=0;
	while(gra_map_FF!=(gra_map|0xFF000000))
	{
		if(pgaf-pgafb>=gafsize-4)
		{
			//gaf.Close();
			UnlockResource(hResGraAssocTable);
			return;
		}
		//gaf.Read(&gra_map_FF,4);
		gra_map_FF=*(u32*)pgaf;pgaf+=4;
	}
	//现在gaf的读取位置已经移动到了数据起始位置

	//从RomRebuil中得到贴图库长度
	u8 *pgmapdata;
	u32 lz77len;
	u16 gmapcount;
	void* pRomRebuild=mrrLockRomResource();
	pgmapdata=(u8*)pRomRebuild+(gra_map-0x08000000);
	lz77len=*(u32*)(pgmapdata);
	lz77len>>=8;
	gmapcount=(u16)(lz77len/8);
	mrrUnlockRomResource();

	//读取数据
	GraAssocLa=new GRA_ASSOC_LIST[gmapcount];//建立新的表
	u16 fr=0;
	for(u16 i=0;i<gmapcount;i++)
	{
		
		while(1)
		{
			//gaf.Read(&fr,2);
			fr=*(u16*)pgaf;pgaf+=2;
			if(fr==0xFFFF)break;
			GraAssocLa[i].up.AddHead(fr);
		}
		while(1)
		{
			//gaf.Read(&fr,2);
			fr=*(u16*)pgaf;pgaf+=2;
			if(fr==0xFFFF)break;
			GraAssocLa[i].down.AddHead(fr);
		}
		while(1)
		{
			//gaf.Read(&fr,2);
			fr=*(u16*)pgaf;pgaf+=2;
			if(fr==0xFFFF)break;
			GraAssocLa[i].left.AddHead(fr);
		}
		while(1)
		{
			//gaf.Read(&fr,2);
			fr=*(u16*)pgaf;pgaf+=2;
			if(fr==0xFFFF)break;
			GraAssocLa[i].right.AddHead(fr);
		}
	}

	//gaf.Close();
	UnlockResource(hResGraAssocTable);
	
}