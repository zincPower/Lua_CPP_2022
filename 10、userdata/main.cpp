//
// Created by 江澎涌 on 2023/1/30.
//

#include <cstdio>
#include "full_userdata/user/1普通版本/user.h"
#include "full_userdata/user/2增加元表检查/user.h"
#include "full_userdata/user/3面向对象/user.h"
#include "full_userdata/array/1普通版本/array.h"
#include "full_userdata/array/2增加元表/array.h"
#include "full_userdata/array/3面向对象/array.h"
#include "full_userdata/array/4数组访问/array.h"
#include "light_userdata/user.h"


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

    printf("\n");
    printf("===============================================\n");
    printf("================ light userdata================\n");
    printf("===============================================\n");

    lightUserdataDemo();

    return 1;
}
