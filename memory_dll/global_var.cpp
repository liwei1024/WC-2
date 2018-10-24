#include "stdafx.h"
#include "global_var.h"

HWND g_hWnd = NULL;
bool g_auto_switch = false;//自动开关
int g_skills_code = 70023;//技能代码
int g_auto_mode = 1;//自动模式 0 搬砖 1剧情
int g_刷图功能;// 0 按键 1技能call 2吞噬魔
int g_keep_fatigue_value = 0; //保留疲劳
int g_刷图次数 = 0;
int g_金币收益 = 0;
int g_魔刹石收益 = 0;
int g_数据芯片收益 = 0;
bool g_首图标记 = true;
int g_开始角色 = -1;
int g_截止角色 = -1;
int g_dungeon_id = 104;
int g_dungeon_rank = 0;
int g_过图时间;
int g_过图方式 = 0; // 0坐标过图 1 强制过图
int g_移动方式 = 0; // 0瞬移 1走路
bool 练习模式 = true;