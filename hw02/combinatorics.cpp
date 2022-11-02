#include "combinatorics.h"

uint64_t result_save[21]{0};

uint64_t factorial(uint64_t val)
{
    if (result_save[val] != 0)
    {
        return result_save[val];
    }
    uint64_t result = 1;
    for (uint64_t i = 1; i <= val; i++)
    {
        result *= i;
    }

    if (val <= 20)
    {
        result_save[val] = result;
    }

    return result;
}

uint64_t permutation(uint64_t val, uint64_t val2)
{
    return factorial(val) / factorial(val - val2);
}

uint64_t combination(uint64_t val, uint64_t val2)
{
    return factorial(val) / (factorial(val2) * factorial(val - val2));
}
