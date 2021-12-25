#include "client.hpp"
#include "request.hpp"
#include <boost/array.hpp>

using boost::asio::ip::tcp;
using namespace http;
const char *crlf = "\r\n";
void client::send(std::string_view message)
{
    boost::asio::write(socket, boost::asio::buffer(message), err_code);
    if (err_code)
    {
        throw boost::system::system_error{err_code};
    }
}

void client::receive_get()
{
    auto buf = boost::array<char, 512>();
    for (;;)
    {
        size_t len = boost::asio::read(socket, boost::asio::buffer(buf), err_code);
        if (err_code == boost::asio::error::eof)
        {
            logger->log(std::string_view{buf.data(), len});
            break;
        }
        else if (err_code)
        {
            throw boost::system::system_error{err_code};
        }
        logger->log(std::string_view{buf.data(), len});
        buf.fill(0);
    }
    logger->log("\n");
}
client::client(std::shared_ptr<logger::logger> logger) : context{},
                                                         socket{context},
                                                         resolver{context},
                                                         err_code{},
                                                         logger{logger}
{
}

void client::get(std::string_view url)
{
    auto endpoints = resolver.resolve(request::get_hostname(url), "http", err_code);
    {
        auto bendpoints = resolver.resolve(request::get_hostname(url), "http", err_code);
        if (err_code)
        {
            throw boost::system::system_error{err_code};
        }
    }
    {
        auto bendpoints = resolver.resolve(request::get_hostname(url), "http", err_code);
        if (err_code)
        {
            throw boost::system::system_error{err_code};
        }
    }
    if (err_code)
    {
        throw boost::system::system_error{err_code};
    }
    boost::asio::connect(socket, endpoints, err_code);
    if (err_code)
    {
        throw boost::system::system_error{err_code};
    }

    request req{url};
    std::string request = req.get();
    send(request);
    receive_get();
}
void client::close()
{
    this->context.stop();
    this->socket.close();
}
client::~client()
{
    this->close();
}