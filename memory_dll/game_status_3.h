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
	void 组包拾取();
	std::vector<MAP_OBJECT_STRUCT> 获取物品信息();
	bool 按键捡物();
	void 全屏聚物();
	int get_map_object_count(DWORD map_start_address);
	void move_to_next_room(int direction);
	void sort_by_distance(std::vector<MAP_OBJECT_STRUCT>& Objects);
	void attack_monster();
	void follow(std::wstring name = L"");
	bool get_the_custom_shop();

	
	bool 是否有怪物();
	void 移动到角色指定位置(int x, int y,int z = 0);
	void 按键_破晓女神();
	void 按键_帝血弑天();
	void 按键_天帝();
	void 按键_剑神();
	void 按键_风神();
};

