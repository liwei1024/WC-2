#pragma once
class game_status_1
{
public:
	game_status_1();
	~game_status_1();

	void manage();

	
private:
	void enter_the_dungeon(int dungeon_id);
	void teleport_to(int city);
};

