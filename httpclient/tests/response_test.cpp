#include "response.hpp"
#include "gtest/gtest.h"

const std::string str_response{"HTTP/1.1 200 OK\r\n"
                               "accept-ranges: bytes\r\n"
                               "cache-control: max-age=3600\r\n"
                               "last-modified: Tue, 28 Dec 2021 17:40:34 GMT\r\n"
                               "etag: W/\"15610463-328-2021-12-28T17:40:34.154Z\"\r\n"
                               "content-length: 334\r\n"
                               "content-type: text/html; charset=UTF-8\r\n"
                               "Date: Sun, 02 Jan 2022 20:02:22 GMT\r\n"
                               "Connection: keep-alive\r\n"
                               "Keep-Alive: timeout=5\r\n"
                               "\r\n"
                               "<!DOCTYPE html>\n"
                               "<html lang=\"en\">\n"
                               "\n"
                               "<head>\n"
                               "    <meta charset=\"UTF-8\">\n"
                               "    <meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\">\n"
                               "    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n"
                               "    <title>Здраствуйте</title>\n"
                               "</head>\n"
                               "\n"
                               "<body>\n"
                               "    <h1>Здраствуйте!</h1>\n"
                               "        <p>Hi!!!!</p>\n"
                               "</body>\n"
                               "\n"
                               "</html>"};
class ResponseTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        try
        {
            response = http::response::parse(str_response);
        }
        catch (std::exception &e)
        {
            FAIL() << e.what();
        }
    }
    http::response response;
};

const std::string print_headers(const http::response &response)
{
    std::string result;
    for (const auto &[key, value] : response.get_headers())
    {
        result.append("[" + key + "]: " + value + "\n");
    }
    return result;
}

TEST_F(ResponseTest, Valid)
{
    EXPECT_EQ(static_cast<int>(response.status_code), 200) << "IDK";
    EXPECT_STREQ(response.http_version.c_str(), "HTTP/1.1") << "HTTP BABY";
    EXPECT_STREQ(response["Accept-Ranges"].c_str(), "bytes") << "Accept-Ranges not found, Headers: \n"
                                                             << print_headers(response);
    EXPECT_NE(response.body.find("Здраствуйте"), response.body.npos);
}
