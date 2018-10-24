#pragma once

static int decrypt(int address)
{
	int eax, esi, edx, i;
	eax = read<int>(address);
	esi = read<int>(__解密基址);
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

//加密
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
	OffsetParam = read<int>(read<int>(__解密基址) + (EncryptId >> 16) * 4 + 36);
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
	//output_bebug_wstring(L"__游戏状态 %d", read<int>(__游戏状态));
	return read<int>(__游戏状态);
}

static void bulletin(LPCWSTR Format, ...)
{
	WCHAR Buffer[0x1000];

	va_list args;
	va_start(args, Format);
	vswprintf_s(Buffer,Format, args);
	va_end(args);

	main_thread_exec_call(Call_公告Call, { (int)&Buffer });
}

static Pos get_current_room_pos()
{
	Pos CurrentRoomPos;
	if (get_game_status() == 1)
	{
		CurrentRoomPos.x = read_offset<int>(__遍历取值, { __大区域偏移 });
		CurrentRoomPos.y = read_offset<int>(__遍历取值, { __小区域偏移 });
	}
	else {
		DWORD OffsetAddress = read_offset<int>(__房间编号, { __时间基址 ,__门型偏移 });
		CurrentRoomPos.x = read<int>(OffsetAddress + __当前房间X);
		CurrentRoomPos.y = read<int>(OffsetAddress + __当前房间Y);
	}

	return CurrentRoomPos;
}

static Pos get_boss_room_pos()
{
	Pos BossRoomPos;
	DWORD OffsetAddress = read_offset<int>(__房间编号, { __时间基址 ,__门型偏移 });
	BossRoomPos.x = decrypt(OffsetAddress + __BOSS房间X);
	BossRoomPos.y = decrypt(OffsetAddress + __BOSS房间Y);
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
		//bulletin(L"在Boss 房间");
		return true;
	}
	//bulletin(L"不Boss 房间");
	return false;
}

static bool is_open_door()
{
	if (decrypt(read_offset<int>(__人物基址, { __地图偏移 }) + __开门偏移) == 0)
	{
		//bulletin(L"已开门");
		return true;
	}
	else {
		//bulletin(L"未开门");
		return false;
	}
}

