#include "client.hpp"
#include "request.hpp"
#include "response.hpp"
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

http::response client::receive()
{
    auto buf = boost::array<char, 512>();
    std::string response;
    for (;;)
    {
        size_t len = boost::asio::read(socket, boost::asio::buffer(buf), err_code);

        // End
        if (err_code == boost::asio::error::eof)
        {
            response.append(buf.data(), len);
            break;
        }
        else if (err_code)
        {
            throw boost::system::system_error{err_code};
        }
        response.append(buf.data(), len);

        // Reuse buffer
        buf.fill(0);
    }
    return http::response::parse(response);
}
client::client(std::shared_ptr<logger::logger> logger) : context{},
                                                         socket{context},
                                                         resolver{context},
                                                         err_code{},
                                                         logger{logger}
{
}

http::response client::get(const std::string &url)
{
    request req{url};
    auto endpoints = resolver.resolve(req["Host"], req["Protocol"], err_code);

    if (err_code)
    {
        throw boost::system::system_error{err_code};
    }
    boost::asio::connect(socket, endpoints, err_code);
    if (err_code)
    {
        throw boost::system::system_error{err_code};
    }

    req["Connection"] = "close";
    std::string request = req.get();
    logger->log(request);
    send(request);
    return receive();
}
void client::close()
{
    this->context.stop();
    this->socket.close();
}
client::~client()
{
    try
    {
        this->close();
    }
    catch (std::exception &e)
    {
        logger->logln("Caught exception on close: " + std::string{e.what()});
    }
}