#include <iostream>
#include <vector>

std::vector<int> range(int end)
{
    std::vector<int> result;
    for (int i{0}; i < end; i++)
    {
        result.push_back(i);
    }
    return result;
}

std::vector<int> range(int start, int end)
{
    std::vector<int> result;
    for (int i{0}; i < end; i++)
    {
        result.push_back(i);
    }
    return result;
}

std::vector<int> range(int start, int end, int step)
{
    std::vector<int> result;
    for (int i{0}; i < end; i += step)
    {
        result.push_back(i);
    }
    return result;
}

int main()
{
    std::cout << range(3) << std::endl;
    std::cout << range(2, 5) << std::end;
    std::cout << range(1, 7, 3) << std::endl;
}
