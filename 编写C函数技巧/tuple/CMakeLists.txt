cmake_minimum_required(VERSION 3.17.5)

set(CMAKE_ANDROID_STL_TYPE c++_shared) # https://blog.csdn.net/fpcc/article/details/72820934
set(CMAKE_BUILD_TYPE DEBUG) #指定生成的版本。RELEASE
set(CMAKE_CXX_STANDARD 11) #c++标准
set(CMAKE_CXX_FLAGS_DEBUG "-std=c++11 -frtti -fexceptions")

project(tuplelib)

include_directories(../../lib/lua-5.4.4)
add_subdirectory(../../lib build)

add_library(TupleLib SHARED tuplelib.c)
target_link_libraries(TupleLib LuaLib)

set_target_properties(TupleLib PROPERTIES OUTPUT_NAME "TupleLib")