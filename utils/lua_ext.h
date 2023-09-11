//
// Created by 江澎涌 on 2023/9/11.
//

#ifndef LUA_CPP_2022_LUA_EXT_H
#define LUA_CPP_2022_LUA_EXT_H

#include "lua.hpp"

namespace LuaExt {

extern void stackDump(lua_State *L);

extern int safeCallLua(lua_State *L, int narg, int nres);

}

#endif //LUA_CPP_2022_LUA_EXT_H
