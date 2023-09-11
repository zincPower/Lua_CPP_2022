//
// Created by 江澎涌 on 2023/9/11.
//

#ifndef LUA_CPP_2022_给LUA调用的C_函数_H
#define LUA_CPP_2022_给LUA调用的C_函数_H

#include <cmath>
#include <dirent.h>
#include <cerrno>
#include <cstring>
#include "lua.hpp"

static int l_sin(lua_State *L);

static int l_dir(lua_State *L);

#endif //LUA_CPP_2022_给LUA调用的C_函数_H
