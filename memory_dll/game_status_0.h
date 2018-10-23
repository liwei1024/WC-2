#pragma once
class game_status_0
{
public:
	game_status_0();
	~game_status_0();
	void manage();

	

private:
	int role_index = 0;
	int role_count = 0;
	int role_max_count = 0;
	int get_role_index();
	int get_role_count();
	int get_role_max_count();
	void select_role();
	void create_role();
};

