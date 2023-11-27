//
// Created by 江澎涌 on 2022/5/8.
//

#include "注册表.h"

// 自定义 key 值
void customKeyRegistryDemo() {
    lua_State *L = luaL_newstate();

    const char *key = "3D-Graphics-xxx";

    lua_pushstring(L, "江澎涌");
    lua_setfield(L, LUA_REGISTRYINDEX, key);

    lua_getfield(L, LUA_REGISTRYINDEX, key);
    printf("content: %s\n", lua_tostring(L, -1));

    lua_close(L);
}

// 引用系统生成 key
void refRegistryDemo() {
    lua_State *L = luaL_newstate();

    lua_pushstring(L, "jiang pengyong");
    // 将栈顶弹出然后设置值
    int ref = luaL_ref(L, LUA_REGISTRYINDEX);
    printf("引用系统创建唯一的键: %d\n", ref);

    // 获取值
    lua_rawgeti(L, LUA_REGISTRYINDEX, ref);
    printf("name: %s\n", lua_tostring(L, -1));
    lua_pop(L, 1);
    // 释放引用
    luaL_unref(L, LUA_REGISTRYINDEX, ref);

    // 释放后在生成，又使用了同一个引用
    lua_pushstring(L, "jiang pengyong!!!\n");
    int ref1 = luaL_ref(L, LUA_REGISTRYINDEX);
    printf("重新申请一个 key : %d\n", ref1);

    lua_pushnil(L);
    int ref2 = luaL_ref(L, LUA_REGISTRYINDEX);
    printf("申请内容为 nil 的 key : %d\n", ref2);

    printf("\n");
    printf("调用了 `lua_rawgeti(L, LUA_REGISTRYINDEX, LUA_REFNIL);` 会压入一个 nil\n");
    // 会导致压入一个 nil
    lua_rawgeti(L, LUA_REGISTRYINDEX, LUA_REFNIL);
    stackDump(L);
    lua_pop(L, 1);

    printf("获取 LUA_RIDX_GLOBALS 值\n");
    lua_rawgeti(L, LUA_REGISTRYINDEX, LUA_RIDX_GLOBALS);
    stackDump(L);
    lua_pop(L, 1);

    printf("获取 LUA_RIDX_MAINTHREAD 值\n");
    lua_rawgeti(L, LUA_REGISTRYINDEX, LUA_RIDX_MAINTHREAD);
    stackDump(L);
    lua_pop(L, 1);

    lua_close(L);
}

// 用静态属性 Key 地址作为键
void cStaticValueRegistryDemo() {
    lua_State *L = luaL_newstate();

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
    // 第二种做法
    lua_rawgetp(L, LUA_REGISTRYINDEX, (void *) &Key);

    printf("注册表[(void *) &Key] = %s\n", lua_tostring(L, -1));

    lua_close(L);
}
