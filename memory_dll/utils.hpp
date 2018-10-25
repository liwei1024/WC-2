#pragma once



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
		printf("getMouseCoord Erro!\n");
	}
	return Coord;
}

static BOOL setMouseCoord(INT x, INT y)
{
	BOOL result;
	result = SetCursorPos(x, y);
	if (result == FALSE) {
		printf("setMouseCoord Erro!\n");
	}
	return result;
}

static VOID mouseClick(INT s)
{
	mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
	Sleep(s + createRandom(0, 10));
	mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
	Sleep(50 + createRandom(0, 10));
}

static VOID mouseDoubleClick(INT s)
{
	mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
	Sleep(s + createRandom(0, 10));
	mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
	Sleep(50 + createRandom(0, 10));
	mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
	Sleep(s + createRandom(0, 10));
	mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
	Sleep(50 + createRandom(0, 10));
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
	if (getKeyStatus(keyCode) == FALSE) {
		keybd_event(keyCode, getSCan(keyCode), 0, 0);
		Sleep(100);
	}
}

static VOID keyUp(INT keyCode)
{
	if (getKeyStatus(keyCode) == TRUE) {
		keybd_event(keyCode, getSCan(keyCode), KEYEVENTF_KEYUP, 0);
		Sleep(100);
	}
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
	SendMessage(g_hWnd, MY_MESSAGE_ID,(WPARAM)pfun,(LPARAM)call_params);
	delete[]call_params;
}

static void output_bebug_wstring(const wchar_t *lpcszFormat, ...)
{
	va_list argList;
	wchar_t buffer[0x1024];
	wchar_t temp_buffer[0x1024];
	va_start(argList, lpcszFormat);
	vswprintf_s(buffer, lpcszFormat, argList);
	swprintf_s(temp_buffer, L"WC %s", buffer);
	OutputDebugString(temp_buffer);
	va_end(argList);
}

static HWND get_game_hwnd()
{
	std::wstring wstr(L"地下城与勇士");
	return FindWindow(wstr.c_str(), wstr.c_str());
}