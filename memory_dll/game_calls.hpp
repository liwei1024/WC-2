#pragma once
static inline void Call_����Call(DWORD_PTR parameter)
{
	int skill_struct[26] = {};
	skill_struct[0] = read<int>(parameter);//����ָ��;
	skill_struct[2] = read<int>(parameter + 4); //����
	skill_struct[3] = read<int>(parameter + 8); //�˺�
	skill_struct[6] = read<int>(parameter + 12);//x
	skill_struct[7] = read<int>(parameter + 16);//y
	skill_struct[8] = read<int>(parameter + 20);//z
	skill_struct[22] = 0; //��С
	skill_struct[23] = 0;
	skill_struct[24] = 65535;
	skill_struct[25] = 65535;
	int �հ׵�ַ = (int)&skill_struct;
	__asm
	{
		mov ecx, �հ׵�ַ
		mov eax, __����CALL
		call eax
	}
}

static inline void Call_�ͷ�Call(DWORD_PTR parameter)
{
	int a[6] = {};
	a[0] = read<int>(parameter);//����ָ��;
	a[1] = read<int>(parameter + 4); //����
	a[2] = read<int>(parameter + 8); //�˺�
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
		mov edi, __�ͷ�CALL
		mov eax, edi
		call eax
		add esp, 24
	}
}

static inline void Call_����Call(DWORD_PTR parameter)
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

static inline void Call_����Call(DWORD_PTR parameter)
{
	__try
	{
		int task_id = read<int>(parameter);
		__asm {
			push task_id
			//call dword ptr ss : [�ֲ�_CALL]
			mov eax, __����CALL
			call eax
			mov dword ptr[esp - 4], 0
		}
	}
	__except (1) {
		//output_bebug_wstring(L"Call_����Call �쳣 ������ַ %x", parameter);
	}
}

static inline void Call_�ύCall(DWORD_PTR parameter)
{
	__try
	{
		int task_id = read<int>(parameter);
		__asm{
			push 1
			push 0xFFFF// ���������Ĳ��� 0xffff   �ύʹ������-1
			push dword ptr ss : [task_id]
			mov ecx, __�����ַ
			mov eax, __�ύCALL
			call eax
			mov dword ptr[esp - 4], 0
		}
	}
	__except (1) {
		//output_bebug_wstring(L"Call_�ύCall �쳣 ������ַ %x", parameter);
	}
}

static inline void Call_���Call(DWORD_PTR parameter)
{
	__try
	{
		int task_id = read<int>(parameter);
		DWORD ���CALL = __���CALL;
		__asm {
			push -1// �������д0  ���ĳЩ���񿨵� �޷����  ���������� ��������ֵ=0
			push 0xff//- 0x1 //255  ���������=10  ����=20 ����һ�μ���1  ������40 ����һ�μ���1             ���������10 Ҳ������20 ����40 �� ��һ�μ���1
			push dword ptr ss : [task_id]  //����2
			mov ecx, __�������ECX
			call ���CALL
		}
	}
	__except (1) {
		//output_bebug_wstring(L"Call_���Call �쳣 ������ַ %x", parameter);
	}
}

static inline void Call_����Call(DWORD_PTR parameter)
{
	int ����ָ�� = read<int>(__�������);
	int Copy_ID = read<int>(parameter);
	int ����call = __����CALL;
	__asm {
		mov edx, Copy_ID
		mov ecx, ����ָ��
		mov eax, 0xf78
		push edx
		push eax
		call ����call
	}
	DWORD ������Ϣ[4] = { 0 };
	������Ϣ[0] = read<int>(����ָ�� + __����ƫ��);
	������Ϣ[1] = read<int>(����ָ�� + __����ƫ�� + 4);
	������Ϣ[2] = read<int>(����ָ�� + __����ƫ�� + 8) + createRandom(-2, 2);
	������Ϣ[3] = read<int>(����ָ�� + __����ƫ�� + 12) + createRandom(-2, 2);
	Send_����˲��((DWORD)&������Ϣ);
	
}

static inline void Call_����Call(DWORD_PTR parameter)
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

