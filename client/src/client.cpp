#include "client.hpp"

#include <boost/array.hpp>

#include "request.hpp"
#include "response.hpp"

namespace http
{
using boost::asio::ip::tcp;
const char *crlf = "\r\n";

http::response receive(tcp::socket &socket, boost::system::error_code &err_code)
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
client::client() : context{}, socket{context}, resolver{context}, err_code{}
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

    boost::asio::write(socket, boost::asio::buffer(request), err_code);
    if (err_code)
    {
        throw boost::system::system_error{err_code};
    }
    return receive(socket, err_code);
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
    }
}
}; // namespace http
