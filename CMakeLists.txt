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
        lua调用c/lua调用c.cpp
        lua调用c/LuaCallCDemo.cpp
        协程/CoroutineDemo.cpp
        库/库.cpp
        编写C函数技巧/LuaArray.cpp
        编写C函数技巧/LuaString.cpp
        编写C函数技巧/注册表.cpp
        编写C函数技巧/上值/上值.cpp
        编写C函数技巧/tuple/tuplelib.cpp
        编写C函数技巧/共享上值/共享上值.cpp
        用户自定义类型/用户数据/newarray.cpp
        管理资源/file.cpp 管理资源/file.h
        #        管理资源/XmlParser.cpp
        #        管理资源/expat.h
        #        线程和状态/ThreadDemo.cpp
        #        线程和状态/lproc.cpp
)

# 添加链接库
target_link_libraries(Lua_CPP_2022 LuaLib)

add_executable(
        C_API
        1、C_API/c_api_main.cpp
        1、C_API/stack.cpp
        utils/stack_dump.cpp
)
target_link_libraries(C_API LuaLib)

add_executable(
        extend_application
        2、application_extend/application_extend_main.cpp
        2、application_extend/config_parser.cpp
        2、application_extend/调用Lua函数/调用Lua函数.cpp
        2、application_extend/通用调用lua函数/call_va.cpp
        utils/lua_error.cpp
        utils/stack_dump.cpp
)
target_link_libraries(extend_application LuaLib)