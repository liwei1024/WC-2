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