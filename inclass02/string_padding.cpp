#include <iostream>
#include <string>

int padding = 5;
void string_padding()
{
    // string can directly cin
    std::string info;
    std::cin >> info;
    int n = info.length();

    std::string barrier(padding + n, '=');
    std::string space(padding, ' ');

    std::cout << barrier << '\n';
    std::cout << space << info << '\n';
    std::cout << barrier << '\n';
}

int main()
{
    string_padding();
}
