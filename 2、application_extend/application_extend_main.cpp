//
// Created by 江澎涌 on 2023/1/24.
//

#include <string>

#include "lua.hpp"
#include "config_parser.h"

int main() {
    std::string filename = "/Users/jiangpengyong/Desktop/code/Lua/Lua_CPP_2022/2、application_extend/config.lua";

    lua_State *L = luaL_newstate();
    // 需要使用 lua_openlibs 进行开启库，否则 lua 中无法使用
    luaL_openlibs(L);
    load(L, filename.c_str());

    lua_close(L);

    return 0;
}
