//
// Created by 江澎涌 on 2023/10/23.
//

#ifndef LUA_CPP_2022_读取目录函数_H
#define LUA_CPP_2022_读取目录函数_H

#include <dirent.h>
#include <cerrno>
#include <cstring>
#include "lua.hpp"

extern int l_dir(lua_State *L);

#endif //LUA_CPP_2022_读取目录函数_H