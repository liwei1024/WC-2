#include "stdafx.h"
#include "global_var.h"

HWND g_hWnd = NULL;
bool g_auto_switch = false;//自动开关
int g_skills_code = 70023;//技能代码
int g_auto_mode = 搬砖;//自动模式 0 搬砖 1剧情 5练习
int g_刷图功能;// 0 按键 1技能call 2吞噬魔
int g_keep_fatigue_value = 0; //保留疲劳
int g_刷图次数 = 0;
int g_金币收益 = 0;
int g_魔刹石收益 = 0;
int g_数据芯片收益 = 0;
bool g_首图标记 = true;
int g_开始角色 = 0;
int g_截止角色 = 7;
int g_dungeon_id = 104;
int g_dungeon_rank = 3;
int g_过图时间;
int g_过图方式 = 0; // 0坐标过图 1 强制过图
int g_移动方式 = 0; // 0瞬移 1走路
//bool g_副本类型 = 0; //0普通 1深渊 2练习
int g_选角方式 = 2;//0-组包 1-call 2-按键
int g_城镇瞬移方式 = 0; //0-组包 1-call
bool g_翻牌模式 = 1;//0组包 1按键
WINDOW_INFO game_window_info;
bool g_返回角色方式 = 1;//0组包 1按键
std::vector<int> g_技能列表 = { 70023,140177,109005914,140158,48172 };
