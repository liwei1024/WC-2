#pragma once
inline void Call_技能Call(DWORD parameter)
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
	/*bulletin(L"空白地址 %x", 空白地址);
	bulletin(L"a %x", (DWORD)a);*/
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

inline void Call_公告Call(DWORD parameter)
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



inline void Call_接受Call(DWORD parameter)
{

}

inline void Call_提交Call(DWORD parameter)
{

}

inline void Call_完成Call(DWORD parameter)
{

}

inline void Call_区域Call(DWORD parameter)
{
	int 区域指针 = read<int>(__区域参数);
	int Copy_ID = read<int>(parameter);
	int 区域call = __区域CALL;
	__asm {
		pushad
		mov edx, Copy_ID
		mov ecx, 区域指针
		mov eax, 0xf78
		push edx
		push eax
		call 区域call
		popad
	}
	DWORD 区域信息[4] = { 0 };
	区域信息[0] = read<int>(区域指针 + __区域偏移);
	区域信息[1] = read<int>(区域指针 + __区域偏移 + 4);
	区域信息[2] = read<int>(区域指针 + __区域偏移 + 8) + createRandom(-2, 2);
	区域信息[3] = read<int>(区域指针 + __区域偏移 + 12) + createRandom(-2, 2);
	Send_城镇瞬移((DWORD)&区域信息);
}


inline void Call_坐标Call(DWORD parameter)
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
		mov eax, [edi + 0xA8]
		mov ecx, esi
		call eax
	}
}

inline void Call_过图Call(DWORD parameter)
{
	int 方向 = read<int>(parameter);
	__asm {
		pushad
		mov ecx, [__房间编号]//
		mov ecx, [ecx + __时间基址]//
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

inline void Call_召唤Call(DWORD parameter)
{

}

inline void Call_变身Call(DWORD parameter)
{

}