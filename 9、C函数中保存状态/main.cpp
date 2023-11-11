//
// Created by 江澎涌 on 2023/1/27.
//

#include <cstdio>
#include "注册表/注册表.h"
#include "上值/上值.h"
#include "tuple/tuplelib.h"
#include "共享上值/共享上值.h"

int main(){
    printf("======================== 注册表 ========================\n");
    printf("------------------------ 模块自定义 key 值 ------------------------\n");
    customKeyRegistryDemo();
    printf("------------------------ 引用系统生成 key 值 ------------------------\n");
    refRegistryDemo();
    printf("------------------------ 静态变量作为 key 值 ------------------------\n");
    cStaticValueRegistryDemo();

    printf("\n");
    printf("======================== up value ========================\n");
    upValueDemo();

    printf("\n");
    printf("======================== tuple ========================\n");
    tupleDemo();

    printf("\n");
    printf("======================== share up value ========================\n");
    shareUpValueDemo();

    return 1;
}
