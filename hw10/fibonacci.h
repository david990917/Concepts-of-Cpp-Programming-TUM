#pragma once
#include <concepts>

template<int N, std::integral T = int> struct fibonacci
{
    static constexpr T value = fibonacci<N - 1, T>::value + fibonacci<N - 2, T>::value;
};

template<typename T> struct fibonacci<1, T>
{
    static constexpr T value = 1;
};

template<typename T> struct fibonacci<0, T>
{
    static constexpr T value = 0;
};
