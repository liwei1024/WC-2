#pragma once
static int get_current_role_fatigue_value()
{
	return decrypt(__最大疲劳) - decrypt(__当前疲劳);
}

static RolePos get_role_pos()
{
	RolePos role_pos;
	Pos current_room_pos = get_current_room_pos();
	role_pos.x = (int)read<float>(__角色坐标);
	role_pos.y = (int)read<float>(__角色坐标 + 4);
	role_pos.z = (int)read<float>(__角色坐标 + 8);
	role_pos.max_city_id = current_room_pos.x;
	role_pos.min_city_id = current_room_pos.y;
	return role_pos;
}

static int get_role_level() {
	return read<int>(__角色等级);
}

static std::wstring get_role_job_name()
{
	return read_wstring(read<DWORD>(__职业名称) + 0x0, 100);
}

static void 按键移动角色(RolePos end_role_pos)
{
	bulletin(L"Start");
	// 游戏状态
	int game_status = get_game_status();
	// 时间变量
	DWORD t1 = getTime();
	DWORD t2 = getTime();
	// 卡点列表
	std::vector<std::wstring> 卡点列表;
	// 位置变量
	RolePos cur_pos, sticking_pos = get_role_pos();
	// 按键状态
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
			KeyUp();//放开所有已按下按键
			break;
		}

		if (abs(cur_pos.x - end_role_pos.x) > 50 && end_role_pos.x > cur_pos.x && right == false)
		{
			keyDown(VK_NUMPAD3);
			bulletin(L"右 Down");
			right = true;
		}
		if(abs(cur_pos.x - end_role_pos.x) > 50 && end_role_pos.x < cur_pos.x && left == false) {
			keyDown(VK_NUMPAD1);
			bulletin(L"左 Down");
			left = true;
		}
		if (abs(cur_pos.y - end_role_pos.y) > 50 &&  end_role_pos.y > cur_pos.y && top == false)
		{
			keyDown(VK_NUMPAD5);
			bulletin(L"上 Down");
			top = true;
		}
		if(abs(cur_pos.y - end_role_pos.y) > 50 && end_role_pos.y < cur_pos.y && bottom == false) {
			keyDown(VK_NUMPAD2);
			bulletin(L"下 Down");
			bottom = true;
		}

		if (abs(end_role_pos.x - cur_pos.x) < 50)
		{
			if (right == true) {
				keyUp(VK_NUMPAD3);
				bulletin(L"右 Up");
				right = false;
			}
				
				
			if (left == true)
			{
				keyUp(VK_NUMPAD1);
				bulletin(L"左 Up");
				left = false;
			}
		}
		if (abs(end_role_pos.y - cur_pos.y) < 50)
		{
			if (top == true)
			{
				keyUp(VK_NUMPAD5);
				bulletin(L"上 Up");
				top = false;
			}
			if (bottom == true) {
				keyUp(VK_NUMPAD2);
				bulletin(L"下 Up");
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
	return read<int>(read<int>(__角色状态) + __角色状态偏移);
}

static void 技能释放延时()
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

static void 按键释放技能(int KeyCode,int s = 0)
{
	if (is_open_door() == false)
	{
		doKeyPress(KeyCode,s);
		技能释放延时();
	}
}