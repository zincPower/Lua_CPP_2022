//
// Created by 江澎涌 on 2022/5/6.
//

#include "LuaArray.h"

using namespace LuaExt;

void luaArrayDemo() {
    lua_State *L = luaL_newstate();

    // 创建并压入一个新表
    lua_newtable(L);

    // --------- 添加至数组的操作方式 ---------
    // 第一种：
    // table[1] = "江澎涌!（快捷方式插入）"
    lua_pushstring(L, "江澎涌!（快捷方式插入）");
    lua_seti(L, -2, 1);

    // 第二种：
    // 栈底 ----> 栈顶
    // table - key - value
    // 使用完后，key - value 会被弹出
    // table[2] = "江澎涌!（常规方式插入）"
    lua_pushnumber(L, 2);
    lua_pushstring(L, "江澎涌!（常规方式插入）");
    lua_settable(L, -3);

    // --------- 从数组中获取值方式 ---------
    // 第一种
    // 获取 table 中索引为 1 的值压入栈
    printf("lua_geti(L, -1, 1) 类型：%d\n", lua_geti(L, -1, 1));
    printf("table[1] = %s\n", lua_tostring(L, -1));
    // 将获取的值弹出
    lua_pop(L, 1);

    // 第二种
    // 压入 key 值
    lua_pushnumber(L, 2);
    // 获取 table 中索引为 2 的值压入栈
    printf("lua_gettable(L, -2) 类型：%d\n", lua_gettable(L, -2));
    printf("table[2] = %s\n", lua_tostring(L, -1));
    // 将获取的值弹出
    lua_pop(L, 1);

    long long n = luaL_len(L, 1);
    printf("lua table length: %lld\n", n);

    lua_close(L);
}

int l_map(lua_State *L) {
    long long i, n;

    // 检查第一个参数是否为 table ，如果不是 table 则会抛异常到 Lua
    luaL_checktype(L, 1, LUA_TTABLE);
    // 检查第二个参数是否为函数，如果不是函数则会抛异常到 Lua
    luaL_checktype(L, 2, LUA_TFUNCTION);

    // 获取表的长度
    n = luaL_len(L, 1);
    printf("lua table length: %lld\n", n);

    for (i = 1; i <= n; i++) {
        // 将函数压到栈顶
        lua_pushvalue(L, 2);
        // 获取第一个元素（即为 table ）的第 i 个元素，放置栈顶
        lua_geti(L, 1, i);
        // 调用函数，传入一个参数（栈顶），返回一个值放置栈顶
        // 如果调用的函数有异常，这里不使用 lua_pcall 捕获，可以让异常传至调用的地方（即 Lua 文件中，Lua 文件中可以进行处理，如果不进行处理就会抛异常给运行 Lua 的 C++ 调用处）
        lua_call(L, 1, 1);
        // 将栈顶的值（即上一行返回的值）设置到 table 中索引为 i 的元素，即 table[i] = "lua_call 返回值"
        lua_seti(L, 1, i);
    }

    return 0;
}

void luaMapFunctionDemo() {
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);

    lua_pushcfunction(L, l_map);
    lua_setglobal(L, "map");

    std::string fname = PROJECT_PATH + "/8、编写C函数技巧/数组便捷存取/Array便捷存取.lua";
    if (luaL_loadfile(L, fname.c_str()) || lua_pcall(L, 0, 0, 0)) {
        printf("can't run config. file: %s\n", lua_tostring(L, -1));
    }

    lua_close(L);
}
