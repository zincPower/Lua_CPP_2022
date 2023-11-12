//
// Created by 江澎涌 on 2022/5/8.
//

#include "user.h"

typedef struct User {
    std::string name;
    long long age;
} User;

/**
 * 创建数组
 * @param L
 * @return
 */
static int newUser(lua_State *L) {
    std::string name = luaL_checkstring(L, 1);
    long long age = luaL_checkinteger(L, 2);

    // 生成一个 User Data 并压入栈中
    auto *user = (User *) lua_newuserdata(L, sizeof(User));
    user->name = std::string(name);
    user->age = age;

    return 1;
}

static int introduce(lua_State *L) {
    User *user = (User *) lua_touserdata(L, 1);
    std::stringstream info;
    info << "大家好。我叫" << user->name << "。今年" << user->age << "岁。请关注我。";
    lua_pushstring(L, info.str().c_str());
    return 1;
}

static int setName(lua_State *L) {
    User *user = (User *) lua_touserdata(L, 1);
    std::string name = luaL_checkstring(L, 2);
    user->name = std::string(name);
    return 0;
}

static int setAge(lua_State *L) {
    User *user = (User *) lua_touserdata(L, 1);
    long long age = luaL_checkinteger(L, 2);
    user->age = age;
    return 0;
}

static int getName(lua_State *L) {
    User *user = (User *) lua_touserdata(L, 1);
    lua_pushstring(L, user->name.c_str());
    return 1;
}

static int getAge(lua_State *L) {
    User *user = (User *) lua_touserdata(L, 1);
    lua_pushinteger(L, user->age);
    return 1;
}

static const struct luaL_Reg userlib[] = {
        {"new",       newUser},
        {"introduce", introduce},
        {"setName",   setName},
        {"setAge",    setAge},
        {"getName",   getName},
        {"getAge",    getAge},
        {nullptr,     nullptr}
};

int luaopen_user(lua_State *L) {
    luaL_newlib(L, userlib);
    return 1;
}

void userSimpleDemo() {
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);

    luaopen_user(L);
    lua_setglobal(L, "user");

    std::string fileName = PROJECT_PATH + "/10、userdata/user/1普通版本/user.lua";
    if (luaL_loadfile(L, fileName.c_str()) || lua_pcall(L, 0, 0, 0)) {
        printf("can't run config. file: %s\n", lua_tostring(L, -1));
    }

    lua_close(L);
}