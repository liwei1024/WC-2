#include "stdafx.h"
#include "game_status_3.h"


game_status_3::game_status_3()
{
}


game_status_3::~game_status_3()
{
}

DWORD game_status_3::get_map_address()
{
	return read_offset<DWORD>(__�����ַ, { __��ͼƫ�� });
}

DWORD game_status_3::get_map_start_address(DWORD map_address)
{
	return read_offset<DWORD>(get_map_address(), { __�׵�ַ });
}

int game_status_3::get_map_object_count(DWORD map_start_address)
{
	return (read_offset<DWORD>(get_map_address(), { __β��ַ }) - map_start_address) / 4;
}

void game_status_3::move_to_next_room(int direction)
{
	DWORD temp_data;
	DWORD coordinate_struct;
	int x, y, xf, yf, cx, cy = 0;
	temp_data = read<DWORD>(__�̵��ַ - 8);
	temp_data = read<DWORD>(temp_data + __ʱ���ַ);
	temp_data = read<DWORD>(temp_data + 140);
	coordinate_struct = temp_data + (direction + direction * 8) * 4 + 5936 + (direction * 4);
	x = read<int>(coordinate_struct + 0x0);
	y = read<int>(coordinate_struct + 0x4);
	xf = read<int>(coordinate_struct + 0x8);
	yf = read<int>(coordinate_struct + 0xc);
	if (direction == 0)
	{
		cx = x + xf;
		cy = y + yf;
	}
	else if (direction == 1) 
	{
		cx = x - 20;
		cy = y + yf / 2;
	}
	else if (direction == 2)
	{
		cx = x - xf / 2;
		cy = y + yf + 20;
	}
	else if (direction == 2)
	{
		cx = x + xf / 2;
		cy = y - 20;
	}
	main_thread_exec_call(Call_����Call, { read<int>(__�����ַ),cx,cy,0 });
	Sleep(200);
	main_thread_exec_call(Call_����Call, { read<int>(__�����ַ),(x + xf / 2), y, 0 });
}