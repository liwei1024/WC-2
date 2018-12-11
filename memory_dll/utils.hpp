#pragma once



static void output_bebug_wstring(const wchar_t *lpcszFormat, ...)
{
	va_list argList;
	wchar_t buffer[0x1024];
	wchar_t temp_buffer[0x1024];
	va_start(argList, lpcszFormat);
	vswprintf_s(buffer, lpcszFormat, argList);
	swprintf_s(temp_buffer, L"WC %s", buffer);
	OutputDebugStringW(temp_buffer);
	va_end(argList);
}

static void output_bebug_string(const char *lpcszFormat, ...)
{
	va_list argList;
	char buffer[0x1024];
	char temp_buffer[0x1024];
	va_start(argList, lpcszFormat);
	vsprintf_s(buffer, lpcszFormat, argList);
	sprintf_s(temp_buffer, "WC %s", buffer);
	OutputDebugStringA(temp_buffer);
	va_end(argList);
}

static int createRandom(int min, int max)
{
	int 随机数 = 0;
	if (max > min) {
		srand((unsigned)time(NULL));
		随机数 = (rand() % (min - max + 1) + max);
	}
	else {
		srand((unsigned)time(NULL));
		随机数 = (rand() % (max - min + 1) + min);
	}
	return 随机数;
}

// 获取时间戳
static DWORD getTime()
{
	DWORD t_start;
	t_start = GetTickCount();//从操作系统启动所经过（elapsed）的毫秒数，它的返回值是DWORD。
	return  t_start;
}

static POINT getMouseCoord()
{
	POINT Coord;
	if (GetCursorPos(&Coord)) {
		//printf("getMouseCoord Erro!\n");
	}
	return Coord;
}

static BOOL setMouseCoord(INT x, INT y)
{
	BOOL result = BOOL();

	//系统api设置
	result = SetCursorPos(x, y);
	if (result == FALSE) {
		//printf("setMouseCoord Erro!\n");
	}

	// 按键盒子设置
	/*POINT Coord = getMouseCoord();
	int i = 0;
	while (abs(Coord.x - x) > 5 || abs(Coord.y - y) > 5)
	{
		MouseMoveTo(0, x, y);
		Sleep(150);
		Coord = getMouseCoord();
		if (i > 3) {
			output_bebug_wstring(L"移动鼠标失败");
			break;
		}
		i++;
	}*/
	return result;
}

static VOID mouseClick(INT s = 100)
{
	//系统api设置
	/*mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
	Sleep(s + createRandom(0, 10));
	mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
	Sleep(50 + createRandom(0, 10));*/
	//硬件按键设置
	MouseEvent(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
	Sleep(s + createRandom(0, 10));
	MouseEvent(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
	Sleep(50 + createRandom(0, 10));
}

static VOID mouseDoubleClick(INT s = 100)
{
	mouseClick(s);
	mouseClick(s);
}

static bool getKeyStatus(INT keyCode)
{
	if (GetKeyState(keyCode) < 0) {
		return TRUE;
	}
	return FALSE;
}

static INT getSCan(INT keyCode)
{
	INT sCan = MapVirtualKey(keyCode, 0);
	if (
		keyCode == VK_LEFT ||
		keyCode == VK_RIGHT ||
		keyCode == VK_DOWN ||
		keyCode == VK_UP
		)
	{
		sCan += 0x80;
	}
	return sCan;
}

static VOID keyDown(INT keyCode)
{
	/*if (getKeyStatus(keyCode) == FALSE) {
		keybd_event(keyCode, getSCan(keyCode), 0, 0);
		Sleep(100);
	}*/
	KeybdEvent(keyCode, 0, 0, 0);
	Sleep(100);
}

static VOID keyUp(INT keyCode)
{
	/*if (getKeyStatus(keyCode) == TRUE) {
		keybd_event(keyCode, getSCan(keyCode), KEYEVENTF_KEYUP, 0);
		Sleep(100);
	}*/
	KeybdEvent(keyCode, 0, KEYEVENTF_KEYUP, 0);
	Sleep(100);
}

static VOID doKeyPress(INT keyCode, INT s = 0)
{
	keyDown(keyCode);
	Sleep(s + createRandom(1, 10));
	keyUp(keyCode);
}



static void main_thread_exec_call(LPVOID pfun, std::vector<int> params = { 0 })
{
	DWORD_PTR *call_params = new DWORD_PTR[params.size()];
	for (size_t i = 0; i < params.size(); i++)
	{
		call_params[i] = params[i];
	}
	RtlRemoteCall_ RtlRemoteCall = (RtlRemoteCall_)GetProcAddress(GetModuleHandle(_T("ntdll.dll")), "RtlRemoteCall");
	/*NtContinue_ NtContinue = (NtContinue_)GetProcAddress(GetModuleHandle(_T("ntdll.dll")), "NtContinue");*/
	//SendMessage(g_hWnd, MY_MESSAGE_ID,(WPARAM)pfun,(LPARAM)call_params);
	/*HANDLE hThread = ::CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)pfun, call_params, 0, NULL);
	::WaitForSingleObject(hThread, INFINITE); 
	::CloseHandle(hThread);*/
	RtlRemoteCall(g_hProcess,g_hThread, pfun, params.size(), call_params,FALSE, FALSE);
	//delete[]call_params;
}


static HWND get_game_hwnd()
{
	std::wstring wstr(_T("地下城与勇士"));
	return FindWindow(wstr.c_str(), wstr.c_str());
}

static WINDOW_INFO  get_window_info(HWND hWnd)
{
	RECT rect;
	WINDOW_INFO window_info;
	GetWindowRect(hWnd, &rect);
	window_info.bottom = rect.bottom;
	window_info.left = rect.left;
	window_info.right = rect.right;
	window_info.top = rect.top;
	window_info.width = window_info.right - window_info.left;
	window_info.height = window_info.bottom - window_info.top;
	return window_info;
}