//
// Created by 江澎涌 on 2022/5/1.
//

#include <cmath>
#include <dirent.h>
#include <cerrno>
#include <cstring>
#include "lua.hpp"

static int l_sin(lua_State *L) {
    double d = lua_tonumber(L, 1);
    lua_pushnumber(L, sin(d));
    return 1;
}

static int l_dir(lua_State *L) {
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