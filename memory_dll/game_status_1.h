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
};

