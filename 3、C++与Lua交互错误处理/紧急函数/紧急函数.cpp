//
// Created by 江澎涌 on 2022/4/28.
//

#include "紧急函数.h"

int panicHandle(lua_State *L) {
    const char *error = lua_tostring(L, -1);
    printf("Lua panic: %s\n", error);

    // 可以进行其他自定义操作，如记录日志、释放资源等

    // 返回程序则会终止
    return 0;
}

void panicMain() {
    lua_State *L = luaL_newstate();

    auto luaFilePath = PROJECT_PATH + "/3、C++与Lua交互错误处理/紧急函数/Lua异常.lua";

    // 加载 Lua 脚本
    auto loadLuaResult = luaL_loadfile(L, luaFilePath.c_str());
    if (loadLuaResult) {
        printf("加载 Lua 文件失败. file: %s\n", lua_tostring(L, -1));
        return;
    }

    lua_atpanic(L, panicHandle);
    lua_call(L, 0, 0);

    lua_close(L);
}
