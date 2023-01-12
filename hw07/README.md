# hw07

- throw exception
- `[](){} lambda function`
- corner case

----

1. std::move

2. `->` 更方便指示返回类型（因为 namespace)

    ```cpp
    auto Video::get_resolution() const -> resolution_t
    {
        return this->resolution;
    }

    ```

3. 类成员最好还是使用 `this->file`
4. shared_pointer
多个指针共用一个对象
5. weak pointer

    ```cpp
    std::weak_ptr<Filesystem> filesystem;
    ```
