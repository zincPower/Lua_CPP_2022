cmake_minimum_required(VERSION 3.21)
project(MyLib)

set(CMAKE_CXX_STANDARD 17)

include_directories(lua_lib/lua-5.4.4)
add_subdirectory(lua_lib)

add_executable(mylib src/mylib.cpp)
target_link_libraries(mylib LuaLibForLib)

# 在 lib 目录下，运行
# cmake .
# make
# 最后编译出 mylib 就是可以运行的 dylib 库

# cmake .  --> 命令会生成构建系统所需的 Makefile 或其他构建工具的配置文件。
# make     --> make命令用于执行构建系统所生成的 Makefile 文件，进行项目的编译和构建。

# nm -gm mylib 进行查看 lib 中的接口