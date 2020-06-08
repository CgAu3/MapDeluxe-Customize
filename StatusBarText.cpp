#include "stdafx.h"
#include "MapDeluxe.h"
#include "MapDeluxeDlg.h"

void CMapDeluxeDlg::OnMenuSelect(UINT nItemID,UINT nFlags,HMENU hSysMenu)
{
	switch(nItemID)
	{
	case ID_M_NEW:
		m_StatusBar.SetPaneText(0,_T("���½�������һ���µ���֮Ȫ��Ϸ��"));
		break;
	case ID_M_NEW_WHITE:
		m_StatusBar.SetPaneText(0,_T("���½��հ���Ϸ������һ���µ���֮Ȫ��Ϸ�����е�ͼ���ڿհ�״̬��"));
		break;
	case ID_M_OPEN:
		m_StatusBar.SetPaneText(0,_T("���򿪡���һ���ñ������������֮Ȫ��Ϸ������������Ϸ����[�½�]�˵��"));
		break;
	case ID_M_SAVE:
		m_StatusBar.SetPaneText(0,_T("�����桿��������Ϊֹ����Ϸ�����������޸ġ�"));
		break;
	case ID_M_SAVEAS:
		m_StatusBar.SetPaneText(0,_T("�����Ϊ��������Ϊֹ����Ϸ�����������޸ı��浽һ���µ���Ϸ�С�"));
		break;
	case ID_M_SAVE_FINAL:
		m_StatusBar.SetPaneText(0,_T("���������հ���Ϸ������һ���޷����ñ�����鿴���޸ĵ���Ϸ��"));
		break;
	case ID_M_GAME_TEST:
		m_StatusBar.SetPaneText(0,_T("��������Ϸ��������Ϸ����������ģ����������Ϸ��"));
		break;
	case ID_M_ROM_IMAGE:
		m_StatusBar.SetPaneText(0,_T("���Զ�����Ϸ��ʼ���桿���������Ϸ����ʱ��ʾһ���Զ����ͼ����Ϊ����ҳ��ʹ�á�"));
		break;
	case ID_M_EXIT:
		m_StatusBar.SetPaneText(0,_T("���˳��������˳����ѡ�"));
		break;
	case ID_M_UNDO:
		m_StatusBar.SetPaneText(0,_T("��������������һ�β�����ֻ���޸ĵ�ͼ��ͼ���֡���ͼ�ж��Ĳ�����Ч��"));
		break;
	case ID_M_REDO:
		m_StatusBar.SetPaneText(0,_T("���ظ���������һ�Ρ���������"));
		break;
	case ID_M_RESIZE:
		m_StatusBar.SetPaneText(0,_T("���޸ĵ�ͼ�ߴ硿�������õ�ǰ��ͼ̫���˻�̫С�˾͵����"));
		break;
	case ID_M_DOOR:
		m_StatusBar.SetPaneText(0,_T("���༭����װ�á��������Ҫ�޸Ĵ����š������ǡ�����һ���װ��������"));
		break;
	case ID_M_OBJ:
		m_StatusBar.SetPaneText(0,_T("���༭������������Ҫ�޸��߶�ϡ�1UP�ȵ�������"));
		break;
	case ID_M_WIND:
		m_StatusBar.SetPaneText(0,_T("���༭�硿��Ҫʹ��ȫ�ִ�������Ĺ���������"));
		break;
	case ID_M_CLEAR_MAP:
		m_StatusBar.SetPaneText(0,_T("����յ�ͼ��ע�⣡����������յ�ǰ��ͼ��������ͼ���ж���"));
		break;
	case ID_M_RESET_MAP:
		m_StatusBar.SetPaneText(0,_T("����λ��ͼ��ע�⣡��������ѵ�ǰ��ͼ�������ݻָ�����ʼ״̬��"));
		break;
	case ID_M_STEP_EXPORT:
		m_StatusBar.SetPaneText(0,_T("��������ǰ��ͼ������ǰ��ͼ���������ݱ���Ϊһ�������ĵ�ͼ�ļ��Է��������˽�����"));
		break;
	case ID_M_STEP_IMPORT:
		m_StatusBar.SetPaneText(0,_T("�������ͼ����һ����ͼ�ļ����벢���ǵ���ǰ��ͼ�ϡ�"));
		break;
	case ID_HELP:
		m_StatusBar.SetPaneText(0,_T("������������ʱ��Ҫ������"));
		break;
	case ID_M_ABOUT:
		m_StatusBar.SetPaneText(0,_T("�����ڡ�������"));
		break;
	case ID_M_XZKBB:
		m_StatusBar.SetPaneText(0,_T("http://tieba.baidu.com/��֮����"));
		break;
	case ID_M_TIEZI:
		m_StatusBar.SetPaneText(0,_T("http://tieba.baidu.com/p/1816594640"));
		break;
	case ID_M_SAVE_TEST:
		m_StatusBar.SetPaneText(0,_T("�����Ե�ͼռ�ÿռ䡿�뾭�������������ͼ���ڸ��Ӿ��г���ռ�ÿռ�Ŀ��ܣ���������������޷�������Ϸ�ġ�"));
		break;
	default:
		m_StatusBar.SetPaneText(0,_T("����"));
		break;
	}
	CDialog::OnMenuSelect(nItemID,nFlags,hSysMenu);
}
BOOL CMapDeluxeDlg::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	if(m_SetCursorResp)
	{
		if(pWnd==(CWnd*)&m_Tree)
			m_StatusBar.SetPaneText(0,_T("�����б���˫��һ������Ҳ�鿴�ͱ༭��"));
		else if(pWnd==(CWnd*)&m_EditStepNumber)
			m_StatusBar.SetPaneText(0,_T("��ͼ����Ϸ�е�λ�á���ֹ�޸�����Ϊ�޸������ᵼ����Ϸ�޷����С�"));
		else if(pWnd==(CWnd*)&m_CheckLz77)
			m_StatusBar.SetPaneText(0,_T("ָʾ��ͼ�Ƿ�Ҫѹ����洢����Ϸ�С������ڱ����ֻ֧��ѹ����ʽ���뱣�ֱ���ѡ�У�������ϣ����Ϸ��÷ǳ����¡�"));
		else if(pWnd==(CWnd*)&m_ComboBgm)
			m_StatusBar.SetPaneText(0,_T("���������пɸ��ı���ͼ��ʹ�õ�BGM��"));
		else if(pWnd==(CWnd*)&m_ComboSpcMap)
			m_StatusBar.SetPaneText(0,_T("������Ĵ������������һЩ�����ʵ��"));
		else if(pWnd==(CWnd*)&m_EditClipX || pWnd==(CWnd*)&m_EditClipY)
			m_StatusBar.SetPaneText(0,_T("��Ϸ�н���ѵ�ͼ����ָ����ֵ���������ұ�Ե���ó�һ����ʹ�䲻��ʾ��ͬʱ�±�Ե���û�Ӱ��׹���ж��ߵ�λ�á�"));
		else if(pWnd==(CWnd*)&m_EditBeginX || pWnd==(CWnd*)&m_EditBeginY)
			m_StatusBar.SetPaneText(0,_T("ָʾ���ȳ��ֵ�λ�á��ƺ�ֻ��Step0��Ч��������Ϊ��λ��"));
		else if(pWnd==(CWnd*)&m_EditBckMov)
			m_StatusBar.SetPaneText(0,_T("�������ָʾ�˱���ͼ�������ǰ���Զ��������ƶ�������ԭ����Ϸ�д˴�ȡֵֻ��8��16���֡�"));
		else if(pWnd==(CWnd*)&m_EditX36)
			m_StatusBar.SetPaneText(0,_T("��������ƫ�ơ�ԭ����Ϸ��ֻ��0��8��16����ȡֵ��"));
		else if(pWnd==(CWnd*)&m_ComboScriptId)
			m_StatusBar.SetPaneText(0,_T("�����־�ŵ�ͼ��һЩ���⹦�ܡ�"));
		else if(pWnd==(CWnd*)&m_ComboGraAni)
			m_StatusBar.SetPaneText(0,_T("��Ϸ�н�����ݴ��ʱ�ظ����ض���ͼ��ͼ�������С������ᶨʱ�����ض�λ�õ��ж���"));
		else if(pWnd==(CWnd*)&m_CheckX55)
			m_StatusBar.SetPaneText(0,_T("����㲻������һЩ��ֵ�ʵ�飬�벻Ҫ������"));
		else if(pWnd==(CWnd*)&m_CheckBckRoll)
			m_StatusBar.SetPaneText(0,_T("�������ѡ�����־�ű������Զ�����������Level4.Stage3�����з���ͧ��������"));
		else if(pWnd==(CWnd*)&m_ComboMapChg)
			m_StatusBar.SetPaneText(0,_T("ѡ��༭��ͼ����ͼ�����ж�����ݼ���Ctrl+D"));
		else if(pWnd==(CWnd*)&m_CheckNest)
			m_StatusBar.SetPaneText(0,_T("��ѡ��༭�ƿ���ͼ�����ڸ��ֿɻ���ש�飨����שը��ש�ȣ�����༭���ƿ����ݡ���ݼ���Ctrl+E"));
		else if(pWnd==(CWnd*)&m_CheckNestAuto)
			m_StatusBar.SetPaneText(0,_T("��ѡ���Զ����ɻ���ש����ƿ����ݡ�"));
		else if(pWnd==(CWnd*)&m_CheckMapOutBck)
			m_StatusBar.SetPaneText(0,_T("ͬʱ���ж�ͼ�����ͼͼ�������ʾ��"));
		else if(pWnd==(CWnd*)&m_CheckEdg || pWnd==(CWnd*)&m_EditEdg )
			m_StatusBar.SetPaneText(0,_T("��ͼ�ж���ÿ������һ��δֵ֪\"Edg\"����ѡ��������ж�ģʽ���޸��ж�����ͬʱ�޸�EdgΪָ��ֵ��Edg���ò�ɫ�ĵ���ʾ��"));
		else if(pWnd==(CWnd*)&m_CheckGraAssoc)
			m_StatusBar.SetPaneText(0,_T("�ò�ɫ���־����ͼ�ٽ�����ͼ����ɫΪ�Ϸ�����ɫΪ�·�����ɫΪ��࣬��ɫΪ�Ҳࡣ"));
		else
		{
			m_StatusBar.SetPaneText(0,_T("����"));
		}
	}

	return CDialog::OnSetCursor(pWnd, nHitTest, message);
}
