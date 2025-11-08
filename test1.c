#define ATTEST_IMPLEMENTATION

#include "attest.h"

REGISTER_TEST(addition)
{
    ATTEST_EQ(2+2, 3);
}

REGISTER_TEST(string)
{
    ATTEST_STR_EQ("hello", "world");
}