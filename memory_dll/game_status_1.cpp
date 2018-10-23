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
			enter_the_dungeon(g_dungeon_id);
		}
		else if (g_auto_mode == 剧情) {

		}
	}
}

void game_status_1::enter_the_dungeon(int dungeon_id)
{

}

void game_status_1::teleport_to(int city_name)
{
	switch (city_name)
	{
	case 格蓝迪门口:
		main_thread_exec_call(Send_城镇瞬移, { 14,2,500,500 });
		break;
	default:
		break;
	}
}