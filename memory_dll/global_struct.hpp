#pragma once

struct COORDINATE
{
	int x, y, z = 0;
};

struct MAP_OBJECT_STRUCT
{
	DWORD address;
	std::wstring name;
	DWORD type;
	DWORD camp;
	DWORD health_point;
	int x;
	int y;
	int z;
};

struct KNAPSACK_LOOT_STRUCT
{
	DWORD address = 0;
	std::wstring name;
	int index = 0;
	DWORD count = 0;
	DWORD grade = 0;
};

struct TASK_STRUCT
{
	DWORD address = 0;
	std::wstring name;
	DWORD type = 0;
	int copy_id = 0;
	int task_id = 0;
	int materials = 0;
	int task_length = 0;
	std::wstring condition_type;
	int ��ɴ��� = 0;
};

