#include "stdafx.h"
#include "game_status_1.h"


game_status_1::game_status_1()
{
}


game_status_1::~game_status_1()
{
}

void game_status_1::manage()
{
	if (get_current_role_fatigue_value() <= g_keep_fatigue_value)
	{
		main_thread_exec_call(Send_返回角色);
		Sleep(2000);
	}
	else {
		
		if (g_auto_mode == 搬砖)
		{
			enter_the_dungeon();
		}
		else if (g_auto_mode == 剧情) {
			auto_master_task();
		}
	}
}

void game_status_1::enter_the_dungeon()
{
	main_thread_exec_call(Call_区域Call, { g_dungeon_id });
	Sleep(1000);
	main_thread_exec_call(Send_进入选图);
	Sleep(1000);
	main_thread_exec_call(Send_选择副本, { 104, 3, 0 });
	while (true)
	{
		if (get_game_status() == 3) {
			break;
		}
		Sleep(1000);
	}
}

void game_status_1::teleport_to(int city_name)
{
	switch (city_name)
	{
	case 格蓝迪门口:
		main_thread_exec_call(Send_城镇瞬移, { 14, 2, 705, 288 });
		break;

	default:
		break;
	}
}