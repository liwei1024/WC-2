#include "stdafx.h"
#include "game_status_2.h"


game_status_2::game_status_2()
{
}


game_status_2::~game_status_2()
{
}
/*
疲劳值大于0则选择副本 小于0则 返回城镇
*/
void game_status_2::manage()
{
	if (get_current_role_fatigue_value() == 0)
	{
		doKeyPress(VK_ESCAPE);
		Sleep(1000);
	}
	else {
		按键选择副本(g_dungeon_id, g_dungeon_rank);
	}
}

void game_status_2::按键选择副本(int 副本ID,int 副本难度)
{
	int 当前副本ID, 当前副本难度;
	int flag = true;
	while (flag && get_game_status() == 2)
	{
		当前副本ID = read<int>(__副本ID);
		当前副本难度 = read<int>(read<int>(__副本难度)+__副本难度偏移);
		Sleep(500);
		if (副本ID == 当前副本ID && 当前副本难度 == 副本难度)
		{
			flag = false;
			while (true)
			{
				if (get_game_status() == 3)
				{
					break;
				}
				doKeyPress(VK_SPACE);
				Sleep(3000);
			}
			if (read<int>(__对话基址) == 1)
			{
				doKeyPress(VK_RETURN);
			}
			break;
		}
		if (副本ID != 当前副本ID)
		{
			doKeyPress(VK_NUMPAD2);
			Sleep(500);
			continue;
		}
		if (副本难度 != 当前副本难度 && 副本难度 > 当前副本难度)
		{
			doKeyPress(VK_NUMPAD3);
			Sleep(500);
			continue;
		}
		else if (副本难度 != 当前副本难度 && 副本难度 < 当前副本难度)
		{
			doKeyPress(VK_NUMPAD1);
			Sleep(500);
			continue;
		}
	}
}