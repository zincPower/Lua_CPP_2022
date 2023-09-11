//
// Created by 江澎涌 on 2023/9/8.
//

#include "C++调用Lua异常处理/C++处理Lua异常.h"
#include "Lua调用C++异常处理/Lua处理C++异常.h"

int main() {
    secureFoo();
//    simpleParser();
    luaHandleCppError();
    return 0;
}