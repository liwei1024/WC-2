#pragma once
static int get_current_role_fatigue_value()
{
	return decrypt(__���ƣ��) - decrypt(__��ǰƣ��);
}

static RolePos get_role_pos()
{
	RolePos role_pos;
	Pos current_room_pos = get_current_room_pos();
	role_pos.x = (int)read<float>(__��ɫ����);
	role_pos.y = (int)read<float>(__��ɫ���� + 4);
	role_pos.z = (int)read<float>(__��ɫ���� + 8);
	role_pos.max_city_id = current_room_pos.x;
	role_pos.min_city_id = current_room_pos.y;
	return role_pos;
}

static int get_role_level() {
	return read<int>(__��ɫ�ȼ�);
}

static std::wstring get_role_job_name()
{
	return read_wstring(read<DWORD>(__ְҵ����) + 0x0, 100);
}

static void �����ƶ���ɫ(RolePos end_role_pos)
{
	bulletin(L"Start");
	// ��Ϸ״̬
	int game_status = get_game_status();
	// ʱ�����
	DWORD t1 = getTime();
	DWORD t2 = getTime();
	// �����б�
	std::vector<std::wstring> �����б�;
	// λ�ñ���
	RolePos cur_pos, sticking_pos = get_role_pos();
	// ����״̬
	bool top, bottom, left, right;
	while (true)
	{
		cur_pos = get_role_pos();
		t2 = getTime();
		if (
			cur_pos.max_city_id != end_role_pos.max_city_id ||
			cur_pos.min_city_id != end_role_pos.min_city_id ||
			(abs(cur_pos.x - end_role_pos.x) < 50 && abs(cur_pos.y - end_role_pos.y) < 50)
		)
		{
			KeyUp();//�ſ������Ѱ��°���
			break;
		}

		if (abs(cur_pos.x - end_role_pos.x) > 50 && end_role_pos.x > cur_pos.x && right == false)
		{
			keyDown(VK_NUMPAD3);
			bulletin(L"�� Down");
			right = true;
		}
		if(abs(cur_pos.x - end_role_pos.x) > 50 && end_role_pos.x < cur_pos.x && left == false) {
			keyDown(VK_NUMPAD1);
			bulletin(L"�� Down");
			left = true;
		}
		if (abs(cur_pos.y - end_role_pos.y) > 50 &&  end_role_pos.y > cur_pos.y && top == false)
		{
			keyDown(VK_NUMPAD5);
			bulletin(L"�� Down");
			top = true;
		}
		if(abs(cur_pos.y - end_role_pos.y) > 50 && end_role_pos.y < cur_pos.y && bottom == false) {
			keyDown(VK_NUMPAD2);
			bulletin(L"�� Down");
			bottom = true;
		}

		if (abs(end_role_pos.x - cur_pos.x) < 50)
		{
			if (right == true) {
				keyUp(VK_NUMPAD3);
				bulletin(L"�� Up");
				right = false;
			}
				
				
			if (left == true)
			{
				keyUp(VK_NUMPAD1);
				bulletin(L"�� Up");
				left = false;
			}
		}
		if (abs(end_role_pos.y - cur_pos.y) < 50)
		{
			if (top == true)
			{
				keyUp(VK_NUMPAD5);
				bulletin(L"�� Up");
				top = false;
			}
			if (bottom == true) {
				keyUp(VK_NUMPAD2);
				bulletin(L"�� Up");
				bottom = false;
			}
		}

		if (t2 - t1 >= 3)
		{
			t1 = getTime();
			if (
				sticking_pos.max_city_id == cur_pos.max_city_id &&
				sticking_pos.min_city_id == cur_pos.min_city_id &&
				abs(sticking_pos.x - cur_pos.x) < 10 &&
				abs(sticking_pos.y - cur_pos.y) < 10
			)
			{
				if (top)
				{
					keyUp(VK_NUMPAD5);
					top = false;
					doKeyPress(VK_NUMPAD2,1000);
				}
				if (bottom)
				{
					keyUp(VK_NUMPAD2);
					bottom = false;
					doKeyPress(VK_NUMPAD5, 1000);
				}
				if (left)
				{
					keyUp(VK_NUMPAD1);
					left = false;
					doKeyPress(VK_NUMPAD3, 1000);
				}
				if (right)
				{
					keyUp(VK_NUMPAD3);
					right = false;
					doKeyPress(VK_NUMPAD1, 1000);
				}
			}
			sticking_pos = get_role_pos();
		}
	}
}

static int get_role_status()
{
	return read<int>(read<int>(__��ɫ״̬) + __��ɫ״̬ƫ��);
}

static void �����ͷ���ʱ()
{
	while (true)
	{
		if (get_role_status() == 0)
		{
			break;
		}
		Sleep(100);
	}
	Sleep(100);
}

static void �����ͷż���(int KeyCode,int s = 0)
{
	if (is_open_door() == false)
	{
		doKeyPress(KeyCode,s);
		�����ͷ���ʱ();
	}
}