#pragma once
static int get_current_role_fatigue_value()
{
	return decrypt(__最大疲劳) - decrypt(__当前疲劳);
}

static RolePos get_role_pos()
{
	RolePos role_pos;
	role_pos.x = (int)read<float>(__角色坐标);
	role_pos.y = (int)read<float>(__角色坐标 + 4);
	role_pos.z = (int)read<float>(__角色坐标 + 8);
	switch (get_game_status())
	{
	case 1:
		role_pos.max_city_id = read_offset<int>(__遍历取值, { __大区域偏移 });
		role_pos.min_city_id = read_offset<int>(__遍历取值, { __小区域偏移 });
		break;
	case 3:
		break;
	default:
		break;
	}
	return role_pos;
}