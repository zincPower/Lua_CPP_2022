//
// Created by 江澎涌 on 2022/5/1.
//

#ifndef CPP2022_CALL_VA_H
#define CPP2022_CALL_VA_H

#include "../../config/env_config.h"
#include <cstring>
#include "lua.hpp"

extern void call_va(lua_State *L, const char *func, const char *sig, ...);

extern void commonCallLuaDemo();

#endif //CPP2022_CALL_VA_H
