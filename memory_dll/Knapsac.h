#pragma once
class Knapsac
{
public:
	Knapsac();
	~Knapsac();
	DWORD GetKnapsacAddress();
	DWORD GetKnapsacStartAddress();
	GOODS_INFO GetGoodsInfo(int GoodsAddress);
	int GetGoodsIndexByGoodsName(std::wstring GoodsName);
	int SaleGoods();
	void OutputGoodsInfo();
	Pos get_goods_pos_by_index(int index);
	int get_goods_count();
	void °´¼üÂôÎï();
};

