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
        5、C++调用Lua代码/Lua作为配置文件/根据环境变量获取值/config_use_env.cpp
        5、C++调用Lua代码/Lua作为配置文件/配置中使用表/config_use_table.cpp
        5、C++调用Lua代码/调用Lua函数/调用Lua函数.cpp
        5、C++调用Lua代码/通用调用lua函数/call_va.cpp
        config/env_config.cpp
        utils/lua_error.cpp
        utils/lua_ext.cpp
)
target_link_libraries(5_CPP_Call_Lua LuaLib)

# 6、 Lua 回调 C++
add_executable(
        6_Lua_Call_CPP
        6、Lua回调C++/main.cpp
        6、Lua回调C++/调用C++函数/简易的sin函数.cpp
        6、Lua回调C++/调用C++函数/读取目录函数.cpp
        6、Lua回调C++/协程/CoroutineDemo.cpp
        6、Lua回调C++/Lua调用C++的lib/
        config/env_config.cpp
        utils/lua_ext.cpp
)
target_link_libraries(6_Lua_Call_CPP LuaLib)

# 7、Lua调用C++的lib
add_executable(
        7_Lua_Call_CPP_Lib
        7、Lua调用C++的lib/main.cpp
        config/env_config.cpp
        utils/lua_ext.cpp
)
target_link_libraries(7_Lua_Call_CPP_Lib LuaLib)

# 8、编写 C 函数技巧
add_executable(
        8_C_Function_Skill
        8、编写C函数便捷技巧/main.cpp
        8、编写C函数便捷技巧/数组便捷存取/LuaArray.cpp
        8、编写C函数便捷技巧/字符串便捷操作/LuaString.cpp
        9、C函数中保存状态/注册表/注册表.cpp
        9、C函数中保存状态/共享上值/共享上值.cpp
        9、C函数中保存状态/上值/上值.cpp
        9、C函数中保存状态/tuple/tuplelib.cpp
        9、C函数中保存状态/共享上值/共享上值.cpp
        config/env_config.cpp
        utils/lua_error.cpp
        utils/lua_ext.cpp
)
target_link_libraries(8_C_Function_Skill LuaLib)

# 9、C函数中保存状态
add_executable(
        9_C_Save_State
        9、C函数中保存状态/main.cpp
        9、C函数中保存状态/注册表/注册表.cpp
        9、C函数中保存状态/共享上值/共享上值.cpp
        9、C函数中保存状态/上值/上值.cpp
        9、C函数中保存状态/tuple/tuplelib.cpp
        9、C函数中保存状态/共享上值/共享上值.cpp
        config/env_config.cpp
        utils/lua_error.cpp
        utils/lua_ext.cpp
)
target_link_libraries(9_C_Save_State LuaLib)

# 10、userdata
add_executable(
        10_Userdata
        10、userdata/main.cpp
        10、userdata/用户数据/newarray.cpp
        10、userdata/用户数据_面向对象/newarray.cpp
        10、userdata/用户数据_数组访问/newarray.cpp
        utils/lua_error.cpp
        utils/lua_ext.cpp)
target_link_libraries(10_Userdata LuaLib)

# 10、管理资源
# https://github.com/libexpat/libexpat/tree/R_2_5_0
find_package(EXPAT 2.4.8 MODULE REQUIRED)
add_executable(
        10_Manage_Resource
        10、管理资源/main.cpp
        10、管理资源/file/file.cpp
        10、管理资源/xml/xml_parser.cpp
        utils/lua_error.cpp
        utils/lua_ext.cpp)
target_link_libraries(10_Manage_Resource PUBLIC LuaLib EXPAT::EXPAT)
target_include_directories(10_Manage_Resource PRIVATE ${EXPAT_INCLUDE_DIRS})
target_link_libraries(10_Manage_Resource PUBLIC ${EXPAT_LIBRARIES})

# 11、线程和状态
add_executable(
        11_Thread_And_State
        11、线程和状态/main.cpp
        11、线程和状态/thread/ThreadDemo.cpp
        11、线程和状态/lproc/lproc.cpp
        utils/lua_error.cpp
        utils/lua_ext.cpp)
target_link_libraries(11_Thread_And_State LuaLib)