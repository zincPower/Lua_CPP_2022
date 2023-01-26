//
// Created by 江澎涌 on 2023/1/24.
//

#include <string>

#include "lua.hpp"
#include "config_parser.h"
#include "调用Lua函数/调用Lua函数.h"
#include "通用调用lua函数/call_va.h"

int main() {
    printf("----------------- 获取、设置 lua 值 -----------------\n");
    std::string filename = "/Users/jiangpengyong/Desktop/code/Lua/Lua_CPP_2022/2、application_extend/config.lua";
    lua_State *L = luaL_newstate();
    // 需要使用 lua_openlibs 进行开启库，否则 lua 中无法使用
    luaL_openlibs(L);
    load(L, filename.c_str());
    lua_close(L);
    printf("----------------------------------\n");

    printf("----------------- 调用 lua 函数 -----------------\n");
    std::string fname2 = "/Users/jiangpengyong/Desktop/code/Lua/Lua_CPP_2022/2、application_extend/调用Lua函数/调用Lua函数.lua";
    lua_State *L2 = luaL_newstate();
    // 需要使用 lua_openlibs 进行开启库，否则 lua 中无法使用
    luaL_openlibs(L2);
    loadForFunction(L2, fname2.c_str());
    printf("f: %f\n", f(L2, 2, 34));
    lua_close(L2);
    printf("----------------------------------\n");

    printf("----------------- 通用调用 lua 函数 -----------------\n");
    std::string fname3 = "/Users/jiangpengyong/Desktop/code/Lua/Lua_CPP_2022/2、application_extend/调用Lua函数/调用Lua函数.lua";
    lua_State *L3 = luaL_newstate();
    // 需要使用 lua_openlibs 进行开启库，否则 lua 中无法使用
    luaL_openlibs(L3);
    loadForFunction(L3, fname3.c_str());
    double z;
    call_va(L3, "f", "dd>d", 2.0, 34.0, &z);
    printf("f: %f\n", z);
    lua_close(L3);

    return 0;
}
