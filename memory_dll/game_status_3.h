#pragma once
class game_status_3
{
public:
	game_status_3();
	~game_status_3();

	void manage();
	void output_map_objects_info();
	
private:
	DWORD get_map_address();
	DWORD get_map_start_address();
	int get_map_object_count(DWORD map_start_address);
	void move_to_next_room(int direction);
	void sort_by_distance(std::vector<MAP_OBJECT_STRUCT>& Objects);
	void attack_monster();
	void follow();
	bool get_the_custom_shop();
	void get_loot();
	bool 是否有怪物();
	void 移动到角色指定位置(int x, int y,int z = 0);
	void 按键_帕拉丁();
};

