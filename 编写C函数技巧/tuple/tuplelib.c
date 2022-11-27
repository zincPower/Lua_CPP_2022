//
// Created by 江澎涌 on 2022/5/8.
//

#include "lua.h"
#include "lauxlib.h"

extern int t_tuple(lua_State *L) {
    // 获取第一个值，是否为整型，不是的话就返回 0
    lua_Integer op = luaL_optinteger(L, 1, 0);
    if (op == 0) { // 没有参数
        int i;
        // 将每一个有效的上值压栈
        for (i = 1; !lua_isnone(L, lua_upvalueindex(i)); i++) {
            lua_pushvalue(L, lua_upvalueindex(i));
        }
        // 值的个数
        return i - 1;
    } else {
        luaL_argcheck(L, 0 < op && op <= 256, 1, "index out of range");
        if (lua_isnone(L, lua_upvalueindex(op))) {
            return 0;
        }
        lua_pushvalue(L, lua_upvalueindex(op));
        return 1;
    }
}

int t_new(lua_State *L) {
    int top = lua_gettop(L);
    luaL_argcheck(L, top < 256, top, "too many fields");
    lua_pushcclosure(L, t_tuple, top);
    return 1;
}

static const struct luaL_Reg tuplelib[] = {
        {"new", t_new},
        {NULL, NULL}
};

extern int luaopen_tuple(lua_State *L) {
    luaL_newlib(L, tuplelib);
    return 1;
}