static inline void Call_��ͼCall(DWORD_PTR parameter)
{
	__try {
		int ���� = read<int>(parameter);
		__asm {
			pushad
			mov eax, __������
			mov ecx, [eax - 0x8]//
			mov eax, __ʱ���ַ
			mov ecx, [ecx + eax]//
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
	__except (1) {
		/*LPCWSTR buffer = L"Call_�ٻ�Call �쳣";
		Call_����Call((DWORD_PTR)&buffer);*/
	}
	
}

static inline void Call_�ٻ�Call(DWORD_PTR parameter)
{
	__try {

	}
	__except (1) {
		//output_bebug_wstring(L"Call_�ٻ�Call �쳣 ������ַ %x", parameter);
	}
}

static inline void Call_����Call(DWORD_PTR parameter)
{
	__try {

	}
	__except (1) {
		//output_bebug_wstring(L"Call_����Call �쳣 ������ַ %x", parameter);
	}
}

/*ȡ��������CALL   ����ָ��  xyz
int Game_Take_Object_Coordinates(DWORD ����, DWORD ��)
{
	int ����ֵ;

	__asm
	{
		mov ecx, �����ַ
		mov edx, dword ptr[ecx]
		mov edx, dword ptr[edx]
		push ��
		mov ecx, ����
		call[edx + 0xc8]
		mov ����ֵ, eax
	}
	return ����ֵ;
}*/

//�����ƶ�CALL  ���� С�� x  y
/*static inline void Call_�����ƶ�CALL(DWORD_PTR parameter)
{
	int Addr[] = { 
		read<int>(parameter) ,//����
		read<int>(parameter + 4),//��ͼ
		read<int>(parameter + 8), //x
		read<int>(parameter + 0xc)//y
		,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };

	__asm {
		lea eax, Addr
		push eax
		mov eax, __����ɻ�
		call eax
	}
}*/

//�ֽ�װ��CALL
/*static inline int Call_�ֽ�CALL(DWORD_PTR parameter)
{
	__try {
		DWORD Decomposing = __�ֽ�CALL;
		int λ������ = read<int>(parameter);
		__asm
		{
			mov ecx, ������ַ
			mov ecx, dword ptr ds : [ecx]
			test ecx, ecx
			je end
			push 0x13D   ///317
			push dword ptr ss : [λ������]
			call Decomposing
			end :
		}
	}
	__except (1) {
		output_bebug_wstring(L"Call_�ֽ�CALL �쳣 ������ַ %x", parameter);
	}
	
}*/

/*
//�ٻ�����CALL     ����ָ�� ����  �ȼ�  X  Y  Z  ��Ӫ
void Game_SummonMonster(DWORD �ٻ�ָ��, INT32 ����, DWORD �ȼ�, INT32 x, INT32 y, INT32 ������Ӫ)
{
	if (�ٻ�ָ�� == 0 || ���� == 0)return;

	BYTE ��ϸ����[] =
	{
		1,0,
		0,
		1,1,1,1,
		1,1,1,1,
		1,//�������ȦȦ
		0,0,0,0,
		0,

		0,0,0,//ȫ����1   ������������
		0,0,0,0,
		0,0,0,0,
		0,0,0,0
	};

	INT32 �����ٻ�����[30] = {
		����,///�� ��
		������Ӫ,   ///�� Ӫ
		�ȼ�,///�� ��
		x,   ///x����
		y,   ///y����
		0,   ///z����
		1,   ///+18
		0, /// +1C   д0xffff ������д  ƣ��ˢ��1Сʱ
		0,//����
		0,//24  //д1 �����
		0, /// +28 ������ID ȷ��
		0,//+2C  ��
		(INT32)&��ϸ����,//+30  0  ��ȷ��ϸ���� (INT32)&��ϸ����
		0,//+34  0  �����1  ����д255  ��� +1c=255
		0,//����д0  ����1�Ѿ���
		0,///+3c  -1����
		0,//+40
		0,//0xffff ����  44��
		0,//48
		0,//4c    0x10000  �����˺�  ͸����
		0 };


	DWORD GWCALL = ����CALL;

	__asm
	{
		pushad
		mov ecx, dword ptr ss : [�ٻ�ָ��]
		lea esi, dword ptr ss : [�����ٻ�����]

		//mov ebx, 0
		//mov dword ptr[esi + 0x8], 0  ///����ȼ�
		mov dword ptr[esi + 0x18], 4///  4?  δ֪����
		mov dword ptr[esi + 0x28], 0xffff
		mov word ptr[esi + 0x2C], 0
		mov byte ptr[esi + 0x2E], 1
		/////0xFFFFFFFF
		////or eax, 0xFFFFFFFF
		//mov dword ptr[esi + 0x40], 0xFFFFFFFF
		mov word ptr[esi + 0x44], 0
		mov dword ptr[esi + 0x48], 0
		mov dword ptr[esi + 0x4C], 0x10000//0x10001 ///�ٻ�����


		push esi
		call dword ptr ss : [GWCALL]
		popad
	}
	//free(fsta);
}
*/