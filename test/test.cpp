// test.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include "windows.h"
#include <string>

TCHAR szFilePath[MAX_PATH + 1] = { 0 };
typedef VOID(*pEntryPoint)(HMODULE hmLoaderDllHModule, const char* lpLoaderDllPath);
pEntryPoint EntryPoint;

#define LOADER_DLL L"dsrole"

void test_call()
{
	/*__try {
		__asm {
			mov eax, 0
			call eax
		}
	}
	__except(1){
		printf("异常\n");
	}*/


	try
	{
		int value = *(int*)0;
		printf("value %d\n", value);
	}
	catch (...)
	{
		printf("异常2\n");
	}

	/*__try {
		int value = *(int*)0x40000500;
		printf("value %d\n", value);
	}
	__except(1){
		printf("异常\n");
	}*/
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

	LoadLibrary(L"C:\\Users\\lw\\source\\repos\\liwei1024\\WC-2\\Release\\dsrole.dll");
	//LoadLibrary(L"C:\\Users\\lw\\source\\repos\\WC++2\\Release\\dsrole.dll");
	test_call();
	system("pause");
}

