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
	return read_offset<DWORD>(__人物基址, { __地图偏移 });
}

DWORD game_status_3::get_map_start_address(DWORD map_address)
{
	return read_offset<DWORD>(get_map_address(), { __首地址 });
}

int game_status_3::get_map_object_count(DWORD map_start_address)
{
	return (read_offset<DWORD>(get_map_address(), { __尾地址 }) - map_start_address) / 4;
}