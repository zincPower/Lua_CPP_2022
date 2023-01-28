//
// Created by 江澎涌 on 2022/5/6.
//

#include <cstring>
#include <cctype>
#include "LuaString.h"
#include "lua.hpp"

void l_split(lua_State *L) {
    const char *s = luaL_checkstring(L, 1);
    const char *sep = luaL_checkstring(L, 2);
    const char *e;
    int i = 1;

    lua_newtable(L);

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
}

void luaStringDemo() {

    lua_State *L = luaL_newstate();

    lua_pushstring(L, "江_澎_涌");
    lua_pushstring(L, "_");
    l_split(L);

    long long len = luaL_len(L, -1);
    printf("len: %lld\n", len);
    for (int i = 1; i <= len; ++i) {
        lua_geti(L, -1, i);
        printf("%s\n", lua_tostring(L, -1));
        lua_pop(L, 1);
    }

    lua_close(L);
}

void luaConcatDemo() {
    lua_State *L = luaL_newstate();

    lua_pushstring(L, "江!");
    lua_pushstring(L, "澎!");
    lua_pushstring(L, "涌!");
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
    size_t i;
    luaL_Buffer b;

    const char *s = luaL_checklstring(L, 1, &l);
    char *p = luaL_buffinitsize(L, &b, l);
    for (i = 0; i < l; i++) {
        p[i] = toupper(s[i]);
    }
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
    luaL_checktype(L, 1, LUA_TTABLE);
    n = luaL_len(L, 1);
    luaL_buffinit(L, &b);
    for (i = 1; i <= n; i++) {
        lua_geti(L, 1, i);
        printf("for add value before: %d\n", lua_gettop(L));
        luaL_addvalue(&b);
        printf("for add value after: %d\n", lua_gettop(L));
    }
    printf("push before: %d\n", lua_gettop(L));
    luaL_pushresult(&b);
    printf("push after: %d\n", lua_gettop(L));
    return 1;
}

void bufferConcatDemo() {
    lua_State *L = luaL_newstate();

    lua_newtable(L);
    lua_pushstring(L, "Jiang");
    lua_seti(L, 1, 1);

    lua_pushstring(L, "Peng");
    lua_seti(L, 1, 2);

    lua_pushstring(L, "Yong");
    lua_seti(L, 1, 3);

    printf("before: %d\n", lua_gettop(L));
    bufferConcat(L);

    printf("%s", lua_tostring(L, -1));
    printf("after: %d\n", lua_gettop(L));

    lua_close(L);
}

