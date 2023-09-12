//
// Created by 江澎涌 on 2023/9/11.
//

#include "lua_ext.h"

namespace LuaExt {
/**
 * 栈打印
 * @param L lua_State
 */
void stackDump(lua_State *L) {
    int i;
    // 获取栈中元素个数
    int top = lua_gettop(L);
    printf("栈顶\n");
    for (i = top; i >= 1; i--) {
        // 元素类型
        int t = lua_type(L, i);
        // 元素类型名称
        printf("^ typename: %s, ", lua_typename(L, t));
        switch (t) {
            case LUA_TSTRING:   // 字符串类型
                printf("value: '%s'", lua_tostring(L, i));
                break;
            case LUA_TBOOLEAN:  // 布尔类型
                printf(lua_toboolean(L, i) ? "value: true" : "value: false");
                break;
            case LUA_TNUMBER:   // 数值类型
                if (lua_isinteger(L, i)) {  // 是否整型
                    printf("value(integer): %lld", lua_tointeger(L, i));
                } else {   // 浮点类型
                    printf("value(number): %g", lua_tonumber(L, i));
                }
                break;
            default:     // 其他类型
                // 类型名称
                printf("value: %s", lua_typename(L, t));
        }
        printf("    \n");
    }
    printf("栈底\n");
    printf("\n");
}

const char *getLuaErrorMsg(lua_State *L) {
    // 获取字符串和数值错误信息
    const char *msg = lua_tostring(L, -1);
    if (msg) return msg;

    // 获取 table 的 __tostring 错误信息
    if (luaL_callmeta(L, -1, "__tostring")) {
        msg = lua_tostring(L, -1);
        if (msg) return msg;
    }

    // 获取布尔值的错误信息
    if (lua_isboolean(L, -1)) {
        if (lua_toboolean(L, -1)) {
            return "true";
        } else {
            return "false";
        }
    }

    // nil、函数、table 没有 __tostring 元方法则会返回这个错误信息
    return "no error message";
}

// 错误处理
int errorTraceback(lua_State *L) {
    auto msg = getLuaErrorMsg(L);

//    printf("\n");
//    printf("-------- traceback 中的 stack 数据（未增加错误信息） --------\n");
//    stackDump(L);

    // 获取函数调用堆栈信息的错误回溯信息
    luaL_traceback(L, L, msg, 1);

//    printf("-------- traceback 中的 stack 数据（增加错误信息） --------\n");
//    stackDump(L);

    return 1;
}

/**
 * 安全调用 Lua 函数，会自动设置异常处理函数
 * @param L lua_State
 * @param narg 入参个数
 * @param nres 出参个数
 * @return 是否运行成功
 *         - 0 运行成功
 *         - 非 0 运行失败，栈顶的第一个元素（即下标 -1 元素）为错误原因
 */
int safeCallLua(lua_State *L, int narg, int nres) {
    // 计算新压入多少个参数
    int base = lua_gettop(L) - narg;
    // 压入异常处理函数
    lua_pushcfunction(L, errorTraceback);
    // 将异常处理函数压入到 base 下标的位置
    lua_insert(L, base);
    // 调用 Lua 函数
    int status = lua_pcall(L, narg, nres, base);
    // 移除异常处理函数
    lua_remove(L, base);
    return status;
}
}