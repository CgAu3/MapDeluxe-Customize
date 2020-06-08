//CodeTran.cpp
//
//编写:wwylele

#include "stdafx.h"
#include "CodeTran.h"




const GRA_LIB_FRT_DESC gra_lib_frt_desc[]={
	{0x08494958,0x08403C94,{0x084EC380,0x0857D67C,0x084EC444,0x0857D5B8,0x00000000,0x00000000,0x00000000,0x00000000},_T("草原")},
	{0x0848C264,0x08402140,{0x0858F4F4,0x0850CAA8,0x085627E4,0x0850CBAC,0x085628E8,0x00000000,0x00000000,0x00000000},_T("山岩")},
	{0x085026DC,0x0850137C,{0x0857D740,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000},_T("梦幻")},
	{0x08423A18,0x083FA590,{0x084EBF6C,0x08526B2C,0x084EC0F4,0x084EC030,0x0857EBCC,0x00000000,0x00000000,0x00000000},_T("洞窟")},
	{0x08461718,0x083FCE84,{0x0858EB6C,0x0850CCB0,0x08549ED4,0x0857EAC8,0x00000000,0x00000000,0x00000000,0x00000000},_T("森林")},
	{0x084CFEF4,0x08405404,{0x08590168,0x0850C9E4,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000},_T("树洞")},
	{0x084D9144,0x08406178,{0x083AF358,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000},_T("大树")},
	{0x084BEA18,0x0840426C,{0x0858FD58,0x0855745C,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000},_T("海岸")},
	{0x0845E4EC,0x083FC4F0,{0x0855C3E8,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000},_T("沙漠")},
	{0x08432464,0x083FBA40,{0x083AEF88,0x0857ED54,0x0857EE18,0x0857EEDC,0x00000000,0x00000000,0x00000000,0x00000000},_T("云彩")},
	{0x084940D4,0x084039D4,{0x0858F6BC,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000},_T("画室")},
	{0x08491650,0x0840333C,{0x0858F5F8,0x0850CF3C,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000},_T("高楼")},
	{0x0847FC00,0x083FE80C,{0x0858EF7C,0x08562C38,0x08562B74,0x08562AB0,0x085629EC,0x0850A604,0x0850CE78,0x00000000},_T("楼内")},
	{0x0848F050,0x08402A98,{0x0855C4AC,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000},_T("雾楼")},
	{0x085051F0,0x08504AA0,{0x085049DC,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000},_T("冰原")},
	{0x085079D0,0x085072EC,{0x08507228,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000},_T("城堡")},
	{0x084E9FF0,0x084E9778,{0x084E96B4,0x0850C920,0x084EC1B8,0x0857EC90,0x0850CDB4,0x00000000,0x00000000,0x00000000},_T("堡内")},
	{0x08587F88,0x08580A7C,{0x0857F1EC,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000},_T("飞艇")},
	{0x08583678,0x0857FAAC,{0x0857F064,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000},_T("艇内")},
	{0x0850A910,0x0850A6C8,{0x0850C5F0,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000},_T("地下")},
	{0x08585BA0,0x0858020C,{0x0857F128,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000},_T("帆船")},
	{0x08581388,0x0857F2B0,{0x0857EFA0,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000},_T("船内")},
	{0x084DB798,0x084067B8,{0x0859022C,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000},_T("黑白")},
	{0x0851CDA0,0x0850D30C,{0x0850D248,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000},_T("月亮")},
	{0x0850D034,0x0850D024,{0x0850D000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000},_T("没用")},
	{0x08422DC0,0x083FA06C,{0x0858E0D8,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000},_T("排错")},
	{0}//结束符
};
const GRA_LIB_BCK_DESC gra_lib_bck_desc[]={
	{0x0858F740,0x08497BDC,0x0841C980,_T("山川-草地")},//1-1-00
	{0x084EC508,0x084F4DF8,0x084ECF28,_T("瀑布")},//1-1-01
	{0x0858FE5C,0x084C131C,0x08420950,_T("夜空")},//1-1-03
	{0x0857D804,0x084B83BC,0x08420034,_T("湖边")},//1-2-00
	{0x0858E0FC,0x08426854,0x08406F78,_T("洞窟")},//1-2-03
	{0x0858E91C,0x0845377C,0x0840C82C,_T("山峰-云")},//1-3-00
	{0x083AF254,0x084D241C,0x084224A4,_T("森林")},//1-4-00
	{0x0858FA4C,0x084A64B0,0x0841E4DC,_T("大海")},//2-1-00
	{0x0858F948,0x084A1410,0x0841DBBC,_T("大海-太阳")},//2-2-00
	{0x0858F844,0x0849CD3C,0x0841D29C,_T("沙漠")},//2-2-03
	{0x0858FB50,0x084ABA94,0x0841EDF8,_T("海岛")},//2-3-00
	{0x0858FC54,0x084B1E98,0x0841F714,_T("大海-云")},//2-4-00
	{0x0853E494,0x0853EC98,0x0853E598,_T("画室")},//2-6-00
	{0x084EC27C,0x084ED848,0x0857DC14,_T("楼内")},//3-1-01
	{0x084EC27C,0x084ED848,0x084EC60C,_T("楼内2")},//3-2-03
	{0x0858E304,0x08434470,0x084081B0,_T("棉花糖")},//3-2-04
	{0x083AF04C,0x0844BA08,0x0840B658,_T("棉花糖2")},//3-4-00
	{0x084F9638,0x084FA05C,0x0857E370,_T("楼内3")},//3-4-03
	{0x0858E408,0x08437F88,0x08408ACC,_T("草地-山峰-云")},//3-5-00
	{0x084F9638,0x084FA05C,0x084F973C,_T("楼内4")},//3-5-02
	{0x0858E50C,0x0843D2D0,0x084093D4,_T("线状云")},//3-6-02
	{0x0850C81C,0x084ED848,0x084EC60C,_T("暗室")},//3-6-05
	{0x0851FFC0,0x08497BDC,0x0841C980,_T("日月1")},//3-7-00
	{0x0851FEBC,0x08497BDC,0x0841C980,_T("日月2")},//3-7-02
	{0x0858EE78,0x08479318,0x0841C060,_T("堡内")},//4-2-01
	{0x0858B5E4,0x084500D4,0x0840BF74,_T("飞云")},//4-3-01
	{0x085200C4,0x08520AE8,0x085201C8,_T("森林2")},//4-4-00
	{0x08568F20,0x085709B4,0x08569940,_T("河流")},//4-4-02
	{0x0858E200,0x0842CA84,0x08407894,_T("地下河")},//4-4-03
	{0x0858EC70,0x0846C7D8,0x0841AE18,_T("宫殿")},//4-6-00
	{0x0850C718,0x08472D78,0x0841B73C,_T("暗室2")},//4-6-01
	{0x0858ED74,0x08472D78,0x0841B73C,_T("宫殿2")},//4-6-02
	{0x0858E610,0x084402F4,0x08409CF0,_T("粉云")},//5-1-01
	{0x0855C5B0,0x0855CFD8,0x0855C6B4,_T("山峰-云2")},//5-1-02 
	{0x08562CFC,0x0856371C,0x08562E00,_T("地下河2")},//5-2-01 
	{0x0857DB10,0x085709B4,0x08569940,_T("黑暗山")},//5-3-00
	{0x0857DA0C,0x0856A2C0,0x08569024,_T("黑暗森林")},//5-3-02 
	{0x0850C614,0x08426854,0x08406F78,_T("黑暗地下河")},//5-3-04
	{0x0858FF60,0x084C6648,0x0842126C,_T("极光")},//5-3-05
	{0x08550844,0x08551264,0x08550948,_T("瀑布2")},//5-4-01 
	{0x084E23AC,0x084E2DCC,0x084E24B0,_T("森林3")},//5-5-00 
	{0x08576A2C,0x0857744C,0x08576B30,_T("地下")},//5-7-00 
	{0x085625DC,0x084B1E98,0x0841F714,_T("大海-云2")},//6-1-00
	{0x0857D908,0x084B83BC,0x08420034,_T("湖边2")},//6-2-00
	{0x08526EFC,0x08437F88,0x08408ACC,_T("草地-山峰-云2")},//6-2-01
	{0x08590064,0x084CB5BC,0x08421B88,_T("极光2")},//6-2-04
	{0x085626E0,0x084ABA94,0x0841EDF8,_T("海岛2")},//6-3-00
	{0x085430EC,0x08543A68,0x085431F0,_T("梅塔")},//6-7-00
	{0x0858EA20,0x08458CB8,0x0840D14C,_T("黑暗山峰-云")},//7-2-00
	{0x0858E714,0x08443B84,0x0840A670,_T("黑暗山峰-云2")},//7-2-02
	{0x08526CF4,0x084402F4,0x08409CF0,_T("黑暗云")},//7-2-03
	{0x08526BF0,0x08434470,0x084081B0,_T("黑暗棉花糖")},//7-2-04
	{0x08526DF8,0x0844BA08,0x0840B658,_T("黑暗棉花糖2")},//7-2-05
	{0x0858E818,0x08448EB0,0x0840AF8C,_T("黑暗线状云")},//7-2-06
	{0x084DC7E0,0x084DD200,0x084DC8E4,_T("湖水-夜")},//7-4-00
	{0x083AF150,0x08464618,0x0841A428,_T("梦之泉")},//7-7-00
	{0x0850D040,0x0851190C,0x0850D8FC,_T("梦魇1")},//8-1-00
	{0x0850D144,0x08517078,0x08510104,_T("梦魇2")},//8-1-01
	{0x0850D040,0x0851190C,0x0858B8D0,_T("梦魇3")},//8-1-02
	{0}
};

