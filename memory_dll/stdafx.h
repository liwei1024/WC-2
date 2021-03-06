// stdafx.h: 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 项目特定的包含文件
//

#pragma once

#include "targetver.h"

//#define WIN32_LEAN_AND_MEAN             // 从 Windows 头文件中排除极少使用的内容
// Windows 头文件
#include <windows.h>
#include <windowsx.h>
#include <vector>
#include <string>
#include <map>
#include <ctime>
#include <process.h>
#include <thread>
#include <direct.h>
#include <tchar.h>

// 在此处引用程序需要的其他标头
typedef int(_stdcall *MouseClick_)(BYTE AKey);
typedef int(_stdcall *MouseDbClick_)(BYTE AKey);
typedef int(_stdcall *GetKeyDev_)(void);
typedef int(_stdcall *KeyUp_)(void);
typedef int(_stdcall *KeybdEvent_)(BYTE bVk, BYTE bScan, int dwFlags, int dwExtraInfo);
typedef int(_stdcall *MouseEvent_)(int dwFlags, int dx, int dy, int dwData, int dwExtraInfo);

typedef NTSTATUS(NTAPI *RtlRemoteCall_)(
	IN HANDLE Process,
	IN HANDLE Thread,
	IN PVOID CallSite, //call 地址
	IN ULONG ArgumentCount,// 参数数量
	IN PULONG Arguments,//参数
	IN BOOLEAN PassContext,
	IN BOOLEAN AlreadySuspended
	);

typedef NTSTATUS(NTAPI* NtContinue_)(
	IN PCONTEXT             ThreadContext,
	IN BOOLEAN              RaiseAlert
	);

extern MouseClick_ MouseClick;
extern MouseDbClick_ MouseDbClick;
extern GetKeyDev_ GetKeyDev;
extern KeyUp_ KeyUp;
extern KeybdEvent_ KeybdEvent;
extern MouseEvent_ MouseEvent;
//#include "KeyCall.h"
#include "global_consts.h"
#include "global_struct.hpp"
#include "global_var.h"
#include "utils.hpp"
#include "memory.hpp"
#include "game_send_packet.hpp"
#include "game_calls.hpp"
#include "game_utils.hpp"
#include "game_knapsac.hpp"


#include "game_role.hpp"
#include "game_task.hpp"



