//
// Created by 江澎涌 on 2023/11/16.
//

#include "user.h"

class User {
private:
    std::string name;
    long long age{};
public:
    User() {
        printf("User 构造。\n");
    }

    ~User() {
        printf("User 析构。\n");
    }

    std::string introduce() {
        std::stringstream info;
        info << "大家好。我叫" << name << "。今年" << age << "岁。请关注我。";
        return info.str();
    }

    void setName(std::string name) {
        this->name = std::move(name);
    }

    void setAge(long long age) {
        this->age = age;
    }

    std::string getName() {
        return this->name;
    }

    long long getAge() {
        return this->age;
    }
};

void lightUserdataDemo() {
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);

    User *user = new User();
    lua_pushlightuserdata(L, user);

    stackDump(L);

    User *user1 = (User *) lua_touserdata(L, 1);
    printf("%s\n", user1->introduce().c_str());

    delete user;
    user = nullptr;

    lua_close(L);
}