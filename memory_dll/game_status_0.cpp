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
	while (get_game_status() == 0)
	{
		

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