TCHAR* CodeTran_GraAni(u32 code)
{
	switch(code)
	{
	case 0x0:return _T("静态");
	case 0x1:return _T("流水");
	case 0x2:return _T("湖水");
	case 0x3:return _T("海水");
	case 0x4:return _T("冰水");
	case 0x5:return _T("雾１");
	case 0x6:return _T("雾２");
//	case 0x7:return _T("地图");
	case 0x8:return _T("池水");
	case 0x9:return _T("飞艇");
	case 0xA:return _T("艇内");
	case 0xB:return _T("帆船");
	case 0xC:return _T("船内");
	}
	return 0;
}

TCHAR* CodeTran_Bck(u32 ptr_plt,u32 ptr_tile,u32 ptr_gra_map)
{
	for(int i=0;i<sizeof(gra_lib_bck_desc)/sizeof(GRA_LIB_BCK_DESC);i++)
	{
		if(gra_lib_bck_desc[i].ptr_plt==ptr_plt &&
			gra_lib_bck_desc[i].ptr_tile==ptr_tile &&
			gra_lib_bck_desc[i].ptr_gra_map==ptr_gra_map)
		{
			return gra_lib_bck_desc[i].desc;
		}
	}
	return 0;
}
TCHAR* CodeTran_FrtGraLib(u32 ptr_tile)
{
	for(int i=0;i<sizeof(gra_lib_frt_desc)/sizeof(GRA_LIB_FRT_DESC);i++)
	{
		if(gra_lib_frt_desc[i].ptr_tile==ptr_tile)
		{
			return gra_lib_frt_desc[i].desc;
		}
	}
	return 0;
}
u32 CodeTran_FrtGraLib_Index(u32 ptr_tile)
{
	for(int i=0;i<sizeof(gra_lib_frt_desc)/sizeof(GRA_LIB_FRT_DESC);i++)
	{
		if(gra_lib_frt_desc[i].ptr_tile==ptr_tile)
		{
			return i;
		}
	}
	return 0xFFFFFFFF;
}
u32 CodeTran_FrtPlt(u32 ptr_tile,u32 ptr_plt)
{
	for(int i=0;i<sizeof(gra_lib_frt_desc)/sizeof(GRA_LIB_FRT_DESC);i++)
	{
		if(gra_lib_frt_desc[i].ptr_tile==ptr_tile)
		{
			for(int j=0;j<GRA_LIB_PLT_MAX_COUNT;j++)
			{
				if(gra_lib_frt_desc[i].ptr_plt[j]==ptr_plt)return j;
			}
		}
	}
	return 0xFFFFFFFF;
}

