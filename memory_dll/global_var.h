#pragma once


extern HWND g_hWnd;
extern bool g_auto_switch;//自动开关
extern int g_skills_code;//技能代码
extern int g_auto_mode;//自动模式 0 搬砖 1剧情 2练习
extern int g_刷图功能;// 0 按键 1技能call 2吞噬魔
extern int g_keep_fatigue_value; //保留疲劳
extern int g_过图方式; // 0坐标过图 1 强制过图
extern int g_移动方式; // 0瞬移 1走路
extern int g_刷图次数;
extern int g_金币收益;
extern int g_魔刹石收益;
extern int g_数据芯片收益;
extern bool g_首图标记;
extern int g_过图时间;
extern int g_开始角色;
extern int g_截止角色;
extern int g_dungeon_id; 
extern int g_dungeon_rank;
extern bool g_练习模式;
extern int g_选角方式;
extern int g_城镇瞬移方式;
extern bool g_翻牌模式;
extern WINDOW_INFO game_window_info;
extern bool g_返回角色方式;
extern std::vector<int> g_技能列表;


extern HANDLE g_hProcess;
extern HANDLE g_hThread;