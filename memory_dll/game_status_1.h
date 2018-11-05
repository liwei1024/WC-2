#pragma once
class game_status_1
{
public:
	game_status_1();
	~game_status_1();

	void manage();

	
private:
	void enter_the_dungeon(int 副本ID, int 副本难度, int 副本类型);
	void move_to_copy_door(int copy_id, int type = 0);
	void teleport_to(RolePos pos);
	void return_role(int type = 0);
	void 组包到副本门口(int copy_id);
	void 按键进入选图(int copy_id);
	CITY_INFO get_city_info(int city_name);
	bool 按键进格蓝迪();
	void 组包到格蓝迪门口();
};

