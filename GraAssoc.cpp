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
	for(int i=0;gra_lib_frt_desc[i].ptr_tile;++i)//��������ͼ��
	{
		pgmapdata=(u8*)pRomRebuild+(gra_lib_frt_desc[i].ptr_gra_map-0x08000000);
		lz77len=*(u32*)(pgmapdata);
		lz77len>>=8;
		mapcount=lz77len/8;
		pListArray=new CList<u16>[mapcount*4];
		for(int step=0;step<STEP_INDEXING_COUNT;++step)
		if(step_header[step].ptr_gra_map_frt==gra_lib_frt_desc[i].ptr_gra_map)//�������йؿ�Ѱ��ƥ��ͼ��
		{
			for(int coor=0;coor<step_header[step].width*step_header[step].height;++coor)//�������и�
			{
				grid=map[1][step][coor];if(*(u32*)&grid==0xFFFFFFFF)grid=map[0][step][coor];
				if(grid.gra)//����˸�ͼ���ǿյ�
				{
					
					//�ϲ�ĸ�
					if(coor>=step_header[step].width)
					{
						grid2=map[1][step][coor-step_header[step].width];if(*(u32*)&grid2==0xFFFFFFFF)grid2=map[0][step][coor-step_header[step].width];
						if(!pListArray[grid.gra*4].Find(grid2.gra,0))pListArray[grid.gra*4].AddHead(grid2.gra);
					}
					//�²�ĸ�
					if(coor<step_header[step].width*(step_header[step].height-1))
					{
						grid2=map[1][step][coor+step_header[step].width];if(*(u32*)&grid2==0xFFFFFFFF)grid2=map[0][step][coor+step_header[step].width];
						if(!pListArray[grid.gra*4+1].Find(grid2.gra,0))pListArray[grid.gra*4+1].AddHead(grid2.gra);
					}
					//���ĸ�
					if(coor%step_header[step].width!=0)
					{
						grid2=map[1][step][coor-1];if(*(u32*)&grid2==0xFFFFFFFF)grid2=map[0][step][coor-1];
						if(!pListArray[grid.gra*4+2].Find(grid2.gra,0))pListArray[grid.gra*4+2].AddHead(grid2.gra);
					}
					//�Ҳ�ĸ�
					if((coor+1)%step_header[step].width!=0)
					{
						grid2=map[1][step][coor+1];if(*(u32*)&grid2==0xFFFFFFFF)grid2=map[0][step][coor+1];
						if(!pListArray[grid.gra*4+3].Find(grid2.gra,0))pListArray[grid.gra*4+3].AddHead(grid2.gra);
					}
				}
			}
		}
		//д���ļ�
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
GraAssocTable.bin�ļ�������
ÿ����ͼ�����ݵĿ�ͷ����д�ϸ���ͼ���ӳ���ַ��������ֽڻᱻ�ĳ�0xFF�����˿�ͷ�Ѷ���λ�õ�4�ֽ�
��ͷ֮��������ݣ����ֽ�Ϊ��λ�����飬0xFFFFΪһ����ͼ�����ݵĽ�������Ȼ�������һ�����顣
���������������ϡ��¡����ҡ���
������ͼ��Ľ�������0xFEDC��Ȼ�������һ����ͼ�⣨����ֽڲ��������ٲ�һ��0xFFFF��
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


	//�����ļ���λ��
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
	//����gaf�Ķ�ȡλ���Ѿ��ƶ�����������ʼλ��

	//��RomRebuil�еõ���ͼ�ⳤ��
	u8 *pgmapdata;
	u32 lz77len;
	u16 gmapcount;
	void* pRomRebuild=mrrLockRomResource();
	pgmapdata=(u8*)pRomRebuild+(gra_map-0x08000000);
	lz77len=*(u32*)(pgmapdata);
	lz77len>>=8;
	gmapcount=(u16)(lz77len/8);
	mrrUnlockRomResource();

	//��ȡ����
	GraAssocLa=new GRA_ASSOC_LIST[gmapcount];//�����µı�
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