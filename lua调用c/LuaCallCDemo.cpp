//
// Created by 江澎涌 on 2022/5/1.
//

#include <string>
#include "lua.hpp"
#include "lua调用c.cpp"
#include "../extend/ConfigParser.h"
#include "../utils/lua_error.h"

void luaCallCDemo() {
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);

    lua_pushcfunction(L, l_dir);
    lua_setglobal(L, "dir");

    std::string fname = "/Users/jiangpengyong/Desktop/code/CPP/CPP2022/lua/lua调用c/luaCallC.lua";
    if (luaL_loadfile(L, fname.c_str()) || lua_pcall(L, 0, 0, 0)) {
        error(L, "can't run config. file: %s", lua_tostring(L, -1));
    }
}
