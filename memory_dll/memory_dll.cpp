// memory_dll.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include"game_astar.hpp"
#include "game_status_0.h"
#include "game_status_1.h"
#include "game_status_2.h"
#include "game_status_3.h"



typedef void(*MainThreadCall)(LONG_PTR);
MainThreadCall _MainThreadCall;

RolePos role_pos;

game_status_0 _game_status_0;
game_status_1 _game_status_1;
game_status_2 _game_status_2;
game_status_3 _game_status_3;

WNDPROC g_orgProc;
char g_gamePath[MAX_PATH + 1] = { 0 };
char command[0x1000] = { 0 };

static  void start_auto()
{
	while (g_auto_switch)
	{
		if (read<int>(__对话基址) == 1)
		{
			doKeyPress(VK_RETURN);
			Sleep(1000);
			continue;
		}
		switch (get_game_status())
		{
		case 0:
			_game_status_0.manage();
			break;
		case 1:
			_game_status_1.manage();
			break;
		case 2:
			_game_status_2.manage();
			break;
		case 3:
			_game_status_3.manage();
			break;
		default:
			bulletin(L"状态获取错误");//按一次Shift  即可  Please press the shift key once.
			break;
		}
	}
}

static  void OnKeyDown(HWND hWnd, UINT wParam, BOOL bCtl, INT lParamL, UINT lParamH)
{
	// 此处处理按键消息
	switch (wParam)
	{
	case 229:
		//bulletin(L"Please press the shift.");//按一次Shift  即可  Please press the shift key once.
		doKeyPress(VK_SHIFT);
		break;
	case VK_HOME:
		//VaBulletin(L"WC MessageTest");
		g_auto_switch = g_auto_switch ? false : true;
		if (g_auto_switch)
			_beginthreadex(NULL, 0, (_beginthreadex_proc_type)start_auto, NULL, 0, 0);
		break;
	case VK_F1:
		_game_status_3.output_map_objects_info();
		break;
	case VK_F2:
		//main_thread_exec_call(Send_返回角色);
		//GetDirection();
		break;
	case VK_F3:
		//main_thread_exec_call(Send_选择角色, { 1 });
		//is_open_door();
		break;
	case VK_F4:
		//main_thread_exec_call(Send_城镇瞬移, { 14, 2, 705, 288 });
		break;
	case VK_F5:
		//main_thread_exec_call(Send_城镇瞬移, { 104 });
		break;
	case VK_F6:
		//role_pos = get_role_pos();
		main_thread_exec_call(Call_技能Call, { 0,70023,113,role_pos.x + createRandom(-10,10),role_pos.y + createRandom(-10,10),role_pos.z });
		break;
	case VK_F7:

		break;
	case VK_F8:

		break;
	case VK_F9:

		break;
	case VK_F10:

		break;

	case 0x56: //v键
		_game_status_3.get_loot();
		break;
	case 0xC0: //波浪键

		break;

	case VK_F11:

		break;

		// End 键
	case VK_END:

		break;

	default:
		break;
	}
}

static  void OnSysKeyDown(HWND hWnd, UINT nChar, BOOL bCtl, UINT nRepCnt, UINT nFlags)
{
	// 此处处理ALT+ 按键消息
	switch (nChar)
	{
	case VK_RIGHT:

		break;
	case VK_UP:

		break;
	case VK_LEFT:

		break;
	case VK_DOWN:

		break;

	case 0x31://alt+1 //歌兰蒂斯

		//exec_call(Send_城市飞机, { 39, 0, 2494, 255 });
		break;
	case 0x32://alt+2 //格蓝迪

		//exec_call(Send_城市飞机, { 14, 2, 705, 288 });
		break;
	case 0x33://alt+3 //出售 时空石

		//exec_call(Send_城市飞机, { 31, 3, 858, 305 });
		break;
	case 0x34://alt+4 //克伦特 兑换矛盾
		//exec_call(Send_城市飞机, { 41, 1, 485, 154 });
		break;
	case 0x35://alt+5 //月光酒馆 兑换
		//exec_call(Send_城市飞机, { 39, 4, 603, 264 });
		break;
	default:
		break;
	}
}

// 窗口消息
static LRESULT CALLBACK CallWndProc(_In_ HWND hWnd, _In_ UINT uMsg, _In_ WPARAM wParam, _In_ LPARAM lParam)
{
	//g_hWnd = hWnd;

	switch (uMsg)
	{
		HANDLE_MSG(hWnd, WM_KEYDOWN, OnKeyDown);
		HANDLE_MSG(hWnd, WM_SYSKEYDOWN, OnSysKeyDown);
	default:
		break;
	}
	switch (uMsg)
	{
	case MY_MESSAGE_ID:
		_MainThreadCall = (MainThreadCall)wParam;
		_MainThreadCall(lParam);
		return LRESULT();
	case WM_CLOSE:
		sprintf_s(command, "@echo off cacls  /e /p everyone:f %s", g_gamePath);
		WinExec(command, SW_HIDE);
	default:
		break;
	}
	// 此处必要 因为是HOOK 消息必须返回给原游戏窗口 再处理一次 否则会造成游戏窗口假死
	return CallWindowProc(g_orgProc, hWnd, uMsg, wParam, lParam);
}

static  void initialize_thread()
{
	while (1)
	{
		if (get_game_status() == 0) {

			g_hWnd = get_game_hwnd();
			if (g_hWnd != NULL)
			{
				LoadLibrary(L"C:\\Windows\\System32\\dsrole.dll");

				_getcwd(g_gamePath, MAX_PATH);
				strcat_s(g_gamePath, MAX_PATH, "\\dsrole.dll");

				sprintf_s(command,"@echo off cacls  /e /p everyone:n %s", g_gamePath);

				WinExec(command, SW_HIDE);
				g_orgProc = (WNDPROC)SetWindowLongW(g_hWnd, GWL_WNDPROC, (LONG_PTR)CallWndProc);
				break;
			}
		}
		Sleep(1000);
	}
}

extern "C" __declspec(dllexport) VOID EntryPoint(HMODULE hmLoaderDllHModule, const char* lpLoaderDllPath)
{
	//CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)initialize_thread, NULL, 0, 0);
	output_bebug_wstring(_T("hModule %x"),(int)GetModuleHandle(NULL));
	_beginthreadex(NULL, 0, (_beginthreadex_proc_type)initialize_thread, NULL, 0, 0);
}