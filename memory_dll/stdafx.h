// stdafx.h: 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 项目特定的包含文件
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 从 Windows 头文件中排除极少使用的内容
// Windows 头文件
#include <windows.h>
#include <windowsx.h>
#include <vector>
#include <string>
#include <map>
#include <ctime>
#include <process.h>
#include <direct.h>
#include <tchar.h>

// 在此处引用程序需要的其他标头
#include "KeyCall.h"
#include "global_consts.h"
#include "global_struct.hpp"
#include "global_var.h"
#include "utils.hpp"
#include "memory.hpp"
#include "game_send_packet.hpp"
#include "game_calls.hpp"
#include "game_utils.hpp"
#include "game_knapsac.hpp"


#include "game_role.hpp"
#include "game_task.hpp"