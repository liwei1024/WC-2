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
	
	if (get_current_role_fatigue_value() <= g_keep_fatigue_value && g_auto_mode != ��ϰ)
	{
		return_role(g_���ؽ�ɫ��ʽ);
		Sleep(2000);
	}
	else if (get_role_level() < 84) {
		return_role(g_���ؽ�ɫ��ʽ);
		Sleep(2000);
	}
	else {
		// 1.�������ſ�
		//������������ſ�();
		// 2.���븱��
		//��������ѡͼ(g_dungeon_id);
		/*if (g_auto_mode == ��ש || g_auto_mode == ��ϰ)
		{
			enter_the_dungeon(g_dungeon_id,g_dungeon_rank,g_auto_mode);
		}
		else if (g_auto_mode == ����) {
			auto_master_task();
		}*/
		//������������();
	}
}

void game_status_1::enter_the_dungeon(int ����ID,int �����Ѷ�,int ��������)
{
	move_to_copy_door(����ID, ��������);
	Sleep(500);
	//main_thread_exec_call(Send_����ѡͼ);
	��������ѡͼ(g_dungeon_id);
	//Sleep(500);
	main_thread_exec_call(Send_ѡ�񸱱�, { ����ID, �����Ѷ�, �������� });

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
				if (type == ��ש || type == ��ϰ)
				{
					teleport_to(role_pos);
				}
				else {
					//�ű��ƶ�

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
	if (g_����˲�Ʒ�ʽ == 0)
	{
		//���
		main_thread_exec_call(Send_����˲��, { pos.max_city_id, pos.min_city_id, pos.x, pos.y,0 });
	}
	else if (g_����˲�Ʒ�ʽ == 1) {
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
		main_thread_exec_call(Send_���ؽ�ɫ);
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

void game_status_1::����������ſ�(int copy_id)
{
	RolePos role_pos = get_role_pos();
	if (copy_id == 104)
	{
		if (role_pos.max_city_id != 14 || role_pos.min_city_id != 2) {
			main_thread_exec_call(Call_����Call, { copy_id ,GetGoodsIndexByGoodsName(L"˲���ƶ�ҩ��")});
		}
	}
}

void game_status_1::��������ѡͼ(int copy_id)
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
	if (city_name == �������ſ�)
	{
		city_info.max_city_id = 14;
		city_info.min_city_id = 2;
		city_info.x = 705;
		city_info.y = 288;
	}
}


bool game_status_1::������������()
{
	RolePos cur_role_pos = get_role_pos();
	if (cur_role_pos.max_city_id == 38 && cur_role_pos.min_city_id == 1)
	{
		//main_thread_exec_call(Call_�����ƶ�, { 450 ,400});
		cur_role_pos.x = 450;
		cur_role_pos.y = 301;
		�����ƶ���ɫ(cur_role_pos);
		doKeyPress(VK_NUMPAD2,500);
	}
	cur_role_pos = get_role_pos();
	if (cur_role_pos.max_city_id == 14 && cur_role_pos.min_city_id == 0)
	{
		//main_thread_exec_call(Call_�����ƶ�, { 852 ,200 });
		doKeyPress(VK_NUMPAD3, 300);
		cur_role_pos.x = 852;
		cur_role_pos.y = 200;
		�����ƶ���ɫ(cur_role_pos);
		doKeyPress(VK_NUMPAD5, 500);
	}
	cur_role_pos = get_role_pos();
	if (cur_role_pos.max_city_id == 14 && cur_role_pos.min_city_id == 1)
	{
		doKeyPress(VK_NUMPAD5, 200);
		cur_role_pos.x = 2120;
		cur_role_pos.y = 270;
		�����ƶ���ɫ(cur_role_pos);
		doKeyPress(VK_NUMPAD3, 500);
	}
	cur_role_pos = get_role_pos();
	if (cur_role_pos.max_city_id == 14 && cur_role_pos.min_city_id == 2)
	{
		cur_role_pos.x = 839;
		cur_role_pos.y = 271;
		�����ƶ���ɫ(cur_role_pos);
		doKeyPress(VK_NUMPAD3, 500);
		return true;
	}
	return false;
}

void game_status_1::������������ſ�()
{
	RolePos role_pos = get_role_pos();
	if (role_pos.max_city_id != 14 || role_pos.min_city_id != 2) {
		main_thread_exec_call(Send_����˲��, { 14, 2, 705, 288 ,GetGoodsIndexByGoodsName(L"˲���ƶ�ҩ��") });
	}
}