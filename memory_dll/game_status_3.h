#pragma once
class game_status_3
{
public:
	game_status_3();
	~game_status_3();

	void manage();
	
	DWORD get_map_address();
	DWORD get_map_start_address();
	DWORD get_map_end_address();
	int get_map_object_count(DWORD map_start_address);
	void move_to_next_room(int direction);
	void output_map_objects_info();
	void sort_by_distance(std::vector<MAP_OBJECT_STRUCT>& Objects);
	void attack_monster();
	bool get_the_custom_shop();
	void get_loot();
	
};

