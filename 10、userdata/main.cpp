//
// Created by 江澎涌 on 2023/1/30.
//

#include <cstdio>
#include "用户数据/newarray.h"
#include "用户数据_面向对象/newarray.h"
#include "用户数据_数组访问/newarray.h"

int main() {
    printf("================ 面向对象使用 userdata ================\n");
    arrayDemo();

    printf("\n");
    printf("================ 使用 userdata ================\n");
    arrayObjectDemo();

    printf("\n");
    printf("================ 数组访问 userdata ================\n");
    arrayArrayDemo();

    return 1;
}
