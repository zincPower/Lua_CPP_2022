//
// Created by 江澎涌 on 2022/4/28.
//

#include "C++处理Lua异常.h"
#include "../../utils/lua_ext.h"

using namespace LuaExt;

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
