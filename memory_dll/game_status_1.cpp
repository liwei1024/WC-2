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
		main_thread_exec_call(Send_���ؽ�ɫ);
		Sleep(2000);
	}
	else {
		
		if (g_auto_mode == ��ש)
		{
			enter_the_dungeon();
		}
		else if (g_auto_mode == ����) {
			auto_master_task();
		}
	}
}

void game_status_1::enter_the_dungeon()
{
	main_thread_exec_call(Call_����Call, { g_dungeon_id });
	Sleep(1000);
	main_thread_exec_call(Send_����ѡͼ);
	Sleep(1000);
	main_thread_exec_call(Send_ѡ�񸱱�, { 104, 3, 0 });
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
	case �������ſ�:
		main_thread_exec_call(Send_����˲��, { 14, 2, 705, 288 });
		break;

	default:
		break;
	}
}