#include <iostream>

// namespace capusulate code
namespace loop
{
    void looping(int upper)
    {
        for (int i = 0; i <= upper; i++)
        {
            std::cout << i << '\n';
        }
    }
}

int main()
{
    loop::looping(8);
}