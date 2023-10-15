//
// Created by 江澎涌 on 2023/1/24.
//

#include <string>

#include "lua.hpp"
#include "Lua作为配置文件/config_parser.h"
#include "调用Lua函数/调用Lua函数.h"
#include "通用调用lua函数/call_va.h"

int main() {
    printf("================= 获取、设置 lua 值 =================\n");
    loadConfig();
    printf("==================================\n");

    printf("\n================= 调用 lua 函数 =================\n");
    cppCallLuaFunction();
    printf("==================================\n");

    printf("\n================= 通用调用 lua 函数 =================\n");
    std::string fname = PROJECT_PATH + "/5、C++调用Lua代码/调用Lua函数/调用Lua函数.lua";
    lua_State *L = luaL_newstate();
    // 需要使用 lua_openlibs 进行开启库，否则 lua 中无法使用
    luaL_openlibs(L);
    if (luaL_loadfile(L, fname.c_str()) || lua_pcall(L, 0, 0, 0)) {
        error(L, "can't run config. file: %s", lua_tostring(L, -1));
    }
    double z;
    call_va(L, "luaFunction", "dd>d", 2.0, 34.0, &z);
    printf("f: %f\n", z);
    lua_close(L);
    printf("==================================\n");

    return 0;
}
