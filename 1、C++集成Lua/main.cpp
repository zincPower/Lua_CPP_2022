//
// Created by 江澎涌 on 2023/1/21.
//

#include "lua.hpp"

/**
 * 验证 Lua 集成是否成功
 */
void verification() {
    int error;
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);

    error = luaL_loadstring(L, "print(\"C++ 集成 Lua 成功！！！\")") || lua_pcall(L, 0, 0, 0);
    if (error) {
        fprintf(stderr, "%s\n", lua_tostring(L, -1));
        lua_pop(L, 1);
    }

    lua_close(L);
}

int main() {
    printf("=============== 验证 Lua 集成 ===============\n");
    verification();
    printf("============================================\n");
    return 0;
}