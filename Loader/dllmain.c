#include "pch.h"
#include "memory_loader.h"
#include <direct.h>

HMODULE g_hDll = NULL;

HMODULE g_hModule;

typedef VOID(*pEntryPoint)(HMODULE hmLoaderDllHModule, const char* lpLoaderDllPath);

//#define DLL_FILE 


char szFilePath[MAX_PATH + 1] = { 0 };

static inline void LoadFromMemory()
{
	//VMProtectBegin("LoadFromMemory");
	FILE *fp;
	unsigned char *data = NULL;
	size_t size;
	HMEMORYMODULE module;
	pEntryPoint EntryPoint;

	/*_getcwd(szFilePath, MAX_PATH);
	strcat_s(szFilePath, MAX_PATH, "\\WCPlusPlus.dat");*/

	//OutputDebugStringA(szFilePath);
	

	//fopen_s(&fp, "C:\\dsrole.dat", "rb");
	fopen_s(&fp, "C:\\Users\\lw\\source\\repos\\liwei1024\\WC-2\\Release\\dsrole.dat", "rb");
	//fopen_s(&fp, szFilePath, "rb");
	if (fp == NULL)
	{
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

	char lpLoaderDllPath[MAX_PATH] = { 0 };

	GetModuleFileNameA(g_hModule, lpLoaderDllPath, sizeof(lpLoaderDllPath));

	EntryPoint(g_hModule, lpLoaderDllPath);

	////CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)UnloadProc, NULL, 0, 0);
	//VMProtectEnd();
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
		g_hDll = LoadLibrary(_T("C:\\Windows\\System32\\dsrole.dll"));
		g_hModule = hModule;
		LoadFromMemory();
		break;
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return FALSE;
}

