//
// Created by 江澎涌 on 2023/1/27.
//

#include <cstdio>
#include "数组便捷存取/LuaArray.h"
#include "字符串便捷操作/LuaString.h"
#include "注册表/注册表.h"
#include "上值/上值.h"
#include "tuple/tuplelib.h"
#include "共享上值/共享上值.h"

int main(){

    printf("======================== 数组便捷存取 ========================\n");
    luaArrayDemo();

    printf("\n");
    printf("======================== Lua 和 C++ 的 table 操作 ========================\n");
    luaMapFunctionDemo();

    printf("\n");
    printf("======================== string ========================\n");
    printf("------------------------ split ------------------------\n");
    luaStringDemo();

    printf("------------------------ concat ------------------------\n");
    luaConcatDemo();

    printf("------------------------ fstring ------------------------\n");
    luaPushFStringDemo();

    printf("------------------------ buffer ------------------------\n");
    strUpperDemo();

    printf("------------------------ buffer ------------------------\n");
    bufferConcatDemo();

    printf("======================== 注册表 ========================\n");
    printf("------------------------ 引用 ------------------------\n");
    refDemo();
    printf("------------------------ register table ------------------------\n");
    registerTableDemo();

    printf("======================== up value ========================\n");
    upValueDemo();

    printf("======================== tuple ========================\n");
    tupleDemo();

    printf("======================== share up value ========================\n");
    shareUpValueDemo();

    return 1;
}
