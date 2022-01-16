#pragma once
#include "client.hpp"
#include <boost/asio.hpp>
#include <memory>

namespace http
{
  struct httpclient final : public client
  {
    httpclient();
    http::response get(const std::string &url) override;
    void close() override;
    ~httpclient();

  private:
    boost::asio::io_context context;
    boost::asio::ip::tcp::socket socket;
    boost::asio::ip::tcp::resolver resolver;
    boost::system::error_code err_code;
  };

} // namespace http
