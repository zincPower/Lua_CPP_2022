//
// Created by 江澎涌 on 2022/4/28.
//

#include "secure_fun.h"
#include "../utils/stack_dump.h"

// 错误处理
int errorTraceback(lua_State *L) {
    // 获取错误信息
    const char *msg = lua_tostring(L, -1);

    if (!msg && !lua_isnoneornil(L, -1)) {
        if (!luaL_callmeta(L, -1, "__tostring")) {
            lua_pushliteral(L, "(no error message)");
        }
    }

    printf("\n");
    printf("-------- traceback 中的 stack 数据（未增加错误信息） --------\n");
    stackDump(L);

    msg = lua_tostring(L, -1);

    // 获取函数调用堆栈信息的错误回溯信息
    luaL_traceback(L, L, msg, 1);

    printf("-------- traceback 中的 stack 数据（增加错误信息） --------\n");
    stackDump(L);

    return 1;
}

// 安全调用 Lua 函数
int safeCallLua(lua_State *L, int narg, int nres) {
    // 计算新压入多少个参数
    int base = lua_gettop(L) - narg;
    // 压入异常处理函数
    lua_pushcfunction(L, errorTraceback);
    // 将异常处理函数压入到 base 下标的位置
    lua_insert(L, base);
    // 调用 Lua 函数
    int status = lua_pcall(L, narg, nres, base);
    // 移除异常处理函数
    lua_remove(L, base);
    return status;
}

void secureFoo() {
    lua_State *L = luaL_newstate();

    // 加载函数库，否则
    luaL_openlibs(L);

    lua_pushinteger(L, 100);
    luaL_loadfile(L, "/Users/jiangpengyong/Desktop/code/Lua/Lua_CPP_2022/3、C++调用Lua的错误处理和内存分配/C运行的Lua文件.lua");
    lua_pushstring(L, "jiang peng yong");
    lua_pushinteger(L, 29);

    printf("-------- 未运行 Lua 的栈 --------\n");
    stackDump(L);

    printf("-------- lua_pcall 调用 --------\n");
    auto result = safeCallLua(L, 2, 1);

    printf("\n");
    printf("-------- 运行完 Lua 的栈 --------\n");
    stackDump(L);

    if (result == 0) {
        auto resultContent = lua_tostring(L, -1);
        printf("lua result: 运行成功，结果：%s", resultContent);
    } else {
        auto error = lua_tostring(L, -1);
        printf("----- lua result: 运行失败，错误堆栈 -----\n%s", error);
    }

    lua_close(L);
}
