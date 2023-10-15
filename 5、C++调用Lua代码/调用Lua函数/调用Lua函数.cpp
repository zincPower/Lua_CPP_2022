//
// Created by 江澎涌 on 2022/5/1.
//

#include "调用Lua函数.h"

using namespace LuaExt;

bool callLuaFunction(lua_State *L, double x, double y, double *result) {
    // 获取全局中的 luaFunction 变量，将其压入栈中
    int getResult = lua_getglobal(L, "luaFunction");
    if (getResult == LUA_TNIL) {
        printf("lua_getglobal get failure\n");
        return false;
    }
    // 将 x 和 y 入栈，会作为 luaFunction 函数的两个参数
    lua_pushnumber(L, x);
    lua_pushnumber(L, y);

//    stackDump(L);

    // 运行 luaFunction 函数
    if (lua_pcall(L, 2, 1, 0) != LUA_OK) {
        printf("error running function 'f': %s", lua_tostring(L, -1));
        return false;
    }

//    stackDump(L);

    int isNum;
    // 获取 luaFunction 的返回值
    *result = lua_tonumberx(L, -1, &isNum);
    if (!isNum) {
        printf("function 'luaFunction' should return a number.");
        return false;
    }

//    stackDump(L);

    // 需要将返回值弹出
    lua_pop(L, 1);
    return true;
}

void cppCallLuaFunction() {
    std::string fname = PROJECT_PATH + "/5、C++调用Lua代码/调用Lua函数/调用Lua函数.lua";
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);

    // 加载 Lua 文件、运行 Lua 文件
    if (luaL_loadfile(L, fname.c_str()) || lua_pcall(L, 0, 0, 0)) {
        printf("can't run config. file: %s\n", lua_tostring(L, -1));
        lua_close(L);
        return;
    }

    double calResult = 0;
    bool isSuccess = false;
    // 调用 Lua 文件中的函数
    isSuccess = callLuaFunction(L, 2, 34, &calResult);
    if (isSuccess) {
        printf("调用 Lua 成功 luaFunction: %f\n", calResult);
    } else {
        printf("调用 Lua 失败\n");
    }

    lua_close(L);
}