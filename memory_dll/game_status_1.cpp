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
	if (get_current_role_fatigue_value() <= g_keep_fatigue_value && 练习模式 != true)
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
	teleport_to(格蓝迪门口);
	Sleep(500);
	main_thread_exec_call(Send_进入选图);
	Sleep(500);
	main_thread_exec_call(Send_选择副本, { g_dungeon_id, g_dungeon_rank, 2 });
	while (true)
	{
		if (get_game_status() == 3) {
			break;
		}
		Sleep(3000);
	}
}

void game_status_1::teleport_to(int city_name)
{
	RolePos role_pos = get_role_pos();
	switch (city_name)
	{
	case 格蓝迪门口:
		if (role_pos.max_city_id != 14)
		{
			main_thread_exec_call(Send_城镇瞬移, { 14, 2, 705, 288,0 });
		}
		
		break;

	default:
		break;
	}
}