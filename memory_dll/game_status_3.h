#pragma once
class game_status_3
{
public:
	game_status_3();
	~game_status_3();
private:
	DWORD get_map_address();
	DWORD get_map_start_address(DWORD map_address);
	int get_map_object_count(DWORD map_start_address);
};

