//
// Created by 江澎涌 on 2022/5/1.
//

#ifndef CPP2022_ERROR_H
#define CPP2022_ERROR_H

#include "lua.hpp"

extern void error(lua_State *L, const char *fmt, ...);

#endif //CPP2022_ERROR_H
