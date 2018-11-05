#include "stdafx.h"
#include "Knapsac.h"


using namespace std;

Knapsac::Knapsac()
{
}


Knapsac::~Knapsac()
{
}

DWORD Knapsac::GetKnapsacAddress()
{
	return read<int>(__背包基址);
}

DWORD Knapsac::GetKnapsacStartAddress()
{
	return read<int>(GetKnapsacAddress() + 88) + 36;
}

GOODS_INFO Knapsac::GetGoodsInfo(int GoodsAddress)
{
	GOODS_INFO _GoodsInfo;
	_GoodsInfo.address = GoodsAddress;
	_GoodsInfo.name = read_wstring(read<int>(GoodsAddress + 36), 52);
	_GoodsInfo.level = read<int>(GoodsAddress + 376);
	return _GoodsInfo;
}

int Knapsac::GetGoodsIndexByGoodsName(std::wstring GoodsName)
{
	DWORD StartAddress = GetKnapsacStartAddress();
	GOODS_INFO _GoodsInfo;
	DWORD GoodsAddress;
	for (size_t i = 0; i < 279; i++)
	{
		GoodsAddress = read<int>(StartAddress + i * 4);
		if (GoodsAddress == 0 || GoodsAddress == NULL)continue;
		_GoodsInfo = GetGoodsInfo(GoodsAddress);
		_GoodsInfo.index = i + 9;
		if (_GoodsInfo.name == GoodsName)
		{
			return _GoodsInfo.index;
		}
	}
	return -1;
}

int Knapsac::SaleGoods()
{
	DWORD StartAddress = GetKnapsacStartAddress();
	GOODS_INFO _GoodsInfo;
	DWORD GoodsAddress;
	for (size_t i = 0; i < 55; i++)
	{
		GoodsAddress = read<int>(StartAddress + i * 4);
		if (GoodsAddress == 0 || GoodsAddress == NULL)continue;
		_GoodsInfo = GetGoodsInfo(GoodsAddress);
		_GoodsInfo.index = i + 9;
		if (
			(_GoodsInfo.name.find(L"传承", 0) == -1) &&
			(_GoodsInfo.name.find(L"周年", 0) == -1) &&
			(_GoodsInfo.name.find(L"活动", 0) == -1)
			)
		{
			if (
				_GoodsInfo.level == 0 ||
				_GoodsInfo.level == 1 ||
				_GoodsInfo.level == 2
				)
			{
				main_thread_exec_call(Send_组包卖物, { _GoodsInfo.index });
				Sleep(500);
			}
		}
	}
	return -1;
}

void Knapsac::OutputGoodsInfo()
{
	DWORD StartAddress = GetKnapsacStartAddress();
	GOODS_INFO _GoodsInfo;
	DWORD GoodsAddress;
	string str;
	str += "====================================================\n";
	for (size_t i = 0; i < 279; i++)
	{
		GoodsAddress = read<int>(StartAddress + i * 4);
		output_bebug_wstring(_T("====================================="));
		output_bebug_wstring(_T("地址 0x%x"), _GoodsInfo.address);
		output_bebug_wstring(_T("等级 %d"), _GoodsInfo.level);
		output_bebug_wstring(_T("名称 %d"), _GoodsInfo.name);
	}
}

Pos Knapsac::get_goods_pos_by_index(int index)
{
	Pos pos;
	int x, y;
	if (index >= 0 and index <= 7)
	{
		x = index * 30;
		y = 0;
	}
	else if (index >= 8 and index <= 15)
	{
		x = (index - 8) * 30;
		y = 30;
	}
	else if (index >= 16 and index <= 23)
	{
		x = (index - 16) * 30;
		y = 60;
	}
	else if (index >= 24 and index <= 31)
	{
		x = (index - 24) * 30;
		y = 90;
	}
	else if (index >= 32 and index <= 39)
	{
		x = (index - 32) * 30;
		y = 120;
	}
	else if (index >= 40 and index <= 47)
	{
		x = (index - 40) * 30;
		y = 150;
	}
	else if (index >= 48 and index <= 55)
	{
		x = (index - 48) * 30;
		y = 180;
	}
	pos.x = game_window_info.left + 623 + x;
	pos.y = game_window_info.top + 301 + y;
	return pos;
}

int Knapsac::get_goods_count()
{
	DWORD StartAddress = GetKnapsacStartAddress();
	GOODS_INFO _GoodsInfo;
	DWORD GoodsAddress;
	int count = 0;
	for (size_t i = 0; i < 55; i++)
	{
		GoodsAddress = read<int>(StartAddress + i * 4);
		if (GoodsAddress == 0 || GoodsAddress == NULL)continue;
		_GoodsInfo = GetGoodsInfo(GoodsAddress);
		_GoodsInfo.index = i + 9;
		if (
			(_GoodsInfo.name.find(L"传承", 0) == -1) &&
			(_GoodsInfo.name.find(L"周年", 0) == -1) &&
			(_GoodsInfo.name.find(L"活动", 0) == -1)
			)
		{
			if (
				_GoodsInfo.level == 0 ||
				_GoodsInfo.level == 1 ||
				_GoodsInfo.level == 2
				)
			{
				count++;
			}
		}
	}
	return count;
}

void Knapsac::按键卖物()
{
	if(get_goods_count() < 15){
		return;
	}
	DWORD StartAddress = GetKnapsacStartAddress();
	GOODS_INFO _GoodsInfo;
	DWORD GoodsAddress;
	Pos goods_pos;
	
	for (size_t i = 0; i < 55; i++)
	{
		GoodsAddress = read<int>(StartAddress + i * 4);
		if (GoodsAddress == 0 || GoodsAddress == NULL)continue;
		_GoodsInfo = GetGoodsInfo(GoodsAddress);
		_GoodsInfo.index = i;
		if (
			(_GoodsInfo.name.find(L"传承", 0) == -1) &&
			(_GoodsInfo.name.find(L"周年", 0) == -1) &&
			(_GoodsInfo.name.find(L"活动", 0) == -1)
			)
		{
			if (
				_GoodsInfo.level == 0 ||
				_GoodsInfo.level == 1 ||
				_GoodsInfo.level == 2
				)
			{
				if (read<int>(__鼠标状态) != 5)
				{
					setMouseCoord(game_window_info.left + 192, game_window_info.top + 518);
					mouseClick();
					Sleep(500);
					setMouseCoord(game_window_info.left + 630, game_window_info.top + 278);
					mouseClick();
				}
				goods_pos = get_goods_pos_by_index(_GoodsInfo.index);
				setMouseCoord(goods_pos.x, goods_pos.y);
				mouseDoubleClick(200);
			}
		}
	}
}