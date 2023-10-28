//
// Created by 江澎涌 on 2023/10/23.
//

#include "简易的sin函数.h"

int l_sin(lua_State *L) {
    // 检测入参是否为数值，如果不是则会抛 Lua 异常
    double d = luaL_checknumber(L, 1);
    lua_pushnumber(L, sin(d));
    return 1;
}