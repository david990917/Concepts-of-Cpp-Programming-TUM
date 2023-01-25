#pragma once

#include <array>

template<typename T, typename U, typename V, typename W> struct Quadruple
{
public:
    Quadruple(const T& x, const U& u, const V& v, const W& w)
    {
        first  = x;
        second = u;
        third  = v;
        fourth = w;
    }

    const T& get_first() const { return first; }
    const U& get_second() const { return second; }
    const V& get_third() const { return third; }
    const W& get_fourth() const { return fourth; }

private:
    T first;
    U second;
    V third;
    W fourth;
};


template<typename T> class Quadruple<T, T, T, T>
{
public:
    Quadruple(const T& x, const T& u, const T& v, const T& w)
    {
        members[0] = x;
        members[1] = u;
        members[2] = v;
        members[3] = w;
    }
    const T& get_first() const { return members[0]; }
    const T& get_second() const { return members[1]; }
    const T& get_third() const { return members[2]; }
    const T& get_fourth() const { return members[3]; }

    std::array<T, 4> members;
};