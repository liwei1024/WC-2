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
	
	if (get_current_role_fatigue_value() <= g_keep_fatigue_value && g_auto_mode != 2)
	{
		main_thread_exec_call(Send_返回角色);
		Sleep(2000);
	}
	else {
		
		if (g_auto_mode == 搬砖)
		{
			enter_the_dungeon(g_dungeon_id,g_dungeon_rank,g_auto_mode);
		}
		else if (g_auto_mode == 剧情) {
			auto_master_task();
		}
	}
}

void game_status_1::enter_the_dungeon(int 副本ID,int 副本难度,int 副本类型)
{
	move_to_copy_door(副本ID);
	Sleep(500);
	main_thread_exec_call(Send_进入选图);
	Sleep(500);
	main_thread_exec_call(Send_选择副本, { 副本ID, 副本难度, 副本类型 });

	while (true)
	{
		Sleep(3000);
		if (get_game_status() == 3) {
			break;
		}
	}
}

void game_status_1::teleport_to(RolePos pos,int type)
{
	RolePos role_pos;
	if (type == 0)
	{
		//组包
		main_thread_exec_call(Send_城镇瞬移, { pos.max_city_id, pos.min_city_id, pos.x, pos.y,pos.z });
	}
	else if (type == 1) {
		//call
	}
	while (true)
	{
		role_pos = get_role_pos();
		if (
			role_pos.max_city_id == pos.max_city_id &&
			role_pos.min_city_id == pos.min_city_id
			)
		{
			break;
		}
		Sleep(1000);
	}
}

void game_status_1::move_to_copy_door(int copy_id,int type)
{
	RolePos role_pos;
	switch (copy_id)
	{
	case 104:
		if (get_role_level() >= 84) {
			role_pos.max_city_id = 14;
			role_pos.max_city_id = 2;
			role_pos.x = 705;
			role_pos.y = 288;
			if (type == 2)
			{
				//脚本移动
			}
			else {
				teleport_to(role_pos, type);
			}
			
		}
		else {
			bulletin(L"等级不够自动切换角色");
			return_role(0);
			return;
		}
		break;
	default:
		break;
	}
}

void game_status_1::return_role(int type)
{
	switch (type)
	{
	case 0:
		main_thread_exec_call(Send_返回角色);
		while (get_game_status() != 0)
		{
			Sleep(1000);
		}
		break;
	default:
		break;
	}
	
}