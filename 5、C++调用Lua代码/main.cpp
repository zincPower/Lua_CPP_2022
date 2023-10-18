//
// Created by 江澎涌 on 2023/1/24.
//

#include "lua.hpp"
#include "调用Lua函数/调用Lua函数.h"
#include "通用调用lua函数/call_va.h"
#include "Lua作为配置文件/根据环境变量获取值/config_use_env.h"
#include "Lua作为配置文件/配置中使用表/config_use_table.h"

int main() {
    printf("================= 获取、设置 lua 值（使用环境变量） =================\n");
    loadConfigUseEnv();
    printf("==================================\n\n");
    printf("================= 获取、设置 lua 值（使用表） =================\n");
    loadConfigUseTable();
    printf("==================================\n\n");

    printf("================= 调用 lua 函数 =================\n");
    cppCallLuaFunction();
    printf("==================================\n\n");

    printf("================= 通用调用 lua 函数 =================\n");
    commonCallLuaDemo();
    printf("==================================\n\n");

    return 0;
}
