//
// Created by 江澎涌 on 2023/1/26.
//
#include <string>
#include "lua.hpp"
#include "../utils/lua_error.h"

int main() {
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);

    std::string fname = "/Users/jiangpengyong/Desktop/code/Lua/Lua_CPP_2022/4、lua_call_c_lib/lua加载c库.lua";
    if (luaL_loadfile(L, fname.c_str()) || lua_pcall(L, 0, 0, 0)) {
        error(L, "can't run config. file: %s", lua_tostring(L, -1));
    }

    lua_close(L);

    return 1;
}
