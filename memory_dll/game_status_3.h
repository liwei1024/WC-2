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
	void ���ʰȡ();
	std::vector<MAP_OBJECT_STRUCT> ��ȡ��Ʒ��Ϣ();
	bool ��������();
	void ȫ������();
	int get_map_object_count(DWORD map_start_address);
	void move_to_next_room(int direction);
	void sort_by_distance(std::vector<MAP_OBJECT_STRUCT>& Objects);
	void attack_monster();
	void follow(std::wstring name = L"");
	bool get_the_custom_shop();

	
	bool �Ƿ��й���();
	void �ƶ�����ɫָ��λ��(int x, int y,int z = 0);
	void ����_����Ů��();
	void ����_��Ѫ߱��();
	void ����_���();
	void ����_����();
	void ����_����();
};

