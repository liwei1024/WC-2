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
	if (is_open_door() == true)
	{
		get_loot();
		if (is_boss_room() == true && �Ƿ��й���() == false)
		{
			//main_thread_exec_call(Send_�������);
			if (get_the_custom_shop() == true)
			{
				main_thread_exec_call(Send_����س�);
				while (true) {
					if (game_status != get_game_status())
					{
						g_ˢͼ����++;
						g_��ͼʱ�� = getTime() - g_��ͼʱ��;
						g_��ͼ��� = true;
						bulletin(L"[GC] �� %d �� ���κ�ʱ %d �� ", g_ˢͼ����, g_��ͼʱ��);
						break;
					}
					Sleep(2000);
				}
			}
			else {
				doKeyPress(VK_ESCAPE);
				Sleep(1000);
			}
		}
		else {
			move_to_next_room(GetDirection());
		}
	}
	else {
		attack_monster();
	}
}

DWORD game_status_3::get_map_address()
{
	
	return read_offset<int>(__�����ַ, { __��ͼƫ�� });
}

DWORD game_status_3::get_map_start_address()
{
	return read<int>(get_map_address() + __�׵�ַ);
}


int game_status_3::get_map_object_count(DWORD map_start_address)
{
	return  (read<int>(get_map_address() + __β��ַ) - map_start_address) / 4;
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

// ��ȡ������Ϣ
MAP_OBJECT_STRUCT get_object_info(DWORD object_pointer)
{
	MAP_OBJECT_STRUCT object;
	DWORD pos_pointer;
	object.address = object_pointer;
	object.type = read<DWORD>(object_pointer + __����ƫ��);
	object.camp = read<DWORD>(object_pointer + __��Ӫƫ��);
	object.health_point = read<DWORD>(object_pointer + __Ѫ��ƫ��);
	object.code = read<DWORD>(object_pointer + __����ƫ��);
	object.name = read_wstring(read<DWORD>(object_pointer + __����ƫ��), 100);
	if (object.type == 273)
	{
		pos_pointer = read<int>(object_pointer + __��������ƫ��);
		object.x = (int)read<float>(__��ɫ���� + 0);
		object.y = (int)read<float>(__��ɫ���� + 4);
		object.z = (int)read<float>(__��ɫ���� + 8);
	}
	else {
		pos_pointer = read<int>(object_pointer + __����ƫ��);
		object.x = (int)read<float>(pos_pointer + 0x10);
		object.y = (int)read<float>(pos_pointer + 0x14);
		object.z = (int)read<float>(pos_pointer + 0x18);
	}
	return object;
}
// ��ӡ����������Ϣ
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
		output_bebug_wstring(L"��ַ 0x%x", _ObjectInfo.address);
		output_bebug_wstring(L"���� %d", _ObjectInfo.code);
		output_bebug_wstring(L"���� %d", _ObjectInfo.type);
		output_bebug_wstring(L"��Ӫ %d", _ObjectInfo.camp);
		output_bebug_wstring(L"Ѫ�� %d", _ObjectInfo.health_point);
		output_bebug_wstring(L"λ�� %d,%d,%d", _ObjectInfo.x, _ObjectInfo.y, _ObjectInfo.z);
		output_bebug_wstring(L"���� %s", _ObjectInfo.name.c_str());
	}
}
// ����ɫ�����������
void game_status_3::sort_by_distance(std::vector<MAP_OBJECT_STRUCT>& Objects)
{
	MAP_OBJECT_STRUCT temp_var;
	MAP_OBJECT_STRUCT RolePos = get_object_info(read<int>(__�����ַ));
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
			if (g_auto_mode == ��ש)
			{
				main_thread_exec_call(Call_����Call, { 0,70032,113,Objects[i].x + createRandom(-10,10),Objects[i].y + createRandom(-10,10),Objects[i].z });
			}
			else {

			}
			Sleep(500);
			break;
		}
	}
}

void game_status_3::follow()
{
	DWORD map_start_address = get_map_start_address();
	DWORD map_object_count = get_map_object_count(map_start_address);
	std::vector<MAP_OBJECT_STRUCT> Objects;
	MAP_OBJECT_STRUCT object;
	RolePos role_pos = get_role_pos();
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
			if (abs(role_pos.x - Objects[i].x) > 150 || abs(role_pos.x - Objects[i].x) > 30)
			{
				if (role_pos.x > Objects[i].x)
				{
					�ƶ�����ɫָ��λ��(Objects[i].x + createRandom(-10, 10) + 100, Objects[i].y + createRandom(-10, 10));
					doKeyPress(VK_NUMPAD1);
				}
				else {
					�ƶ�����ɫָ��λ��(Objects[i].x + createRandom(-10, 10) - 100, Objects[i].y + createRandom(-10, 10));
					doKeyPress(VK_NUMPAD3);
				}
				Sleep(200);
				break;
			}
			
			
		}
	}
}

