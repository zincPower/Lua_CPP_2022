//
// Created by 江澎涌 on 2022/5/8.
//

#ifndef CPP2022_TUPLELIB_H
#define CPP2022_TUPLELIB_H

#include <iostream>
#include "../../utils/lua_error.h"
#include "lua.hpp"
#include "../../config/env_config.h"

int luaopen_tuple(lua_State *L);

void tupleDemo();

#endif //CPP2022_TUPLELIB_H
