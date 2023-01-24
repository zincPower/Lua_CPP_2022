//
// Created by 江澎涌 on 2022/5/1.
//

#include <string>
#include "库.h"
#include "../1、C_API/Error.h"

extern void libDemo() {
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);
//    luaopen_mylib(L);

    std::string fname = "/Users/jiangpengyong/Desktop/code/CPP/CPP2022/lua/库/库.lua";
    if (luaL_loadfile(L, fname.c_str()) || lua_pcall(L, 0, 0, 0)) {
        error(L, "can't run config. file: %s", lua_tostring(L, -1));
    }

    lua_close(L);
}