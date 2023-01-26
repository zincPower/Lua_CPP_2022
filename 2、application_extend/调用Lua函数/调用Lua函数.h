//
// Created by 江澎涌 on 2022/5/1.
//

#ifndef CPP2022_调用LUA函数_H
#define CPP2022_调用LUA函数_H

#include "lua.hpp"

extern void loadForFunction(lua_State *L, const char *fname);

extern double f(lua_State *L, double x, double y);


#endif //CPP2022_调用LUA函数_H
