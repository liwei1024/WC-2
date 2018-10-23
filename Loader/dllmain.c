#define WIN32_LEAN_AND_MEAN

#include "pch.h"
#include "memory_loader.h"

HMODULE g_hDll = NULL;

HMODULE g_hModule;

typedef VOID(*pEntryPoint)(HMODULE hmLoaderDllHModule, const char* lpLoaderDllPath);

//#define DLL_FILE 


void LoadFromMemory()
{
	//VMProtectBegin("LoadFromMemory");
	FILE *fp;
	unsigned char *data = NULL;
	size_t size;
	HMEMORYMODULE module;
	pEntryPoint EntryPoint;


	fopen_s(&fp, "C:\\Users\\lw\\source\\repos\\liwei1024\\WC-2\\Release\\WCPlusPlus.dat", "rb");
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
		g_hDll = LoadLibrary(L"C:\\Windows\\System32\\dsrole.dll");
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

