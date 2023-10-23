//
// Created by 江澎涌 on 2023/10/23.
//

#include "读取目录函数.h"

int l_dir(lua_State *L) {
    DIR *dir;
    struct dirent *entry;
    int i;
    const char *path = luaL_checkstring(L, 1);

    dir = opendir(path);
    if (dir == nullptr) {
        lua_pushnil(L);
        lua_pushstring(L, strerror(errno));
        return 2;
    }

    lua_newtable(L);
    i = 1;
    while ((entry = readdir(dir)) != nullptr) {
        lua_pushinteger(L, ++i);
        lua_pushstring(L, entry->d_name);
        lua_settable(L, -3);
    }

    closedir(dir);
    return 1;
}