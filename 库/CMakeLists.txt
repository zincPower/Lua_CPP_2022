cmake_minimum_required(VERSION 3.17.5)
project(CPP2022)

set(CMAKE_CXX_STANDARD 14)

add_library(
        mylib
        SHARED
        mylib.cpp
)
#include_directories(../../lua/lib/lua-5.4.4)
#add_subdirectory(../../lua/lib)

#ADD_EXECUTABLE(mylib lua/库/mylib.cpp)

#target_link_libraries(mylib LuaLib)

