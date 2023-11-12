//
// Created by 江澎涌 on 2023/1/30.
//

#include <cstdio>
#include "user/1普通版本/user.h"
#include "user/2增加元表检查/user.h"
#include "user/3面向对象/user.h"
#include "array/1普通版本/array.h"
#include "array/2增加元表/array.h"
#include "array/3面向对象/array.h"
#include "array/4数组访问/array.h"

int main() {
    printf("\n");
    printf("==============================================\n");
    printf("================ user userdata================\n");
    printf("==============================================\n");
    printf("\n");
    printf("================ 1普通版本 ================\n");
    userSimpleDemo();

    printf("\n");
    printf("================ 2增加元表 ================\n");
    userMetatableDemo();

    printf("\n");
    printf("================ 3面向对象 ================\n");
    userObjDemo();

    printf("\n");
    printf("===============================================\n");
    printf("================ array userdata================\n");
    printf("===============================================\n");
    printf("\n");
    printf("================ 1普通版本 ================\n");
    arraySimpleDemo();

    printf("\n");
    printf("================ 2增加元表 ================\n");
    arrayUseMetatableDemo();

    printf("\n");
    printf("================ 3面向对象 ================\n");
    arrayObjectDemo();

    printf("\n");
    printf("================ 4数组访问 ================\n");
    arrayArrayDemo();

    return 1;
}
