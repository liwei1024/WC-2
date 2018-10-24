#pragma once
static inline void Call_技能Call(DWORD_PTR parameter)
{
	int a[26] = {};
	a[0] = read<int>(parameter);//触发指针;
	a[2] = read<int>(parameter + 4); //代码
	a[3] = read<int>(parameter + 8); //伤害
	a[6] = read<int>(parameter + 12);//x
	a[7] = read<int>(parameter + 16);//y
	a[8] = read<int>(parameter + 20);//z
	a[23] = 0;
	a[24] = 65535;
	a[25] = 65535;
	int 空白地址 = (int)&a;
	__asm
	{
		pushad
		pushfd
		mov ecx, 空白地址
		mov eax, __技能CALL
		call eax
		popfd
		popad
	}
}

static inline void Call_释放Call(DWORD_PTR parameter)
{
	int a[6] = {};
	a[0] = read<int>(parameter);//触发指针;
	a[1] = read<int>(parameter + 4); //代码
	a[2] = read<int>(parameter + 8); //伤害
	a[3] = read<int>(parameter + 12);//x
	a[4] = read<int>(parameter + 16);//y
	a[5] = read<int>(parameter + 20);//z
	__asm
	{
		push a[5]
		push a[4]
		push a[3]
		push a[2]
		push a[1]
		push a[0]
		mov edi, __释放CALL
		mov eax, edi
		call eax
		add esp, 24
	}
}

static inline void Call_公告Call(DWORD_PTR parameter)
{
	DWORD Buffer = read<DWORD>(parameter);
	if (Buffer > 0) {
		__asm
		{
			mov ecx, __商店基址
			mov ecx, [ecx]
			mov ecx, [ecx + 0x50]
			push 0
			push 0
			push 0
			push 0
			push 0
			push 37
			push 0xff0078ff
			push Buffer
			mov eax, __喇叭公告
			call eax
		}
	}
}

static inline void Call_接受Call(DWORD_PTR parameter)
{
	__try
	{
	}
	__except (1) {
		output_bebug_wstring(L"Call_接受Call 异常 参数地址 %x", parameter);
	}
}

static inline void Call_提交Call(DWORD_PTR parameter)
{
	__try
	{
	}
	__except (1) {
		output_bebug_wstring(L"Call_提交Call 异常 参数地址 %x", parameter);
	}
}

static inline void Call_完成Call(DWORD_PTR parameter)
{
	__try
	{
	}
	__except (1) {
		output_bebug_wstring(L"Call_完成Call 异常 参数地址 %x", parameter);
	}
}

static inline void Call_区域Call(DWORD_PTR parameter)
{
	int 区域指针 = read<int>(__区域参数);
	int Copy_ID = read<int>(parameter);
	int 区域call = __区域CALL;
	__asm {
		mov edx, Copy_ID
		mov ecx, 区域指针
		mov eax, 0xf78
		push edx
		push eax
		call 区域call
	}
	DWORD 区域信息[4] = { 0 };
	区域信息[0] = read<int>(区域指针 + __区域偏移);
	区域信息[1] = read<int>(区域指针 + __区域偏移 + 4);
	区域信息[2] = read<int>(区域指针 + __区域偏移 + 8) + createRandom(-2, 2);
	区域信息[3] = read<int>(区域指针 + __区域偏移 + 12) + createRandom(-2, 2);
	Send_城镇瞬移((DWORD)&区域信息);
	
}

static inline void Call_坐标Call(DWORD_PTR parameter)
{
	__try
	{
		DWORD object_pointer = read<int>(parameter);
		DWORD x = read<int>(parameter + 4);
		DWORD y = read<int>(parameter + 8);
		DWORD z = read<int>(parameter + 12);
		__asm
		{
			mov esi, object_pointer
			mov edi, [esi]
			push z
			push y
			push x
			mov eax, [edi + 0xb4]
			mov ecx, esi
			call eax
		}
	}
	__except (1) {
		output_bebug_wstring(L"Call_区域Call 异常 参数地址 %x", parameter);
	}
	
}

static inline void Call_过图Call(DWORD_PTR parameter)
{
	int 方向 = read<int>(parameter);
	__asm {
		pushad
		mov eax, __房间编号
		mov ecx, [eax - 0x8]//
		mov eax, __时间基址
		mov ecx, [ecx + eax]//
		mov ecx, [ecx + 0x8c]
		push - 1
		push - 1
		push 0
		push 0
		push 0
		push 0
		push 0
		push 方向//左0右1上2下3
		mov eax, __过图CALL//
		call eax
		popad
	}
	
}

static inline void Call_召唤Call(DWORD_PTR parameter)
{
	__try {

	}
	__except (1) {
		output_bebug_wstring(L"Call_召唤Call 异常 参数地址 %x", parameter);
	}
}

static inline void Call_变身Call(DWORD_PTR parameter)
{
	__try {

	}
	__except (1) {
		output_bebug_wstring(L"Call_变身Call 异常 参数地址 %x", parameter);
	}
}