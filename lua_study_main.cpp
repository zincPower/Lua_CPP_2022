//
// Created by 江澎涌 on 2022/1/12.
//
#include "iostream"
#include "string"

void printDivide(std::string title) {
    std::cout << std::endl;
    std::cout << "================ " << title << " =====================" << std::endl;
}

int main() {

    printDivide("Lua");

//    printDivide("lua stack");
//    stackDemo();
//
//    printDivide("lua error");
//    lua_State *L = luaL_newstate();
//    printf("secureFoo result: %d", secureFoo(L));
//    lua_close(L);
//
//    printDivide("lua config");
//    std::string fname1 = "/Users/jiangpengyong/Desktop/code/CPP/CPP2022/lua/2、application_extend/config.lua";
//    lua_State *L1 = luaL_newstate();
//    // 需要使用 lua_openlibs 进行开启库，否则 lua 中无法使用
//    luaL_openlibs(L1);
//    load(L1, fname1.c_str());
//    lua_close(L1);
//
//    printDivide("lua config");
//    std::string fname2 = "/Users/jiangpengyong/Desktop/code/CPP/CPP2022/lua/调用Lua函数/调用Lua函数.lua";
//    lua_State *L2 = luaL_newstate();
//    // 需要使用 lua_openlibs 进行开启库，否则 lua 中无法使用
//    luaL_openlibs(L2);
//    loadForFunction(L2, fname2.c_str());
//    printf("f: %f\n", f(L2, 2, 34));
//    lua_close(L2);
//
//    printDivide("lua call_va");
//    std::string fname3 = "/Users/jiangpengyong/Desktop/code/CPP/CPP2022/lua/调用Lua函数/调用Lua函数.lua";
//    lua_State *L3 = luaL_newstate();
//    // 需要使用 lua_openlibs 进行开启库，否则 lua 中无法使用
//    luaL_openlibs(L3);
//    loadForFunction(L3, fname3.c_str());
//    double z;
//    call_va(L3, "f", "dd>d", 2.0, 34.0, &z);
//    printf("f: %f\n", z);
//    lua_close(L3);
//
//    printDivide("lua lua call c");
//    luaCallCDemo();

//    printDivide("lua coroutine");
//    coroutineDemo();

//    printDivide("lua_lib");
//    libDemo();

//    printDivide("lua_array");
//    luaArrayDemo();

//    printDivide("lua_map");
//    luaMapFunctionDemo();

//    printDivide("lua_string");
//    luaStringDemo();

//    printDivide("lua_concat");
//    luaConcatDemo();

//    printDivide("lua_pushFString");
//    luaPushFStringDemo();

//    printDivide("lua_buffer");
//    strUpperDemo();

//    printDivide("lua_buffer");
//    bufferConcatDemo();

//    printDivide("lua_registerTable");
//    registerTableDemo();

//    printDivide("lua_register_ref");
//    refDemo();

//    printDivide("lua_upValue");
//    upValueDemo();

//    printDivide("lua_upValueTuple");
//    tupleDemo();

//    printDivide("lua_共享上值");
//    shareUpValueDemo();

//    printDivide("lua_userdata-array");
//    arrayDemo();

//    printDivide("lua_resource_manager");
//    resourceManageDemo();

//    printDivide("lua_xml");
//    xmlParserDemo();

//    printDivide("lua_thread");
//    threadDemo();

    return 0;
}