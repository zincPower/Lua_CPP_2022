//
// Created by 江澎涌 on 2022/5/10.
//

#include "lproc.h"

#include <pthread.h>
#include <cstring>
#include "lua.hpp"

typedef struct Proc {
    lua_State *L;
    pthread_t thread;
    pthread_cond_t cond;
    const char *channel;
    struct Proc *previous, *next;
} Proc;

static Proc *waitsend = nullptr;
static Proc *waitreceive = nullptr;

pthread_mutex_t kernel_access;

static Proc *getself(lua_State *L) {
    Proc *p;
    lua_getfield(L, LUA_REGISTRYINDEX, "_SELF");
    p = (Proc *) lua_touserdata(L, -1);
    lua_pop(L, 1);
    return p;
}

static void movevalues(lua_State *send, lua_State *rec) {
    int n = lua_gettop(send);
    int i;
    luaL_checkstack(rec, n, "too many results");
    for (i = 2; i <= n; i++) {
        lua_pushstring(rec, lua_tostring(send, i));
    }
}

static Proc *searchmatch(const char *channel, Proc **list) {
    Proc *node;
    for (node = *list; node != nullptr; node = node->next) {
        if (strcmp(channel, node->channel) == 0) {
            if (*list == node) {
                *list = (node->next == node) ? nullptr : node->next;
            }
            node->previous->next = node->next;
            node->next->previous = node->previous;
            return node;
        }
    }
    return nullptr;
}

static void waitonlist(lua_State *L, const char *channel, Proc **list) {
    Proc *p = getself(L);

    if (*list == nullptr) {
        *list = p;
        p->previous = p->next = p;
    } else {
        p->previous = (*list)->previous;
        p->next = *list;
        p->previous->next = p->next->previous = p;
    }

    p->channel = channel;

    do {
        pthread_cond_wait(&p->cond, &kernel_access);
    } while (p->channel);
}

static int ll_send(lua_State *L) {
    Proc *p;
    const char *channel = luaL_checkstring(L, 1);

    pthread_mutex_lock(&kernel_access);

    p = searchmatch(channel, &waitreceive);

    if (p) {
        movevalues(L, p->L);
        p->channel = NULL;
        pthread_cond_signal(&p->cond);
    } else {
        waitonlist(L, channel, &waitsend);
    }

    pthread_mutex_unlock(&kernel_access);
    return 0;
}

static int ll_receive(lua_State *L) {
    Proc *p;
    const char *channel = luaL_checkstring(L, 1);
    lua_settop(L, 1);

    pthread_mutex_lock(&kernel_access);

    p = searchmatch(channel, &waitsend);

    if (p) {
        movevalues(p->L, L);
        p->channel = nullptr;
        pthread_cond_signal(&p->cond);
    } else {
        waitonlist(L, channel, &waitreceive);
    }

    pthread_mutex_unlock(&kernel_access);

    return lua_gettop(L) - 1;
}

static int ll_start(lua_State *L) {
    pthread_t thread;
    const char *chunk = luaL_checkstring(L, 1);
    lua_State *L1 = luaL_newstate();

    if (L1 == nullptr) {
        luaL_error(L, "unable to create new state");
    }

    if (luaL_loadstring(L1, chunk) != 0) {
        luaL_error(L, "error in thread body: %s", lua_tostring(L1, -1));
    }

    if (pthread_create(&thread, nullptr, ll_thread, L1) != 0) {
        luaL_error(L, "unable to create new thread");
    }

    pthread_detach(thread);
    return 0;
}

int luaopen_lproc(lua_State *L);

static void *ll_thread(void *arg) {
    lua_State *L = (lua_State *) arg;
    Proc *self;

    luaL_openlibs(L);
    luaL_requiref(L, "lproc", luaopen_lproc, 1);
    lua_pop(L, 1);
    self = (Proc *) lua_newuserdata(L, sizeof(Proc));
    lua_setfield(L, LUA_REGISTRYINDEX, "_SELF");
    self->L = L;
    self->thread = pthread_self();
    self->channel = nullptr;
    pthread_cond_init(&self->cond, nullptr);

    if (lua_pcall(L, 0, 0, 0) != 0) {
        fprintf(stderr, "thread error: %s", lua_tostring(L, -1));
    }

    pthread_cond_destroy(&getself(L)->cond);
    lua_close(L);
    return nullptr;
}

static int ll_exit(lua_State *L) {
    pthread_exit(nullptr);
    return 0;
}

static const struct luaL_Reg ll_funcs[] = {
        {"start", ll_start},
        {"send", ll_send},
        {"receive", ll_receive},
        {"exit", ll_exit},
        {nullptr, nullptr}
};

int luaopen_lproc(lua_State *L) {
    luaL_newlib(L, ll_funcs);
    return 1;
}

static void registerlib(lua_State *L, const char *name, lua_CFunction f) {
    lua_getglobal(L, "package");
    lua_getfield(L, -1, "preload");
    lua_pushcfunction(L, f);
    lua_setfield(L, -2, name);
    lua_pop(L, 2);
}

static void openlibs(lua_State *L) {
    luaL_requiref(L, "_G", luaopen_base, 1);
    luaL_requiref(L, "package", luaopen_package, 1);
    lua_pop(L, 2);
    registerlib(L, "coroutine", luaopen_coroutine);
    registerlib(L, "table", luaopen_table);
    registerlib(L, "io", luaopen_io);
    registerlib(L, "os", luaopen_os);
    registerlib(L, "string", luaopen_string);
    registerlib(L, "math", luaopen_math);
    registerlib(L, "utf8", luaopen_utf8);
    registerlib(L, "debug", luaopen_debug);
}

void lprocDemo() {

}