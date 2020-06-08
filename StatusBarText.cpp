#include "stdafx.h"
#include "MapDeluxe.h"
#include "MapDeluxeDlg.h"

void CMapDeluxeDlg::OnMenuSelect(UINT nItemID,UINT nFlags,HMENU hSysMenu)
{
	switch(nItemID)
	{
	case ID_M_NEW:
		m_StatusBar.SetPaneText(0,_T("【新建】建立一个新的梦之泉游戏。"));
		break;
	case ID_M_NEW_WHITE:
		m_StatusBar.SetPaneText(0,_T("【新建空白游戏】建立一个新的梦之泉游戏，所有地图处于空白状态。"));
		break;
	case ID_M_OPEN:
		m_StatusBar.SetPaneText(0,_T("【打开】打开一个用本软件创建的梦之泉游戏。初次制作游戏请点击[新建]菜单项。"));
		break;
	case ID_M_SAVE:
		m_StatusBar.SetPaneText(0,_T("【保存】保存至今为止对游戏所作的所有修改。"));
		break;
	case ID_M_SAVEAS:
		m_StatusBar.SetPaneText(0,_T("【另存为】将至今为止对游戏所作的所有修改保存到一个新的游戏中。"));
		break;
	case ID_M_SAVE_FINAL:
		m_StatusBar.SetPaneText(0,_T("【生成最终版游戏】生成一个无法再用本软件查看或修改的游戏。"));
		break;
	case ID_M_GAME_TEST:
		m_StatusBar.SetPaneText(0,_T("【测试游戏】保存游戏并立即启动模拟器运行游戏。"));
		break;
	case ID_M_ROM_IMAGE:
		m_StatusBar.SetPaneText(0,_T("【自定义游戏起始画面】你可以在游戏启动时显示一张自定义的图像作为标题页来使用。"));
		break;
	case ID_M_EXIT:
		m_StatusBar.SetPaneText(0,_T("【退出】就是退出而已。"));
		break;
	case ID_M_UNDO:
		m_StatusBar.SetPaneText(0,_T("【撤销】撤销上一次操作。只对修改地图贴图布局、地图判定的操作有效。"));
		break;
	case ID_M_REDO:
		m_StatusBar.SetPaneText(0,_T("【重复】撤销上一次“撤销”。"));
		break;
	case ID_M_RESIZE:
		m_StatusBar.SetPaneText(0,_T("【修改地图尺寸】如果你觉得当前地图太大了或太小了就点这里。"));
		break;
	case ID_M_DOOR:
		m_StatusBar.SetPaneText(0,_T("【编辑传送装置】如果你需要修改传送门、传送星、大炮一类的装置请点这里。"));
		break;
	case ID_M_OBJ:
		m_StatusBar.SetPaneText(0,_T("【编辑物件】如果你需要修改瓦多迪、1UP等等请点这里。"));
		break;
	case ID_M_WIND:
		m_StatusBar.SetPaneText(0,_T("【编辑风】需要使用全局大风这样的功能请点这里。"));
		break;
	case ID_M_CLEAR_MAP:
		m_StatusBar.SetPaneText(0,_T("【清空地图】注意！点击此项将会清空当前地图的所有贴图和判定！"));
		break;
	case ID_M_RESET_MAP:
		m_StatusBar.SetPaneText(0,_T("【复位地图】注意！点击此项将会把当前地图所有数据恢复到初始状态！"));
		break;
	case ID_M_STEP_EXPORT:
		m_StatusBar.SetPaneText(0,_T("【导出当前地图】将当前地图的所有数据保存为一个独立的地图文件以方便与他人交流。"));
		break;
	case ID_M_STEP_IMPORT:
		m_StatusBar.SetPaneText(0,_T("【导入地图】将一个地图文件导入并覆盖到当前地图上。"));
		break;
	case ID_HELP:
		m_StatusBar.SetPaneText(0,_T("【帮助】请暂时不要点这里"));
		break;
	case ID_M_ABOUT:
		m_StatusBar.SetPaneText(0,_T("【关于】啦啦啦"));
		break;
	case ID_M_XZKBB:
		m_StatusBar.SetPaneText(0,_T("http://tieba.baidu.com/星之卡比"));
		break;
	case ID_M_TIEZI:
		m_StatusBar.SetPaneText(0,_T("http://tieba.baidu.com/p/1816594640"));
		break;
	case ID_M_SAVE_TEST:
		m_StatusBar.SetPaneText(0,_T("【测试地图占用空间】请经常点击此项。如果地图过于复杂就有超出占用空间的可能，在那种情况下是无法保存游戏的。"));
		break;
	default:
		m_StatusBar.SetPaneText(0,_T("就绪"));
		break;
	}
	CDialog::OnMenuSelect(nItemID,nFlags,hSysMenu);
}
BOOL CMapDeluxeDlg::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	if(m_SetCursorResp)
	{
		if(pWnd==(CWnd*)&m_Tree)
			m_StatusBar.SetPaneText(0,_T("请在列表中双击一项后在右侧查看和编辑。"));
		else if(pWnd==(CWnd*)&m_EditStepNumber)
			m_StatusBar.SetPaneText(0,_T("地图在游戏中的位置。禁止修改是因为修改它将会导致游戏无法运行。"));
		else if(pWnd==(CWnd*)&m_CheckLz77)
			m_StatusBar.SetPaneText(0,_T("指示地图是否要压缩后存储进游戏中。但由于本软件只支持压缩格式，请保持本项选中，除非你希望游戏变得非常可怕。"));
		else if(pWnd==(CWnd*)&m_ComboBgm)
			m_StatusBar.SetPaneText(0,_T("在下拉框中可更改本地图所使用的BGM。"));
		else if(pWnd==(CWnd*)&m_ComboSpcMap)
			m_StatusBar.SetPaneText(0,_T("请勿更改此项，除非你想做一些奇葩的实验"));
		else if(pWnd==(CWnd*)&m_EditClipX || pWnd==(CWnd*)&m_EditClipY)
			m_StatusBar.SetPaneText(0,_T("游戏中将会把地图按照指定的值在上下左右边缘剪裁出一部分使其不显示。同时下边缘剪裁还影响坠崖判定线的位置。"));
		else if(pWnd==(CWnd*)&m_EditBeginX || pWnd==(CWnd*)&m_EditBeginY)
			m_StatusBar.SetPaneText(0,_T("指示卡比出现的位置。似乎只对Step0有效。以像素为单位。"));
		else if(pWnd==(CWnd*)&m_EditBckMov)
			m_StatusBar.SetPaneText(0,_T("这个参数指示了背景图将相对于前景以多大的速率移动。不过原版游戏中此处取值只有8与16两种。"));
		else if(pWnd==(CWnd*)&m_EditX36)
			m_StatusBar.SetPaneText(0,_T("背景纵向偏移。原版游戏中只有0、8、16三种取值。"));
		else if(pWnd==(CWnd*)&m_ComboScriptId)
			m_StatusBar.SetPaneText(0,_T("此项标志着地图的一些特殊功能。"));
		else if(pWnd==(CWnd*)&m_ComboGraAni)
			m_StatusBar.SetPaneText(0,_T("游戏中将会根据此项定时地更换特定贴图的图案。其中“雾”还会定时更换特定位置的判定。"));
		else if(pWnd==(CWnd*)&m_CheckX55)
			m_StatusBar.SetPaneText(0,_T("如果你不是想做一些奇怪的实验，请不要动此项"));
		else if(pWnd==(CWnd*)&m_CheckBckRoll)
			m_StatusBar.SetPaneText(0,_T("这项如果选中则标志着背景会自动滚动，比如Level4.Stage3（空中飞行艇）中那样"));
		else if(pWnd==(CWnd*)&m_ComboMapChg)
			m_StatusBar.SetPaneText(0,_T("选择编辑地图的贴图还是判定。快捷键：Ctrl+D"));
		else if(pWnd==(CWnd*)&m_CheckNest)
			m_StatusBar.SetPaneText(0,_T("勾选后编辑掀开地图。对于各种可击碎砖块（星星砖炸弹砖等）都需编辑其掀开数据。快捷键：Ctrl+E"));
		else if(pWnd==(CWnd*)&m_CheckNestAuto)
			m_StatusBar.SetPaneText(0,_T("勾选后自动填充可击碎砖块的掀开数据。"));
		else if(pWnd==(CWnd*)&m_CheckMapOutBck)
			m_StatusBar.SetPaneText(0,_T("同时把判定图层和贴图图层叠放显示。"));
		else if(pWnd==(CWnd*)&m_CheckEdg || pWnd==(CWnd*)&m_EditEdg )
			m_StatusBar.SetPaneText(0,_T("地图判定中每个格都有一个未知值\"Edg\"，勾选本项后在判定模式下修改判定将会同时修改Edg为指定值。Edg将用彩色的点显示。"));
		else if(pWnd==(CWnd*)&m_CheckGraAssoc)
			m_StatusBar.SetPaneText(0,_T("用彩色框标志该贴图临近的贴图。黄色为上方，青色为下方，绿色为左侧，蓝色为右侧。"));
		else
		{
			m_StatusBar.SetPaneText(0,_T("就绪"));
		}
	}

	return CDialog::OnSetCursor(pWnd, nHitTest, message);
}
