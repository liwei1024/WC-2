#include "stdafx.h"
#include "game_status_2.h"


game_status_2::game_status_2()
{
}


game_status_2::~game_status_2()
{
}
/*
ƣ��ֵ����0��ѡ�񸱱� С��0�� ���س���
*/
void game_status_2::manage()
{
	if (get_current_role_fatigue_value() == 0)
	{
		doKeyPress(VK_ESCAPE);
		Sleep(1000);
	}
	else {
		����ѡ�񸱱�(g_dungeon_id, g_dungeon_rank);
	}
}

void game_status_2::����ѡ�񸱱�(int ����ID,int �����Ѷ�)
{
	int ��ǰ����ID, ��ǰ�����Ѷ�;
	int flag = true;
	while (flag && get_game_status() == 2)
	{
		��ǰ����ID = read<int>(__����ID);
		��ǰ�����Ѷ� = read<int>(read<int>(__�����Ѷ�)+__�����Ѷ�ƫ��);
		Sleep(500);
		if (����ID == ��ǰ����ID && ��ǰ�����Ѷ� == �����Ѷ�)
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
			if (read<int>(__�Ի���ַ) == 1)
			{
				doKeyPress(VK_RETURN);
			}
			break;
		}
		if (����ID != ��ǰ����ID)
		{
			doKeyPress(VK_NUMPAD2);
			Sleep(500);
			continue;
		}
		if (�����Ѷ� != ��ǰ�����Ѷ� && �����Ѷ� > ��ǰ�����Ѷ�)
		{
			doKeyPress(VK_NUMPAD3);
			Sleep(500);
			continue;
		}
		else if (�����Ѷ� != ��ǰ�����Ѷ� && �����Ѷ� < ��ǰ�����Ѷ�)
		{
			doKeyPress(VK_NUMPAD1);
			Sleep(500);
			continue;
		}
	}
}