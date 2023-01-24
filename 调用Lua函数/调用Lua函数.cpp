//
// Created by 江澎涌 on 2022/5/1.
//

#include "lua.hpp"
#include "../utils/lua_error.h"

double f(lua_State *L, double x, double y) {
    int isNum;
    double z;

    lua_getglobal(L, "f");
    lua_pushnumber(L, x);
    lua_pushnumber(L, y);

    if (lua_pcall(L, 2, 1, 0) != LUA_OK) {
        error(L, "error running function 'f': %s", lua_tostring(L, -1));
    }

    z = lua_tonumberx(L, -1, &isNum);
    if (!isNum) {
        error(L, "function 'f' should return a number.");
    }

    lua_pop(L, 1);
    return z;

}

void loadForFunction(lua_State *L, const char *fname){
    if (luaL_loadfile(L, fname) || lua_pcall(L, 0, 0, 0)) {
        error(L, "can't run config. file: %s", lua_tostring(L, -1));
    }
}
