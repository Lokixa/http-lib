#include "tlsclient.hpp"
#include <gtest/gtest.h>

class TLSTest : public ::testing::Test
{

protected:
    TLSTest() : client{new http::tls::tlsclient{}} {}
    void SetUp() override
    {
    }
    std::unique_ptr<http::client> client;
};

TEST_F(TLSTest, GetDNS)
{
    try
    {
        http::response response = client->get("https://example.com");
        EXPECT_EQ((int)response.status_code, 200) << "Actual status: " << (int)response.status_code;
    }
    catch (std::exception &e)
    {
        FAIL() << e.what();
    }
}

TEST_F(TLSTest, MultipleGetDNS)
{
    try
    {
        http::response response = client->get("https://example.com");
        EXPECT_EQ((int)response.status_code, 200) << "Actual status: " << (int)response.status_code;
        response = client->get("https://example.com");
        EXPECT_EQ((int)response.status_code, 200) << "Actual status: " << (int)response.status_code;
        response = client->get("https://example.com");
        EXPECT_EQ((int)response.status_code, 200) << "Actual status: " << (int)response.status_code;
    }
    catch (std::exception &e)
    {
        FAIL() << e.what();
    }
}
// TODO Allow self signed certs with warning
// or fix https localhost not detected
TEST_F(TLSTest, SelfSignedCert)
{
    try
    {
        http::response response = client->get("https://localhost");
        EXPECT_EQ((int)response.status_code, 200) << "Actual status: " << (int)response.status_code;
    }
    catch (std::exception &e)
    {
        FAIL() << e.what();
    }
}