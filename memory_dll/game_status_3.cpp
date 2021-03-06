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
	
	int game_status = get_game_status();
	if (is_open_door() == true && 是否有怪物() == false)
	{
		if (按键捡物() == true)
		{
			return;
		}
		if (is_boss_room() == true && 是否有怪物() == false)
		{
			switch (g_auto_mode)
			{
			case 练习:
				while (true)
				{
					if (game_status != get_game_status() || is_boss_room() == false)
					{
						g_刷图次数++;
						g_过图时间 = getTime() - g_过图时间;
						g_首图标记 = true;
						//bulletin(_T("练习第 %d 次 耗时 %d s "), g_刷图次数, (int)(g_过图时间 / 1000));
						Sleep(1000);
						break;
					}
					doKeyPress(VK_F10);
					Sleep(1000);
				}
				break;
			case 搬砖:
				while (true)
				{
					if (get_the_custom_shop() == false)
					{
						Sleep(2000);
						doKeyPress(VK_ESCAPE);
						continue;
					}
					按键卖物();
					doKeyPress(VK_ESCAPE);
					while (true)
					{
						if (game_status != get_game_status() || is_boss_room() == false)
						{
							g_刷图次数++;
							g_过图时间 = getTime() - g_过图时间;
							g_首图标记 = true;
							//bulletin(_T("搬砖第 %d 次 耗时 %d 秒 "), g_刷图次数, (int)(g_过图时间 / 1000));
							Sleep(1000);
							break;
						}
						if (get_current_role_fatigue_value() <= 0) {
							doKeyPress(VK_F12);
						}
						else {
							doKeyPress(VK_F10);
						}
						Sleep(1000);
					}
					break;
				}
				break;
			case 剧情:

				break;
			default:
				break;
			}
		}
		else {
			move_to_next_room(GetDirection());
		}
	}
	else {
		if (g_首图标记 == true)
		{
			g_过图时间 = getTime();
			g_首图标记 = false;
		}
		//attack_monster();
		std::wstring role_job_name = get_role_job_name();
		if (wcscmp(role_job_name.c_str(),L"破晓女神") == 0)
		{
			按键_破晓女神();
		}
		else if (wcscmp(role_job_name.c_str(), L"帝血弑天") == 0) {
			按键_帝血弑天();
		}
		else if (wcscmp(role_job_name.c_str(), L"天帝") == 0) {
			按键_天帝();
		}
		else if (wcscmp(role_job_name.c_str(), L"剑神") == 0) {
			按键_剑神(); 
		}
		else if (wcscmp(role_job_name.c_str(), L"风神") == 0) {
			按键_风神(); 
		}
		
	}
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
	temp_data = read<DWORD>(temp_data + __坐标结构偏移1);
	coordinate_struct = temp_data + (direction + direction * 8) * 4 + __坐标结构偏移2 + (direction * 4);
	x = read<int>(coordinate_struct + 0x0);
	y = read<int>(coordinate_struct + 0x4);
	xf = read<int>(coordinate_struct + 0x8);
	yf = read<int>(coordinate_struct + 0xc);
	if (direction == 0)
	{
		cx = x + xf + 20;
		cy = y + yf / 2;
		//doKeyPress(VK_NUMPAD1);
	}
	else if (direction == 1) 
	{
		cx = x - 20;
		cy = y + yf / 2;
		//doKeyPress(VK_NUMPAD3);
	}
	else if (direction == 2)
	{
		cx = x + xf / 2;
		cy = y + yf + 20;
		//doKeyPress(VK_NUMPAD5);
	}
	else if (direction == 3)
	{
		cx = x + xf / 2;
		cy = y - 20;
		//doKeyPress(VK_NUMPAD2);
	}
	Sleep(200);
	//main_thread_exec_call(Call_坐标Call, { read<int>(__人物基址),cx,cy,0 });
	移动到角色指定位置(cx, cy);
	Sleep(200);
	/*main_thread_exec_call(Call_坐标Call, { read<int>(__人物基址),(x + xf / 2), y, 0 });
	Sleep(1000);*/
	//RolePos role_pos = get_role_pos();
	//bulletin(L"方向 %d 门坐标 %d,%d", direction,cx,cy);
	if (direction == 0) {
		doKeyPress(VK_NUMPAD1,500);
	}
	else if (direction == 1) {
		doKeyPress(VK_NUMPAD3, 500);
	}
	else if (direction == 2)
	{
		/*if (cx > role_pos.x)
		{
			doKeyPress(VK_NUMPAD3);
		}
		else {
			doKeyPress(VK_NUMPAD1);
		}*/
		doKeyPress(VK_NUMPAD5, 500);
	}
	else if (direction == 3) {
		/*if (cx > role_pos.x)
		{
			doKeyPress(VK_NUMPAD3);
		}
		else {
			doKeyPress(VK_NUMPAD1);
		}*/
		doKeyPress(VK_NUMPAD2, 500);
	}
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
	if (object.type == 289 && object.camp == 200)
	{
		object.name = read_wstring(read<DWORD>(read<DWORD>(object_pointer + __地面物品名称偏移) + 0x24) + 0, 100);
	}
	else {
		object.name = read_wstring(read<DWORD>(object_pointer + __名称偏移), 100);
	}
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
	output_bebug_wstring(_T("map_start_address %x\n"), map_start_address);
	DWORD map_object_count = get_map_object_count(map_start_address);
	output_bebug_wstring(_T("map_object_count %d\n"), map_object_count);
	MAP_OBJECT_STRUCT _ObjectInfo;
	DWORD object_address;
	for (size_t i = 0; i < map_object_count; i++)
	{
		object_address = read<int>(map_start_address + i * 4);
		if (object_address <= 0)continue;
		_ObjectInfo = get_object_info(object_address);
		output_bebug_wstring(_T("====================================="));
		output_bebug_wstring(_T("address 0x%x"), _ObjectInfo.address);
		output_bebug_wstring(_T("code %d"), _ObjectInfo.code);
		output_bebug_wstring(_T("type %d"), _ObjectInfo.type);
		output_bebug_wstring(_T("camp %d"), _ObjectInfo.camp);
		output_bebug_wstring(_T("health_point %d"), _ObjectInfo.health_point);
		output_bebug_wstring(_T("pos %d,%d,%d"), _ObjectInfo.x, _ObjectInfo.y, _ObjectInfo.z);
		output_bebug_wstring(_T("name %s"), _ObjectInfo.name.c_str());
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
	MAP_OBJECT_STRUCT object;
	DWORD object_address;
	for (size_t i = 0; i < map_object_count; i++) {
		object_address = read<int>(map_start_address + i * 4);
		if (object_address <= 0)continue;
		object = get_object_info(object_address);
		if (object.code == 258 || object.code == 818 || object.code == 63821)
		{
			continue;
		}
		if (object.type == 529 || object.type == 273 || object.type == 545)
		{
			if (object.camp > 0)
			{
				if (object.health_point > 0 || object.code == 8104 || object.code == 817)
				{
					
					this->follow();
					main_thread_exec_call(Call_技能Call, { read<int>(__人物基址),g_技能列表[createRandom(0,(g_技能列表.size()-1))],createRandom(100000,10000000), object.x + createRandom(-10, 10), object.y + createRandom(-10, 10), object.z });
					Sleep(100);
					break;
				}
			}
		}
		
	}
}

