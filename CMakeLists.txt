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

add_executable(
        Lua_CPP_2022
        lua_study_main.cpp
        2、application_extend/调用Lua函数/调用Lua函数.cpp
        2、application_extend/通用调用lua函数/call_va.cpp
        3、lua_call_c/lua_call_c.cpp
        3、lua_call_c/lua_call_c_main.cpp
        协程/CoroutineDemo.cpp
        5、编写C函数技巧/LuaArray.cpp
        5、编写C函数技巧/LuaString.cpp
        5、编写C函数技巧/注册表.cpp
        5、编写C函数技巧/上值/上值.cpp
        5、编写C函数技巧/tuple/tuplelib.cpp
        5、编写C函数技巧/共享上值/共享上值.cpp
        6、userdata/用户数据/newarray.cpp
        管理资源/file.cpp 管理资源/file.h
        #        管理资源/XmlParser.cpp
        #        管理资源/expat.h
        #        线程和状态/ThreadDemo.cpp
        #        线程和状态/lproc.cpp
        5、编写C函数技巧/main.cpp)

# 添加链接库
target_link_libraries(Lua_CPP_2022 LuaLib)

# 1、 c api
add_executable(
        1_C_API
        1、C_API/c_api_main.cpp
        1、C_API/stack.cpp
        utils/stack_dump.cpp
        6、userdata/main.cpp)
target_link_libraries(1_C_API LuaLib)

# 2、 c 调用 lua 函数
add_executable(
        2_application_extend
        2、application_extend/application_extend_main.cpp
        2、application_extend/config_parser.cpp
        2、application_extend/调用Lua函数/调用Lua函数.cpp
        2、application_extend/通用调用lua函数/call_va.cpp
        utils/lua_error.cpp
        utils/stack_dump.cpp
)
target_link_libraries(2_application_extend LuaLib)

# 3、 lua 调用 c 函数
add_executable(
        3_lua_call_c
        3、lua_call_c/lua_call_c_main.cpp
        utils/lua_error.cpp
        utils/stack_dump.cpp
)
target_link_libraries(3_lua_call_c LuaLib)

# 4、 调用 lua_call_c_lib
add_executable(
        4_lua_call_c_lib
        4、lua_call_c_lib/c_lib_main.cpp
        utils/lua_error.cpp
        utils/stack_dump.cpp
)
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
        utils/stack_dump.cpp
)
target_link_libraries(5_c_function_skill LuaLib)

# 6、userdata
add_executable(
        6_userdata
        6、userdata/main.cpp
        6、userdata/用户数据/newarray.cpp
        6、userdata/用户数据_面向对象/newarray.cpp
        6、userdata/用户数据_数组访问/newarray.cpp
        utils/lua_error.cpp
        utils/stack_dump.cpp
)
target_link_libraries(6_userdata LuaLib)

