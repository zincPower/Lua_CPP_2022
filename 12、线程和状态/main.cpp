//
// Created by 江澎涌 on 2023/2/2.
//

#include "thread/thread_demo.h"
#include "lproc/lproc.h"

int main(){
    printf("=================== 多线程使用 ===================\n");
    threadDemo();

    printf("=================== 多线程封装 ===================");
    lprocDemo();

    return 1;
}
