# 设置 LUA_DIR 指向 lua-5.4.4 目录
set(LUA_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lua-5.4.4)

# 如果需要使用自己的 c lib ，则需要配置这个
# Mac: LUA_USE_MACOSX
# Linux: LUA_USE_LINUX
# Windows: LUA_USE_WIN
add_definitions(-DLUA_USE_MACOSX)
# 在 lua 中，定义了 LUA_USE_MACOSX 则会定义 LUA_USE_POSIX 和 LUA_USE_DLOPEN
# 所以两者是一样的
#add_definitions(-DLUA_USE_POSIX -DLUA_USE_DLOPEN)

# 设置 Lua 源码
set(LUA_RUNTIME_SOURCES
        "${LUA_DIR}/lapi.c"
        "${LUA_DIR}/lauxlib.c"
        "${LUA_DIR}/lbaselib.c"
        "${LUA_DIR}/lcode.c"
        "${LUA_DIR}/lcorolib.c"
        "${LUA_DIR}/lctype.c"
        "${LUA_DIR}/ldblib.c"
        "${LUA_DIR}/ldebug.c"
        "${LUA_DIR}/ldo.c"
        "${LUA_DIR}/ldump.c"
        "${LUA_DIR}/lfunc.c"
        "${LUA_DIR}/lgc.c"
        "${LUA_DIR}/linit.c"
        "${LUA_DIR}/liolib.c"
        "${LUA_DIR}/llex.c"
        "${LUA_DIR}/lmathlib.c"
        "${LUA_DIR}/lmem.c"
        "${LUA_DIR}/loadlib.c"
        "${LUA_DIR}/lobject.c"
        "${LUA_DIR}/lopcodes.c"
        "${LUA_DIR}/loslib.c"
        "${LUA_DIR}/lparser.c"
        "${LUA_DIR}/lstate.c"
        "${LUA_DIR}/lstring.c"
        "${LUA_DIR}/lstrlib.c"
        "${LUA_DIR}/ltable.c"
        "${LUA_DIR}/ltablib.c"
        "${LUA_DIR}/ltm.c"
        "${LUA_DIR}/lua.c"
        "${LUA_DIR}/lundump.c"
        "${LUA_DIR}/lutf8lib.c"
        "${LUA_DIR}/lvm.c"
        "${LUA_DIR}/lzio.c"
        )

add_library(
        LuaLib
        SHARED
        ${LUA_RUNTIME_SOURCES}
)