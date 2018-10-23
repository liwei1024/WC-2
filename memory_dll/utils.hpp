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
static INT getTime()
{
	DWORD t_start, t_end;
	t_start = GetTickCount();//从操作系统启动所经过（elapsed）的毫秒数，它的返回值是DWORD。
	Sleep(3000);
	t_end = GetTickCount();
	return  t_end - t_start;
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
	Sleep(s + createRandom(200, 300));
	keyUp(keyCode);
}

static void main_thread_exec_call(LPVOID pfun, std::vector<DWORD> params = { 0 })
{
	DWORD a[100] = { 0 };
	for (size_t i = 0; i < params.size(); i++)
	{
		a[i] = params[i];
	}
	PostMessage(g_hWnd, MY_MESSAGE_ID,(WPARAM)pfun,(LPARAM)a);
}

