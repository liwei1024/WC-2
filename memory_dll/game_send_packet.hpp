#pragma once

static inline void Send_缓冲CALL(int cdov)
{
	__asm {
		push cdov
		mov ecx, __发包基址
		mov ecx, dword ptr ss : [ecx]
		mov eax, __缓冲CALL
		call eax
	}
}
static inline void Send_密包CALL(int wtud, int taya)
{
	int cdov = 0;
	if (taya == 1)cdov = __密包CALL;
	if (taya == 2)cdov = __密包CALL + 0x30;
	if (taya == 3)cdov = __密包CALL + 0x60;
	if (taya == 4)cdov = __密包CALL + 0x90;
	__asm {
		push wtud
		mov ecx, __发包基址
		mov ecx, dword ptr ss : [ecx]
		mov eax, cdov
		call eax
	}
}
static inline void Send_发包CALL(void)
{
	__asm {
		mov eax, __发包CALL
		call eax
	}
}

static inline void Send_返回角色(DWORD parameter)
{
	Send_缓冲CALL(0x7);
	Send_发包CALL();
}

static inline void Send_选择角色(DWORD parameter)
{
	int role_index = read<int>(parameter);

	Send_缓冲CALL(4);
	Send_密包CALL(role_index, 3);
	Send_发包CALL();
}

static inline void Send_城镇瞬移(DWORD parameter)
{
	int max_map_id = read<int>(parameter + 0);
	int min_map_id = read<int>(parameter + 4);
	int x = read<int>(parameter + 8);
	int y = read<int>(parameter + 12);
	int goods_index = read<int>(parameter + 16);// get_goods_index_by_goods_name(L"瞬间移动药剂");
	if (goods_index > 0)
	{
		Send_缓冲CALL(237);
		Send_密包CALL(goods_index, 2);
		Send_密包CALL(2600014, 3);
		Send_密包CALL(0, 1);
		Send_密包CALL(max_map_id, 1);
		Send_密包CALL(min_map_id, 1);
		Send_密包CALL(x, 2);
		Send_密包CALL(y, 2);
		Send_发包CALL();
	}
	else {
		Send_缓冲CALL(36);
		Send_密包CALL(max_map_id, 1);
		Send_密包CALL(min_map_id, 1);
		Send_密包CALL(x, 2);
		Send_密包CALL(y, 2);
		Send_密包CALL(5, 1);
		Send_密包CALL(38, 2);
		Send_密包CALL(1, 2);
		Send_密包CALL(0, 3);
		Send_密包CALL(0, 1);
		Send_发包CALL();
	}
}

static inline void Send_进入选图(DWORD parameter)
{
	Send_缓冲CALL(15);
	Send_密包CALL(0, 3);
	Send_发包CALL();
}

static inline void Send_选择副本(DWORD parameter)
{
	int 副本编号 = read<int>(parameter);
	int 副本难度 = read<int>(parameter + 4);
	int 副本模式 = read<int>(parameter + 8) == -1 ? 0 : read<int>(parameter + 8);
	Send_缓冲CALL(16);
	Send_密包CALL(104, 3);
	if (副本编号 > 7100 && 副本编号 < 7200)
	{
		Send_密包CALL(2, 1);
		Send_密包CALL(副本难度, 2);
	}
	else
	{
		Send_密包CALL(副本难度, 1);
		Send_密包CALL(0, 2);
	}
	if (副本模式 == 0) {	 //普通
		Send_密包CALL(0, 1);
		Send_密包CALL(0, 1);
	}
	else if (副本模式 == 0) { // 深渊
		Send_密包CALL(1, 1);
		Send_密包CALL(0, 1);
	}
	else {
		Send_密包CALL(0, 1);//练习
		Send_密包CALL(1, 1);
	}
	Send_密包CALL(65535, 2);
	Send_密包CALL(0, 3);
	Send_密包CALL(0, 1);
	Send_密包CALL(0, 3);
	Send_发包CALL();
}

static inline void Send_组包拾取(DWORD parameter)
{
	DWORD loot_address = read<int>(parameter);
	DWORD x = read<int>(parameter + 4);
	DWORD y = read<int>(parameter + 8);

	Send_缓冲CALL(43);
	Send_密包CALL(loot_address, 3);
	Send_密包CALL(0, 1);
	Send_密包CALL(1, 1);
	Send_密包CALL(x, 2);
	Send_密包CALL(y, 2);
	Send_密包CALL(0, 2);
	Send_密包CALL(x + ((x % 4) + 1), 2);
	Send_密包CALL(y + ((y % 4) + 1), 2);
	Send_密包CALL(0, 2);
	Send_密包CALL(0, 2);
	Send_发包CALL();
}

static inline void Send_组包翻牌(DWORD parameter)
{
	Send_缓冲CALL(69);
	Send_发包CALL();
	Send_缓冲CALL(70);
	Send_发包CALL();
	Send_缓冲CALL(71);
	Send_密包CALL(createRandom(0, 3), 1);
	Send_密包CALL(0, 1);
	Send_发包CALL();
}

static inline void Send_组包卖物(DWORD parameter)
{
	DWORD 物品下标 = read<int>(parameter);

	Send_缓冲CALL(593);
	Send_密包CALL(2, 3);
	Send_密包CALL(0, 3);
	Send_发包CALL();

	Send_缓冲CALL(22);
	Send_密包CALL(0, 1);
	Send_密包CALL(物品下标, 2);
	Send_密包CALL(1, 3);
	Send_密包CALL(1000, 3);
	Send_密包CALL(物品下标 * 2 + 3, 3);
	Send_发包CALL();
}


static inline void Send_组包回城(DWORD parameter)
{
	Send_缓冲CALL(123);
	Send_密包CALL(createRandom(1, 1500), 3);
	Send_密包CALL(createRandom(1, 1500), 3);
	Send_密包CALL(createRandom(1, 1500), 3);
	Send_密包CALL(createRandom(1, 1500), 3);
	Send_密包CALL(createRandom(1, 1500), 3);
	Send_密包CALL(createRandom(1, 1500), 3);
	Send_发包CALL();
	Send_缓冲CALL(42);
	Send_发包CALL();
}