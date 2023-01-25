#pragma once

#include <cmath>

template<typename T> constexpr auto gcd(T x, T y)
{
    while (y != 0) {
        auto tmp = y;
        y        = x % y;
        x        = tmp;
    }
    return x;
}

template<typename T, typename... Args> constexpr auto gcd(T x, T y, Args... args)
{
    return gcd(x, gcd(y, args...));
}

template<typename T> constexpr auto mcm(T x, T y)
{
    return x * y / gcd(x, y);
}

template<typename T, typename... Args> constexpr auto mcm(T x, T y, Args... args)
{
    return mcm(x, mcm(y, args...));
}

template<int base, int exponent, int modulus> struct Power
{
    static constexpr int value = base * Power<base, exponent - 1, modulus>::value % modulus;
};

template<int base, int modulus> struct Power<base, 0, modulus>
{
    static constexpr int value = 1 % modulus;
};