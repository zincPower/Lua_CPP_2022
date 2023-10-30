//
// Created by 江澎涌 on 2022/5/8.
//

#include "注册表.h"
#include "lua.hpp"

// 用静态属性 Key 地址作为键
void registerTable(lua_State *L) {

    static char Key = 'k';

    // 保存字符串
    // 注册表[(void *) &Key] = "江澎涌"
    // 第一种做法
//    lua_pushlightuserdata(L, (void *) &Key);
//    lua_pushstring(L, "江澎涌");
//    lua_settable(L, LUA_REGISTRYINDEX);
    // 第二种做法
    lua_pushstring(L, "江澎涌");
    lua_rawsetp(L, LUA_REGISTRYINDEX, (void *) &Key);

    // 获取字符串
    // 第一种做法
//    lua_pushlightuserdata(L, (void *) &Key);
//    lua_gettable(L, LUA_REGISTRYINDEX);
//    printf("content1: %s", lua_tostring(L, -1));
    lua_rawgetp(L, LUA_REGISTRYINDEX, (void *) &Key);
    printf("content: %s\n", lua_tostring(L, -1));

}

void registerTableDemo() {

    lua_State *L = luaL_newstate();
    registerTable(L);
    lua_close(L);

}

void refDemo() {

    lua_State *L = luaL_newstate();
    luaL_openlibs(L);

    // 1、为 "jiang pengyong" 创建唯一的键
    lua_pushstring(L, "jiang pengyong");
    // 将栈顶弹出然后设置值
    int ref = luaL_ref(L, LUA_REGISTRYINDEX);
    printf("ref: %d\n", ref);
    // 3、获取值
    lua_rawgeti(L, LUA_REGISTRYINDEX, ref);
    printf("name: %s\n", lua_tostring(L, -1));
    // 4、释放引用
    luaL_unref(L, LUA_REGISTRYINDEX, ref);

    // 释放后在生成，又使用了同一个引用
    lua_pushstring(L, "jiang pengyong!!!\n");
    int ref1 = luaL_ref(L, LUA_REGISTRYINDEX);
    printf("ref: %d\n", ref1);

    lua_close(L);

}