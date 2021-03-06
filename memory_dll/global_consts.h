#pragma once

#define TIMER_MIN 100
#define MY_MESSAGE_ID 10024 //自定义消息ID

#define __人物基址 0x057A7B88
#define __当前疲劳 0x057A7E28
#define __最大疲劳 0x057A7E30
#define __商店基址 0x05694370
#define __对话基址 0x057D6D44
#define __释放CALL 0x023AC430

#define __变量入栈CALL 0x08F1230
#define __移动CALL 0x01E3EC80
#define __移动偏移_1 0x69C //7度_获取
#define __移动偏移_2 0x6B0 //7度_获取

#define __发包基址 0x057DE43C
#define __缓冲CALL 0x03745C20
#define __密包CALL 0x03745D30
#define __发包CALL 0x03747460
#define __接受CALL 0x01EF8B10
#define __完成CALL 0x01EF8A10
#define __提交CALL 0x01EF8A90
#define __任务基址 0x056943A8
#define __房间编号 0x05694368

#define __过图CALL 0x01A63C00
#define __跳过CALL 0x01C8C4E0
#define __游戏状态 0x05589464
#define __角色等级 0x05676C34 

#define __召唤参数 0x056BB0B0
#define __职业名称 0x05676C18



#define __解密基址 0x057E9580
#define __背包基址 0x05694374
#define __区域CALL 0x0369D5A0
#define __区域参数 0x057DC6AC
#define __时间基址 0x020A028 
#define __技能CALL 0x0250BBD0

#define __怪物CALL 0x025D1D50

#define __角色状态 0x057A7B88 //0不动 1 动 2放技能中
#define __角色坐标 0x05694DAC//
#define __遍历取值 0x05693C60//
#define __任务完成ECX 0x0
#define __分解CALL 0x0
#define __鼠标状态 0x05837318
#define __副本ID 0x0556B888
#define __副本难度 0x05693C60

//#define  __攻击阵营  55938496
//#define  __技能坐标  40079936
//#define  __目录基址  107784148
//#define  __路径基址  90331632
//#define  __副本信息  90331612
//#define  __路径CALL  59503072
//#define  __加载CALL  57738400
//#define  __分割CALL  58318400


#define __喇叭公告 0x029F9E70

#define __副本难度偏移 0x20c
#define __角色状态偏移 0x338c
#define __地图偏移 0xC8
#define __首地址 0xC0
#define __尾地址 0xC4

#define __A星_当前房间X 0xcc
#define __A星_当前房间Y 0xd0

#define __阵营偏移 0x828
#define __类型偏移 0xA4
#define __血量偏移 0x3B04
#define __坐标偏移 0xb8
#define __人物坐标偏移 0x1D0

#define __名称偏移 0x404
#define __代码偏移 0x400
//#define __地图名称偏移 0x1A0
//#define __地图编号偏移 0x19c
#define __门型偏移 0xc8
#define __当前房间X 0xBCC
#define __当前房间Y 0xBD0
#define __BOSS房间X 0xC70
#define __BOSS房间Y 0xC78
#define __深渊房间X 0xB80
#define __深渊房间Y 0xB88
#define __宽高偏移 0x2AC
#define __数组偏移 0x2C0
#define __区域偏移 0xcbc4
#define __开门偏移 0x118
#define __角色下标偏移 0x108
#define __大区域偏移 0x1E4
#define __小区域偏移 0x1Ec
#define __角色数量偏移2 0x3c0
#define __当前角色数量 0xa70
#define __最大角色数量 0xa78
#define __坐标结构偏移1 0x8c
#define __坐标结构偏移2 0x1744
#define __地面物品名称偏移 0x16c4



#define 搬砖 1
#define 剧情 2
#define 深渊 3
#define 黄龙 4
#define 练习 5

// NPC编号
#define 格蓝迪门口 0
#define 克伦特 1
#define 歌兰蒂斯 2
#define 月光酒馆 3

// 副本编号
#define 格蓝迪 104

//键码
#define VK_0  48
#define VK_1  49
#define VK_2  50
#define VK_3  51
#define VK_4  52
#define VK_5  53
#define VK_6  54
#define VK_7  55
#define VK_8  56
#define VK_9  57
#define VK_A  65
#define VK_B  66
#define VK_C  67
#define VK_D  68
#define VK_E  69
#define VK_F  70
#define VK_G  71
#define VK_H  72
#define VK_I  73
#define VK_J  74
#define VK_K  75
#define VK_L  76
#define VK_M  77
#define VK_N  78
#define VK_O  79
#define VK_P  80
#define VK_Q  81
#define VK_R  82
#define VK_S  83
#define VK_T  84
#define VK_U  85
#define VK_V  86
#define VK_W  87
#define VK_X  88
#define VK_Y  89
#define VK_Z  90


#define Code_成长之泉水 490007518
#define Code_肉块 10158893
#define Code_鸡腿 10158901



