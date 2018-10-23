#pragma once

static int get_game_status()
{
	int game_status = 0;
	return game_status;
}

static void bulletin(CONST LPWSTR Format, ...)
{
	WCHAR Buffer[0x1000];

	va_list args;
	va_start(args, Format);
	vswprintf_s(Buffer, Format, args);
	va_end(args);

	main_thread_exec_call(Call_¹«¸æCall, { (DWORD)&Buffer });
}