//
// Created by 江澎涌 on 2022/4/29.
//

#include <cstring>
#include "lua.hpp"
#include "../utils/lua_error.h"
#include "../utils/stack_dump.h"

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

/**
 * 获取全局 int
 * @param L lua state
 * @param var 字段名
 * @return lua 中字段名对应的值
 * lua_getglobal 将会从 lua 中读取全局变量，将值压入栈中
 */
int getGlobInt(lua_State *L, const char *var) {
    int isNum, result;
    // 将 var 对应的值压入栈中
    lua_getglobal(L, var);
    result = (int) lua_tointegerx(L, -1, &isNum);
    if (!isNum) {
        error(L, "'%s' should be a number\n", var);
    }
    // 将 var 对应值压入栈中的值弹出
    lua_pop(L, 1);
    return result;
}

/**
 * 获取 lua 中 table 颜色值
 * @param L lua state
 * @param key 字段名
 * @return 获取字段名的值
 * 步骤：
 * 栈顶已经有一个 table
 * 1、将 key 压入栈中
 * 2、lua_table 将栈顶 key 弹出，从 table 中读取后压入栈
 */
int getColorField(lua_State *L, const char *key) {
    int result, isNum;

    // 第一种做法
    // 将 key 压入栈
    lua_pushstring(L, key);
    // 将栈顶（key）弹出，然后将读取的值压入
    lua_gettable(L, -2);

    // 第二种做法（lua_getfield 和 lua_gettable 都会返回类型）
//    if (lua_getfield(L, -1, key) == LUA_TNUMBER) {
//        error(L, "invalid component in background color");
//    }

    result = (int) (lua_tonumberx(L, -1, &isNum) * MAX_COLOR);
    if (!isNum) {
        error(L, "invalid component '%s' in color", key);
    }

    lua_pop(L, 1);
    return result;
}

/**
 * 设置 lua 中颜色值
 * @param L lua state
 * @param index 索引（颜色名）
 * @param value 值
 * 步骤：（栈顶是 table ）
 * 1、将 key 值压栈（ 栈底 -> table -> key -> 栈顶 ）
 * 2、将 value 值压栈（ 栈底 -> table -> key -> value -> 栈顶 ）
 * 3、设置进 table ，弹出 value 、 key ，设置 table[stack[-2]] = stack[-1]
 */
void setColorField(lua_State *L, const char *index, int value) {
    // 第一种
    // 键
    lua_pushstring(L, index);
    // 值
    lua_pushnumber(L, (double) value / MAX_COLOR);
    // 将键和值弹出，然后设置到 table 中，table[stack[-2]] = stack[-1]
    lua_settable(L, -3);

    // 第二种
//    lua_pushnumber(L, (double) value / MAX_COLOR);
//    lua_setfield(L, -2, index);
}

/**
 * 设置颜色
 * @param L
 * @param ct
 */
void setColor(lua_State *L, struct ColorTable *ct) {
    // 创建一个空表，并压入栈顶
    // lua_newtable 这是一个宏，真是定义是 lua_createtable(L, 0, 0)
    // lua_newtable 和 lua_createtable 会压入一个 table 到栈中
    lua_newtable(L);
//    lua_createtable(L, 0, 3);

    setColorField(L, "red", ct->red);
    setColorField(L, "green", ct->green);
    setColorField(L, "blue", ct->blue);

    // 'name' = table
    // 弹出表，并且将其设置为指定名称的全局变量的值
    lua_setglobal(L, ct->name);
}

void load(lua_State *L, const char *fname) {
    int i = 0;
    while (colorTable[i].name != nullptr) {
        setColor(L, &colorTable[i++]);
    }

    if (luaL_loadfile(L, fname) || lua_pcall(L, 0, 0, 0)) {
        error(L, "can't run config. file: %s", lua_tostring(L, -1));
    }

    int w = getGlobInt(L, "width");
    int h = getGlobInt(L, "height");
    printf("size: %d x %d\n", w, h);

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
