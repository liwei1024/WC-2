#pragma once
class game_status_1
{
public:
	game_status_1();
	~game_status_1();

	void manage();

	
private:
	void enter_the_dungeon(int ����ID, int �����Ѷ�, int ��������);
	void teleport_to(RolePos pos, int type = 0);//type 0-��� 1-call
	void move_to_copy_door(int copy_id, int type = 0); //copy_id����id //type 0-���˲�� 1-call˲�� 2-�ű��ƶ�
	void return_role(int type = 0);// 0-��� 1-call 2-�ű�
};

