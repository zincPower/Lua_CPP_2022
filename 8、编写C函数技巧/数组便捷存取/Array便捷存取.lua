---
--- Generated by EmmyLua(https://github.com/EmmyLua)
--- Created by jiangpengyong.
--- DateTime: 2023/10/30 08:43
---

print("map", map)

local info = { "name: 江澎涌", "age: 28", "height: 171" }
local change = function(key)
    return "【Lua map】" .. key
end

print(pcall(function()
    map(info, {})
end))

for i, v in pairs(info) do
    print(i, "---", v)
end