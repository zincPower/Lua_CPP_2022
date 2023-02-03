//
// Created by 江澎涌 on 2022/5/10.
//

#include <iostream>

#include "ThreadDemo.h"
#include "lua.hpp"

#include "../utils/lua_error.h"
#include "../utils/stack_dump.h"

void threadDemo() {

    lua_State *L = luaL_newstate();
    luaL_openlibs(L);

    // 用 L 创建一个新的线程
    // L 和 L1 两者内部都是引用同一个 lua_State
    // L 和 L1 各自有一个栈
    // L 的栈顶是 L1 的 thread
    // L1 的栈是空
    lua_State *L1 = lua_newthread(L);

    printf("---------------- 线程内部栈深度 ----------------\n");
    printf("L1 栈内容长度：%d\n", lua_gettop(L1));
    printf("L 栈内容长度：%d - %s\n", lua_gettop(L), luaL_typename(L, -1));

    std::string fname = "/Users/jiangpengyong/Desktop/code/Lua/Lua_CPP_2022/8、线程和状态/thread.lua";
    if (luaL_loadfile(L1, fname.c_str()) || lua_pcall(L1, 0, 0, 0)) {
        error(L, "can't run config. file: %s", lua_tostring(L1, -1));
    }

    printf("---------------- 线程栈元素拷贝 ----------------\n");
    // 获取 L1 中的 lua 文件的函数 foo1
    lua_getglobal(L1, "foo2");
    // 压入 integer
    lua_pushinteger(L1, 5);
    // 调用函数 foo2(5) -> 25
    lua_call(L1, 1, 1);
    printf("L1 栈元素(xmove 前)：\n");
    stackDump(L1);
    // 从 L1 中拷贝 1 个元素到 L 中（会将 L1 元素弹出）
    lua_xmove(L1, L, 1);
    printf("L1 栈元素(xmove 后)：\n");
    stackDump(L1);
    printf("L 栈元素：\n");
    stackDump(L);

    printf("---------------- 协程 ----------------\n");
    int result = 0;
    // 获取 L1 中的 lua 文件的函数 foo1
    lua_getglobal(L1, "foo1");
    // 压入 integer
    lua_pushinteger(L1, 20);
    printf("第一次调用：\n");
    // nres 是结果个数
    printf("lua_resume: %d\n", lua_resume(L1, L, 1, &result));
    printf("LUA_YIELD: %d\n", LUA_YIELD);
    printf("result: %d\n", result);
    printf("top: %d\n", lua_gettop(L1));
    printf("yield 返回 num1: %lld\n", lua_tointeger(L1, 1));
    printf("yield 返回 num2: %lld\n", lua_tointeger(L1, 2));

    printf("第二次调用：\n");
    printf("lua_resume: %d\n", lua_resume(L1, L, 0, &result));
    printf("LUA_OK: %d\n", LUA_OK);
    printf("result: %d\n", result);
    printf("top: %d\n", lua_gettop(L1));
    printf("num: %lld\n", lua_tointeger(L1, 1));

    lua_close(L);

}