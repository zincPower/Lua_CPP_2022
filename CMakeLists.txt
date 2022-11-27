cmake_minimum_required(VERSION 3.21)
project(Lua_CPP_2022)

set(CMAKE_CXX_STANDARD 17)

include_directories(lua_lib/lua-5.4.4)
add_subdirectory(lua_lib)

add_executable(
        Lua_CPP_2022
        lua_study_main.cpp
        simple_parser.cpp simple_parser.h
        LuaStack.cpp
        LuaSecureFun.cpp
        extend/ConfigParser.cpp
        调用Lua函数/调用Lua函数.cpp
        Error.cpp
        通用调用lua函数/call_va.cpp
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