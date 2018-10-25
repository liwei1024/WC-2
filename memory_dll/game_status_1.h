#pragma once
class game_status_1
{
public:
	game_status_1();
	~game_status_1();

	void manage();

	
private:
	void enter_the_dungeon(int 副本ID, int 副本难度, int 副本类型);
	void teleport_to(RolePos pos, int type = 0);//type 0-组包 1-call
	void move_to_copy_door(int copy_id, int type = 0); //copy_id副本id //type 0-组包瞬移 1-call瞬移 2-脚本移动
	void return_role(int type = 0);// 0-组包 1-call 2-脚本
};

