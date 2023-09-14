//
// Created by 江澎涌 on 2022/4/28.
//

#include "C++处理Lua异常.h"

using namespace LuaExt;

/**
 * C++ 运行 Lua ，错误处理，提供一个保护区
 */
void cppHandleLuaError() {
    lua_State *L = luaL_newstate();

    // 加载函数库，否则加载的 Lua 无法使用内置库
    luaL_openlibs(L);

    auto luaFilePath = PROJECT_PATH + "/3、C++调用Lua的错误处理和内存分配/C++调用Lua异常处理/C运行的Lua文件.lua";

    // 开启这段代码可以验证错误处理函数的栈是新的
    lua_pushinteger(L, 100);
    // 加载 Lua 脚本
    auto loadLuaResult = luaL_loadfile(L, luaFilePath.c_str());
    if (loadLuaResult) {
        printf("加载 Lua 文件失败. file: %s\n", lua_tostring(L, -1));
        return;
    }

    // 压入参数，传递给 Lua 脚本
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
        printf("lua result: 运行成功，结果：%s\n", resultContent);
    } else {
        auto error = lua_tostring(L, -1);
        printf("----- lua result: 运行失败，错误堆栈 -----\n%s\n", error);
    }

    lua_close(L);
}
