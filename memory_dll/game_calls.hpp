#pragma once
inline void Call_����Call(DWORD parameter)
{
	int a[26] = {};
	a[0] = read<int>(parameter);//����ָ��;
	a[2] = read<int>(parameter + 4); //����
	a[3] = read<int>(parameter + 8); //�˺�
	a[6] = read<int>(parameter + 12);//x
	a[7] = read<int>(parameter + 16);//y
	a[8] = read<int>(parameter + 20);//z
	a[23] = 0;
	a[24] = 65535;
	a[25] = 65535;
	int �հ׵�ַ = (int)&a;
	/*bulletin(L"�հ׵�ַ %x", �հ׵�ַ);
	bulletin(L"a %x", (DWORD)a);*/
	__asm
	{
		pushad
		pushfd
		mov ecx, �հ׵�ַ
		mov eax, __����CALL
		call eax
		popfd
		popad
	}
}

inline void Call_����Call(DWORD parameter)
{
	DWORD Buffer = read<DWORD>(parameter);
	if (Buffer > 0) {
		__asm
		{
			mov ecx, __�̵��ַ
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
			mov eax, __���ȹ���
			call eax
		}
	}
}



inline void Call_����Call(DWORD parameter)
{

}

inline void Call_�ύCall(DWORD parameter)
{

}

inline void Call_���Call(DWORD parameter)
{

}

inline void Call_����Call(DWORD parameter)
{
	int ����ָ�� = read<int>(__�������);
	int Copy_ID = read<int>(parameter);
	int ����call = __����CALL;
	__asm {
		pushad
		mov edx, Copy_ID
		mov ecx, ����ָ��
		mov eax, 0xf78
		push edx
		push eax
		call ����call
		popad
	}
	DWORD ������Ϣ[4] = { 0 };
	������Ϣ[0] = read<int>(����ָ�� + __����ƫ��);
	������Ϣ[1] = read<int>(����ָ�� + __����ƫ�� + 4);
	������Ϣ[2] = read<int>(����ָ�� + __����ƫ�� + 8) + createRandom(-2, 2);
	������Ϣ[3] = read<int>(����ָ�� + __����ƫ�� + 12) + createRandom(-2, 2);
	Send_����˲��((DWORD)&������Ϣ);
}


inline void Call_����Call(DWORD parameter)
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

inline void Call_��ͼCall(DWORD parameter)
{
	int ���� = read<int>(parameter);
	__asm {
		pushad
		mov ecx, [__������]//
		mov ecx, [ecx + __ʱ���ַ]//
		mov ecx, [ecx + 0x8c]
		push - 1
		push - 1
		push 0
		push 0
		push 0
		push 0
		push 0
		push ����//��0��1��2��3
		mov eax, __��ͼCALL//
		call eax
		popad
	}
}

inline void Call_�ٻ�Call(DWORD parameter)
{

}

inline void Call_����Call(DWORD parameter)
{

}