//
// Created by 江澎涌 on 2022/5/8.
//

#include "array.h"

// CHAR_BIT 用于表示一个 char 占用的位数，现在的架构基本上都是 8 位，以前旧设备有些是 7 位
// https://stackoverflow.com/questions/3200954/what-is-char-bit
// 1 字节 = 8 位（具体是由 CHAR_BIT 决定）
// BITS_PER_WORD 一个无符号整型数的位数，即 "CHAR_BIT 的位数" 乘以 "无符号整型数" 的尺寸
// I_WORD 用于根据指定的索引来计算存放相应比特位的字，即存放在哪个字节中（存放该比特位的字节索引）
// I_BIT 用于计算访问这个字中相应比特位要用的掩码，即在一个字节中的第几个位
#define BITS_PER_WORD (CHAR_BIT * sizeof(unsigned int))
#define I_WORD(i) ((unsigned int) (i) / BITS_PER_WORD)
#define I_BIT(i) (1 << ((unsigned int) (i) % BITS_PER_WORD))

// 检查第一个参数是否是一个有效的数组
// 如果元表类型不对，则会抛出
// .../Lua/Lua_CPP_2022/10、userdata/用户数据/newarray_数组访问.lua:15: bad argument #1 to 'get' (df expected, got Jiang.array)
#define checkarray(L) (BitArray *)luaL_checkudata(L, 1, META.c_str())

static const std::string META = "Jiang.array_array";

typedef struct BitArray {
    int size;
    // 因为 C89 不允许分配长度位零的数组，所以申明为一
    unsigned int values[1];
} BitArray;

/**
 * 创建数组
 * @param L
 * @return
 */
int newarrayForArray(lua_State *L) {
    int i;
    size_t nbytes;
    BitArray *a;

    // lua 传递过来的参数，
    int n = (int) luaL_checkinteger(L, 1);
    luaL_argcheck(L, n >= 1, 1, "invalid size");

    // 计算所需要的存储长度
    nbytes = sizeof(BitArray) + I_WORD(n - 1) * sizeof(unsigned int);
    // 生成一个 user data 并压入栈中
    a = (BitArray *) lua_newuserdata(L, nbytes);
    a->size = n;
    for (i = 0; i < I_WORD(n - 1); ++i) {
        a->values[i] = 0;
    }

    // 将 META.c_str() 的对应表入栈，然后关联到 -2 的表做元表
    luaL_getmetatable(L, META.c_str());
    lua_setmetatable(L, -2);

    return 1;
}

static unsigned int *getparamsForArray(lua_State *L, unsigned int *mask) {
    auto *a = checkarray(L);
    int index = (int) luaL_checkinteger(L, 2) - 1;

    luaL_argcheck(L, 0 <= index && index < a->size, 2, "index out of range");
    *mask = I_BIT(index);
    return &a->values[I_WORD(index)];
}

static int setarrayForArray(lua_State *L) {
    unsigned int mask;
    unsigned int *entry = getparamsForArray(L, &mask);
    luaL_checkany(L, 3);
    if (lua_toboolean(L, 3)) {
        // 置位
        *entry |= mask;
    } else {
        // 复位
        *entry &= ~mask;
    }
    return 0;
}

static int getarrayForArray(lua_State *L) {
    unsigned int mask;
    unsigned int *entry = getparamsForArray(L, &mask);
    lua_pushboolean(L, *entry & mask);
    return 1;
}

static int getsizeForArray(lua_State *L) {
//    auto *a = (BitArray *) lua_touserdata(L, 1);
//    luaL_argcheck(L, a != nullptr, 1, "'array' expected");
    auto *a = checkarray(L);
    lua_pushinteger(L, a->size);
    return 1;
}

int array2stringForArray(lua_State *L) {
    BitArray *a = checkarray(L);
    lua_pushfstring(L, "array(%d)", a->size);
    return 1;
}

static const struct luaL_Reg arraylib_f_array[] = {
        {"new",   newarrayForArray},
        {nullptr, nullptr}
};
static const struct luaL_Reg arraylib_m_array[] = {
        {"__newindex", setarrayForArray},
        {"__index",    getarrayForArray},
        {"__len",      getsizeForArray},
        {"__tostring", array2stringForArray},
        {nullptr,      nullptr}
};

int luaopen_array_for_array(lua_State *L) {
    // 创建元表
    luaL_newmetatable(L, META.c_str());
    // 注册元方法
    luaL_setfuncs(L, arraylib_m_array, 0);
    // 创建库
    luaL_newlib(L, arraylib_f_array);
    return 1;
}

void arrayArrayDemo() {
    lua_State *L = luaL_newstate();

    luaL_openlibs(L);
    luaopen_array_for_array(L);
    lua_setglobal(L, "array");

    std::string fileName = PROJECT_PATH + "/10、userdata/full_userdata/array/4数组访问/array.lua";
    if (luaL_loadfile(L, fileName.c_str()) || lua_pcall(L, 0, 0, 0)) {
        printf("can't run config. file: %s\n", lua_tostring(L, -1));
    }

    lua_close(L);
}