# hw05 作业总结与讨论

## Step1 - 修正 CMakeLists.txt

重新生成 build 文件夹，需要删除掉根目录下的 cache 文件，然后再重新 cmake ..

## Step2 - 从 run.cpp 理解逻辑

- 实际上我们的命令，就是 tokens(vector)，由 token namespace 里面一个个 struct 拼接而成。
- 然后经由函数验证是否为有效的 token

# 代码实现收获

[[nodiscard]] C++ 17新引入的标记符，含义为“不可舍弃”