void game_status_3::follow(std::wstring name)
{
	DWORD map_start_address = get_map_start_address();
	DWORD map_object_count = get_map_object_count(map_start_address);
	MAP_OBJECT_STRUCT object;
	RolePos role_pos = get_role_pos();
	DWORD object_address;
	for (size_t i = 0; i < map_object_count; i++) {
		object_address = read<int>(map_start_address + i * 4);
		if (object_address <= 0)continue;
		object = get_object_info(object_address);
		if (object.code == 258 || object.code == 818 || object.code == 63821)
			continue;
		if (!(object.health_point > 0 || object.code == 8104 || object.code == 817))
			continue;
		if (!name.empty() && wcscmp(object.name.c_str(), name.c_str()) != 0)
			continue;
		if (!(object.type == 529 || object.type == 273 || object.type == 545))
			continue;
		if (!(object.camp > 0))
			continue;
		if (role_pos.x > object.x)
			doKeyPress(VK_NUMPAD1);
		if (role_pos.x < object.x)
			doKeyPress(VK_NUMPAD3);
		Sleep(200);
		if (abs(role_pos.x - object.x) > 200 || abs(role_pos.y - object.y) > 50)
		{
			if (role_pos.x > object.x)
			{
				移动到角色指定位置(object.x + createRandom(-10, 10) + 200, object.y + createRandom(-10, 10));
				doKeyPress(VK_NUMPAD1);
			}
			else {
				移动到角色指定位置(object.x + createRandom(-10, 10) - 200, object.y + createRandom(-10, 10));
				doKeyPress(VK_NUMPAD3);
			}
			//Sleep(200);
			break;
		}
	}
}


