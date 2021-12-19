#pragma once
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include "../logger/logger.hpp"

namespace http
{
    class httpclient
    {
        const char *VERSION = "HTTP/1.1";
        const char *USER_AGENT = "User-Agent: http-lib/0.0.1";
        boost::asio::io_context context;
        boost::asio::ip::tcp::socket socket;
        boost::asio::ip::tcp::resolver resolver;
        boost::system::error_code err_code;
        void send_get(std::string_view hostname, std::string_view page);
        void receive_get();
        void send(std::string_view message);
        logger &LOG;

    public:
        httpclient(logger &LOG) : socket{context}, resolver{context}, LOG{LOG} {}
        ~httpclient();
        void get(std::string_view url);
    };

};