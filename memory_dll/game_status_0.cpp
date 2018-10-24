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
	write_offset(__遍历取值, { __角色下标偏移 }, select_role_index);
	while (get_game_status() == 0)
	{
		main_thread_exec_call(Send_选择角色, { select_role_index });
		Sleep(3000);
	}
}

int game_status_0::get_role_index()
{
	this->role_index = read_offset<int>(__遍历取值, {__角色下标偏移});
	return this->role_index;
	
}

int game_status_0::get_role_count()
{
	this->role_count = read_offset<int>(__遍历取值, { __当前角色数量,__角色数量偏移2 });
	return this->role_count;
}

int game_status_0::get_role_max_count()
{
	this->role_max_count = read_offset<int>(__遍历取值, { __最大角色数量,__角色数量偏移2 });
	return this->role_max_count;
}



void game_status_0::select_role()
{

}



void game_status_0::create_role()
{

}