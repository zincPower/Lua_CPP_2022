//
// Created by 江澎涌 on 2022/5/9.
//

#include <iostream>

#include "xml_parser.h"
#include "expat.h"
#include "lua.hpp"

#include "../../utils/lua_error.h"
#include "../../utils/stack_dump.h"

typedef struct lxp_userdata {
    XML_Parser parser;
    lua_State *L;
} lxp_userdata;

static void f_StartElement(void *ud, const char *name, const char **atts);

static void f_CharData(void *ud, const char *s, int len);

static void f_EndElement(void *ud, const char *name);

const static std::string LXP_META_TABLE = "Expat";

static int lxp_make_parser(lua_State *L) {
    XML_Parser p;

    auto *xpu = (lxp_userdata *) lua_newuserdata(L, sizeof(lxp_userdata));
    xpu->parser = nullptr;

    // 获取元表
    luaL_getmetatable(L, LXP_META_TABLE.c_str());
    // 设置元表
    lua_setmetatable(L, -2);

    p = xpu->parser = XML_ParserCreate(nullptr);
    if (!p) {
        luaL_error(L, "XML_ParserCreate failed.");
    }

    // 检查并保存回调函数表
    // 第一个参数就是 Lua 中的 callback 函数
    luaL_checktype(L, 1, LUA_TTABLE);
    lua_pushvalue(L, 1);
    // lua_setuservalue 从堆栈中弹出一个值并将其设置为与给定索引处的完整用户数据关联的新值
    // 每个用户数据（user data）都可以有一个与其直接关联的唯一的 Lua 语言值，这个值为用户值（user value）
    // -2 是一个 user data
    // -1 是一个 callback
    lua_setuservalue(L, -2);

    XML_SetUserData(p, xpu);
    XML_SetElementHandler(p, f_StartElement, f_EndElement);
    XML_SetCharacterDataHandler(p, f_CharData);

    return 1;
}

static int lxp_parse(lua_State *L) {
    int status;
    size_t len;
    const char *s;
    lxp_userdata *xpu;

    // 获取第一个参数
    xpu = (lxp_userdata *) luaL_checkudata(L, 1, LXP_META_TABLE.c_str());

    luaL_argcheck(L, xpu->parser != nullptr, 1, "parser is closed");

    // 获取第二个参数
    s = luaL_optlstring(L, 2, nullptr, &len);

    // 将回调函数表放在栈索引为 3 的位置
    lua_settop(L, 2);
    // 获取 user data 的 user value ，即 lua 文件设置的 callback
    lua_getuservalue(L, 1);

    xpu->L = L;

    // 这里会触发回调，回调中的 lua_State 的栈深度也就是此时的栈深度
    // 3、回调表
    // 2、内容
    // 1、user data
    status = XML_Parse(xpu->parser, s, (int) len, s == nullptr);

    // 返回错误码
    lua_pushboolean(L, status);
    return 1;
}

static void f_CharData(void *ud, const char *s, int len) {
    auto *xpu = (lxp_userdata *) ud;
    lua_State *L = xpu->L;

    // 从回调函数表中获取处理函数
    lua_getfield(L, 3, "CharacterData");

    // 没有处理函数？
    if (lua_isnil(L, -1)) {
        lua_pop(L, 1);
        return;
    }

    // 解析器压栈（parser）
    lua_pushvalue(L, 1);
    // 压入字符数据（content）
    lua_pushlstring(L, s, len);
    // 调用处理函数
    lua_call(L, 2, 0);
}

static void f_EndElement(void *ud, const char *name) {
    auto *xpu = (lxp_userdata *) ud;
    lua_State *L = xpu->L;

    lua_getfield(L, 3, "EndElement");
    if (lua_isnil(L, -1)) {
        lua_pop(L, 1);
        return;
    }

    lua_pushvalue(L, 1);
    lua_pushstring(L, name);
    lua_call(L, 2, 0);
}

static void f_StartElement(void *ud, const char *name, const char **atts) {
    auto *xpu = (lxp_userdata *) ud;
    lua_State *L = xpu->L;

    lua_getfield(L, 3, "StartElement");
    if (lua_isnil(L, -1)) {
        lua_pop(L, 1);
        return;
    }

    lua_pushvalue(L, 1);
    lua_pushstring(L, name);

    lua_newtable(L);
    for (; *atts; atts += 2) {
        lua_pushstring(L, *(atts + 1));
        lua_setfield(L, -2, *atts);
    }

    lua_call(L, 3, 0);
}

static int lxp_close(lua_State *L) {
    auto *xpu = (lxp_userdata *) luaL_checkudata(L, 1, LXP_META_TABLE.c_str());

    if (xpu->parser) {
        XML_ParserFree(xpu->parser);
    }
    xpu->parser = nullptr;
    printf("---- lxp close ----\n");
    return 0;
}

static const struct luaL_Reg lxp_meths[] = {
        {"parse", lxp_parse},
        {"close", lxp_close},
        {"__gc",  lxp_close},
        {nullptr, nullptr}
};

static const struct luaL_Reg lxp_funcs[] = {
        {"new",   lxp_make_parser},
        {nullptr, nullptr}
};

int luaopen_lxp(lua_State *L) {
    luaL_newmetatable(L, LXP_META_TABLE.c_str());

    // 复制元表
    lua_pushvalue(L, -1);
    // mt.__index = mt
    lua_setfield(L, -2, "__index");
    // 元表设置方法
    luaL_setfuncs(L, lxp_meths, 0);

    luaL_newlib(L, lxp_funcs);
    lua_setglobal(L, "lxp");

    return 1;
}

void xmlParserDemo() {

    lua_State *L = luaL_newstate();
    luaL_openlibs(L);
    luaopen_lxp(L);

    std::string fileName = "/Users/jiangpengyong/Desktop/code/Lua/Lua_CPP_2022/10、管理资源/xml/xml_parser.lua";
    if (luaL_loadfile(L, fileName.c_str()) || lua_pcall(L, 0, 0, 0)) {
        error(L, "can't run file. file: %s", lua_tostring(L, -1));
    }

    lua_close(L);

}