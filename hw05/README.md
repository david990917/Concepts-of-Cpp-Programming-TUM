# hw05 作业总结与讨论

## Step1 - 修正 CMakeLists.txt

重新生成 build 文件夹，需要删除掉根目录下的 cache 文件，然后再重新 cmake ..

## Step2 - 从 run.cpp 理解逻辑

- 实际上我们的命令，就是 tokens(vector)，由 token namespace 里面一个个 struct 拼接而成。
- 然后经由函数验证是否为有效的 token

## Step3 - 核心实现

本质上就是使用 `std::visit` 访问一种情况内的多种函数。

# 代码实现收获

[[nodiscard]] C++ 17新引入的标记符，含义为“不可舍弃”

# 未来提高的地方

不使用 `if`，直接使用 `C++` 的 `template` 进行实现。