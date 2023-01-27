//
// Created by 江澎涌 on 2022/5/1.
//

#include <string>
#include "lua.hpp"
#include "lua_call_c.cpp"
#include "../utils/lua_error.h"

int main() {
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);

    // 压入 l_sin 函数
    lua_pushcfunction(L, l_sin);
    // 将压入的函数 l_sin 设置为 sin 变量
    lua_setglobal(L, "sin");

    // 压入 l_dir 函数
    lua_pushcfunction(L, l_dir);
    // 将压入的函数 l_dir 设置为 dir 变量
    lua_setglobal(L, "dir");

    std::string fname = "/Users/jiangpengyong/Desktop/code/Lua/Lua_CPP_2022/3、lua_call_c/lua_call_c.lua";
    if (luaL_loadfile(L, fname.c_str()) || lua_pcall(L, 0, 0, 0)) {
        error(L, "can't run config. file: %s", lua_tostring(L, -1));
    }
}
