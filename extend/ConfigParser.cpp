//
// Created by 江澎涌 on 2022/4/29.
//

#include <cstdlib>
#include <cstring>
#include "lua.hpp"
#include "../Error.h"

#define MAX_COLOR 255

struct ColorTable {
    char *name;
    unsigned char red, green, blue;
} colorTable[] = {
        {"WHITE", MAX_COLOR, MAX_COLOR, MAX_COLOR},
        {"RED",   MAX_COLOR, 0,         0},
        {"GREEN", 0,         MAX_COLOR, 0},
        {"BLUE",  0,         0,         MAX_COLOR},
        {"PINK",  255,       192,       203},
        {nullptr, 0,         0,         0}
};

// 获取全局 int
int getGlobInt(lua_State *L, const char *var) {
    int isNum, result;
    lua_getglobal(L, var);
    result = (int) lua_tointegerx(L, -1, &isNum);
    if (!isNum) {
        error(L, "'%s' should be a number\n", var);
    }
    lua_pop(L, 1);
    return result;
}

int getColorField(lua_State *L, const char *key) {
    int result, isNum;

    // 第一种做法
//    lua_pushstring(L, key);
//    lua_gettable(L, -2);

    // 第二种做法（lua_getfield 和 lua_gettable 都会返回类型）
    if (lua_getfield(L, -1, key) == LUA_TNUMBER) {
        error(L, "invalid component in background color");
    }

    result = (int) (lua_tonumberx(L, -1, &isNum) * MAX_COLOR);
    if (!isNum) {
        error(L, "invalid component '%s' in color", key);
    }
    lua_pop(L, 1);
    return result;
}

void setColorField(lua_State *L, const char *index, int value) {
    // 第一种
//    // 键
//    lua_pushstring(L, index);
//    // 值
//    lua_pushnumber(L, (double) value / MAX_COLOR);
//    lua_settable(L, -3);

    // 第二种
    lua_pushnumber(L, (double) value / MAX_COLOR);
    lua_setfield(L, -2, index);
}

void setColor(lua_State *L, struct ColorTable *ct) {
    // 创建一个空表，并压入栈顶
//    lua_newtable(L);
    lua_createtable(L, 0, 3);

    setColorField(L, "red", ct->red);
    setColorField(L, "green", ct->green);
    setColorField(L, "blue", ct->blue);
    // 'name' = table
    // 弹出表，并且将其设置为指定名称的全局变量的值
    lua_setglobal(L, ct->name);
}

void load(lua_State *L, const char *fname) {
    if (luaL_loadfile(L, fname) || lua_pcall(L, 0, 0, 0)) {
        error(L, "can't run config. file: %s", lua_tostring(L, -1));
    }
    int w = getGlobInt(L, "width");
    int h = getGlobInt(L, "height");
    printf("size: %d x %d\n", w, h);

    int i = 0;
    while (colorTable[i].name != nullptr) {
        setColor(L, &colorTable[i++]);
    }

    // 将 background 压入栈
    lua_getglobal(L, "background");
    if (lua_istable(L, -1)) {
        int red = getColorField(L, "red");
        int green = getColorField(L, "green");
        int blue = getColorField(L, "blue");
        printf("table color: (%d, %d, %d)\n", red, green, blue);

    } else if (lua_isstring(L, -1)) {
        const char *name = lua_tostring(L, -1);
        int i;
        for (i = 0; colorTable[i].name != nullptr; i++) {
            if (strcmp(name, colorTable[i].name) == 0) {
                break;
            }
        }
        if (colorTable[i].name == nullptr) {
            error(L, "invalid color name (%s)", name);
        }
        int red = colorTable[i].red;
        int green = colorTable[i].green;
        int blue = colorTable[i].blue;
        printf("string color: (%d, %d, %d)\n", red, green, blue);

    } else {
        error(L, "'background' is not a table.");
    }


}
