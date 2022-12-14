//
// Created by 江澎涌 on 2022/5/8.
//

#include "tuplelib.h"
#include "../../Error.h"
#include <iostream>

extern "C" int t_tuple(lua_State *L) {
    // 获取第一个值，是否为整型，不是的话就返回 0
    lua_Integer op = luaL_optinteger(L, 1, 0);
    printf("t_tuple: %lld\n", op);
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

extern "C" int t_new(lua_State *L) {
    int top = lua_gettop(L);
    printf("new top: %d\n", top);
    luaL_argcheck(L, top < 256, top, "too many fields");
    lua_pushcclosure(L, t_tuple, top);
    lua_pushstring(L, "jiang pengyong");
    // 返回值代表着返回值的数量
    return 2;
}

static const struct luaL_Reg tuplelib[] = {
        {"new",   t_new},
        {nullptr, nullptr}
};

int luaopen_tuple(lua_State *L) {
    printf("stack: %d\n", lua_gettop(L));
    luaL_newlib(L, tuplelib);
    printf("stack: %d\n", lua_gettop(L));
    lua_setglobal(L, "tuple");
    return 1;
}

void tupleDemo() {
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);
    luaopen_tuple(L);

    std::string filename = "/Users/jiangpengyong/Desktop/code/CPP/CPP2022/lua/编写C函数技巧/tuple/tuple.lua";
    if (luaL_loadfile(L, filename.c_str()) || lua_pcall(L, 0, 0, 0)) {
        error(L, "can't run config. file: %s", lua_tostring(L, -1));
    }

    lua_close(L);
}