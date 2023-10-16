//
// Created by 江澎涌 on 2022/5/1.
//

#include "call_va.h"

void call_va(lua_State *L, const char *func, const char *sig, ...) {
    va_list vl;
    // 参数和结果的个数
    int narg, nres;

    va_start(vl, sig);
    // 函数压栈
    lua_getglobal(L, func);

    // 压入参数
    for (narg = 0; *sig; narg++) {
        luaL_checkstack(L, 1, "too many arguments");

        switch (*sig++) {
            case 'd':
                lua_pushnumber(L, va_arg(vl, double));
                break;
            case 'i':
                lua_pushinteger(L, va_arg(vl, int));
                break;
            case 's':
                lua_pushstring(L, va_arg(vl, char *));
                break;
            case '>':
                goto endargs;
            default:
                error(L, "invalid option (%c)", *(sig - 1));
        }
    }
    endargs:

    nres = strlen(sig);

    if (lua_pcall(L, narg, nres, 0) != 0) {
        error(L, "error calling '%s'", func, lua_tostring(L, -1));
    }

    // 获取输出
    nres = -nres;
    while (*sig) {
        switch (*sig++) {
            case 'd': {
                int isNum;
                double n = lua_tonumberx(L, nres, &isNum);
                if (!isNum) {
                    error(L, "wrong result type");
                }
                *va_arg(vl, double *) = n;
                break;
            }
            case 'i': {
                int isNum;
                long n = lua_tointegerx(L, nres, &isNum);
                if (!isNum) {
                    error(L, "wrong result type");
                }
                *va_arg(vl, long *) = n;
                break;
            }
            case 's': {
                const char *s = lua_tostring(L, nres);
                if (s == nullptr) {
                    error(L, "wrong result type");
                }
                *va_arg(vl, const char **) = s;
                break;
            }
            default:
                error(L, "invalid option (%c)", *(sig - 1));
        }
        nres++;
    }

    va_end(vl);
}

void commonCallLuaDemo(){
    std::string fname = PROJECT_PATH + "/5、C++调用Lua代码/调用Lua函数/调用Lua函数.lua";
    lua_State *L = luaL_newstate();
    // 需要使用 lua_openlibs 进行开启库，否则 lua 中无法使用
    luaL_openlibs(L);
    if (luaL_loadfile(L, fname.c_str()) || lua_pcall(L, 0, 0, 0)) {
        printf("can't run config. file: %s", lua_tostring(L, -1));
        return;
    }
    double z;
    call_va(L, "luaFunction", "dd>d", 2.0, 34.0, &z);
    printf("f: %f\n", z);
    lua_close(L);
}