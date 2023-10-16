//
// Created by 江澎涌 on 2022/4/29.
//

#include "config_use_env.h"

/**
 * 获取全局 int
 * @param L lua state
 * @param var 字段名
 * @param result lua 中字段名对应的值
 * @return 是否获取成功
 * lua_getglobal 将会从 lua 中读取全局变量，将值压入栈中
 */
bool getGlobInt(lua_State *L, const char *var, int *result) {
    int isNum;
    // 将 var 对应的值压入栈中
    lua_getglobal(L, var);
    *result = (int) lua_tointegerx(L, -1, &isNum);
    if (!isNum) {
        printf("'%s' should be a number\n", var);
        return false;
    }
    // 将 var 对应值压入栈中的值弹出
    lua_pop(L, 1);
    return true;
}

void loadConfigUseEnv() {
    std::string filename = PROJECT_PATH + "/5、C++调用Lua代码/Lua作为配置文件/根据环境变量获取值/config.lua";
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);

    if (luaL_loadfile(L, filename.c_str()) || lua_pcall(L, 0, 0, 0)) {
        printf("can't run config. file: %s\n", lua_tostring(L, -1));
        return;
    }

    int width;
    if (!getGlobInt(L, "width", &width)) {
        printf("Get width failure.");
        return;
    }
    int height;
    if (!getGlobInt(L, "height", &height)) {
        printf("Get height failure.");
        return;
    }

    printf("size: %d x %d\n", width, height);

    lua_close(L);
}