const OBJ_TEX obj_tex[]={
	{0x0001,  0,  0,19,19,10,10},//瓦多迪
	{0x0101, 19,  0,20,18,10, 9},//岩石
	{0x0201, 39,  0,20,17,10, 9},//睡觉
	{0x0301, 59,  0,21,20,10,10},//扫帚
	{0x0401, 80,  0,20,20,10,10},//企鹅
	{0x0501,100,  0,19,19,10,10},//激光
	{0x0601,119,  0,21,22,10,11},//雪人
	{0x0701,140,  0,23,21,11,12},//回力标
	{0x0801,  0, 24,18,18, 9, 9},//蘑菇
	{0x0901, 18, 24,19,22, 9,12},//瓦多度
	{0x0A01, 37, 24,22,22,11,11},//刺球
	{0x0B01, 59, 20,19,30, 9,15},//光明
	{0x0C01, 78, 24,19,19, 9, 9},//苍蝇
	{0x0D01, 97, 24,16,19, 8, 9},//卡布
	{0x0E01,113, 24,19,18, 9, 9},//巨爆
	{0x0F01,132, 24,16,16, 8, 8},//爆炸坚果
	{0x1001,  0, 50,20,17,10, 9},//小鸟
	{0x1101, 20, 50,19,21, 9,10},//小炮
	{0x1201, 39, 50,19,18, 9, 9},//闪电
	{0x1301, 58, 50,20,19,10, 9},//旋风
	{0x1401, 78, 50,20,21,10,10},//乌贼
	{0x1501, 98, 50,18,18, 9, 9},//scarfy
	{0x1601,116, 50,18,18, 9, 9},//球球
	{0x1701,134, 50,23,20,11,10},//超人
	{0x1801,  0, 71,20,21,10,10},//火焰
	{0x1901, 20, 71,24,20,12,10},//海葵
	{0x1A01, 44, 71,19,19, 9, 9},//蛙
	{0x1B01, 63, 71,21,17,10, 8},//鱼
	{0x1C01,117, 71,31,23,18,12},//剑士A
	{0x1D01, 84, 71,33,23,20,12},//剑士B
	{0x1E01,  0, 92,20,20,10,10},//Poppy
	{0x1F01, 20, 92,20,36,10,25},//Poppy苹果
	{0x2001, 40, 92,20,36,10,25},//PoppyM果
	{0x2101, 60,110,20,18,10, 9},//海螺
	{0x2201, 80,110,19,17, 9, 8},//车轮
	{0x2301, 99,110,16,16, 8, 8},//火球
	{0x2401,115,110,23,18,11, 9},//针刺
	{0x2501,138,110,24,23,12,11},//UFO
	{0x2701, 60, 91,23,19,11, 9},//猪
	{0x0104,  0,138,16,16, 8, 8},//1UP
	{0x0204, 16,138,16,16, 8, 8},//M
	{0x0304, 32,138,16,16, 8, 8},//棒棒糖
	{0x0404, 48,138,16,16, 8, 8},//药瓶
	{0x0504, 64,138,11,24, 5,12},//星星棒
	{0x0105,  0,165,48,32,24,24},//按钮
	{0x0205, 48,165, 8, 8, 0, 0},//导火索头
	{0x0405, 84,165,23,24,12,12},//传送星
	{0x0605, 56,165,28,32,14,24},//大炮
	{0}
};
u32 CodeTran_ObjTex(u16 obj_class)
{
	for(u32 i=0;obj_tex[i].obj_class;++i)
	{
		if(obj_tex[i].obj_class==obj_class)return i;
	}
	return 0xFFFFFFFF;
}

