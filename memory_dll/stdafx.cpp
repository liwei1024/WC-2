#include "stdafx.h"

using namespace std;

void test()
{
	write_bytes(0x400500, { 1,2,34 });
	get_game_status();
}