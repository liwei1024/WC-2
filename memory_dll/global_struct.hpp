#pragma once

struct Pos
{
	int x, y, z = 0;
};

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
	DWORD code;
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
	int 完成次数 = 0;
};

struct RolePos
{
	int max_city_id = 38;
	int min_city_id = 2;
	int x = 0;
	int y = 0;
	int z = 0;
};

typedef struct _WINDOW_INFO
{
	int top = 0;
	int bottom = 0;
	int left = 0;
	int right = 0;
	int width = 0;
	int height = 0;
} WINDOW_INFO, *PWINDOW_INFO;

struct GOODS_INFO
{
	int address;
	int count = 1;
	int level;
	std::wstring name;
	int index;
};