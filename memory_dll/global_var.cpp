#include "stdafx.h"
#include "global_var.h"

HWND g_hWnd = NULL;
bool g_auto_switch = false;//�Զ�����
int g_skills_code = 70023;//���ܴ���
int g_auto_mode = ��ש;//�Զ�ģʽ 0 ��ש 1���� 5��ϰ
int g_ˢͼ����;// 0 ���� 1����call 2����ħ
int g_keep_fatigue_value = 0; //����ƣ��
int g_ˢͼ���� = 0;
int g_������� = 0;
int g_ħɲʯ���� = 0;
int g_����оƬ���� = 0;
bool g_��ͼ��� = true;
int g_��ʼ��ɫ = 0;
int g_��ֹ��ɫ = 7;
int g_dungeon_id = 104;
int g_dungeon_rank = 3;
int g_��ͼʱ��;
int g_��ͼ��ʽ = 0; // 0�����ͼ 1 ǿ�ƹ�ͼ
int g_�ƶ���ʽ = 0; // 0˲�� 1��·
//bool g_�������� = 0; //0��ͨ 1��Ԩ 2��ϰ
int g_ѡ�Ƿ�ʽ = 2;//0-��� 1-call 2-����
int g_����˲�Ʒ�ʽ = 0; //0-��� 1-call
bool g_����ģʽ = 1;//0��� 1����
WINDOW_INFO game_window_info;
bool g_���ؽ�ɫ��ʽ = 1;//0��� 1����
std::vector<int> g_�����б� = { 70023,140177,109005914,140158,48172 };
