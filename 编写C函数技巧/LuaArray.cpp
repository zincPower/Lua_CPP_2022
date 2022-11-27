//
// Created by 江澎涌 on 2022/5/6.
//

#include "LuaArray.h"
#include "lua.hpp"

void luaArrayDemo() {

    lua_State *L = luaL_newstate();

    // 创建并押入一个新表
    lua_newtable(L);
    // 添加至数组的操作方式
    // 第一种：
//    lua_pushstring(L, "江澎涌!");
//    lua_seti(L, -2, 1);
    // 第二种：
    // 栈底 ----> 栈顶
    // table - key - value
    // 使用完后，key - value 会被弹出
    lua_pushnumber(L, 1);
    lua_pushstring(L, "江澎涌!");
    lua_settable(L, -3);

    // 从数组中获取值方式：
    // 第一种
    lua_geti(L, -1, 1);
    printf("%s\n", lua_tostring(L, -1));
    // 不用弹出，lua_tostring 已经将值弹出
//    lua_pop(L, -1);
    // 第二种
//    lua_pushnumber(L, 1);
//    lua_gettable(L, -2);
//    printf("%s\n", lua_tostring(L, -1));
    // 不用弹出，lua_tostring 已经将值弹出
//    lua_pop(L, -1);

    long long n = luaL_len(L, 1);
    printf("lua table length: %lld", n);

    lua_close(L);
}

static int showName(lua_State *L) {
    printf("江澎涌!!! %s\n", lua_tostring(L, 1));
    return 100;
}

int l_map(lua_State *L) {
    long long i, n;

    luaL_checktype(L, 1, LUA_TTABLE);
    luaL_checktype(L, 2, LUA_TFUNCTION);

    n = luaL_len(L, 1);
    printf("lua table length: %lld\n", n);

    for (i = 1; i <= n; i++) {
        // 将函数压到栈顶
        lua_pushvalue(L, 2);
        // 获取第一个元素（为 table ）的第 i 个元素，放置栈顶
        lua_geti(L, 1, i);
        // 调用函数，传入一个参数（栈顶），返回一个
        lua_call(L, 1, 1);
        // 设置第一个元素（为 table ）的值，下标为 i ，栈顶
        lua_seti(L, 1, i);
    }

    return 0;
}

void luaMapFunctionDemo() {

    lua_State *L = luaL_newstate();

    lua_newtable(L);
    lua_pushcfunction(L, showName);

    // 添加元素 t[1] = 江澎涌！!!!!ha
    lua_pushnumber(L, 1);
    lua_pushstring(L, "江澎涌!!!!!ha");
    lua_settable(L, 1);

    l_map(L);

    long long n = luaL_len(L, 1);
    printf("lua table length: %lld\n", n);

    lua_close(L);
}