COLORREF R5G5B5X1toR8G8B8X8(u16 value)
{
	return RGB(
		(value&0x1F)*255/31,
		((value&0x3E0)>>5)*255/31,
		(value>>10)*255/31);
}
u16 R8G8B8X8toR5G5B5X1(COLORREF value)
{
	return (GetRValue(value)*31/255)|
		((GetGValue(value)*31/255)<<5)|
		((GetBValue(value)*31/255)<<10);
}
TCHAR* CodeTran_Bgm(u8 code)
{
	switch(code)
	{
	case 0:return _T("Music#02");
	case 1:return _T("Music#13-WarpStar");
	case 2:return _T("Music#10");
	case 3:return _T("Music#26-死亡");
	case 4:return _T("Music#27-Level1大地图");
	case 5:return _T("Music#28-Level2大地图");
	case 6:return _T("Music#29-Level3大地图");
	case 7:return _T("Music#30-Level4大地图");
	case 8:return _T("Music#31-Level5大地图");
	case 9:return _T("Music#32-Level6大地图");
	case 10:return _T("Music#33-Level7大地图");
	case 0xB:return _T("Music#04");
	case 0xC:return _T("Music#07");
	case 0xD:return _T("Music#15-卡比舞");
	case 0xE:return _T("Music#14-卡比舞缩短版");
	case 0xF:return _T("Music#09");
	case 0x10:return _T("Music#43-GameOver");
	case 0x11:return _T("Music#05");
	case 0x12:return _T("Music#08");
	case 0x13:return _T("Music#42-无敌");
	case 0x14:return _T("Music#19-GreenGreens");
	case 0x15:return _T("Music#03");
	case 0x16:return _T("Music#06");
	case 0x17:return _T("Music#39");
	case 0x18:return _T("Music#25-Ending");
	case 0x19:return _T("Music#17");
	case 0x1A:return _T("Music#00");
	case 0x1B:return _T("Music#20-VsDedede");
	case 0x1C:return _T("Music#40");
	case 0x1D:return _T("Music#41");
	case 0x1E:return _T("Music#12");
	case 0x1F:return _T("Music#21");
	case 0x20:return _T("Music#22");
	case 0x21:return _T("Music#23");
	case 0x22:return _T("Music#24");
	case 0x23:return _T("Music#34");
	//case 0x24:return _T("Music#");
	case 0x25:return _T("Music#11");
	case 0x26:return _T("Music#18");
	case 0x27:return _T("Music#16");
	case 0x28:return _T("Music#01");
	case 0x29:return _T("风");
	case 0x2A:return _T("Music#36");
	case 0x2B:return _T("Music#37");
	case 0x2C:return _T("Music#38");
	//case 0x2D:return _T("Music#");
	case 0x2E:return _T("Music#35");
	case 0x2F:return _T("无头Music#02");
	case 0x30:return _T("无头Music#04");
	case 0x31:return _T("无头Music#07");
	case 0x32:return _T("无头Music#05");
	case 0x33:return _T("无头Music#08");
	case 0x34:return _T("无头Music#19");
	case 0x35:return _T("无头Music#03");
	case 0x36:return _T("无头Music#06");
	case 0x37:return _T("无头Music#09");
	case 0x38:return _T("梦魇出现-这是个什么鬼BGM?!");

	case 0xFF:return _T("无音乐");
	default:
		return 0;
	}
}
TCHAR* CodeTran_SpcMap(u8 code)
{
	switch(code)
	{
	case 0:return _T("无");
	case 1:return _T("?");
	case 2:return _T("?");
	case 3:return _T("?");
	case 4:return _T("?");
	case 5:return _T("大BOSS关");
	case 6:return _T("?");
	case 7:return _T("?");
	case 8:return _T("?");
	case 9:return _T("?");
	default:
		return 0;
	}
}

