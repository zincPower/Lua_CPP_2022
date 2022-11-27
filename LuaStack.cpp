//
// Created by 江澎涌 on 2022/4/28.
//

#include "LuaStack.h"

void stackDump(lua_State *L) {
    int i;
    // 获取栈中元素个数
    int top = lua_gettop(L);
    for (i = 1; i <= top; i++) {
        // 元素类型
        int t = lua_type(L, i);
        switch (t) {
            case LUA_TSTRING:   // 字符串类型
                printf("'%s'", lua_tostring(L, i));
                break;
            case LUA_TBOOLEAN:  // 布尔类型
                printf(lua_toboolean(L, i) ? "true" : "false");
                break;
            case LUA_TNUMBER:   // 数值类型
                if (lua_isinteger(L, i)) {  // 是否整型
                    printf("%lld", lua_tointeger(L, i));
                } else {   // 浮点类型
                    printf("%g", lua_tonumber(L, i));
                }
                break;
            default:     // 其他类型
                // 类型名称
                printf("%s", lua_typename(L, t));
        }
        printf("    ");
    }
    printf("\n");
}

void stackDemo() {
    lua_State *L = luaL_newstate();

    printf("bottom ------------ top\n");

    lua_pushboolean(L, 1);
    lua_pushnumber(L, 10);
    lua_pushnil(L);
    lua_pushstring(L, "hello");

    printf("original:  ");
    stackDump(L);

    // 将栈顶第四位数压进栈顶，不会变动原来的数
    lua_pushvalue(L, -4);
    printf("lua_pushvalue:  ");
    stackDump(L);

    // 将栈顶的值弹出，放置指定位置
    lua_replace(L, 3);
    printf("lua_replace:  ");
    stackDump(L);

    // 设置栈长度，比原先长则用 nil 补，比原先短则截断
    lua_settop(L, 6);
    printf("lua_settop:  ");
    stackDump(L);

    // 从指定索引的地方开始转动，n 为正数则往栈顶转，n 为负数则往栈底转
    lua_rotate(L, 3, 1);
    printf("lua_rotate:  ");
    stackDump(L);

    // 删除指定索引
    lua_remove(L, -3);
    printf("lua_remove:  ");
    stackDump(L);

    // 栈顶值弹出，插入到指定位置
    lua_insert(L, 2);
    printf("lua_insert:  ");
    stackDump(L);

    // 设置栈顶
    lua_settop(L, -5);
    printf("lua_settop:  ");
    stackDump(L);

    lua_close(L);
}