// ��ȡͨ���̵�
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
		if (object.type == 289 && object.camp == 200)
		{
			Objects.insert(Objects.end(), object);
		}
	}
	if (Objects.size() > 0)
	{
		sort_by_distance(Objects);
		for (size_t i = 0; i < Objects.size(); i++)
		{
			main_thread_exec_call(Send_���ʰȡ, { decrypt(Objects[i].address + 160),Objects[i].x + createRandom(-10,10),Objects[i].y + createRandom(-10,10) });
			Sleep(200);
		}
	}

}

bool game_status_3::�Ƿ��й���()
{
	DWORD map_start_address = get_map_start_address();
	DWORD map_object_count = get_map_object_count(map_start_address);
	MAP_OBJECT_STRUCT object;
	for (size_t i = 0; i < map_object_count; i++) {
		object = get_object_info(map_start_address + i * 4);
		if (object.code == 258 || object.code == 818 || object.code == 63821)
		{
			continue;
		}
		if (object.camp > 0)
		{
			if (object.type == 529 ||object.type == 273 || object.type == 545)
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

void game_status_3::�ƶ�����ɫָ��λ��(int x,int y,int z)
{
	if (g_�ƶ���ʽ == 0) //����call
	{
		main_thread_exec_call(Call_����Call, { read<int>(__�����ַ),x,y,z });
	}
	else if (g_�ƶ���ʽ == 1) { //�ű��ƶ�

	}
	Sleep(200);
}


void game_status_3::����_������()
{
	Pos current_room = get_current_room_pos();
	DWORD figure_pointer = read<DWORD>(__�����ַ);
	if (g_dungeon_id == ������)
	{
		if (current_room.x == 0 && current_room.y == 0 && g_��ͼ��� == true)
		{
			g_��ͼʱ�� = getTime();
			g_��ͼ��� = false;
			doKeyPress(VK_F);
			Sleep(800);
			doKeyPress(VK_Y);
			Sleep(2500);
		}
		else if (current_room.x == 1 && current_room.y == 0) {
			�ƶ�����ɫָ��λ��(345, 216);
			doKeyPress(VK_A);
			Sleep(2000);
		}
		else if (current_room.x == 2 && current_room.y == 0) {
			�ƶ�����ɫָ��λ��(582, 241);
			doKeyPress(VK_A);
			Sleep(1000);
		}
		else if (current_room.x == 2 && current_room.y == 1) {
			�ƶ�����ɫָ��λ��(521, 200);
			doKeyPress(VK_R);
			Sleep(1500);
		}
		else if (current_room.x == 2 && current_room.y == 2) {
			�ƶ�����ɫָ��λ��(611, 201);
			doKeyPress(VK_T);
			Sleep(1000);
			�ƶ�����ɫָ��λ��(550, 335);
			doKeyPress(VK_A);
			Sleep(500);
			this->follow();
			doKeyPress(VK_Q);
			Sleep(1500);
		}
		else if (current_room.x == 3 && current_room.y == 2) {
			�ƶ�����ɫָ��λ��(343, 273);
			doKeyPress(VK_A);
			Sleep(1500);
		}
		else if (current_room.x == 3 && current_room.y == 1) {
			�ƶ�����ɫָ��λ��(343, 273);
			doKeyPress(VK_NUMPAD3);
			doKeyPress(VK_W);
			Sleep(3000);
		}
		if (is_open_door() == true)
		{
			return;
		}
		this->follow();
		doKeyPress(VK_S);
		if (is_open_door() == true)
		{
			return;
		}
		this->follow();
		doKeyPress(VK_E);
		if (is_open_door() == true)
		{
			return;
		}
		this->follow();
		doKeyPress(VK_G);
		if (is_open_door() == true)
		{
			return;
		}
		this->follow();
		doKeyPress(VK_H);
		if (is_open_door() == true)
		{
			return;
		}
		this->follow();
		doKeyPress(VK_S);
		if (is_open_door() == true)
		{
			return;
		}
		while (is_open_door() == true)
		{
			this->follow();
			doKeyPress(VK_X, 1500);
		}
	}
}