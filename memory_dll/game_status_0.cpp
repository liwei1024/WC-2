#include "stdafx.h"
#include "game_status_0.h"


game_status_0::game_status_0()
{
	g_role_index = get_role_index();
}


game_status_0::~game_status_0()
{
}

void game_status_0::manage()
{
	if (g_role_index == get_role_count()) {
		bulletin(L"所有角色刷图完毕，自动关闭");
		g_auto_switch = false;
	}
	else {
		select_role(g_选角方式);
	}
	
}

int game_status_0::get_role_index()
{
	int role_index = read_offset<int>(__遍历取值, {__角色下标偏移});
	return role_index;
	
}

int game_status_0::get_role_count()
{
	int role_count = read_offset<int>(__遍历取值, { __当前角色数量,__角色数量偏移2 });
	return role_count;
}

int game_status_0::get_role_max_count()
{
	int role_max_count = read_offset<int>(__遍历取值, { __最大角色数量,__角色数量偏移2 });
	return role_max_count;
}



void game_status_0::select_role(int type)
{
	int select_role_index = g_role_index + 1;
	if (type == 0)
	{
		write_offset(__遍历取值, { __角色下标偏移 }, select_role_index);
		while (get_game_status() == 0)
		{
			main_thread_exec_call(Send_选择角色, { select_role_index });
			Sleep(3000);
		}
	}
	else if (type == 1) {

	}
	else if (type == 2) {
		
		while (get_game_status() == 0)
		{
			if (select_role_index != get_role_index())
			{
				doKeyPress(VK_LEFT);
			}
			doKeyPress(VK_RETURN);
			Sleep(3000);
		}
	}
	g_role_index = select_role_index;
}



void game_status_0::create_role()
{

}