bool CodeTran_DetNset(u8 code)
{
	switch(code)
	{
	case 0x20:return true;//return _T("易碎砖");
	case 0x24:return true;//return _T("星星砖");
	case 0x2D:return true;//return _T("爆炸连锁砖");
	case 0x2E:return true;//return _T("炸弹砖");
	case 0x2F:return true;//return _T("钢砖");
	case 0x33:return true;//return _T("木桩");
	case 0x34:return true;//return _T("爆炸连锁单项平台");
	case 0x35:return true;//return _T("隐藏爆炸连锁砖");
	case 0x38:return true;//return _T("导火索│");
	case 0x39:return true;//return _T("导火索─");
	case 0x3A:return true;//return _T("导火索└");
	case 0x3B:return true;//return _T("导火索┘");
	case 0x3C:return true;//return _T("导火索┌");
	case 0x3D:return true;//return _T("导火索┐");
	default:return false;
	}
}
TCHAR* CodeTran_Det(u8 code)
{
	switch(code)
	{
	case 0x00:return _T("无");
	case 0x01:return _T("墙");
	case 0x02:return _T("斜上坡");
	case 0x03:return _T("斜下坡");
	case 0x04:return _T("缓斜上坡左");
	case 0x05:return _T("缓斜上坡右");
	case 0x06:return _T("缓斜下坡左");
	case 0x07:return _T("缓斜下坡右");
	case 0x08:return _T("反斜下坡");
	case 0x09:return _T("反斜上坡");
	case 0x0A:return _T("缓反斜下坡左");
	case 0x0B:return _T("缓反斜下坡右");
	case 0x0C:return _T("缓反斜上坡左");
	case 0x0D:return _T("缓反斜上坡右");
	//case 0x0E
	//case 0x0F
	case 0x10:return _T("门");
	case 0x11:return _T("单向平台");
	case 0x12:return _T("单向斜上平台");
	case 0x13:return _T("单向斜下平台");
	case 0x14:return _T("单向缓斜上平台左");
	case 0x15:return _T("单向缓斜上平台右");
	case 0x16:return _T("单向缓斜下平台左");
	case 0x17:return _T("单向缓斜下平台右");
	//case 0x18
	case 0x19:return _T("双向平台");
	case 0x1A:return _T("双向斜上平台");
	case 0x1B:return _T("双向斜下平台");
	case 0x1C:return _T("双向缓斜上平台左");
	case 0x1D:return _T("双向缓斜上平台右");
	case 0x1E:return _T("双向缓斜下平台左");
	case 0x1F:return _T("双向缓斜下平台右");
	case 0x20:return _T("易碎砖");
	case 0x24:return _T("星星砖");
	case 0x2D:return _T("爆炸连锁砖");
	case 0x2E:return _T("炸弹砖");
	case 0x2F:return _T("钢砖");
	case 0x30:return _T("梯子");
	case 0x31:return _T("梯子顶端");
	case 0x33:return _T("木桩");
	case 0x34:return _T("爆炸连锁单项平台");
	case 0x35:return _T("隐藏爆炸连锁砖");
	case 0x36:return _T("隐藏门");
	case 0x37:return _T("宽门");
	case 0x38:return _T("导火索│");
	case 0x39:return _T("导火索─");
	case 0x3A:return _T("导火索└");
	case 0x3B:return _T("导火索┘");
	case 0x3C:return _T("导火索┌");
	case 0x3D:return _T("导火索┐");
	case 0x40:return _T("风↑");
	case 0x41:return _T("风↗");
	case 0x42:return _T("风→");
	case 0x43:return _T("风↘");
	case 0x44:return _T("风↓");
	case 0x45:return _T("风↙");
	case 0x46:return _T("风←");
	case 0x47:return _T("风↖");
	case 0x48:return _T("风坡↗");
	case 0x49:return _T("风坡↖");
	case 0x4A:return _T("风坡↙");
	case 0x4B:return _T("风坡↘");
	case 0x4C:return _T("反风坡↖");
	case 0x4D:return _T("反风坡↗");
	case 0x4E:return _T("反风坡↘");
	case 0x4F:return _T("反风坡↙");
	case 0x60:return _T("刺↓");
	case 0x61:return _T("刺↑");
	case 0x62:return _T("刺←");
	case 0x63:return _T("刺→");
	case 0x70:return _T("冰墙");
	case 0x71:return _T("冰斜上坡");
	case 0x72:return _T("冰斜下坡");
	case 0x73:return _T("冰缓斜上坡左");
	case 0x74:return _T("冰缓斜上坡右");
	case 0x75:return _T("冰缓斜下坡左");
	case 0x76:return _T("冰缓斜下坡右");
	case 0x80:return _T("水");
	//case 0x01:return _T("墙");
	case 0x82:return _T("水中斜上坡");
	case 0x83:return _T("水中斜下坡");
	case 0x84:return _T("水中缓斜上坡左");
	case 0x85:return _T("水中缓斜上坡右");
	case 0x86:return _T("水中缓斜下坡左");
	case 0x87:return _T("水中缓斜下坡右");
	case 0x88:return _T("水中反斜下坡");
	case 0x89:return _T("水中反斜上坡");
	case 0x8A:return _T("水中缓反斜下坡左");
	case 0x8B:return _T("水中缓反斜下坡右");
	case 0x8C:return _T("水中缓反斜上坡左");
	case 0x8D:return _T("水中缓反斜上坡右");
	case 0x90:return _T("水中门");
	case 0x91:return _T("水中单向平台");
	case 0xB6:return _T("水中隐藏门");
	case 0xB7:return _T("水中宽门");
	case 0xC0:return _T("水流↑");
	case 0xC1:return _T("水流↗");
	case 0xC2:return _T("水流→");
	case 0xC3:return _T("水流↘");
	case 0xC4:return _T("水流↓");
	case 0xC5:return _T("水流↙");
	case 0xC6:return _T("水流←");
	case 0xC7:return _T("水流↖");
	case 0xC8:return _T("水流坡↗");
	case 0xC9:return _T("水流坡↖");
	case 0xCA:return _T("水流坡↙");
	case 0xCB:return _T("水流坡↘");
	case 0xCC:return _T("反水流坡↖");
	case 0xCD:return _T("反水流坡↗");
	case 0xCE:return _T("反水流坡↘");
	case 0xCF:return _T("反风水流坡↙");
	case 0xE0:return _T("水中刺↓");
	case 0xE1:return _T("水中刺↑");
	case 0xE2:return _T("水中刺←");
	case 0xE3:return _T("水中刺→");
	default:return _T("?");
	}
}

