//
// Created by 江澎涌 on 2022/5/8.
//

#include "共享上值.h"

int showInfo(lua_State *L) {
    // 获取 lua 传过来的第一个参数
    std::string tip = lua_tostring(L, 1);
    // 获取 lua 传过来的第二个参数
    long long value = lua_tointeger(L, 2);
    printf("【showInfo】C++ 函数获取到 Lua 传递的参数：%s, %lld\n", tip.c_str(), value);

    // 获取第一个上值，整数型
    long long age = lua_tointeger(L, lua_upvalueindex(1));
    // 获取第二个上值，字符串
    std::string name = lua_tostring(L, lua_upvalueindex(2));
    printf("【showInfo】C++ 函数获取到上值：%lld, %s\n", age, name.c_str());

    // 给第三个上值 table 设置值 table["up"] = "up value jiang"
    lua_pushstring(L, "up value jiang");
    lua_setfield(L, lua_upvalueindex(3), "up");

    lua_pushstring(L, name.c_str());
    lua_pushinteger(L, age);
    // 将参数和上值拼凑后作为返回值
    lua_concat(L, 4);

    return 1;
}

int showCode(lua_State *L) {
    // 获取 lua 传过来的第一个参数
    std::string value = lua_tostring(L, 1);
    printf("【showCode】C++ 函数获取到 Lua 传递的参数：%s\n", value.c_str());

    // 获取第一个上值，整数型
    long long age = lua_tointeger(L, lua_upvalueindex(1));
    // 获取第二个上值，字符串
    std::string name = lua_tostring(L, lua_upvalueindex(2));
    // 获取第三个上值 table 中 key 为 "up" 的 value
    // table["up"]
    lua_getfield(L, lua_upvalueindex(3), "up");
    std::string up = lua_tostring(L, 1);
    printf("【showInfo】C++ 函数获取到上值：%lld, %s, %s\n", age, name.c_str(), up.c_str());

    lua_pushstring(L, name.c_str());
    lua_pushinteger(L, age);
    lua_pushstring(L, up.c_str());
    // 将参数和上值拼凑后作为返回值
    lua_concat(L, 4);
    return 1;
}

static const struct luaL_Reg user[] = {
        {"showInfo", showInfo},
        {"showCode", showCode},
        {nullptr,    nullptr}
};

int luaopen_user(lua_State *L) {
    // 创建一个 lib
    luaL_newlibtable(L, user);
    // 压入上值
    lua_pushnumber(L, 28);
    lua_pushstring(L, "江澎涌");
    lua_newtable(L);
    // 设置函数
    luaL_setfuncs(L, user, 3);
    lua_setglobal(L, "User");
    return 1;
}

void shareUpValueDemo() {
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);

    luaopen_user(L);

    std::string fileName = PROJECT_PATH + "/9、C函数中如何保存Lua的数据/共享上值/共享上值.lua";
    if (luaL_loadfile(L, fileName.c_str()) || lua_pcall(L, 0, 0, 0)) {
        printf("can't run config. file: %s", lua_tostring(L, -1));
    }

    lua_close(L);
}