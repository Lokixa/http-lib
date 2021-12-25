#pragma once
#include <boost/asio.hpp>
#include "logger.hpp"

namespace http
{
    class client
    {
        boost::asio::io_context context;
        boost::asio::ip::tcp::socket socket;
        boost::asio::ip::tcp::resolver resolver;
        void receive_get();
        void send(std::string_view message);
        boost::system::error_code err_code;
        std::shared_ptr<logger::logger> logger;

    public:
        client(std::shared_ptr<logger::logger>);
        void get(std::string_view url);
        ~client();
        void close();
    };

};