#include <algorithm>
#include <iostream>
#include <string>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

[[nodiscard]] std::string reverse_names(std::string name)
{
    auto comma_position = std::find(name.begin(), name.end(), ',');
    auto paste_end      = std::rotate(name.begin(), comma_position, name.end());
    std::rotate(name.begin(), std::next(name.begin()), paste_end);
    return name;
}

TEST_CASE("Simple test case")
{
    auto result = reverse_names("David,Frank");

    CHECK_EQ(result, "Frank,David");
}