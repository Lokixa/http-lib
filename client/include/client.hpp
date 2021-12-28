#pragma once
#include <boost/asio.hpp>
#include <memory>
#include "logger.hpp"
#include "response.hpp"

namespace http
{
    struct client
    {
        client(std::shared_ptr<logger::logger>);
        // TODO Return response
        http::response get(const std::string &url);
        ~client();
        void close();

    private:
        http::response receive();
        void send(std::string_view message);

        boost::asio::io_context context;
        boost::asio::ip::tcp::socket socket;
        boost::asio::ip::tcp::resolver resolver;
        boost::system::error_code err_code;
        std::shared_ptr<logger::logger> logger;
    };

};