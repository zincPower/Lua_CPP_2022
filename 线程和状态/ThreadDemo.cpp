//
// Created by 江澎涌 on 2022/5/10.
//

#include "ThreadDemo.h"
#include "lua.hpp"
#include "../utils/lua_error.h"
#include <iostream>

void threadDemo() {

    lua_State *L = luaL_newstate();
    luaL_openlibs(L);

    lua_State *L1 = lua_newthread(L);

    std::string fname = "/Users/jiangpengyong/Desktop/code/CPP/CPP2022/lua/线程和状态/thread.lua";
    if (luaL_loadfile(L1, fname.c_str()) || lua_pcall(L1, 0, 0, 0)) {
        error(L, "can't run config. file: %s", lua_tostring(L1, -1));
    }

    int result = 0;
    lua_getglobal(L1, "foo1");
    lua_pushinteger(L1, 20);
    // nres 是结果个数
    printf("lua_resume: %d\n", lua_resume(L1, L, 1, &result));
    printf("LUA_YIELD: %d\n", LUA_YIELD);
    printf("result: %d\n", result);
    printf("top: %d\n", lua_gettop(L1));
    printf("num1: %lld\n", lua_tointeger(L1, 1));
    printf("num2: %lld\n", lua_tointeger(L1, 2));

    printf("lua_resume: %d\n", lua_resume(L1, L, 0, &result));
    printf("LUA_OK: %d\n", LUA_OK);
    printf("result: %d\n", result);
    printf("top: %d\n", lua_gettop(L1));
    printf("num: %lld\n", lua_tointeger(L1, 1));

    lua_close(L);

}