MAP_OBJECT_STRUCT game_status_3::getObjectInfoByNmae(std::wstring name)
{
	DWORD map_start_address = get_map_start_address();
	DWORD map_object_count = get_map_object_count(map_start_address);
	MAP_OBJECT_STRUCT object;
	RolePos role_pos = get_role_pos();
	DWORD object_address;
	for (size_t i = 0; i < map_object_count; i++) {
		object_address = read<int>(map_start_address + i * 4);
		if (object_address <= 0)continue;
		object = get_object_info(object_address);
		if (!name.empty() && wcscmp(object.name.c_str(), name.c_str()) == 0) {
			break;
		}
	}
	return object;
}

// 获取通关商店 营火
bool game_status_3::get_the_custom_shop()
{
	DWORD map_start_address = get_map_start_address();
	DWORD map_object_count = get_map_object_count(map_start_address);
	MAP_OBJECT_STRUCT object;
	DWORD object_address;
	for (size_t i = 0; i < map_object_count; i++) {
		object_address = read<int>(map_start_address + i * 4);
		if (object_address <= 0)continue;
		object = get_object_info(object_address);
		if (object.code == 48026)
		{
			return true;
		}
	}
	return false;
}

void game_status_3::组包拾取()
{

	DWORD map_start_address = get_map_start_address();
	DWORD map_object_count = get_map_object_count(map_start_address);
	std::vector<MAP_OBJECT_STRUCT> Objects;
	MAP_OBJECT_STRUCT object;
	DWORD object_address;
	for (size_t i = 0; i < map_object_count; i++) {
		object_address = read<int>(map_start_address + i * 4);
		if (object_address <= 0)continue;
		object = get_object_info(object_address);
		if (object.code == Code_鸡腿 || object.code == Code_肉块 || object.code == Code_成长之泉水)
			continue;
		if (object.type == 289 && object.camp == 200)
		{
			main_thread_exec_call(Send_组包拾取, { decrypt(object.address + 172),object.x + createRandom(-10,10),object.y + createRandom(-10,10) });
			Sleep(100);
		}
	}
}

std::vector<MAP_OBJECT_STRUCT> game_status_3::获取物品信息()
{
	DWORD map_start_address = get_map_start_address();
	DWORD map_object_count = get_map_object_count(map_start_address);
	std::vector<MAP_OBJECT_STRUCT> Objects;
	MAP_OBJECT_STRUCT object;
	DWORD object_address;
	RolePos role_pos = get_role_pos();
	for (size_t i = 0; i < map_object_count; i++) {
		object_address = read<int>(map_start_address + i * 4);
		if (object_address <= 0)continue;
		object = get_object_info(object_address);
		if (object.code == Code_鸡腿 || object.code == Code_肉块 || object.code == Code_成长之泉水)
			continue;
		if (
			wcscmp(object.name.c_str(), L"碎布片") == 0 ||
			wcscmp(object.name.c_str(), L"最下级硬化剂") == 0 ||
			wcscmp(object.name.c_str(), L"最下级砥石") == 0 ||
			wcscmp(object.name.c_str(), L"风化的碎骨") == 0 ||
			wcscmp(object.name.c_str(), L"钢铁片") == 0 ||
			wcscmp(object.name.c_str(), L"生锈的铁片") == 0 ||
			wcscmp(object.name.c_str(), L"破旧的皮革") == 0 ||
			wcscmp(object.name.c_str(), L"丢失的圣诞袜") == 0 
			)
			continue;
		
		if (object.type == 289 && object.camp == 200)
		{
			if (object.z > 0)
			{
				Sleep(1000);
			}
			Objects.insert(Objects.begin(), object);
		}
	}
	return Objects;
}

