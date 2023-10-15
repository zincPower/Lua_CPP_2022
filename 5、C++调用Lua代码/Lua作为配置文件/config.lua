io.write("jiang pengyong\n")

-- DISPLAY_ENV 在环境变量中配置，open ~/.zshrc 可以查看
local displayEnv = os.getenv("DISPLAY_ENV");
print("displayEnv", displayEnv)

if displayEnv == "Mac" then
    width = 3072
    height = 1920
else
    width = 1920
    height = 1080
end

--BLUE = { red = 0, green = 0, blue = 1.0 }
--background = { red = 0.3, green = 0.1, blue = 0 }
--background = "PINK"--{ red = 0.3, green = 0.1, blue = 0 }
print(PINK)
background = PINK


