#pragma once
static inline void Call_技能Call(DWORD_PTR parameter)
{
	int skill_struct[26] = {};
	skill_struct[0] = read<int>(parameter);//触发指针;
	skill_struct[2] = read<int>(parameter + 4); //代码
	skill_struct[3] = read<int>(parameter + 8); //伤害
	skill_struct[6] = read<int>(parameter + 12);//x
	skill_struct[7] = read<int>(parameter + 16);//y
	skill_struct[8] = read<int>(parameter + 20);//z
	skill_struct[22] = 0; //大小
	skill_struct[23] = 0;
	skill_struct[24] = 65535;
	skill_struct[25] = 65535;
	int 空白地址 = (int)&skill_struct;
	__asm
	{
		mov ecx, 空白地址
		mov eax, __技能CALL
		call eax
	}
}

static inline void Call_释放Call(DWORD_PTR parameter)
{
	int 触发指针 = read<int>(parameter);//触发指针;
	int 代码 = read<int>(parameter + 4); //代码
	int 伤害= read<int>(parameter + 8); //伤害
	int x = read<int>(parameter + 12);//x
	int y = read<int>(parameter + 16);//y
	int z = read<int>(parameter + 20);//z
	__asm
	{
		push z
		push y
		push x
		push 伤害
		push 代码
		push 触发指针
		mov edi, __释放CALL
		mov eax, edi
		call eax
		add esp, 24
	}
}

