#pragma once

static inline void Send_����CALL(int cdov)
{
	__asm {
		push cdov
		mov ecx, __������ַ
		mov ecx, dword ptr ss : [ecx]
		mov eax, __����CALL
		call eax
	}
}
static inline void Send_�ܰ�CALL(int wtud, int taya)
{
	int cdov = 0;
	if (taya == 1)cdov = __�ܰ�CALL;
	if (taya == 2)cdov = __�ܰ�CALL + 0x30;
	if (taya == 3)cdov = __�ܰ�CALL + 0x60;
	if (taya == 4)cdov = __�ܰ�CALL + 0x90;
	__asm {
		push wtud
		mov ecx, __������ַ
		mov ecx, dword ptr ss : [ecx]
		mov eax, cdov
		call eax
	}
}
static inline void Send_����CALL(void)
{
	__asm {
		mov eax, __����CALL
		call eax
	}
}

static inline void Send_���ؽ�ɫ(DWORD parameter)
{
	Send_����CALL(0x7);
	Send_����CALL();
}

static inline void Send_ѡ���ɫ(DWORD parameter)
{
	int role_index = read<int>(parameter);

	Send_����CALL(4);
	Send_�ܰ�CALL(role_index, 3);
	Send_����CALL();
}

static inline void Send_����˲��(DWORD parameter)
{
	int max_map_id = read<int>(parameter + 0);
	int min_map_id = read<int>(parameter + 4);
	int x = read<int>(parameter + 8);
	int y = read<int>(parameter + 12);
	int goods_index = read<int>(parameter + 16);// get_goods_index_by_goods_name(L"˲���ƶ�ҩ��");
	if (goods_index > 0)
	{
		Send_����CALL(237);
		Send_�ܰ�CALL(goods_index, 2);
		Send_�ܰ�CALL(2600014, 3);
		Send_�ܰ�CALL(0, 1);
		Send_�ܰ�CALL(max_map_id, 1);
		Send_�ܰ�CALL(min_map_id, 1);
		Send_�ܰ�CALL(x, 2);
		Send_�ܰ�CALL(y, 2);
		Send_����CALL();
	}
	else {
		Send_����CALL(36);
		Send_�ܰ�CALL(max_map_id, 1);
		Send_�ܰ�CALL(min_map_id, 1);
		Send_�ܰ�CALL(x, 2);
		Send_�ܰ�CALL(y, 2);
		Send_�ܰ�CALL(5, 1);
		Send_�ܰ�CALL(38, 2);
		Send_�ܰ�CALL(1, 2);
		Send_�ܰ�CALL(0, 3);
		Send_�ܰ�CALL(0, 1);
		Send_����CALL();
	}
}

static inline void Send_����ѡͼ(DWORD parameter)
{
	Send_����CALL(15);
	Send_�ܰ�CALL(0, 3);
	Send_����CALL();
}

static inline void Send_ѡ�񸱱�(DWORD parameter)
{
	int ������� = read<int>(parameter);
	int �����Ѷ� = read<int>(parameter + 4);
	int ����ģʽ = read<int>(parameter + 8) == -1 ? 0 : read<int>(parameter + 8);
	Send_����CALL(16);
	Send_�ܰ�CALL(104, 3);
	if (������� > 7100 && ������� < 7200)
	{
		Send_�ܰ�CALL(2, 1);
		Send_�ܰ�CALL(�����Ѷ�, 2);
	}
	else
	{
		Send_�ܰ�CALL(�����Ѷ�, 1);
		Send_�ܰ�CALL(0, 2);
	}
	if (����ģʽ == 0) {	 //��ͨ
		Send_�ܰ�CALL(0, 1);
		Send_�ܰ�CALL(0, 1);
	}
	else if (����ģʽ == 0) { // ��Ԩ
		Send_�ܰ�CALL(1, 1);
		Send_�ܰ�CALL(0, 1);
	}
	else {
		Send_�ܰ�CALL(0, 1);//��ϰ
		Send_�ܰ�CALL(1, 1);
	}
	Send_�ܰ�CALL(65535, 2);
	Send_�ܰ�CALL(0, 3);
	Send_�ܰ�CALL(0, 1);
	Send_�ܰ�CALL(0, 3);
	Send_����CALL();
}

static inline void Send_���ʰȡ(DWORD parameter)
{
	DWORD loot_address = read<int>(parameter);
	DWORD x = read<int>(parameter + 4);
	DWORD y = read<int>(parameter + 8);

	Send_����CALL(43);
	Send_�ܰ�CALL(loot_address, 3);
	Send_�ܰ�CALL(0, 1);
	Send_�ܰ�CALL(1, 1);
	Send_�ܰ�CALL(x, 2);
	Send_�ܰ�CALL(y, 2);
	Send_�ܰ�CALL(0, 2);
	Send_�ܰ�CALL(x + ((x % 4) + 1), 2);
	Send_�ܰ�CALL(y + ((y % 4) + 1), 2);
	Send_�ܰ�CALL(0, 2);
	Send_�ܰ�CALL(0, 2);
	Send_����CALL();
}

static inline void Send_�������(DWORD parameter)
{
	Send_����CALL(69);
	Send_����CALL();
	Send_����CALL(70);
	Send_����CALL();
	Send_����CALL(71);
	Send_�ܰ�CALL(createRandom(0, 3), 1);
	Send_�ܰ�CALL(0, 1);
	Send_����CALL();
}

static inline void Send_�������(DWORD parameter)
{
	DWORD ��Ʒ�±� = read<int>(parameter);

	Send_����CALL(593);
	Send_�ܰ�CALL(2, 3);
	Send_�ܰ�CALL(0, 3);
	Send_����CALL();

	Send_����CALL(22);
	Send_�ܰ�CALL(0, 1);
	Send_�ܰ�CALL(��Ʒ�±�, 2);
	Send_�ܰ�CALL(1, 3);
	Send_�ܰ�CALL(1000, 3);
	Send_�ܰ�CALL(��Ʒ�±� * 2 + 3, 3);
	Send_����CALL();
}


static inline void Send_����س�(DWORD parameter)
{
	Send_����CALL(123);
	Send_�ܰ�CALL(createRandom(1, 1500), 3);
	Send_�ܰ�CALL(createRandom(1, 1500), 3);
	Send_�ܰ�CALL(createRandom(1, 1500), 3);
	Send_�ܰ�CALL(createRandom(1, 1500), 3);
	Send_�ܰ�CALL(createRandom(1, 1500), 3);
	Send_�ܰ�CALL(createRandom(1, 1500), 3);
	Send_����CALL();
	Send_����CALL(42);
	Send_����CALL();
}