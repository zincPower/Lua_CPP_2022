---
--- Generated by EmmyLua(https://github.com/EmmyLua)
--- Created by jiangpengyong.
--- DateTime: 2022/5/8 18:29
---

local myUser = user.new("江澎涌", 29)
print("type(user) =>>", type(user))
print("type(myUser) =>>", type(myUser))

print(user.introduce(myUser));

user.setName(myUser, "jiang peng yong");
user.setAge(myUser, 28);

print(user.introduce(myUser));

print("姓名 -->> ", user.getName(myUser));
print("年龄 -->> ", user.getAge(myUser));