bool game_status_3::按键捡物()
{
	std::vector<MAP_OBJECT_STRUCT> Objects = 获取物品信息();
	MAP_OBJECT_STRUCT object;
	RolePos role_pos = get_role_pos();
	Pos current_room = get_current_room_pos();
	if (Objects.size() > 0)
	{
		if (current_room.x == 2 && current_room.y == 2 && g_dungeon_id == 104)
		{
			doKeyPress(VK_V);
			Sleep(200);
			doKeyPress(VK_X, 120 * Objects.size());
		}
		else {
			for (size_t i = 0; i < Objects.size(); i++) {
				object = Objects[i];
				role_pos = get_role_pos();
				if (abs(role_pos.x - object.x) > 2 || abs(role_pos.y - object.y) > 2)
				{
					//main_thread_exec_call(Call_坐标Call, { read<int>(__人物基址),object.x + createRandom(-2,2),object.y + createRandom(-2,2),0 });
					移动到角色指定位置(object.x + createRandom(-2, 2), object.y + createRandom(-2, 2));
				}
				Sleep(200);
				if (wcscmp(object.name.c_str(), L"金币") != 0)
				{
					doKeyPress(VK_X);
					Sleep(100);
				}
				return true;
			}
		}
	}
	return false;
}

void game_status_3::全屏聚物()
{
	DWORD map_start_address = get_map_start_address();
	DWORD map_object_count = get_map_object_count(map_start_address);
	std::vector<MAP_OBJECT_STRUCT> Objects;
	MAP_OBJECT_STRUCT object;
	DWORD object_address;
	for (size_t i = 0; i < map_object_count; i++) {
		object_address = read<int>(map_start_address + i * 4);
		if (object_address <= 0)continue;
		object = get_object_info(object_address);
		if (object.code == Code_鸡腿 || object.code == Code_肉块 || object.code == Code_成长之泉水)
			continue;
		if (object.type == 289 && object.camp == 200)
		{
			if (read<int>(object.address + 0x210) == 0)//可拾取状态
			{
				write<float>(read<int>(object.address + __坐标偏移) + 16,
					read<float>(read<int>(read<int>(__人物基址) + __人物坐标偏移) + 0));//取对象坐标(一级偏移, 0)

				write<float>(read<int>(object.address + __坐标偏移) + 20,
					read<float>(read<int>(read<int>(__人物基址) + __人物坐标偏移) + 4));//取对象坐标(一级偏移, 1)
			}
		}
	}
}

bool game_status_3::是否有怪物()
{
	DWORD map_start_address = get_map_start_address();
	DWORD map_object_count = get_map_object_count(map_start_address);
	std::vector<MAP_OBJECT_STRUCT> Objects;
	MAP_OBJECT_STRUCT object;
	DWORD object_address;
	for (size_t i = 0; i < map_object_count; i++) {
		object_address = read<int>(map_start_address + i * 4);
		if (object_address <= 0)continue;
		object = get_object_info(object_address);
		if (object.code == 258 || object.code == 818 || object.code == 63821)
		{
			continue;
		}
		if (object.type == 529 || object.type == 273 || object.type == 545)
		{
			if (object.camp > 0)
			{
				if (object.health_point > 0 || object.code == 8104 || object.code == 817)
				{
					return true;
				}
			}
		}

	}
	return false;
}

void game_status_3::移动到角色指定位置(int x,int y,int z)
{
	if (get_game_status() == 3)
	{
		if (g_移动方式 == 0) //坐标call
		{
			main_thread_exec_call(Call_坐标Call, { read<int>(__人物基址),x,y,z });
		}
		else if (g_移动方式 == 1) { //脚本移动
			RolePos rolePos = get_role_pos();
			main_thread_exec_call(Call_移动Call, { (abs(rolePos.x - x) + abs(rolePos.y - y)),x,y });
			Sleep((abs(rolePos.x - x) + abs(rolePos.y - y))+100);
		}
	}
	Sleep(100);
}

