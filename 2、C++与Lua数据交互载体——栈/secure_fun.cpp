//
// Created by 江澎涌 on 2022/4/28.
//

#include "secure_fun.h"

static int foo(lua_State *pState) {
    printf("江澎涌");
    return 100;
}

int secureFoo(lua_State *L) {
    lua_pushcfunction(L, foo);
    return (lua_pcall(L, 0, 0, 0) == 0);
}
