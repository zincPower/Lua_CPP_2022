//
// Created by 江澎涌 on 2022/5/1.
//

#include "CoroutineDemo.h"

void coroutineDemo() {
    std::string fileName = "/Users/jiangpengyong/Desktop/code/CPP/CPP2022/lua/协程/coroutine.lua";
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);
    if (luaL_loadfile(L, fileName.c_str()) || lua_pcall(L, 0, 0, 0)) {
        error(L, "can't run file. file: %s", lua_tostring(L, -1));
    }
}

int finishPCall(lua_State *L, int status, intptr_t ctx) {
    (void) ctx;
    status = (status != LUA_OK && status != LUA_YIELD);
    lua_pushboolean(L, (status == 0));
    lua_insert(L, 1);
    return lua_gettop(L);
}

//int luaB_pcall(lua_State *L) {
//    int status;
//    luaL_checkany(L, 1);
//    status = lua_pcall(L, lua_gettop(L) - 1, LUA_MULTRET, 0);
//    lua_pushboolean(L, (status == LUA_OK));
//    lua_insert(L, 1);
//    return lua_gettop(L);
//}

int luaB_pcall(lua_State *L) {
    int status;
    luaL_checkany(L, 1);
    status = lua_pcallk(L, lua_gettop(L) - 1, LUA_MULTRET, 0, 0, finishPCall);
    return finishPCall(L, status, 0);
}

