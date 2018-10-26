// test.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include "windows.h"
#include <string>
#include <tchar.h>

TCHAR szFilePath[MAX_PATH + 1] = { 0 };
typedef VOID(*pEntryPoint)(HMODULE hmLoaderDllHModule, const char* lpLoaderDllPath);
pEntryPoint EntryPoint;

ULONG_PTR
CompareMemory(
	CONST CHAR *Dest,
	CONST CHAR *Src,
	SIZE_T cbData)
{
	if (!cbData) return 0;

	while (--cbData && (*Dest == *Src || '?' == *Src))
	{
		printf("%s ------ %s\n", Dest, Src);
		Dest++;
		Src++;
	}

	return(*Dest - *Src);
}

ULONG_PTR
SearchMemoryEx(
	HANDLE Process,
	ULONG_PTR BaseAddress,
	ULONG_PTR RegionSize,
	LPCSTR szSigMask,
	SIZE_T cbData
)
{
	MEMORY_BASIC_INFORMATION info;
	ZeroMemory(&info, sizeof(MEMORY_BASIC_INFORMATION));

	ULONG_PTR BufferAddress = BaseAddress;

	while (BufferAddress < BaseAddress + RegionSize)
	{
		if (!VirtualQueryEx(Process, (PVOID)BufferAddress, &info, sizeof(MEMORY_BASIC_INFORMATION)))
			return 0;

		if (info.Protect && MEM_COMMIT == info.State)
		{
			PCHAR Buffer = (PCHAR)malloc(info.RegionSize);

			//ReadMemoryEx(Process, (PVOID)BufferAddress, Buffer, info.RegionSize);
			ReadProcessMemory(Process, (PVOID)BufferAddress, Buffer, info.RegionSize,NULL);

			for (SIZE_T i = 0; i < info.RegionSize - cbData; i++)
			{
				if (!CompareMemory(Buffer + i, szSigMask, cbData)) return i + BufferAddress;
			}

			free(Buffer);
			Buffer = NULL;
		}

		BufferAddress += info.RegionSize;
	}

	return 0;
}

ULONG_PTR
SearchMemory(
	ULONG_PTR BaseAddress,
	ULONG_PTR RegionSize,
	LPCSTR szSigMask,
	SIZE_T cbData
)
{
	return SearchMemoryEx((HANDLE)-1, BaseAddress, RegionSize, szSigMask, cbData);
}


int main()
{
	/*char lpLoaderDllPath[MAX_PATH] = { 0 };
	HMODULE hMoudle = LoadLibrary(L"C:\\Users\\lw\\source\\repos\\liwei1024\\WC-2\\Release\\WCPlusPlus.dll");
	EntryPoint = (pEntryPoint)GetProcAddress(hMoudle, "EntryPoint");
	GetModuleFileNameA(hMoudle, lpLoaderDllPath, sizeof(lpLoaderDllPath));
	EntryPoint(hMoudle, lpLoaderDllPath);*/

	/*_wgetcwd(szFilePath, MAX_PATH);
	std::wstring str(szFilePath);
	str += L"\\dsrole.dll";
	wprintf_s(L"path %s\n", str.c_str());*/
	//LoadLibrary(str.c_str());

	//LoadLibrary(L"C:\\Users\\lw\\source\\repos\\liwei1024\\WC-2\\Release\\dsrole.dll");
	//LoadLibrary(_T("C:\\Users\\lw\\source\\repos\\WC++2\\Release\\dsrole.dll"));

	/*LPCSTR str = "79 00 00 00 0D 00";
	DWORD addr = SearchMemoryEx(hProcess,0x00C005BE,100000, str,6);
	printf("addr %x\n", addr);*/

	HANDLE hProcess;
	hProcess = OpenProcess(PROCESS_ALL_ACCESS, false,15396 );
	MEMORY_BASIC_INFORMATION info;
	ZeroMemory(&info, sizeof(MEMORY_BASIC_INFORMATION));
	ULONG_PTR BufferAddress = 0;
	if (!VirtualQueryEx(hProcess, (PVOID)BufferAddress, &info, sizeof(MEMORY_BASIC_INFORMATION)))
		return 0;
	LPCSTR str = "8BFF558BEC5DFF25C012D276";
	DWORD addr = SearchMemory((ULONG_PTR)info.BaseAddress,1111111111111, str,24);//
	printf("addr %x\n", addr);

	
	printf("AllocationBase %x\n", info.AllocationBase);
	printf("AllocationProtect %x\n", info.AllocationProtect);
	printf("BaseAddress %x\n", info.BaseAddress);
	printf("Protect %x\n", info.Protect);
	printf("RegionSize %x\n", info.RegionSize);
	printf("State %x\n", info.State);
	printf("Type %x\n", info.Type);
	system("pause");
}

