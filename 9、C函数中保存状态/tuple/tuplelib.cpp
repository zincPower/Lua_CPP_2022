//
// Created by 江澎涌 on 2022/5/8.
//

#include "tuplelib.h"

int t_tuple(lua_State *L) {
    // 获取第一个值，是否为整型，不是的话就返回 0
    lua_Integer op = luaL_optinteger(L, 1, 0);
//    printf("t_tuple: %lld\n", op);
    if (op == 0) { // 没有参数
        int i;
        // 将每一个有效的上值压栈
        for (i = 1; !lua_isnone(L, lua_upvalueindex(i)); i++) {
            lua_pushvalue(L, lua_upvalueindex(i));
        }
        // 值的个数
        return i - 1;
    } else {
        luaL_argcheck(L, 0 < op && op < 256, 1, "index out of range");
        if (lua_isnone(L, lua_upvalueindex(op))) {
            return 0;
        }
        lua_pushvalue(L, lua_upvalueindex(op));
        return 1;
    }
}

int t_new(lua_State *L) {
    // 是 lua 中携带过来的函数
    int top = lua_gettop(L);
//    printf("new top: %d\n", top);
    luaL_argcheck(L, top < 256, top, "too many fields");
    // 将 lua 传递过来的值都作为 闭包 t_tuple 函数的 上值
    lua_pushcclosure(L, t_tuple, top);
    // 返回值代表着返回值的数量
    return 1;
}

static const struct luaL_Reg tuplelib[] = {
        {"new",   t_new},
        {nullptr, nullptr}
};

int luaopen_tuple(lua_State *L) {
    // 将 tuple lib 加载为 table
    luaL_newlib(L, tuplelib);
    // 将新的 table 设置为 tuple
    // tuple = table
    lua_setglobal(L, "tuple");
    return 1;
}

void tupleDemo() {
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);
    luaopen_tuple(L);

    std::string filename = PROJECT_PATH+"/9、C函数中保存状态/tuple/tuple.lua";
    if (luaL_loadfile(L, filename.c_str()) || lua_pcall(L, 0, 0, 0)) {
        error(L, "can't run config. file: %s", lua_tostring(L, -1));
    }

    lua_close(L);
}