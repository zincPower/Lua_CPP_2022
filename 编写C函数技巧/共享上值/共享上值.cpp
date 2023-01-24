//
// Created by 江澎涌 on 2022/5/8.
//

#include <string>
#include "共享上值.h"
#include "lua.hpp"
#include "../../1、C_API/Error.h"

int showInfo(lua_State *L) {
    long long age = lua_tointeger(L, lua_upvalueindex(1));
    std::string name = lua_tostring(L, lua_upvalueindex(2));
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

    luaL_newlibtable(L, user);
    lua_pushnumber(L, 28);
    lua_pushstring(L, "江澎涌");
    luaL_setfuncs(L, user, 2);
    lua_setglobal(L, "User");

    std::string fileName = "/Users/jiangpengyong/Desktop/code/CPP/CPP2022/lua/编写C函数技巧/共享上值/共享上值.lua";
    if (luaL_loadfile(L, fileName.c_str()) || lua_pcall(L, 0, 0, 0)) {
        error(L, "can't run config. file: %s", lua_tostring(L, -1));
    }

    lua_close(L);
}