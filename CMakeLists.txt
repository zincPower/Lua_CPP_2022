cmake_minimum_required(VERSION 3.21)
project(Lua_CPP_2022)

set(CMAKE_CXX_STANDARD 17)

# 将 lua_lib/lua-5.4.4 目录添加至编译器的搜索目录中
# 这样使用 Lua 的源文件时，#include 的文件路径就不需要使用 "lua_lib/lua-5.4.4" 了
# 如果没有这一句，使用 "lua.hpp" ，就需要 #include "lua_lib/lua-5.4.4/lua.hpp"
# 有了这一句，就只需要 #include "lua.hpp"
include_directories(lua_lib/lua-5.4.4)
# 将子目录添加到构建中
# 参数 source_dir（ 即这里的 lua_lib ）指定源 CMakeLists.txt 和代码文件所在的目录
# 这样就会把 lua_lib/CMakeLists.txt 加入到构建中
add_subdirectory(lua_lib)

# 1、 C++ 集成 Lua
add_executable(
        1_CPP_integration_Lua
        1、C++集成Lua/main.cpp
        1、C++集成Lua/simple_parser.cpp
        utils/lua_ext.cpp
        config/env_config.cpp
)
target_link_libraries(1_CPP_integration_Lua LuaLib)

# 2、 C++ 与 Lua 数据交互载体——栈
add_executable(
        2_CPP_Lua_communication_stack
        2、C++与Lua数据交互载体——栈/main.cpp
        2、C++与Lua数据交互载体——栈/stack.cpp
        utils/lua_ext.cpp
)
target_link_libraries(2_CPP_Lua_communication_stack LuaLib)

# 3、C++与Lua交互错误处理
add_executable(
        3_CPP_Lua_handle_error
        3、C++与Lua交互错误处理/main.cpp
        3、C++与Lua交互错误处理/C++调用Lua异常处理/C++处理Lua异常.cpp
        3、C++与Lua交互错误处理/Lua调用C++异常处理/Lua处理C++异常.cpp
        3、C++与Lua交互错误处理/紧急函数/紧急函数.cpp
        config/env_config.cpp
        utils/lua_ext.cpp
)
target_link_libraries(3_CPP_Lua_handle_error LuaLib)

# 4、C++与Lua交互内存管理
add_executable(
        4_CPP_Lua_alloc_memory
        4、C++与Lua交互内存管理/main.cpp
        4、C++与Lua交互内存管理/自定义内存分配器.cpp
        config/env_config.cpp
        utils/lua_ext.cpp
)
target_link_libraries(4_CPP_Lua_alloc_memory LuaLib)

# 5、 C++ 调用 Lua 函数
add_executable(
        5_CPP_Call_Lua
        5、C++调用Lua代码/main.cpp
        5、C++调用Lua代码/Lua作为配置文件/config_parser.cpp
        5、C++调用Lua代码/调用Lua函数/调用Lua函数.cpp
        5、C++调用Lua代码/通用调用lua函数/call_va.cpp
        config/env_config.cpp
        utils/lua_error.cpp
        utils/lua_ext.cpp
)
target_link_libraries(5_CPP_Call_Lua LuaLib)

# 3、 lua 调用 c 函数
add_executable(
        3_lua_call_c
        3、lua_call_c/main.cpp
        utils/lua_error.cpp
        utils/lua_ext.cpp)
target_link_libraries(3_lua_call_c LuaLib)

# 4、 调用 lua_call_c_lib
add_executable(
        4_lua_call_c_lib
        4、lua_call_c_lib/main.cpp
        utils/lua_error.cpp
        utils/lua_ext.cpp)
target_link_libraries(4_lua_call_c_lib LuaLib)

# 5、 编写 C 函数技巧
add_executable(
        5_c_function_skill
        5、编写C函数技巧/main.cpp
        5、编写C函数技巧/LuaArray.cpp
        5、编写C函数技巧/LuaString.cpp
        5、编写C函数技巧/注册表.cpp
        5、编写C函数技巧/共享上值/共享上值.cpp
        5、编写C函数技巧/上值/上值.cpp
        5、编写C函数技巧/tuple/tuplelib.cpp
        5、编写C函数技巧/共享上值/共享上值.cpp
        utils/lua_error.cpp
        utils/lua_ext.cpp)
target_link_libraries(5_c_function_skill LuaLib)

# 6、userdata
add_executable(
        6_userdata
        6、userdata/main.cpp
        6、userdata/用户数据/newarray.cpp
        6、userdata/用户数据_面向对象/newarray.cpp
        6、userdata/用户数据_数组访问/newarray.cpp
        utils/lua_error.cpp
        utils/lua_ext.cpp)
target_link_libraries(6_userdata LuaLib)

# 7、管理资源
# https://github.com/libexpat/libexpat/tree/R_2_5_0
find_package(EXPAT 2.4.8 MODULE REQUIRED)
add_executable(
        7_manage_resource
        7、管理资源/main.cpp
        7、管理资源/file/file.cpp
        7、管理资源/xml/xml_parser.cpp
        utils/lua_error.cpp
        utils/lua_ext.cpp)
target_link_libraries(7_manage_resource PUBLIC LuaLib EXPAT::EXPAT)
target_include_directories(7_manage_resource PRIVATE ${EXPAT_INCLUDE_DIRS})
target_link_libraries(7_manage_resource PUBLIC ${EXPAT_LIBRARIES})

# 8、线程和状态
add_executable(
        8_thread_and_state
        8、线程和状态/main.cpp
        8、线程和状态/thread/ThreadDemo.cpp
        8、线程和状态/lproc/lproc.cpp
        utils/lua_error.cpp
        utils/lua_ext.cpp)
target_link_libraries(8_thread_and_state LuaLib)