//
// Created by 江澎涌 on 2022/5/6.
//

#include "LuaString.h"

int lua_split(lua_State *L) {
    // 被分割的内容
    const char *s = luaL_checkstring(L, 1);
    // 分割符
    const char *sep = luaL_checkstring(L, 2);

    // 创建一个 table ，并且压入到栈中，后续的分割结果会压入到该 table 中
    lua_newtable(L);

    const char *e;
    int i = 1;
    // char *strchr(const char *str, int c) 在参数 str 所指向的字符串中搜索第一次出现字符 c（一个无符号字符）的位置
    // 该函数返回在字符串 str 中第一次出现字符 c 的位置，如果未找到该字符则返回 NULL
    while ((e = strchr(s, *sep)) != nullptr) {
        // 将 s 中 （ e - s ） 个字符压入栈顶
        lua_pushlstring(L, s, e - s);
        // 设置到 -2 （ table ）中
        lua_rawseti(L, -2, i++);
        s = e + 1;
    }

    // 把最后的字符也压入
    lua_pushstring(L, s);
    lua_rawseti(L, -2, i);

    return 1;
}

void luaStringDemo() {
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);

    lua_pushcfunction(L, lua_split);
    lua_setglobal(L, "split");

    std::string fname = PROJECT_PATH + "/8、编写C函数便捷技巧/字符串便捷操作/字符串截取.lua";
    if (luaL_loadfile(L, fname.c_str()) || lua_pcall(L, 0, 0, 0)) {
        printf("can't run config. file: %s\n", lua_tostring(L, -1));
    }

    lua_close(L);
}

void luaConcatDemo() {
    lua_State *L = luaL_newstate();

    // 压入三个字符串
    lua_pushstring(L, "江!");
    lua_pushstring(L, "澎!");
    lua_pushstring(L, "涌!");
    // 将三个字符串进行弹出并拼接
    lua_concat(L, 3);

    printf("stack top: %d\n", lua_gettop(L));
    printf("concat: %s\n", lua_tostring(L, -1));

    lua_close(L);
}

void luaPushFStringDemo() {
    lua_State *L = luaL_newstate();

    lua_pushfstring(L, "%d-%s%s%s", 29, "江", "澎", "涌");

    printf("stack top: %d\n", lua_gettop(L));
    printf("fstring: %s\n", lua_tostring(L, -1));

    lua_close(L);
}

int str_upper(lua_State *L) {
    size_t l;
    // 检测参数是否为字符串，并且获取长度
    const char *s = luaL_checklstring(L, 1, &l);

    size_t i;
    // 声明缓冲区
    luaL_Buffer b;
    // 初始化缓冲区
    char *p = luaL_buffinitsize(L, &b, l);
    for (i = 0; i < l; i++) {
        p[i] = toupper(s[i]);
    }
    // 将缓冲区中的内容转换为一个新的 Lua 字符串，并将字符串压栈
    luaL_pushresultsize(&b, l);
}

void strUpperDemo() {
    lua_State *L = luaL_newstate();

    lua_pushstring(L, "jiang peng yong");
    str_upper(L);
    printf("to upper: %s\n", lua_tostring(L, -1));

    lua_close(L);
}

int bufferConcat(lua_State *L) {
    luaL_Buffer b;
    long long i, n;
    // 检测是否为 table
    luaL_checktype(L, 1, LUA_TTABLE);
    // 获取 table 长度
    n = luaL_len(L, 1);
    // 初始化缓冲区
    luaL_buffinit(L, &b);
    // 循环取出 table 的值，添加到缓冲区中
    for (i = 1; i <= n; i++) {
        lua_geti(L, 1, i);
        luaL_addvalue(&b);
    }
    // 将缓冲区内容组装为字符串，压入栈
    luaL_pushresult(&b);
    return 1;
}

void bufferConcatDemo() {
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);

    lua_pushcfunction(L, bufferConcat);
    lua_setglobal(L, "concat");

    std::string fname = PROJECT_PATH + "/8、编写C函数便捷技巧/字符串便捷操作/字符串连接（缓冲区）.lua";
    if (luaL_loadfile(L, fname.c_str()) || lua_pcall(L, 0, 0, 0)) {
        printf("can't run config. file: %s\n", lua_tostring(L, -1));
    }

    lua_close(L);
}

