//
// Created by 江澎涌 on 2023/1/24.
//

#include "stack_dump.h"

/**
 * 栈打印
 * @param L lua_State
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