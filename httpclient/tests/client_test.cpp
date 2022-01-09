#include "httpclient.hpp"
#include "gtest/gtest.h"
class ClientTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        try
        {
            client = std::make_unique<http::httpclient>();
        }
        catch (std::exception &e)
        {
            FAIL() << e.what();
        }
    }
    std::unique_ptr<http::client> client;
};

TEST_F(ClientTest, Get)
{
    http::response response = client->get("http://google.com");
    ASSERT_EQ((int)response.status_code, 301);
}