static inline void Call_公告Call(DWORD_PTR parameter)
{
	__try
	{
		DWORD Buffer = read<DWORD>(parameter);
		if (Buffer > 0) {
			__asm
			{
				mov ecx, __商店基址
				mov ecx, dword ptr[ecx]
				mov ecx, dword ptr[ecx + 0x50]
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
	__except (1) {
		output_bebug_wstring(L"Call_公告Call");
	}
}

static inline void Call_接受Call(DWORD_PTR parameter)
{
	__try
	{
		int task_id = read<int>(parameter);
		__asm {
			push task_id
			//call dword ptr ss : [局部_CALL]
			mov eax, __接受CALL
			call eax
			mov dword ptr[esp - 4], 0
		}
	}
	__except (1) {
		//output_bebug_wstring(L"Call_接受Call 异常 参数地址 %x", parameter);
	}
}

static inline void Call_提交Call(DWORD_PTR parameter)
{
	__try
	{
		int task_id = read<int>(parameter);
		__asm{
			push 1
			push 0xFFFF// 拦截下来的参数 0xffff   提交使命任务-1
			push dword ptr ss : [task_id]
			mov ecx, __任务基址
			mov eax, __提交CALL
			call eax
			mov dword ptr[esp - 4], 0
		}
	}
	__except (1) {
		//output_bebug_wstring(L"Call_提交Call 异常 参数地址 %x", parameter);
	}
}

static inline void Call_完成Call(DWORD_PTR parameter)
{
	__try
	{
		int task_id = read<int>(parameter);
		DWORD 完成CALL = __完成CALL;
		__asm {
			push -1// 这个参数写0  会把某些任务卡的 无法完成  拦截下来的 主线任务值=0
			push 0xff//- 0x1 //255  当这个参数=10  或者=20 都多一次加密1  不等于40 都多一次加密1             如果不等于10 也不等于20 等于40 则 少一次加密1
			push dword ptr ss : [task_id]  //加密2
			mov ecx, __任务完成ECX
			call 完成CALL
		}
	}
	__except (1) {
		//output_bebug_wstring(L"Call_完成Call 异常 参数地址 %x", parameter);
	}
}

static inline void Call_区域Call(DWORD_PTR parameter)
{
	__try
	{
		int 区域指针 = read<int>(__区域参数);
		int Copy_ID = read<int>(parameter);
		int goods_id = read<int>(parameter + 4);
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
		区域信息[4] = goods_id;
		Send_城镇瞬移((DWORD)&区域信息);
	}
	__except (1) {
		LPCWSTR buffer = L"Call_区域Call 异常";
		Call_公告Call((DWORD_PTR)&buffer);
	}
}

static inline void Call_坐标Call(DWORD_PTR parameter)
{
	__try {
		DWORD object_pointer = read<int>(parameter);
		DWORD x = read<int>(parameter + 4);
		DWORD y = read<int>(parameter + 8);
		DWORD z = read<int>(parameter + 12);
		__asm
		{
			mov esi, object_pointer
			mov edi, dword ptr[esi]
			push z
			push y
			push x
			mov eax, dword ptr[edi + 0xbc]
			mov ecx, esi
			call eax
		}
		}
	__except (1) {
		LPCWSTR buffer = L"Call_坐标Call 异常";
		Call_公告Call((DWORD_PTR)&buffer);
	}
}

static inline void Call_过图Call(DWORD_PTR parameter)
{
	__try {
		int 方向 = read<int>(parameter);
		__asm {
			pushad
			mov eax, __房间编号
			mov ecx, dword ptr[eax - 0x8]//
			mov eax, __时间基址
			mov ecx, dword ptr[ecx + eax]//
			mov ecx, dword ptr[ecx + 0x8c]
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
	__except (1) {
		/*LPCWSTR buffer = L"Call_召唤Call 异常";
		Call_公告Call((DWORD_PTR)&buffer);*/
	}
}

static inline void Call_召唤Call(DWORD_PTR parameter)
{
	__try {

	}
	__except (1) {
		//output_bebug_wstring(L"Call_召唤Call 异常 参数地址 %x", parameter);
	}
}

static inline void Call_变身Call(DWORD_PTR parameter)
{
	__try {

	}
	__except (1) {
		//output_bebug_wstring(L"Call_变身Call 异常 参数地址 %x", parameter);
	}
}

static inline void Call_城镇移动(DWORD_PTR parameter)
{
	__try {

	}
	__except (1) {
		output_bebug_wstring(L"Call_城镇移动 异常");
	}
}

static inline void Call_移动Call(DWORD_PTR parameter)
{
	__try {
		int 移动指针 = read<int>(__人物基址);
		int 变量入栈CALL = __变量入栈CALL;
		int 移动CALL = __移动CALL;
		int 移动速度 = read<int>(parameter + 0);
		int 目标x = read<int>(parameter + 4);
		int 目标y = read<int>(parameter + 8);
		__asm
		{
			mov esi, 移动指针
			mov eax, dword ptr ds : [esi]
			mov edx, dword ptr ds : [eax + __移动偏移_1]
			lea ecx, dword ptr ds : [0x400C00]
			push ecx
			mov ecx, esi
			call edx //call eax	
			push 目标y
			push 目标x
			push 移动速度
			push 0x0
			sub esp, 0x8
			lea edx, dword ptr ds : [0x400C00]
			mov ecx, esp
			push edx
			call 变量入栈CALL
			mov esi, 移动指针
			mov eax, dword ptr ds : [esi]
			mov edx, dword ptr ds : [eax + __移动偏移_2]
			lea ecx, dword ptr ds : [0x400C00]
			push ecx
			mov ecx, esi
			call edx
			sub esp, 0x8
			lea eax, dword ptr ds : [0x400C00]
			mov ecx, esp
			push eax
			call 变量入栈CALL
			push 移动指针
			mov ecx, 移动指针
			call 移动CALL
		}
	}
	__except (1) {
		/*LPCWSTR buffer = L"Call_坐标Call 异常";
		Call_公告Call((DWORD_PTR)&buffer);*/
	}
}

//#define FlashFunc0x02413300//闪现CALL
//VOID 男法瞬移(DWORD Point, DWORD Ex, DWORD Ey)
//{
//	DWORD Sx = ReadGrid(Point, 0);//当前 x坐标
//	DWORD Sy = ReadGrid(Point, 1);//当前 y坐标
//	DWORD FlashCall = FlashFunc;
//	_asm
//	{
//		mov esi, Point
//		push 0xA
//		push Sy//当前y坐标
//		push Sx//当前x坐标
//		push Ey//目的y坐标
//		push Ex//目的x坐标
//		mov ecx, esi
//		call FlashCall
//	}
//	return VOID();
//}

/*取对象坐标CALL   对象指针  xyz
int Game_Take_Object_Coordinates(DWORD 对象, DWORD 轴)
{
	int 坐标值;

	__asm
	{
		mov ecx, 人物基址
		mov edx, dword ptr[ecx]
		mov edx, dword ptr[edx]
		push 轴
		mov ecx, 对象
		call[edx + 0xc8]
		mov 坐标值, eax
	}
	return 坐标值;
}*/

//城镇移动CALL  大区 小区 x  y
/*static inline void Call_城镇移动CALL(DWORD_PTR parameter)
{
	int Addr[] = { 
		read<int>(parameter) ,//区域
		read<int>(parameter + 4),//地图
		read<int>(parameter + 8), //x
		read<int>(parameter + 0xc)//y
		,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };

	__asm {
		lea eax, Addr
		push eax
		mov eax, __城镇飞机
		call eax
	}
}*/

//分解装备CALL
/*static inline int Call_分解CALL(DWORD_PTR parameter)
{
	__try {
		DWORD Decomposing = __分解CALL;
		int 位置索引 = read<int>(parameter);
		__asm
		{
			mov ecx, 背包基址
			mov ecx, dword ptr ds : [ecx]
			test ecx, ecx
			je end
			push 0x13D   ///317
			push dword ptr ss : [位置索引]
			call Decomposing
			end :
		}
	}
	__except (1) {
		output_bebug_wstring(L"Call_分解CALL 异常 参数地址 %x", parameter);
	}
	
}*/

/*
//召唤怪物CALL     对象指针 代码  等级  X  Y  Z  阵营
void Game_SummonMonster(DWORD 召唤指针, INT32 代码, DWORD 等级, INT32 x, INT32 y, INT32 怪物阵营)
{
	if (召唤指针 == 0 || 代码 == 0)return;

	BYTE 详细参数[] =
	{
		1,0,
		0,
		1,1,1,1,
		1,1,1,1,
		1,//怪物脚下圈圈
		0,0,0,0,
		0,

		0,0,0,//全部改1   卡卡西不出来
		0,0,0,0,
		0,0,0,0,
		0,0,0,0
	};

	INT32 怪物召唤数据[30] = {
		代码,///代 码
		怪物阵营,   ///阵 营
		等级,///等 级
		x,   ///x坐标
		y,   ///y坐标
		0,   ///z坐标
		1,   ///+18
		0, /// +1C   写0xffff 其他不写  疲劳刷完1小时
		0,//崩溃
		0,//24  //写1 不打怪
		0, /// +28 服务器ID 确认
		0,//+2C  字
		(INT32)&详细参数,//+30  0  正确详细参数 (INT32)&详细参数
		0,//+34  0  随机数1  这里写255  配合 +1c=255
		0,//这里写0  好像1把就死
		0,///+3c  -1崩溃
		0,//+40
		0,//0xffff 智商  44字
		0,//48
		0,//4c    0x10000  黄字伤害  透明了
		0 };


	DWORD GWCALL = 怪物CALL;

	__asm
	{
		pushad
		mov ecx, dword ptr ss : [召唤指针]
		lea esi, dword ptr ss : [怪物召唤数据]

		//mov ebx, 0
		//mov dword ptr[esi + 0x8], 0  ///怪物等级
		mov dword ptr[esi + 0x18], 4///  4?  未知参数
		mov dword ptr[esi + 0x28], 0xffff
		mov word ptr[esi + 0x2C], 0
		mov byte ptr[esi + 0x2E], 1
		/////0xFFFFFFFF
		////or eax, 0xFFFFFFFF
		//mov dword ptr[esi + 0x40], 0xFFFFFFFF
		mov word ptr[esi + 0x44], 0
		mov dword ptr[esi + 0x48], 0
		mov dword ptr[esi + 0x4C], 0x10000//0x10001 ///召唤变身


		push esi
		call dword ptr ss : [GWCALL]
		popad
	}
	//free(fsta);
}
*/