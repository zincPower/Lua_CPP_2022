//
// Created by 江澎涌 on 2023/10/26.
//

#include <string>
#include "lua.hpp"
#include "../config/env_config.h"

int main(){
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);

    printf("\n");
    printf("=============== Lua调用 ===============\n");
    std::string fname = PROJECT_PATH +"/7、Lua调用C++的lib/Lua加载C模块.lua";
    if (luaL_loadfile(L, fname.c_str()) || lua_pcall(L, 0, 0, 0)) {
        printf("can't run config. file: %s", lua_tostring(L, -1));
    }

    lua_close(L);

    return 1;
}