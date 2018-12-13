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
	
	if (get_current_role_fatigue_value() <= g_keep_fatigue_value && g_auto_mode != 练习)
	{
		return_role(g_返回角色方式);
		Sleep(2000);
	}
	else if (get_role_level() < 84) {
		return_role(g_返回角色方式);
		Sleep(2000);
	}
	else {
		// 1.到副本门口
		//组包到格蓝迪门口();
		// 2.进入副本
		//按键进入选图(g_dungeon_id);
		/*if (g_auto_mode == 搬砖 || g_auto_mode == 练习)
		{
			enter_the_dungeon(g_dungeon_id,g_dungeon_rank,g_auto_mode);
		}
		else if (g_auto_mode == 剧情) {
			auto_master_task();
		}*/
		//按键进格蓝迪();
	}
}

void game_status_1::enter_the_dungeon(int 副本ID,int 副本难度,int 副本类型)
{
	move_to_copy_door(副本ID, 副本类型);
	Sleep(500);
	//main_thread_exec_call(Send_进入选图);
	按键进入选图(g_dungeon_id);
	//Sleep(500);
	main_thread_exec_call(Send_选择副本, { 副本ID, 副本难度, 副本类型 });

	while (true)
	{
		Sleep(3000);
		if (get_game_status() == 3) {
			break;
		}
	}
}

void game_status_1::move_to_copy_door(int copy_id, int type)
{
	RolePos role_pos = get_role_pos();
	if (copy_id == 104 || copy_id == 103)
	{
		if (get_role_level() >= 84) {
			if (role_pos.max_city_id != 14 || role_pos.min_city_id != 2) {
				role_pos.max_city_id = 14;
				role_pos.min_city_id = 2;
				role_pos.x = 705;
				role_pos.y = 288;
				if (type == 搬砖 || type == 练习)
				{
					teleport_to(role_pos);
				}
				else {
					//脚本移动

				}
			}
		}
		else {
			bulletin(L"deng ji bu gou zi don qie huan jue se");
			return_role(0);
			return;
		}
	}
}

void game_status_1::teleport_to(RolePos pos)
{
	RolePos role_pos;
	if (g_城镇瞬移方式 == 0)
	{
		//组包
		main_thread_exec_call(Send_城镇瞬移, { pos.max_city_id, pos.min_city_id, pos.x, pos.y,0 });
	}
	else if (g_城镇瞬移方式 == 1) {
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
	case 1:
		doKeyPress(VK_ESCAPE);
		Sleep(1000);
		setMouseCoord(game_window_info.left + 518, game_window_info.top + 449);
		mouseClick();
	default:
		break;
	}
	
}

void game_status_1::组包到副本门口(int copy_id)
{
	RolePos role_pos = get_role_pos();
	if (copy_id == 104)
	{
		if (role_pos.max_city_id != 14 || role_pos.min_city_id != 2) {
			main_thread_exec_call(Call_区域Call, { copy_id ,GetGoodsIndexByGoodsName(L"瞬间移动药剂")});
		}
	}
}

void game_status_1::按键进入选图(int copy_id)
{
	if (copy_id == 104 || copy_id == 102 || copy_id == 103)
	{
		keyDown(VK_NUMPAD3);
		while (true) 
		{
			if (get_game_status() == 2)
			{
				keyUp(VK_NUMPAD3);
				break;
			}
			Sleep(500);
		}
	}
}


CITY_INFO game_status_1::get_city_info(int city_name)
{
	CITY_INFO city_info;
	if (city_name == 格蓝迪门口)
	{
		city_info.max_city_id = 14;
		city_info.min_city_id = 2;
		city_info.x = 705;
		city_info.y = 288;
	}
}


bool game_status_1::按键进格蓝迪()
{
	RolePos cur_role_pos = get_role_pos();
	if (cur_role_pos.max_city_id == 38 && cur_role_pos.min_city_id == 1)
	{
		//main_thread_exec_call(Call_城镇移动, { 450 ,400});
		cur_role_pos.x = 450;
		cur_role_pos.y = 301;
		按键移动角色(cur_role_pos);
		doKeyPress(VK_NUMPAD2,500);
	}
	cur_role_pos = get_role_pos();
	if (cur_role_pos.max_city_id == 14 && cur_role_pos.min_city_id == 0)
	{
		//main_thread_exec_call(Call_城镇移动, { 852 ,200 });
		doKeyPress(VK_NUMPAD3, 300);
		cur_role_pos.x = 852;
		cur_role_pos.y = 200;
		按键移动角色(cur_role_pos);
		doKeyPress(VK_NUMPAD5, 500);
	}
	cur_role_pos = get_role_pos();
	if (cur_role_pos.max_city_id == 14 && cur_role_pos.min_city_id == 1)
	{
		doKeyPress(VK_NUMPAD5, 200);
		cur_role_pos.x = 2120;
		cur_role_pos.y = 270;
		按键移动角色(cur_role_pos);
		doKeyPress(VK_NUMPAD3, 500);
	}
	cur_role_pos = get_role_pos();
	if (cur_role_pos.max_city_id == 14 && cur_role_pos.min_city_id == 2)
	{
		cur_role_pos.x = 839;
		cur_role_pos.y = 271;
		按键移动角色(cur_role_pos);
		doKeyPress(VK_NUMPAD3, 500);
		return true;
	}
	return false;
}

void game_status_1::组包到格蓝迪门口()
{
	RolePos role_pos = get_role_pos();
	if (role_pos.max_city_id != 14 || role_pos.min_city_id != 2) {
		main_thread_exec_call(Send_城镇瞬移, { 14, 2, 705, 288 ,GetGoodsIndexByGoodsName(L"瞬间移动药剂") });
	}
}