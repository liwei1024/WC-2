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