TCHAR* CodeTran_Obj(u16 code)
{
	switch(code)
	{
	case 0x0001:return _T("瓦多迪");
	case 0x0101:return _T("岩石");
	case 0x0201:return _T("睡觉");
	case 0x0301:return _T("扫帚");
	case 0x0401:return _T("企鹅");
	case 0x0501:return _T("激光");
	case 0x0601:return _T("雪人");
	case 0x0701:return _T("回力标");
	case 0x0801:return _T("蘑菇");
	case 0x0901:return _T("瓦多度");
	case 0x0A01:return _T("刺球");
	case 0x0B01:return _T("光明");
	case 0x0C01:return _T("苍蝇");
	case 0x0D01:return _T("卡布");
	case 0x0E01:return _T("巨爆");
	case 0x0F01:return _T("爆炸坚果");
	case 0x1001:return _T("小鸟");
	case 0x1101:return _T("小炮");
	case 0x1201:return _T("闪电");
	case 0x1301:return _T("旋风");
	case 0x1401:return _T("乌贼");
	case 0x1501:return _T("Scarfy");
	case 0x1601:return _T("球球");
	case 0x1701:return _T("超人");
	case 0x1801:return _T("火焰");
	case 0x1901:return _T("海葵");
	case 0x1A01:return _T("蛙");
	case 0x1B01:return _T("鱼");
	case 0x1C01:return _T("剑士A");
	case 0x1D01:return _T("剑士B");
	case 0x1E01:return _T("Puppy.JR");
	case 0x1F01:return _T("Puppy.JR苹果");
	case 0x2001:return _T("Puppy.JRM果");
	case 0x2101:return _T("海螺");
	case 0x2201:return _T("车轮");
	case 0x2301:return _T("火球");
	case 0x2401:return _T("针刺");
	case 0x2501:return _T("UFO");
	case 0x2601:return _T("阳伞(已删)");//
	case 0x2701:return _T("猪");
	//case 0x2801:return _T("消失");//
	case 0x2901:return _T("不动的锤子(已删)");//
	//case 0x2A01:return _T("贴图错误");//
	case 0x0003:return _T("Dedede");
	case 0x0103:return _T("画画");
	case 0x0203:return _T("梅塔");
	case 0x0303:return _T("挖土机");
	case 0x0403:return _T("日月");
	case 0x0503:return _T("大树");
	case 0x0603:return _T("云");
	case 0x0703:return _T("梦魇第一形态");
	case 0x0803:return _T("梦魔第二形态");
	//case 0x0903:return _T("");//
	//case 0x0A03:return _T("");//
	//case 0x0004:return _T("怪物消失");//
	case 0x0104:return _T("1UP");
	case 0x0204:return _T("M果");
	case 0x0304:return _T("棒棒糖");
	case 0x0404:return _T("药瓶");
	case 0x0504:return _T("星星棒");
	case 0x0105:return _T("按钮");
	case 0x0205:return _T("导火索头");
	case 0x0305:return _T("木桩");
	case 0x0405:return _T("传送星");
	//case 0x0505:return _T("");//
	case 0x0605:return _T("大炮");
	//case 0x0705:return _T("");//
	case 0x0805:return _T("风");
	case 0x0008:return _T("梅塔军队");
	
	case 0x0206:return _T("锁屏位置");
	case 0x0406:return _T("锁门位置");
	case 0x0506:return _T("锁砖位置");

	case 0x0007:return _T("锤子");
	case 0x0107:return _T("炸弹");
	case 0x0207:return _T("车轮");
	case 0x0307:return _T("冰冻");
	case 0x0407:return _T("闹钟");
	case 0x0507:return _T("摔跤");
	case 0x0607:return _T("狮子");
	case 0x0707:return _T("大象");
	default:return _T("?");
	}
}

