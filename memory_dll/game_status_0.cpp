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
		bulletin(L"���н�ɫˢͼ��ϣ��Զ��ر�");
		g_auto_switch = false;
	}
	else {
		select_role(g_ѡ�Ƿ�ʽ);
	}
	
}

int game_status_0::get_role_index()
{
	int role_index = read_offset<int>(__����ȡֵ, {__��ɫ�±�ƫ��});
	return role_index;
	
}

int game_status_0::get_role_count()
{
	int role_count = read_offset<int>(__����ȡֵ, { __��ǰ��ɫ����,__��ɫ����ƫ��2 });
	return role_count;
}

int game_status_0::get_role_max_count()
{
	int role_max_count = read_offset<int>(__����ȡֵ, { __����ɫ����,__��ɫ����ƫ��2 });
	return role_max_count;
}



void game_status_0::select_role(int type)
{
	int select_role_index = g_role_index + 1;
	if (type == 0)
	{
		write_offset(__����ȡֵ, { __��ɫ�±�ƫ�� }, select_role_index);
		while (get_game_status() == 0)
		{
			main_thread_exec_call(Send_ѡ���ɫ, { select_role_index });
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