//
// Created by 江澎涌 on 2022/5/8.
//

#include <string>
#include "共享上值.h"
#include "lua.hpp"
#include "../../utils/lua_error.h"

int showInfo(lua_State *L) {
    long long age = lua_tointeger(L, lua_upvalueindex(1));
    std::string name = lua_tostring(L, lua_upvalueindex(2));
    lua_pushstring(L, "up value jiang");
    lua_setfield(L, lua_upvalueindex(3), "up");
    std::string tip = lua_tostring(L, 1);
    long long value = lua_tointeger(L, 2);
    char *buf = new char[strlen(name.c_str()) + sizeof(age) + strlen(tip.c_str()) + sizeof(value) + 1];
    sprintf(buf, "%s-%lld-%s-%lld", name.c_str(), age, tip.c_str(), value);
    lua_pushstring(L, buf);
    delete[] buf;
    return 1;
}

int showCode(lua_State *L) {
    long long age = lua_tointeger(L, lua_upvalueindex(1));
    std::string name = lua_tostring(L, lua_upvalueindex(2));
    lua_getfield(L, lua_upvalueindex(3), "up");
    std::string value = lua_tostring(L, 2);
    printf("v: %s\n", value.c_str());
    std::string tip = lua_tostring(L, 1);
    char *buf = new char[strlen(name.c_str()) + sizeof(age) + strlen(tip.c_str()) + 1];
    sprintf(buf, "%s---%lld---%s", name.c_str(), age, tip.c_str());
    lua_pushstring(L, buf);
    delete[] buf;
    return 1;
}

static const struct luaL_Reg user[] = {
        {"showInfo", showInfo},
        {"showCode", showCode},
        {nullptr,    nullptr}
};

void shareUpValueDemo() {
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);

    // 创建一个 lib
    luaL_newlibtable(L, user);
    // 压入上值
    lua_pushnumber(L, 28);
    lua_pushstring(L, "江澎涌");
    lua_newtable(L);
    // 设置函数
    luaL_setfuncs(L, user, 3);
    lua_setglobal(L, "User");

    std::string fileName = "/Users/jiangpengyong/Desktop/code/Lua/Lua_CPP_2022/8、编写C函数技巧/共享上值/共享上值.lua";
    if (luaL_loadfile(L, fileName.c_str()) || lua_pcall(L, 0, 0, 0)) {
        error(L, "can't run config. file: %s", lua_tostring(L, -1));
    }

    lua_close(L);
}