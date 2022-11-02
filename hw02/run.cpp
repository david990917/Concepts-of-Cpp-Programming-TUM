#include "combinatorics.h"
#include "hw02.h"

#include <iostream>

int main()
{
    // here you can test your functions
    std::cout << "fact(10)=" << factorial(10) << std::endl;
    std::cout << "fact(3)=" << factorial(3) << std::endl;
    std::cout << "perm(10, 3)=" << permutation(10, 3) << std::endl;
    std::cout << "comb(10, 3)=" << combination(10, 3) << std::endl;

    return 0;
}
