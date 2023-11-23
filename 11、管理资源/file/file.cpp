//
// Created by 江澎涌 on 2022/5/8.
//

#include "file.h"

static const std::string DIR_METE_TABLE = "Jiang.dir";

static int dir_iter(lua_State *L) {
//    printf("不可变量 %s\n", lua_tostring(L, -2));
//    printf("上一次循环变量 %s\n", lua_tostring(L, -1));

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
        printf("-- gc 回收 dir --\n");
        closedir(d);
    }
    return 0;
}

static int l_dir(lua_State *L) {
    // 文件路径
    const char *path = luaL_checkstring(L, 1);
    // 创建一个完全用户数据
    // 内部保存的是一个 "指向 DIR 类型结构体的指针"
    DIR **d = (DIR **) lua_newuserdata(L, sizeof(DIR *));

    *d = nullptr;

    // 设置一个元表
    luaL_getmetatable(L, DIR_METE_TABLE.c_str());
    lua_setmetatable(L, -2);

    *d = opendir(path);
    if (*d == nullptr) {
        // errno 是全局变量，表示上一个调用的错误代码，如果成功就为 0
        // C 库函数 char *strerror(int errnum) 从内部数组中搜索错误号 errnum，并返回一个指向错误消息字符串的指针。
        // strerror 生成的错误字符串取决于开发平台和编译器。
        luaL_error(L, "cannot open: %s", path, strerror(errno));
    }

    // 压入一个闭包，有一个上值，上值就是 **dir
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

    std::string fileName = "/Users/jiangpengyong/Desktop/code/Lua/Lua_CPP_2022/11、管理资源/file/file.lua";
    if (luaL_loadfile(L, fileName.c_str()) || lua_pcall(L, 0, 0, 0)) {
        printf("can't run file. file: %s", lua_tostring(L, -1));
    }

    lua_close(L);
}