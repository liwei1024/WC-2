#pragma once
static int get_current_role_fatigue_value()
{
	return decrypt(__���ƣ��) - decrypt(__��ǰƣ��);
}

static RolePos get_role_pos()
{
	RolePos role_pos;
	role_pos.x = (int)read<float>(__��ɫ����);
	role_pos.y = (int)read<float>(__��ɫ���� + 4);
	role_pos.z = (int)read<float>(__��ɫ���� + 8);
	switch (get_game_status())
	{
	case 1:
		role_pos.max_city_id = read_offset<int>(__����ȡֵ, { __������ƫ�� });
		role_pos.min_city_id = read_offset<int>(__����ȡֵ, { __С����ƫ�� });
		break;
	case 3:
		break;
	default:
		break;
	}
	return role_pos;
}