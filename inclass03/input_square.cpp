#include <iostream>

int main()
{
    int x;
    std::cout << "Please enter a numebr: " << std::endl;
    std::cin >> x;
    std::cout << "What you input was " << x << std::endl;
    std::cout << "The square of " << x << " is " << x * x << std::endl;
}