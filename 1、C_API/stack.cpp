//
// Created by 江澎涌 on 2022/4/28.
//

#include "stack.h"

/**
 * 栈打印
 * @param L
 */
void stackDump(lua_State *L) {
    int i;
    // 获取栈中元素个数
    int top = lua_gettop(L);
    for (i = top; i >= 1; i--) {
        // 元素类型
        int t = lua_type(L, i);
        // 元素类型名称
        printf("typename: %s|", lua_typename(L, t));
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
        printf("    \n");
    }
    printf("\n");
}

void stackDemo() {
    lua_State *L = luaL_newstate();

    int checkSize = lua_checkstack(L, 100000000);
    printf("1,0000,0000 栈空间: %d\n", checkSize);
    checkSize = lua_checkstack(L, 10);
    printf("10 栈空间: %d\n", checkSize);

    // PANIC: unprotected error in call to Lua API (stack overflow (Not enough space.))
//    luaL_checkstack(L, 100000000, "Not enough space.");
    luaL_checkstack(L, 10, "Not enough space.");

    // 将数值压入栈
    lua_pushboolean(L, 1);
    lua_pushinteger(L, 10);
    lua_pushnumber(L, 0);
    lua_pushnumber(L, 0.1);
    lua_pushnil(L);
    lua_pushstring(L, "hello");

    printf("------ 栈中内容: ------\n");
    printf("bottom >>>>>>>>>>>>>>>>>> top\n");
    stackDump(L);

    printf("------ lua_tonumberx ------\n");
    int isNumber = false;
    lua_tointegerx(L, 2, &isNumber);
    printf("integer isNumber: %s\n", (isNumber == 0 ? "false" : "true"));
    lua_tonumberx(L, 1, &isNumber);
    printf("boolean isNumber: %s\n", (isNumber == 0 ? "false" : "true"));

    printf("------ lua_tolstring ------\n");
    printf("%s\n", lua_tolstring(L, -1, nullptr));
    printf("%s\n", lua_tostring(L, -1));

    printf("------ 栈中元素个数 ------\n");
    printf("%d\n", lua_gettop(L));

    printf("------ lua_pushvalue(-4): ------\n");
    // 将栈顶第四位数压进栈顶，不会变动原来的数
    lua_pushvalue(L, -4);
    stackDump(L);

    printf("------ lua_replace(1): ------\n");
    // 将栈顶的元素放置到指定的位置，并将栈顶元素弹出
    lua_replace(L, 1);
    stackDump(L);

    printf("------ lua_settop(5): ------\n");
    // 设置栈长度，比原先长则用 nil 补，比原先短则截断
    lua_settop(L, 5);
    stackDump(L);

    lua_settop(L, 6);
    stackDump(L);

    printf("------ lua_rotate(3, 1): ------\n");
    // 从指定索引的地方开始转动，n 为正数则往栈顶转，n 为负数则往栈底转
    lua_rotate(L, 3, 1);
    stackDump(L);
//    lua_rotate(L, 3, -2);
//    stackDump(L);

    printf("------ lua_remove(-3): ------\n");
    // 删除指定索引
    lua_remove(L, -3);
    stackDump(L);

    printf("------ lua_insert(2): ------\n");
    // 将栈顶元素移动到指定索引位置
    lua_insert(L, 2);
    stackDump(L);

    printf("------ lua_settop(-5): ------\n");
    // 设置栈顶
    lua_settop(L, -5);
    printf("  \n");
    stackDump(L);

    lua_close(L);
}
