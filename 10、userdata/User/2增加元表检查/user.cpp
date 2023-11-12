//
// Created by 江澎涌 on 2022/5/8.
//

#include "user.h"

static const std::string META = "Jiang.user";

#define checkUser(L) (User *)luaL_checkudata(L, 1, META.c_str())

typedef struct User {
    std::string name;
    long long age;
} User;

/**
 * 创建数组
 * @param L
 * @return
 */
static int newUserForMetatable(lua_State *L) {
    std::string name = luaL_checkstring(L, 1);
    long long age = luaL_checkinteger(L, 2);

    // 生成一个 User Data 并压入栈中
    auto *user = (User *) lua_newuserdata(L, sizeof(User));
    user->name = std::string(name);
    user->age = age;

    // 将 META.c_str() 的对应表入栈，然后关联到 -2 的表做元表
    luaL_getmetatable(L, META.c_str());
    lua_setmetatable(L, -2);

    return 1;
}

static int introduceForMetatable(lua_State *L) {
    User *user = checkUser(L);
    std::stringstream info;
    info << "大家好。我叫" << user->name << "。今年" << user->age << "岁。请关注我。";
    lua_pushstring(L, info.str().c_str());
    return 1;
}

static int setNameForMetatable(lua_State *L) {
    User *user = checkUser(L);
    std::string name = luaL_checkstring(L, 2);
    user->name = std::string(name);
    return 0;
}

static int setAgeForMetatable(lua_State *L) {
    User *user = checkUser(L);
    long long age = luaL_checkinteger(L, 2);
    user->age = age;
    return 0;
}

static int getNameForMetatable(lua_State *L) {
    User *user = checkUser(L);
    lua_pushstring(L, user->name.c_str());
    return 1;
}

static int getAgeForMetatable(lua_State *L) {
    User *user = checkUser(L);
    lua_pushinteger(L, user->age);
    return 1;
}

static const struct luaL_Reg userlib[] = {
        {"new",       newUserForMetatable},
        {"introduce", introduceForMetatable},
        {"setName",   setNameForMetatable},
        {"setAge",    setAgeForMetatable},
        {"getName",   getNameForMetatable},
        {"getAge",    getAgeForMetatable},
        {nullptr,     nullptr}
};

int luaopen_userForMetatable(lua_State *L) {
    luaL_newmetatable(L, META.c_str());
    luaL_newlib(L, userlib);
    return 1;
}

void userMetatableDemo() {
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);

    luaopen_userForMetatable(L);
    lua_setglobal(L, "user");

    std::string fileName = PROJECT_PATH + "/10、userdata/user/2增加元表检查/user.lua";
    if (luaL_loadfile(L, fileName.c_str()) || lua_pcall(L, 0, 0, 0)) {
        printf("can't run config. file: %s\n", lua_tostring(L, -1));
    }

    lua_close(L);
}