#include "stdafx.h"
#include "game_status_2.h"


game_status_2::game_status_2()
{
}


game_status_2::~game_status_2()
{
}

void game_status_2::manage()
{
	if (get_current_role_fatigue_value() == 0)
	{
		doKeyPress(VK_ESCAPE);
		Sleep(1000);
	}
	else {
		main_thread_exec_call(Send_ѡ�񸱱�, { g_dungeon_id, g_dungeon_rank, g_auto_mode });
		while (true)
		{
			Sleep(3000);
			if (get_game_status() == 3) { break; }
		}
	}
}