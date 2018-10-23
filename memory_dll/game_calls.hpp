#pragma once
inline void Call_技能Call(DWORD parameter)
{

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

}

inline void Call_坐标Call(DWORD parameter)
{

}

inline void Call_过图Call(DWORD parameter)
{

}

inline void Call_召唤Call(DWORD parameter)
{

}

inline void Call_变身Call(DWORD parameter)
{

}