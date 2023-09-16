//
// Created by 江澎涌 on 2022/4/28.
//

#ifndef CPP2022_LUASTACK_H
#define CPP2022_LUASTACK_H

#include <cstring>
#include "lua.hpp"
#include "../utils/lua_ext.h"

using namespace LuaExt;

extern void stackDemo();

void showInfo(lua_State *L, ...);

#endif //CPP2022_LUASTACK_H
