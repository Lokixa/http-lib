#include <gtest/gtest.h>
#include "../http.h"

TEST(GeneralHTTP, WordIsCorrect)
{
    EXPECT_EQ(http::get_word(), "HTTP MODULES");
}