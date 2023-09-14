//
// Created by 江澎涌 on 2023/9/8.
//

#include "C++调用Lua异常处理/C++处理Lua异常.h"
#include "Lua调用C++异常处理/Lua处理C++异常.h"
#include "紧急函数/紧急函数.h"
#include "内存分配/自定义内存分配器.h"

int main() {
//    printf("============= C++ 处理 Lua 异常 =============\n");
//    cppHandleLuaError();
//
//    printf("\n");
//    printf("============= Lua 处理 C++ 异常 =============\n");
//    luaHandleCppError();

//    printf("\n");
//    printf("============= Lua 内存分配 =============\n");
//    allocationFunction();

    printf("\n");
    printf("============= Lua 紧急函数 =============\n");
    panicMain();

    return 0;
}