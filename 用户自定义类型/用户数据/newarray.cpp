//
// Created by 江澎涌 on 2022/5/8.
//

#include "newarray.h"
#include "lua.hpp"
#include "../../Error.h"
#include <limits.h>
#include <string>

#define BITS_PER_WORD (CHAR_BIT * sizeof(unsigned int))
#define I_WORD(i) ((unsigned int)(i) / BITS_PER_WORD)
#define I_BIT(i) (1<< ((unsigned int) (i) %BITS_PER_WORD))
#define checkarray(L) (BitArray *)luaL_checkudata(L,1,METE.c_str())

static const std::string METE = "Jiang.array";

typedef struct BitArray {
    int size;
    unsigned int values[1];
} BitArray;

static int newarray(lua_State *L) {
    int i;
    size_t nbytes;
    BitArray *a;

    int n = (int) luaL_checkinteger(L, 1);
    luaL_argcheck(L, n >= 1, 1, "invalid size");
    nbytes = sizeof(BitArray) + I_WORD(n - 1) * sizeof(unsigned int);
    a = (BitArray *) lua_newuserdata(L, nbytes);
    a->size = n;
    for (i = 0; i < I_WORD(n - 1); ++i) {
        a->values[i] = 0;
    }

    // 将 METE.c_str() 的对应表入栈，然后关联到 -2 的表做元表
    luaL_getmetatable(L, METE.c_str());
    lua_setmetatable(L, -2);

    return 1;
}

static unsigned int *getparams(lua_State *L, unsigned int *mask) {
    BitArray *a = checkarray(L);
    int index = (int) luaL_checkinteger(L, 2) - 1;

    luaL_argcheck(L, 0 <= index && index < a->size, 2, "index out of range");
    *mask = I_BIT(index);
    return &a->values[I_WORD(index)];
}

//static int setarray(lua_State *L) {
//    BitArray *a = (BitArray *) lua_touserdata(L, 1);
//    int index = (int) luaL_checkinteger(L, 2) - 1;
//    luaL_argcheck(L, a != nullptr, 1, "'array' expected");
//    luaL_argcheck(L, 0 <= index && index < a->size, 2, "index out of range");
//
//    luaL_checkany(L, 3);
//
//    if (lua_toboolean(L, 3)) {
//        // 置位
//        a->values[I_WORD(index)] |= I_BIT(index);
//    } else {
//        // 复位
//        a->values[I_WORD(index)] &= ~I_BIT(index);
//    }
//
//    return 0;
//}
static int setarray(lua_State *L) {
    unsigned int mask;
    unsigned int *entry = getparams(L, &mask);
    luaL_checkany(L, 3);
    if (lua_toboolean(L, 3)) {
        // 置位
        *entry |= mask;
    } else {
        // 复位
        *entry &= mask;
    }
    return 0;
}

//static int getarray(lua_State *L) {
//    BitArray *a = (BitArray *) lua_touserdata(L, 1);
//    int index = (int) luaL_checkinteger(L, 2) - 1;
//
//    luaL_argcheck(L, a != nullptr, 1, "'array' expected");
//    luaL_argcheck(L, 0 <= index && index < a->size, 2, "index out of range");
//
//    lua_pushboolean(L, a->values[I_WORD(index)] & I_BIT(index));
//    return 1;
//}
static int getarray(lua_State *L) {
    unsigned int mask;
    unsigned int *entry = getparams(L, &mask);
    lua_pushboolean(L, *entry & mask);
    return 1;
}

static int getsize(lua_State *L) {
//    BitArray *a = (BitArray *) lua_touserdata(L, 1);
//    luaL_argcheck(L, a != nullptr, 1, "'array' expected");
    BitArray *a = checkarray(L);
    lua_pushinteger(L, a->size);
    return 1;
}

static const struct luaL_Reg arraylib[] = {
        {"new",   newarray},
        {"set",   setarray},
        {"get",   getarray},
        {"size",  getsize},
        {nullptr, nullptr}
};

int luaopen_array(lua_State *L) {
    luaL_newmetatable(L, "Jiang.array");
    luaL_newlib(L, arraylib);
    return 1;
}

void arrayDemo() {
    lua_State *L = luaL_newstate();

    luaL_openlibs(L);
    luaopen_array(L);
    lua_setglobal(L, "array");

    std::string fileName = "/Users/jiangpengyong/Desktop/code/CPP/CPP2022/lua/用户自定义类型/用户数据/newarray.lua";
    if (luaL_loadfile(L, fileName.c_str()) || lua_pcall(L, 0, 0, 0)) {
        error(L, "can't run config. file: %s", lua_tostring(L, -1));
    }

    lua_close(L);
}