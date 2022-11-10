#include <iostream>

namespace loop
{
    void looping(int upper)
    {
        for (int i = 0; i <= upper; i++)
        {
            std::cout << i << std::endl;
        }
    }
}

int main()
{
    loop::looping(8);
}