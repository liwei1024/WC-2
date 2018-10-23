#include "stdafx.h"
#include "game_status_3.h"
#include "game_astar.hpp"


game_status_3::game_status_3()
{
}


game_status_3::~game_status_3()
{
}

void game_status_3::manage()
{

}

DWORD game_status_3::get_map_address()
{
	
	return read_offset<int>(__人物基址, { __地图偏移 });
}

DWORD game_status_3::get_map_start_address()
{
	return read<int>(get_map_address() + __首地址);
}


int game_status_3::get_map_object_count(DWORD map_start_address)
{
	return  (read<int>(get_map_address() + __尾地址) - map_start_address) / 4;
}

void game_status_3::move_to_next_room(int direction)
{
	DWORD temp_data;
	DWORD coordinate_struct;
	int x, y, xf, yf, cx, cy = 0;
	temp_data = read<DWORD>(__商店基址 - 8);
	temp_data = read<DWORD>(temp_data + __时间基址);
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
	main_thread_exec_call(Call_坐标Call, { read<int>(__人物基址),cx,cy,0 });
	Sleep(200);
	main_thread_exec_call(Call_坐标Call, { read<int>(__人物基址),(x + xf / 2), y, 0 });
}

// 获取对象信息
MAP_OBJECT_STRUCT get_object_info(DWORD object_pointer)
{
	MAP_OBJECT_STRUCT object;
	DWORD pos_pointer;
	object.address = object_pointer;
	object.type = read<DWORD>(object_pointer + __类型偏移);
	object.camp = read<DWORD>(object_pointer + __阵营偏移);
	object.health_point = read<DWORD>(object_pointer + __血量偏移);
	object.code = read<DWORD>(object_pointer + __代码偏移);
	object.name = read_wstring(read<DWORD>(object_pointer + __名称偏移), 100);
	if (object.type == 273)
	{
		pos_pointer = read<int>(object_pointer + __人物坐标偏移);
		object.x = (int)read<float>(__角色坐标 + 0);
		object.y = (int)read<float>(__角色坐标 + 4);
		object.z = (int)read<float>(__角色坐标 + 8);
	}
	else {
		pos_pointer = read<int>(object_pointer + __坐标偏移);
		object.x = (int)read<float>(pos_pointer + 0x10);
		object.y = (int)read<float>(pos_pointer + 0x14);
		object.z = (int)read<float>(pos_pointer + 0x18);
	}
	return object;
}
// 打印副本对象信息
void game_status_3::output_map_objects_info()
{
	DWORD map_start_address = get_map_start_address();
	output_bebug_wstring(L"map_start_address %x\n", map_start_address);
	DWORD map_object_count = get_map_object_count(map_start_address);
	output_bebug_wstring(L"map_object_count %d\n", map_object_count);
	MAP_OBJECT_STRUCT _ObjectInfo;
	DWORD object_address;
	for (size_t i = 0; i < map_object_count; i++)
	{
		object_address = read<int>(map_start_address + i * 4);
		if (object_address <= 0)continue;
		_ObjectInfo = get_object_info(object_address);
		output_bebug_wstring(L"=====================================");
		output_bebug_wstring(L"地址 0x%x", _ObjectInfo.address);
		output_bebug_wstring(L"代码 %d", _ObjectInfo.code);
		output_bebug_wstring(L"类型 %d", _ObjectInfo.type);
		output_bebug_wstring(L"阵营 %d", _ObjectInfo.camp);
		output_bebug_wstring(L"血量 %d", _ObjectInfo.health_point);
		output_bebug_wstring(L"位置 %d,%d,%d", _ObjectInfo.x, _ObjectInfo.y, _ObjectInfo.z);
		output_bebug_wstring(L"名称 %s", _ObjectInfo.name.c_str());
	}
}
// 按角色最近距离排序
void game_status_3::sort_by_distance(std::vector<MAP_OBJECT_STRUCT>& Objects)
{
	MAP_OBJECT_STRUCT temp_var;
	MAP_OBJECT_STRUCT RolePos = get_object_info(read<int>(__人物基址));
	for (size_t i = 0; i < Objects.size(); i++)
	{
		for (size_t j = 0; j < Objects.size() - i; j++)
		{
			if (abs(Objects[j].x - RolePos.x) + abs(Objects[j].y - RolePos.y) > abs(Objects[j + 1].x - RolePos.x) + abs(Objects[j + 1].y - RolePos.y))
			{
				temp_var = Objects[j];
				Objects[j + 1] = Objects[j];
				Objects[j] = temp_var;
			}
		}
	}
}

// 
void game_status_3::attack_monster()
{
	DWORD map_start_address = get_map_start_address();
	DWORD map_object_count = get_map_object_count(map_start_address);
	std::vector<MAP_OBJECT_STRUCT> Objects;
	MAP_OBJECT_STRUCT object;
	for (size_t i = 0; i < map_object_count; i++) {
		object = get_object_info(map_start_address + i * 4);
		if (object.code == 258 || object.code == 818 || object.code == 63821)
		{
			continue;
		}
		if (
			object.type == 529 ||
			object.type == 273 ||
			object.type == 545
			)
		{
			if (object.camp > 0)
			{
				if (object.health_point > 0 || object.code == 8104 || object.code == 817)
				{
					Objects.insert(Objects.end(), object);
				}
			}
		}
	}
	if (Objects.size() > 0)
	{
		sort_by_distance(Objects);
		for (size_t i = 0; i < Objects.size(); i++)
		{
			//AttackFunction(Objects[i]);
			if (g_auto_mode == 搬砖)
			{
				main_thread_exec_call(Call_技能Call, { 0,70032,113,Objects[i].x + createRandom(-10,10),Objects[i].y + createRandom(-10,10),Objects[i].z });
			}
			else {

			}
			Sleep(500);
		}
	}
}

// 获取通关商店
bool game_status_3::get_the_custom_shop()
{
	DWORD map_start_address = get_map_start_address();
	DWORD map_object_count = get_map_object_count(map_start_address);
	MAP_OBJECT_STRUCT object;
	for (size_t i = 0; i < map_object_count; i++) {
		object = get_object_info(map_start_address + i * 4);
		if (object.type == 33 && object.camp == 200)
		{
			if (read<int>(object.address + 1020) == 48026)
			{
				return true;
			}
		}
	}
	return false;
}

void game_status_3::get_loot()
{
	DWORD map_start_address = get_map_start_address();
	DWORD map_object_count = get_map_object_count(map_start_address);
	std::vector<MAP_OBJECT_STRUCT> Objects;
	MAP_OBJECT_STRUCT object;
	for (size_t i = 0; i < map_object_count; i++) {
		object = get_object_info(map_start_address + i * 4);
		if (object.code == 258 || object.code == 818 || object.code == 63821)
		{
			continue;
		}
		if (
			object.type == 289
			)
		{
			if (object.camp == 200)
			{
				Objects.insert(Objects.end(), object);
			}
		}
	}
	if (Objects.size() > 0)
	{
		sort_by_distance(Objects);
		for (size_t i = 0; i < Objects.size(); i++)
		{
			main_thread_exec_call(Send_组包拾取, { decrypt(Objects[i].address + 160),Objects[i].x + createRandom(-10,10),Objects[i].y + createRandom(-10,10) });
			Sleep(200);
		}
	}

}