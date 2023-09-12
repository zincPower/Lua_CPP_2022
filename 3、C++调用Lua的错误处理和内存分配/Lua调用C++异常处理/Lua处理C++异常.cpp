//
// Created by 江澎涌 on 2022/5/1.
//

#include "Lua处理C++异常.h"

int cppError(lua_State *L) {
    // 第一种方式，lua_error 会将栈顶的元素作为 Lua 的错误信息
    lua_pushstring(L, "C++ throw error. 来自 lua_error");
    lua_error(L);

    // 第二种方式，luaL_error 会将字符串作为错误信息
//    luaL_error(L, "C++ throw error. 来自 luaL_error");
    return 0;
}

void luaHandleCppError() {
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);

    // 压入 cppError 函数
    lua_pushcfunction(L, cppError);
    // 将压入的函数 cppError 设置为 cppError 变量
    lua_setglobal(L, "cppError");

    std::string fname = PROJECT_PATH + "/3、C++调用Lua的错误处理和内存分配/Lua调用C++异常处理/Lua处理C++异常.lua";
    if (luaL_loadfile(L, fname.c_str()) || LuaExt::safeCallLua(L, 0, 0)) {
        printf("运行 Lua 文件失败. file: %s\n", lua_tostring(L, -1));
    }
}