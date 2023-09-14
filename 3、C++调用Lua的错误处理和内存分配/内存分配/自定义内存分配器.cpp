//
// Created by 江澎涌 on 2023/9/13.
//

#include "自定义内存分配器.h"

static void *alloc(void *ud, void *ptr, size_t osize, size_t nsize) {
    const char *udContent = *(const char **) ud;
    std::cout << "ud: " << udContent << "; *ptr: " << ptr << "; osize: " << osize << "; nsize: " << nsize << std::endl;
    if (nsize == 0) {
        free(ptr);
        return nullptr;
    } else
        return realloc(ptr, nsize);
}

void allocationFunction() {
    // 常规的创建 lua_State
//    auto L = luaL_newstate();

    printf("------------- 自定义内存分配函数 -------------\n");
    // 自定义内存分配数据
    auto ud = "ud test message.";
    auto L = lua_newstate(alloc, &ud);

//    printf("------------- 获取 Lua 自带的内存分配函数 -------------\n");
//    // lua_getallocf 第二个参数会返回之前设置的 自定义内存分配数据
//    void *userData = nullptr;
//    lua_Alloc allocFunc = lua_getallocf(L, &userData);
//    const char *udContent = *(const char **) userData;
//    std::cout << udContent << std::endl;
//
//    printf("------------- 设置 Lua 自带的内存分配函数 -------------\n");
//    lua_setallocf(L, allocFunc, nullptr);

    std::cout << "关闭 lua_State " << std::endl;
    lua_close(L);

}