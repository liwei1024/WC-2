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
	if (get_current_role_fatigue_value() <= g_keep_fatigue_value && ��ϰģʽ != true)
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
	teleport_to(�������ſ�);
	Sleep(500);
	main_thread_exec_call(Send_����ѡͼ);
	Sleep(500);
	main_thread_exec_call(Send_ѡ�񸱱�, { g_dungeon_id, g_dungeon_rank, 2 });
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
	case �������ſ�:
		if (role_pos.max_city_id != 14)
		{
			main_thread_exec_call(Send_����˲��, { 14, 2, 705, 288,0 });
		}
		
		break;

	default:
		break;
	}
}