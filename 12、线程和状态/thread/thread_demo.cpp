//
// Created by 江澎涌 on 2022/5/10.
//

#include "thread_demo.h"

// 将协程的返回值转换为字符串
std::string getResumeState(int state) {
    switch (state) {
        case LUA_OK:
            return "LUA_OK";
        case LUA_YIELD:
            return "LUA_YIELD";
        case LUA_ERRRUN:
            return "LUA_ERRRUN";
        case LUA_ERRSYNTAX:
            return "LUA_ERRSYNTAX";
        case LUA_ERRMEM:
            return "LUA_ERRMEM";
        case LUA_ERRERR:
            return "LUA_ERRERR";
        default:
            return "Unknown";
    }
}

// 延续函数
int cfooK(lua_State *L, int status, lua_KContext ctx) {
    printf("恢复协程体后，调用 C++ 延续函数\n");
    return 1;
}

// 暴露给 lua 调用的 C++ 函数
int primCFunction(lua_State *L) {
    lua_pushstring(L, "调用 C++ 函数，会进行挂起");

    // 设置了 cfooK 作为延续函数，恢复协程之后，会进入 cfook 这一延续函数
    lua_yieldk(L, 1, 0, &cfooK);

    // 这两种的使用结果是一样的，都不舍之延续函数
//    lua_yieldk(L, 1, 0, nullptr);
//    lua_yield(L, 1);

    // 不会被执行，恢复之后会运行延续函数，不会执行后续的语句
    printf("挂起之后的输（不会被输出）");

    return 1;
}

void createThread() {
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);

    // 用 L 创建一个新的线程
    // L 和 L1 各自有一个栈
    // L 的栈顶是 L1 的 thread
    // L1 的栈是空
    lua_State *L1 = lua_newthread(L);

    printf("主线程 L 栈深度：%d\n", lua_gettop(L));
    printf("------------ 主线程 L 栈内容：------------\n");
    stackDump(L);

    printf("新线程 L1 栈深度：%d\n", lua_gettop(L1));
    printf("------------ 新线程 L1 栈内容：------------\n");
    stackDump(L1);

    // 向 L 的注册表插入数据，从 L1 中获取数据
    printf("L 注册表插入数据，L1 获取对应数据\n");
    const char *key = "thread-demo-name";
    lua_pushstring(L, "江澎涌");
    lua_setfield(L, LUA_REGISTRYINDEX, key);
    lua_getfield(L1, LUA_REGISTRYINDEX, key);
    stackDump(L1);
    lua_pop(L1, 1);

    // 向 L 插入全局数据，从 L1 获取全局数据
    printf("L 插入全局数据，L1 获取全局数据\n");
    lua_pushstring(L, "29");
    lua_setglobal(L, "age");
    lua_getglobal(L1, "age");
    stackDump(L1);
    lua_pop(L1, 1);

    lua_close(L);
}

void useThread() {
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);
    lua_State *L1 = lua_newthread(L);

    lua_pushcfunction(L1, primCFunction);
    lua_setglobal(L1, "primCFunction");

    std::string fname = PROJECT_PATH + "/12、线程和状态/thread/coroutine.lua";
    if (luaL_loadfile(L1, fname.c_str()) || lua_pcall(L1, 0, 0, 0)) {
        printf("can't run config. file: %s", lua_tostring(L1, -1));
    }

    printf("LUA_YIELD=%d\n", LUA_YIELD);
    printf("LUA_OK=%d\n", LUA_OK);

    // 返回值个数
    int result = 0;
    // 获取 L1 中的 lua 文件的函数 foo1
    lua_getglobal(L1, "foo1");
    // 压入 integer
    lua_pushinteger(L1, 20);

    printf("第一次调用，Lua 脚本中挂起：\n");
    auto state = lua_resume(L1, L, 1, &result);
    printf("协程状态: %s\n", getResumeState(state).c_str());
    printf("L1 栈深度: %d\n", lua_gettop(L1));
    printf("返回值个数: %d\n", result);
    printf("------------ L1 栈内容：------------\n");
    stackDump(L1);

    printf("第二次调用，Lua 调用 C++ ，C++ 中挂起：\n");
    state = lua_resume(L1, L, 0, &result);
    printf("协程状态: %s\n", getResumeState(state).c_str());
    printf("L1 栈深度: %d\n", lua_gettop(L1));
    printf("返回值个数: %d\n", result);
    printf("------------ L1 栈内容：------------\n");
    stackDump(L1);

    printf("第三次调用，运行 C++ 延续函数，协程体结束：：\n");
    state = lua_resume(L1, L, 0, &result);
    printf("协程状态: %s\n", getResumeState(state).c_str());
    printf("L1 栈深度: %d\n", lua_gettop(L1));
    printf("返回值个数: %d\n", result);
    printf("------------ L1 栈内容：------------\n");
    stackDump(L1);

    lua_close(L);
}

void copyStackElement() {
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);
    lua_State *L1 = lua_newthread(L);

    // 新线程中执行 Lua 脚本
    std::string fname = PROJECT_PATH + "/12、线程和状态/thread/copy_stack.lua";
    if (luaL_loadfile(L1, fname.c_str()) || lua_pcall(L1, 0, 0, 0)) {
        printf("can't run config. file: %s", lua_tostring(L1, -1));
    }

    // 获取 L1 中的 lua 文件的函数 foo
    lua_getglobal(L1, "foo");
    // 压入 integer
    lua_pushinteger(L1, 5);
    // 调用函数 foo(5) -> "江澎涌", 25
    lua_call(L1, 1, 2);

    printf("------------ 主线程 L 栈内容（xmove 前）：--------------\n");
    stackDump(L);

    printf("------------ 新线程 L1 栈内容（xmove 前）：--------------\n");
    stackDump(L1);
    // 从 L1 中拷贝 1 个元素到 L 中（会将 L1 元素弹出）
    lua_xmove(L1, L, 2);

    printf("------------ 主线程 L 栈内容（xmove 后）：--------------\n");
    stackDump(L);

    printf("------------ 新线程 L1 栈内容（xmove 后）：--------------\n");
    stackDump(L1);
}

void threadDemo() {
    printf("=================== 创建新线程 ===================\n");
    createThread();

    printf("=================== 协程 ===================\n");
    useThread();

    printf("=================== 线程栈元素拷贝 ===================\n");
    copyStackElement();
}