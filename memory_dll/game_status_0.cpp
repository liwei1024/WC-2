#include "stdafx.h"
#include "game_status_0.h"


game_status_0::game_status_0()
{
	
}


game_status_0::~game_status_0()
{
}

void game_status_0::manage()
{
	int current_role_index = get_role_index();
	int select_role_index = current_role_index + 1;
	write_offset(__����ȡֵ, { __��ɫ�±�ƫ�� }, select_role_index);
	while (get_game_status() == 0)
	{
		main_thread_exec_call(Send_ѡ���ɫ, { select_role_index });
		Sleep(3000);
	}
}

int game_status_0::get_role_index()
{
	this->role_index = read_offset<int>(__����ȡֵ, {__��ɫ�±�ƫ��});
	return this->role_index;
	
}

int game_status_0::get_role_count()
{
	this->role_count = read_offset<int>(__����ȡֵ, { __��ǰ��ɫ����,__��ɫ����ƫ��2 });
	return this->role_count;
}

int game_status_0::get_role_max_count()
{
	this->role_max_count = read_offset<int>(__����ȡֵ, { __����ɫ����,__��ɫ����ƫ��2 });
	return this->role_max_count;
}



void game_status_0::select_role()
{

}



void game_status_0::create_role()
{

}