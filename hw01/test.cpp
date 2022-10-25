// g++ -std=c++20 -Wall -Wextra -Wl,-rpath . -I "/Users/hanwen/Library/CloudStorage/OneDrive-TUM/TUM/第三学期/C++/gitlab/doctest/doctest/" -o hw01test test.cpp -L . -llibrary

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "library.h"

TEST_CASE("testing the library")
{
    CHECK(library_function() == 1337);
}
