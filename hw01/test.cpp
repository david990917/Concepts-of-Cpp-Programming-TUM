#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "library.h"

TEST_CASE("testing the library")
{
    CHECK(library_function() == 1337);
}
