//
// Created by 江澎涌 on 2023/1/27.
//

#include <cstdio>
#include "数组便捷存取/LuaArray.h"
#include "字符串便捷操作/LuaString.h"

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

    return 1;
}
