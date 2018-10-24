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
		main_thread_exec_call(Send_Ñ¡Ôñ¸±±¾, { g_dungeon_id, g_dungeon_rank, 0 });
		while (true)
		{
			if (get_game_status() == 3) { break; }
		}
	}
}