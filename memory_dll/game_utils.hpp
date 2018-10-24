#pragma once

static int decrypt(int address)
{
	int eax, esi, edx, i;
	eax = read<int>(address);
	esi = read<int>(__���ܻ�ַ);
	edx = eax >> 16;
	edx = read<int>(esi + edx * 4 + 36);
	eax = eax & 65535;
	eax = read<int>(edx + eax * 4 + 8468);
	edx = eax & 65535;
	esi = edx << 16;
	esi = esi | edx;
	i = read<int>(address + 4);
	esi = esi ^ i;
	return esi;
}

//����
static void encrypt(INT32 Address, INT32 Value)
{
	INT32 EncryptId = 0;
	INT32 OffsetParam = 0;
	INT32 OffsetAddress = 0;
	INT32 Data = 0;
	INT32 AddressMask = 0;
	INT16 ax = 0;
	INT16 si = 0;
	EncryptId = read<int>(Address);
	OffsetParam = read<int>(read<int>(__���ܻ�ַ) + (EncryptId >> 16) * 4 + 36);
	OffsetAddress = OffsetParam + (EncryptId & 0xFFFF) * 4 + 8468;
	OffsetParam = read<int>(OffsetAddress);
	Data = OffsetParam & 0xFFFF;
	Data += Data << 16;
	ax = OffsetParam & 0xFFFF;
	AddressMask = Address & 0xF;
	if (AddressMask == 0x0)
	{
		si = Value >> 16;
		si -= ax;
		si += Value;
	}
	else if (AddressMask == 0x4)
	{
		si = (Value & 0xFFFF) - (Value >> 16);
	}
	else if (AddressMask == 0x8)
	{
		si = Value >> 16;
		si *= Value;
	}
	else if (AddressMask == 0xC)
	{
		si = Value >> 16;
		si += Value;
		si += ax;
	}
	else
	{
		return;
	}
	ax ^= si;
	write<BYTE>(OffsetAddress + 2, (BYTE)ax);
	write<BYTE>(OffsetAddress + 3, (BYTE)(ax >> 8));
	write<int>(Address + 4, Data ^ Value);
}

static int get_game_status()
{
	//output_bebug_wstring(L"__��Ϸ״̬ %d", read<int>(__��Ϸ״̬));
	return read<int>(__��Ϸ״̬);
}

static void bulletin(LPCWSTR Format, ...)
{
	WCHAR Buffer[0x1000];

	va_list args;
	va_start(args, Format);
	vswprintf_s(Buffer,Format, args);
	va_end(args);

	main_thread_exec_call(Call_����Call, { (int)&Buffer });
}

static Pos get_current_room_pos()
{
	Pos CurrentRoomPos;
	if (get_game_status() == 1)
	{
		CurrentRoomPos.x = read_offset<int>(__����ȡֵ, { __������ƫ�� });
		CurrentRoomPos.y = read_offset<int>(__����ȡֵ, { __С����ƫ�� });
	}
	else {
		DWORD OffsetAddress = read_offset<int>(__������, { __ʱ���ַ ,__����ƫ�� });
		CurrentRoomPos.x = read<int>(OffsetAddress + __��ǰ����X);
		CurrentRoomPos.y = read<int>(OffsetAddress + __��ǰ����Y);
	}

	return CurrentRoomPos;
}

static Pos get_boss_room_pos()
{
	Pos BossRoomPos;
	DWORD OffsetAddress = read_offset<int>(__������, { __ʱ���ַ ,__����ƫ�� });
	BossRoomPos.x = decrypt(OffsetAddress + __BOSS����X);
	BossRoomPos.y = decrypt(OffsetAddress + __BOSS����Y);
	return BossRoomPos;
}

static bool is_boss_room()
{
	Pos current_room_pos;
	Pos boss_room_pos;

	current_room_pos = get_current_room_pos();
	boss_room_pos = get_boss_room_pos();

	if (current_room_pos.x == boss_room_pos.x && current_room_pos.y == boss_room_pos.y)
	{
		//bulletin(L"��Boss ����");
		return true;
	}
	//bulletin(L"��Boss ����");
	return false;
}

static bool is_open_door()
{
	if (decrypt(read_offset<int>(__�����ַ, { __��ͼƫ�� }) + __����ƫ��) == 0)
	{
		//bulletin(L"�ѿ���");
		return true;
	}
	else {
		//bulletin(L"δ����");
		return false;
	}
}

