#include "client.hpp"
#include "gtest/gtest.h"

TEST(HTTPResponse, Valid)
{
    EXPECT_STRNE("HTTP", "AFASF");
}
