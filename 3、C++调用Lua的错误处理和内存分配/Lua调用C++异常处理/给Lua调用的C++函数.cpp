//
// Created by 江澎涌 on 2023/9/11.
//

#include "给Lua调用的C++函数.h"

int cppError(lua_State *L) {
    luaL_error(L, "C++ throw error.");
}