void game_status_3::按键_破晓女神()
{
	Pos current_room = get_current_room_pos();
	RolePos role_pos;
	//DWORD 副本ID = read<int>(__图内副本ID);
	if (g_dungeon_id == 格蓝迪)
	{
		if (current_room.x == 0 && current_room.y == 0)
		{
			Sleep(1000);
			按键释放技能(VK_F);
			移动到角色指定位置(468, 239);
			Sleep(300);
			按键释放技能(VK_G);
		}
		else if (current_room.x == 1 && current_room.y == 0) {
			Sleep(500);
			doKeyPress(VK_Y);
			Sleep(3000);
		}
		else if (current_room.x == 2 && current_room.y == 0) {
			移动到角色指定位置(582, 241);
			Sleep(300);
			按键释放技能(VK_A,300);
		}
		else if (current_room.x == 2 && current_room.y == 1) {
			移动到角色指定位置(521, 200);
			Sleep(300);
			doKeyPress(VK_NUMPAD1);
			Sleep(100);
			按键释放技能(VK_R);
		}
		else if (current_room.x == 2 && current_room.y == 2) {
			移动到角色指定位置(331, 329);
			Sleep(200);
			doKeyPress(VK_NUMPAD3);
			按键释放技能(VK_A);
			移动到角色指定位置(611, 201);
			Sleep(300);
			按键释放技能(VK_T);
			Sleep(300);
			this->follow(L"巨人波图拉");
			按键释放技能(VK_Q);
		}
		else if (current_room.x == 3 && current_room.y == 2) {
			移动到角色指定位置(343, 290);
			Sleep(300);
			按键释放技能(VK_A, 300);
		}
		else if (current_room.x == 3 && current_room.y == 1) {
			doKeyPress(VK_NUMPAD3);
			/*移动到角色指定位置(333, 216);
			按键释放技能(VK_H);
			if (is_open_door() == true)
			{
				return;
			}*/
			doKeyPress(VK_W);
			Sleep(4000);
		}
		if (is_open_door() == true)
		{
			
			return;
		}
		this->follow();
		按键释放技能(VK_S);
		if (is_open_door() == true)
		{
			return;
		}
		this->follow();
		按键释放技能(VK_E);
		if (is_open_door() == true)
		{
			return;
		}
		this->follow();
		按键释放技能(VK_G);
		if (is_open_door() == true)
		{
			return;
		}
		this->follow();
		按键释放技能(VK_H);
		if (is_open_door() == true)
		{
			return;
		}
		this->follow();
		按键释放技能(VK_D);
		if (is_open_door() == true)
		{
			return;
		}
		this->follow();
		按键释放技能(VK_S);
		if (is_open_door() == true)
		{
			return;
		}
		int i = 0;
		while (is_open_door() == false)
		{
			if (read<int>(__对话基址) == 1)
			{
				doKeyPress(VK_RETURN);
				continue;
			}
			this->follow();
			doKeyPress(VK_X, 1500);
			if (i>3)
			{
				this->follow();
				按键释放技能(VK_S, 1500);
			}
			if (i > 20)
			{
				this->follow();
				按键释放技能(VK_G);
			}
			if (i>50) {
				g_auto_switch = false;
				return;
			}
			i++;
		}
	}
}

void game_status_3::按键_帝血弑天()
{
	Pos current_room = get_current_room_pos();
	DWORD figure_pointer = read<DWORD>(__人物基址);
	//DWORD 副本ID = read<int>(__图内副本ID);
	if (g_dungeon_id == 格蓝迪)
	{
		if (current_room.x == 0 && current_room.y == 0)
		{
			Sleep(1000);
			按键释放技能(VK_F);
			按键释放技能(VK_H,500);
			按键释放技能(VK_E);
			移动到角色指定位置(364, 236);
			doKeyPress(VK_A);
		}
		else if (current_room.x == 1 && current_room.y == 0) {
			移动到角色指定位置(255, 252);
			按键释放技能(VK_W, 500);
		}
		else if (current_room.x == 2 && current_room.y == 0) {
			移动到角色指定位置(265, 246);
			按键释放技能(VK_E);
			Sleep(500);
		}
		else if (current_room.x == 2 && current_room.y == 1) {
			移动到角色指定位置(889, 250);
			doKeyPress(VK_NUMPAD1);
			doKeyPress(VK_X,500);
			按键释放技能(VK_S);
			按键释放技能(VK_Q);
			按键释放技能(VK_A);
		}
		else if (current_room.x == 2 && current_room.y == 2) {
			移动到角色指定位置(221, 186);
			按键释放技能(VK_G);
			doKeyPress(VK_NUMPAD3);
			按键释放技能(VK_Y);
		}
		else if (current_room.x == 3 && current_room.y == 2) {
			移动到角色指定位置(540, 300);
			按键释放技能(VK_T);
		}
		else if (current_room.x == 3 && current_room.y == 1) {
			移动到角色指定位置(542, 171);
			doKeyPress(VK_NUMPAD3);
			doKeyPress(VK_R);
		}
		if (is_open_door() == true)
		{
			return;
		}
		this->follow();
		doKeyPress(VK_A);
		Sleep(1500);
		while (is_open_door() == false)
		{
			if (read<int>(__对话基址) == 1)
			{
				doKeyPress(VK_RETURN);
				continue;
			}
			this->follow();
			doKeyPress(VK_X, 1500);
		}
	}
}

void game_status_3::按键_天帝()
{

}

void game_status_3::按键_剑神()
{

}

void game_status_3::按键_风神()
{

}
