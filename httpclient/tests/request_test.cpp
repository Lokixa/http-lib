#include "request.hpp"
#include "gtest/gtest.h"

TEST(RequestTest, ValidDNS)
{
    http::request request{"https://google.com"};
    EXPECT_STREQ(request["Host"].c_str(), "google.com") << request["Host"].c_str();
    EXPECT_STREQ(request["Protocol"].c_str(), "https");
    EXPECT_STREQ(request["Resource"].c_str(), "/");
}
TEST(RequestTest, ValidIP)
{
    http::request request{"https://127.0.0.1"};
    EXPECT_STREQ(request["Host"].c_str(), "127.0.0.1") << "Actual hostname: " << request["Host"].c_str();
    EXPECT_STREQ(request["Protocol"].c_str(), "https");
    EXPECT_STREQ(request["Resource"].c_str(), "/");
}