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
			enter_the_dungeon(g_dungeon_id);
		}
		else if (g_auto_mode == ����) {

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
	case �������ſ�:
		main_thread_exec_call(Send_����˲��, { 14,2,500,500 });
		break;
	default:
		break;
	}
}