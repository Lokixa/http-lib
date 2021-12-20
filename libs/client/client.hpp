#pragma once
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include "../logger/logger.hpp"

namespace http
{
    class client
    {
        std::string_view VERSION = "1.1";
        std::string_view USER_AGENT = "http-lib/0.0.1";
        boost::asio::io_context context;
        boost::asio::ip::tcp::socket socket;
        boost::asio::ip::tcp::resolver resolver;
        boost::system::error_code err_code;
        void send_get(std::string_view hostname, std::string_view page);
        void receive_get();
        void send(std::string_view message);
        //TODO Provide proper support for logger or remove.
        logger LOG;

    public:
        client(logger &LOG) : context{},
                              socket{context},
                              resolver{context},
                              err_code{},
                              LOG{LOG} {}
        ~client();
        void get(std::string_view url);
    };

};