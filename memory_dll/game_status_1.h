#pragma once
class game_status_1
{
public:
	game_status_1();
	~game_status_1();

	void manage();

	
private:
	void enter_the_dungeon(int ����ID, int �����Ѷ�, int ��������);
	void move_to_copy_door(int copy_id, int type = 0);
	void teleport_to(RolePos pos);
	void return_role(int type = 0);
};

