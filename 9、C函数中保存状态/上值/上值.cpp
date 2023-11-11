//
// Created by 江澎涌 on 2022/5/8.
//

#include "上值.h"

static int counter(lua_State *L) {
    // 通过 lua_upvalueindex 获取第一个上值的伪索引，并通过 lua_tointeger 获取到对应的值
    int value = lua_tointeger(L, lua_upvalueindex(1));
    // 将数值累加后压栈，后续可以用作 "更新上值" 和 "返回"
    lua_pushinteger(L, ++value);
    // 通过 lua_upvalueindex 获取第一个上值的伪索引
    // 并通过 lua_copy 将索引为 -1 的值拷贝到第一个上值
    lua_copy(L, -1, lua_upvalueindex(1));
    // 返回累加后的数值
    return 1;
}

int newCounter(lua_State *L) {
    // 压入初始上值，即整型数值 0
    lua_pushinteger(L, 0);
    // 压入闭包函数 counter ， 并携带一个上值
    // counter 函数则可以获取到该上值
    lua_pushcclosure(L, &counter, 1);
    // 返回一个闭包，该闭包的执行体是 counter ，上值为一个整型数值
    return 1;
}

static const struct luaL_Reg luaLReg[] = {
        {"newCounter", newCounter},
        {nullptr,      nullptr}
};

void upValueDemo() {
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);

    // 创建一个 lib
    luaL_newlib(L, luaLReg);
    // Counter = lib
    lua_setglobal(L, "Counter");

    std::string fileName = PROJECT_PATH + "/9、C函数中保存状态/上值/上值.lua";
    if (luaL_loadfile(L, fileName.c_str()) || lua_pcall(L, 0, 0, 0)) {
        error(L, "can't run config. file: %s", lua_tostring(L, -1));
    }

    lua_close(L);
}