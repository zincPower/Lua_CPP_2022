//
// Created by 江澎涌 on 2022/5/8.
//

#include "file.h"
#include "../utils/lua_error.h"


static const std::string DIR_METE_TABLE = "Jiang.dir";

static int dir_iter(lua_State *L) {
    DIR *d = *(DIR **) lua_touserdata(L, lua_upvalueindex(1));
    struct dirent *entry = readdir(d);
    if (entry != nullptr) {
        lua_pushstring(L, entry->d_name);
        return 1;
    } else {
        return 0;
    }
}

static int dir_gc(lua_State *L) {
    // 这里不是上值
    DIR *d = *(DIR **) lua_touserdata(L, 1);
    if (d) {
        printf("gc\n");
        closedir(d);
    }
    return 0;
}

static int l_dir(lua_State *L) {
    const char *path = luaL_checkstring(L, 1);
    // 创建一个完全用户数据
    DIR **d = (DIR **) lua_newuserdata(L, sizeof(DIR *));

    *d = nullptr;

    // 设置一个元表
    luaL_getmetatable(L, DIR_METE_TABLE.c_str());
    lua_setmetatable(L, -2);

    *d = opendir(path);
    if (*d == nullptr) {
        luaL_error(L, "cannot open: %s", path, strerror(errno));
    }

    // 压入一个闭包，上值就是 **dir
    lua_pushcclosure(L, dir_iter, 1);
    return 1;
}

static const struct luaL_Reg dirlib[] = {
        {"open",  l_dir},
        {nullptr, nullptr}
};

int luaopen_dir(lua_State *L) {
    luaL_newmetatable(L, DIR_METE_TABLE.c_str());

    lua_pushcfunction(L, dir_gc);
    lua_setfield(L, -2, "__gc");

    luaL_newlib(L, dirlib);
    lua_setglobal(L, "dir");

    return 1;
}

void resourceManageDemo() {
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);
    luaopen_dir(L);

    std::string fileName = "/Users/jiangpengyong/Desktop/code/CPP/CPP2022/lua/管理资源/file.lua";
    if (luaL_loadfile(L, fileName.c_str()) || lua_pcall(L, 0, 0, 0)) {
        error(L, "can't run file. file: %s", lua_tostring(L, -1));
    }

    lua_close(L);
}