TCHAR* CodeTran_FoeBeh(u16 objcode,u16 behcode)
{
	switch(objcode)
	{
	case 0x0001:switch(behcode){
		case 0:return _T("行进");
		case 1:return _T("折返行进");
		case 2:return _T("行进跳跃");
		case 3:return _T("阳伞行进");
		case 4:return _T("弱");
		case 5:return _T("阳伞静止");
		default:return 0;
		}
	case 0x0101:switch(behcode){
		case 0:return _T("间断行进");
		case 1:return _T("弱");
		case 2:return _T("静止");
		default:return 0;
		}
	case 0x0201:switch(behcode){
		case 0:return _T("正常");
		default:return 0;
		}
	case 0x0301:switch(behcode){
		case 0:return _T("正常");
		case 1:return _T("正常?");
		default:return 0;
		}
	case 0x0401:switch(behcode){
		case 0:return _T("正常");
		default:return 0;
		}
	case 0x0501:switch(behcode){
		case 0:return _T("行进");
		case 1:return _T("静止");
		default:return 0;
		}
	case 0x0601:switch(behcode){
		case 0:return _T("正常");
		default:return 0;
		}
	case 0x0701:switch(behcode){
		case 0:return _T("静止");
		case 1:return _T("行进");
		default:return 0;
		}
	case 0x0801:switch(behcode){
		case 0:return _T("正常");
		default:return 0;
		}
	case 0x0901:switch(behcode){
		case 0:return _T("行进");
		case 1:return _T("阳伞行进");
		case 2:return _T("弱");
		default:return 0;
		}
	case 0x0A01:switch(behcode){
		case 0:return _T("静止");
		case 1:return _T("垂直行进");
		case 2:return _T("水平行进");
		case 3:return _T("垂直正弦");
		default:return 0;
		}
	case 0x0B01:switch(behcode){
		case 0:return _T("正常");
		default:return 0;
		}
	case 0x0C01:switch(behcode){
		case 0:return _T("浮动行进");
		case 1:return _T("下降浮动前进");
		case 2:return _T("身后降落");
		case 3:return _T("斜直线");
		case 4:return _T("追踪");
		case 5:return _T("起飞");
		default:return 0;
		}
	case 0x0D01:switch(behcode){
		case 0:return _T("正常");
		case 1:return _T("瞬移爆炸");
		case 2:return _T("快速滑动");
		default:return 0;
		}
	case 0x0E01:switch(behcode){
		case 0:return _T("正常");
		default:return 0;
		}
	case 0x0F01:switch(behcode){
		case 0:return _T("正常");
		case 1:return _T("正常?");
		default:return 0;
		}
	case 0x1001:switch(behcode){
		case 0:return _T("浮动行进");
		case 1:return _T("下降浮动前进");
		case 2:return _T("身后降落");
		case 3:return _T("斜直线");
		case 4:return _T("追踪");
		case 5:return _T("起飞");
		case 6:return _T("跳起");
		case 7:return _T("跳起起飞");
		case 8:return _T("浮空");
		default:return 0;
		}
	case 0x1101:switch(behcode){
		case 0:return _T("可转动");
		case 1:return _T("上");
		case 2:return _T("右上");
		case 3:return _T("左上");
		case 4:return _T("带阳伞");
		case 5:return _T("弱");
		default:return 0;
		}
	case 0x1201:switch(behcode){
		case 0:return _T("行进");
		case 1:return _T("弱");
		case 2:return _T("静止");
		default:return 0;
		}
	case 0x1301:switch(behcode){
		case 0:return _T("正常");
		default:return 0;
		}
	case 0x1401:switch(behcode){
		case 0:return _T("A");
		case 1:return _T("B");
		case 2:return _T("C");
		default:return 0;
		}
	case 0x1501:switch(behcode){
		case 0:return _T("正常");
		case 1:return _T("后方落下");
		case 2:return _T("前方落下");
		case 3:return _T("后方升起");
		case 4:return _T("前方升起");
		default:return 0;
		}
	case 0x1601:switch(behcode){
		case 0:return _T("正常");
		default:return 0;
		}
	case 0x1701:switch(behcode){
		case 0:return _T("斜飞");
		case 1:return _T("纵飞");
		case 2:return _T("横飞");
		default:return 0;
		}
	case 0x1801:switch(behcode){
		case 0:return _T("行进");
		case 1:return _T("弱");
		case 2:return _T("静止");
		default:return 0;
		}
	case 0x1901:switch(behcode){
		case 0:return _T("正常");
		default:return 0;
		}
	case 0x1A01:switch(behcode){
		case 0:return _T("正常");
		default:return 0;
		}
	case 0x1B01:switch(behcode){
		case 0:return _T("A");
		case 1:return _T("B");
		case 2:return _T("C");
		case 3:return _T("D");
		case 4:return _T("E");
		default:return 0;
		}
	case 0x1C01:switch(behcode){
		case 0:return _T("行进");
		case 1:return _T("弱");
		case 2:return _T("静止");
		default:return 0;
		}
	case 0x1D01:switch(behcode){
		case 0:return _T("正常");
		default:return 0;
		}
	case 0x1E01:switch(behcode){
		case 0:return _T("正常");
		default:return 0;
		}
	case 0x1F01:switch(behcode){
		case 0:return _T("正常");
		default:return 0;
		}
	case 0x2001:switch(behcode){
		case 0:return _T("正常");
		default:return 0;
		}
	case 0x2101:switch(behcode){
		case 0:return _T("正常");
		default:return 0;
		}
	case 0x2201:switch(behcode){
		case 0:return _T("行进");
		case 1:return _T("行进?");
		case 2:return _T("弱");
		default:return 0;
		}
	case 0x2301:switch(behcode){
		case 0:return _T("慢");
		case 1:return _T("快");
		default:return 0;
		}
	case 0x2401:switch(behcode){
		case 0:return _T("正常");
		default:return 0;
		}
	case 0x2501:switch(behcode){
		case 0:return _T("正常");
		default:return 0;
		}

	case 0x2701:switch(behcode){
		case 0:return _T("正常");
		default:return 0;
		}

	default:return 0;
	}
}

TCHAR* CodeTran_ScriptId(u8 code)
{
	switch(code)
	{
	case 0:return _T("无");
	case 1:return _T("挖土机BOSS脚本");
	case 2:return _T("云BOSS脚本");
	//case 3:return _T("小游戏脚本");
	case 4:return _T("最终BOSS脚本1");
	case 5:return _T("最终BOSS脚本2");
	case 6:return _T("暗室脚本");
	case 7:return _T("日月BOSS脚本");
	default:return 0;
	}
}