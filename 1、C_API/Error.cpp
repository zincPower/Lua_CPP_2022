//
// Created by 江澎涌 on 2022/5/1.
//

#include "Error.h"

#include <cstdlib>
#include "lua.hpp"

// 错误
void error(lua_State *L, const char *fmt, ...) {
    va_list argp;
    va_start(argp, fmt);
    vfprintf(stderr, fmt, argp);
    va_end(argp);
    lua_close(L);
    exit(EXIT_FAILURE);
}