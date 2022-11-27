//
// Created by 江澎涌 on 2022/5/1.
//

#ifndef CPP2022_库_H
#define CPP2022_库_H

#include <dirent.h>
#include <cerrno>
#include <cstring>
#include "库.h"
#include "lua.hpp"
#include "lua.hpp"

extern int luaopen_mylib(lua_State *L);
extern void libDemo();

#endif //CPP2022_库_H
