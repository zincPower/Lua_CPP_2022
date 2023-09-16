//
// Created by 江澎涌 on 2022/4/28.
//

#include "stack.h"

void showInfo(lua_State *L, ...) {
    va_list args;
    // 用于开启遍历可变参数，第二个参数是可变参数列表的前一参数
    va_start(args, L);
    // 在这里可以使用 va_list 对象 args
    lua_pushvfstring(L, "lua_pushvfstring name: %s, age: %d", args);
    va_end(args);
}

void stackDemo() {
    lua_State *L = luaL_newstate();

    printf("===================== 压栈（ C++ 传递值给 Lua ） =====================\n");
    lua_pushnil(L);
    lua_pushnumber(L, 0.1);
    lua_pushnumber(L, 0);
    lua_pushinteger(L, 10);
    lua_pushboolean(L, 1);
    // lua_pushstring 会在 "\0" 终止
    lua_pushstring(L, "lua_pushstring hello 江澎涌\0jiang peng yong");

    // lua_pushlstring 同样会在 "\0" 终止，但会结合考虑长度参数
    const char *sayHello = "lua_pushlstring hello jiang peng yong.\0 会被忽略的字符";
    lua_pushlstring(L, sayHello, strlen(sayHello) - 6);

    // lua_pushvfstring
    const char *name = "jiang peng yong";
    int age = 29;
    showInfo(L, name, age);

    lua_pushfstring(L, "lua_pushfstring name: %s, age: %d", name, age);

    lua_pushthread(L);
    // 验证 lua_pushthread 中的值，就是 lua_State
    lua_State *threadState = lua_tothread(L, -1);
    luaL_openlibs(threadState);
    // 在线程状态对象上执行Lua代码
    luaL_dostring(threadState, "print('Hello from the thread!')");
    if (L == threadState) {
        printf("L 和 threadState 相同\n");
    }

    printf("\n");
    printf("------ 栈中内容: ------\n");
    LuaExt::stackDump(L);

    printf("\n");
    printf("===================== 栈空间检查 =====================\n");
    int checkSize = lua_checkstack(L, 100000000);
    printf("1,0000,0000 栈空间: %d\n", checkSize);
    checkSize = lua_checkstack(L, 10);
    printf("10 栈空间: %d\n", checkSize);

    // PANIC: unprotected error in call to Lua API (stack overflow (Not enough space.))
//    luaL_checkstack(L, 100000000, "Not enough space.");
    luaL_checkstack(L, 10, "Not enough space.");

    printf("\n");
    printf("===================== 查询元素 =====================\n");
    printf("------ lua_toxxx 的错误表现 ------\n");
    int isNum = false;
    printf("lua_tonumberx(L, -1,&isNum) --> %f\n", lua_tonumberx(L, 1, &isNum));
    printf("lua_tointegerx(L, -1,&isNum) --> %llu\n", lua_tointegerx(L, 1, &isNum));
    printf("lua_toboolean(L, -1) --> %d\n", lua_toboolean(L, 1));

    size_t length = 0;
    printf("lua_tolstring(L, -1, &length) == nullptr --> %d\n", lua_tolstring(L, 1, &length) == nullptr);
    printf("lua_rawlen(L, -1) --> %llu\n", lua_rawlen(L, 1));

    printf("lua_tocfunction(L, -1)) == nullptr --> %d\n", lua_tocfunction(L, 1) == nullptr);
    printf("lua_touserdata(L, -1) == nullptr --> %d\n", lua_touserdata(L, 1) == nullptr);
    printf("lua_tothread(L, -1) == nullptr --> %d\n", lua_tothread(L, 1) == nullptr);
    printf("lua_topointer(L, -1) == nullptr --> %d\n", lua_topointer(L, 1) == nullptr);

    printf("\n");
    printf("------ lua_len 的错误表现 ------\n");
    // 如果获取错误会抛出异常，PANIC: unprotected error in call to Lua API (attempt to get length of a nil value)
//    lua_len(L, 1);
    // 会将 -2 的内容长度压入栈
    lua_len(L, -2);
    // 获取栈顶数据进行打印
    printf("lua_len(L, -2) --> %lld\n", lua_tointeger(L, -1));
    // 将长度弹出
    lua_pop(L, 1);

    printf("\n");
    printf("------ 数值转换 ------\n");
    printf("lua_tonumber(L, -1) %f\n", lua_tonumber(L, -1));
    printf("lua_tointeger(L, -1) %llu\n", lua_tointeger(L, -1));

    int isNumber = false;
    printf("lua_tointegerx(L, 2, &isNumber) %lld\n", lua_tointegerx(L, 2, &isNumber));
    printf("%s 转 integer 是否成功 %s\n", lua_tostring(L, 2), (isNumber == 0 ? "false" : "true"));

    printf("lua_tonumberx(L, 2, &isNumber) %f\n", lua_tonumberx(L, 2, &isNumber));
    printf("%s 转 number 是否成功 %s\n", lua_tostring(L, 2), (isNumber == 0 ? "false" : "true"));

    printf("\n");
    printf("------ lua_tolstring 和 lua_tostring ------\n");
    printf("lua_tolstring(L, -2, nullptr) --> %s\n", lua_tolstring(L, -2, nullptr));
    printf("lua_tostring(L, -2) --> %s\n", lua_tostring(L, -2));
    printf("lua_tostring(L, -1) 获取非字符串内容 --> %s\n", lua_tostring(L, -1));

    printf("\n");
    printf("===================== 栈操作 =====================\n");
    printf("------ 栈中元素个数 ------\n");
    printf("lua_gettop(L) %d\n", lua_gettop(L));
    // 清空栈
    lua_settop(L, 0);
    printf("lua_gettop(L) %d\n", lua_gettop(L));

    printf("\n");
    printf("------ 构建测试数据的栈 ------\n");
    lua_pushnumber(L, 10.8);
    lua_pushstring(L, "jiang peng yong");
    lua_pushnil(L);
    lua_pushinteger(L, 29);
    stackDump(L);

    printf("\n");
    printf("------ lua_absindex ------\n");
    printf("lua_absindex(L, -1) --> %d\n", lua_absindex(L, -1));
    printf("lua_absindex(L, 1) --> %d\n", lua_absindex(L, 1));

    printf("\n");
    printf("------ lua_pushvalue(-3): ------\n");
    // 将栈顶第二位的元素压进栈顶，不会变动原来的数
    lua_pushvalue(L, -3);
    stackDump(L);

    printf("\n");
    printf("------ lua_rotate(3, 1): ------\n");
    // 从指定索引的地方开始转动，n 为正数则往栈顶转，n 为负数则往栈底转
    lua_rotate(L, 3, 1);
    stackDump(L);
    printf("------ lua_rotate(3, -2): ------\n");
    lua_rotate(L, 3, -2);
    stackDump(L);

    printf("\n");
    printf("------  lua_copy(L, 1, -1): ------\n");
    lua_copy(L, 1, -1);
    stackDump(L);

    printf("\n");
    printf("------ lua_insert(2): ------\n");
    // 将栈顶元素移动到指定索引位置
    lua_insert(L, 2);
    stackDump(L);

    printf("------ lua_remove(-3): ------\n");
    // 删除指定索引
    lua_remove(L, -3);
    stackDump(L);

    printf("\n");
    printf("------ lua_replace(1): ------\n");
    // 将栈顶的元素放置到指定的位置，并将栈顶元素弹出
    lua_replace(L, 1);
    stackDump(L);

    printf("\n");
    printf("------ lua_pop(2): ------\n");
    lua_pop(L, 1);
    stackDump(L);

    printf("\n");
    printf("------ lua_gettop(): ------\n");
    printf("lua_gettop(L) --> %d\n", lua_gettop(L));

    printf("\n");
    printf("------ lua_settop(5): ------\n");
    // 设置栈长度，比原先长则用 nil 补，比原先短则截断
    lua_settop(L, 5);
    stackDump(L);

    printf("\n");
    printf("------ lua_settop(3): ------\n");
    lua_settop(L, 3);
    stackDump(L);

    lua_close(L);
}
