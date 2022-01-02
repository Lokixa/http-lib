#pragma once
#include <boost/asio.hpp>
#include <memory>

namespace http
{
struct response;
struct client
{
    client();
    virtual ~client();

    virtual response get(const std::string &url);
    void close();

  protected:
    boost::asio::io_context context;
    boost::asio::ip::tcp::socket socket;
    boost::asio::ip::tcp::resolver resolver;
    boost::system::error_code err_code;
};

}; // namespace http
