#include "pch.h"
#include "memory_loader.h"
#include <direct.h>

HMODULE g_hDll = NULL;

HMODULE g_hModule;


typedef int(_stdcall *MouseClick_)(BYTE AKey);
typedef int(_stdcall *MouseDbClick_)(BYTE AKey);
typedef int(_stdcall *GetKeyDev_)(void);
typedef int(_stdcall *KeyUp_)(void);
typedef int(_stdcall *KeybdEvent_)(BYTE bVk, BYTE bScan, int dwFlags, int dwExtraInfo);
typedef int(_stdcall *MouseEvent_)(int dwFlags, int dx, int dy, int dwData, int dwExtraInfo);

typedef VOID(*pEntryPoint)(MouseClick_,MouseDbClick_ ,GetKeyDev_ ,KeyUp_ ,KeybdEvent_ ,MouseEvent_);

MouseClick_ MouseClick;
MouseDbClick_ MouseDbClick;
GetKeyDev_ GetKeyDev;
KeyUp_ KeyUp;
KeybdEvent_ KeybdEvent;
MouseEvent_ MouseEvent;

char szFilePath[MAX_PATH + 1] = { 0 };

BOOL LoadFromMemory1()
{
	FILE *fp;
	unsigned char *data = NULL;
	size_t size;
	HMEMORYMODULE module;

	//fopen_s(&fp, "C:\\Users\\lw\\source\\repos\\liwei1024\\WC-2\\Release\\KeyCall.dat", "rb");
	fopen_s(&fp, "C:\\KeyCall.dat", "rb");
	if (fp == NULL)
	{
		//OutputDebugString(L"WC KeyCall load fail");
		return FALSE;
	}
	fseek(fp, 0, SEEK_END);
	size = ftell(fp);
	data = (unsigned char *)malloc(size);
	fseek(fp, 0, SEEK_SET);
	fread(data, 1, size, fp);
	fclose(fp);
	module = MemoryLoadLibrary(data);
	if (module == NULL)
	{
		return FALSE;
	}

	MouseClick = (MouseClick_)MemoryGetProcAddress(module, "MouseClick");
	MouseDbClick = (MouseDbClick_)MemoryGetProcAddress(module, "MouseDbClick");
	GetKeyDev = (GetKeyDev_)MemoryGetProcAddress(module, "GetKeyDev");
	KeyUp = (KeyUp_)MemoryGetProcAddress(module, "KeyUp");
	KeybdEvent = (KeybdEvent_)MemoryGetProcAddress(module, "KeybdEvent");
	MouseEvent = (MouseEvent_)MemoryGetProcAddress(module, "MouseEvent");

	return TRUE;
}

void LoadFromMemory2()
{
	FILE *fp;
	unsigned char *data = NULL;
	size_t size;
	HMEMORYMODULE module;
	pEntryPoint EntryPoint;

	//fopen_s(&fp, "C:\\Users\\lw\\source\\repos\\liwei1024\\WC-2\\Release\\dsrole.dat", "rb");
	fopen_s(&fp, "C:\\dsrole.dat", "rb");
	if (fp == NULL)
	{
		OutputDebugString(L"WC dsrole load fail");
		return;
	}
	fseek(fp, 0, SEEK_END);
	size = ftell(fp);
	data = (unsigned char *)malloc(size);
	fseek(fp, 0, SEEK_SET);
	fread(data, 1, size, fp);
	fclose(fp);

	module = MemoryLoadLibrary(data);
	if (module == NULL)
	{
		return;
	}
	EntryPoint = (pEntryPoint)MemoryGetProcAddress(module, "EntryPoint");
	EntryPoint(
		MouseClick,
		MouseDbClick,
		GetKeyDev,
		KeyUp,
		KeybdEvent,
		MouseEvent
	);
}

BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		//DisableThreadLibraryCalls(hModule);//禁用指定的DLL的DLL_THREAD_ATTACH和DLL_THREAD_DETACH通知，这样可以减小某些程序的工作集大小。
		//g_hDll = LoadLibrary(_T("C:\\Windows\\System32\\dsrole.dll"));
		g_hModule = hModule;
		if (LoadFromMemory1() == TRUE) {
			LoadFromMemory2();
			OutputDebugString(L"WC 加载");
		}
			
		break;
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return FALSE;
}

