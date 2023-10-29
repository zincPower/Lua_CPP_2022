//
// Created by 江澎涌 on 2022/5/1.
//

#include "lua.hpp"
#include <dirent.h>
#include <cerrno>
#include <cstring>

int l_dir(lua_State *L) {
    // 检测入参是否为字符串
    // 如果不是，则会抛出异常到 Lua 中，can't run config. file: .../6、Lua回调C++/调用C++函数/读取目录函数.lua:11: bad argument #1 to 'dir' (string expected, got table)
    const char *path = luaL_checkstring(L, 1);

    // 打开相应目录
    DIR *dir = opendir(path);
    if (dir == nullptr) {
        // 抛异常至 Lua
        luaL_error(L, strerror(errno));
    }

    // 创建表，用于装载目录下 "索引" 和 "文件名"
    // 格式为 table[index] = "文件名"
    lua_newtable(L);
    int i = 1;
    struct dirent *entry;
    while ((entry = readdir(dir)) != nullptr) {
        // 压入 key ，即索引
        lua_pushinteger(L, i++);
        // 压入 value ，即文件名
        lua_pushstring(L, entry->d_name);
        // 将 key 和 value 插入 table
        lua_settable(L, -3);
    }

    closedir(dir);
    // 只有一个返回值，即 table
    return 1;
}

static const struct luaL_Reg mylib[] = {
        {"dir",   l_dir},
        {nullptr, nullptr}
};

extern "C" int luaopen_mylib(lua_State *L) {
    luaL_newlib(L, mylib);
    return 1;
}