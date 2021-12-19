#include "httpclient.hpp"

using boost::asio::ip::tcp;
using namespace http;
constexpr const char *crlf()
{
    return "\r\n";
}
void httpclient::send(std::string_view message)
{
    size_t len = boost::asio::write(socket, boost::asio::buffer(message));
    // LOG("Wrote: " + std::to_string(len));
}
void httpclient::send_get(std::string_view hostname, std::string_view page)
{
    //TODO Add checking for page validity and clear whitespace
    std::string message;
    message.append("GET ");
    message.append(page);
    message.append(" ");
    message.append(VERSION);
    message.append(crlf());
    send(message);
    message.clear();
    message.append(USER_AGENT);
    message.append(crlf());
    send(message);
    message.clear();
    message.append("Host: ");
    message.append(hostname);
    send(message);
    send("Accept-Language: en\n\r");
    send(crlf());
    send(crlf());
}
void httpclient::receive_get()
{
    for (;;)
    {
        boost::array<char, 256> buf;
        size_t len = boost::asio::read(socket, boost::asio::buffer(buf), err_code);
        LOG("Read: " + std::to_string(len));
        if (err_code == boost::asio::error::eof)
        {
            LOG(std::string_view{buf.data(), len});
            break;
        }
        else if (err_code)
        {
            throw boost::system::system_error(err_code);
        }
        LOG(std::string_view{buf.data(), len});
    }
}
httpclient::~httpclient()
{
    context.stop();
    socket.close();
}

void httpclient::get(std::string_view url)
{
    auto endpoints = resolver.resolve(url, "8080", err_code);
    boost::asio::connect(socket, endpoints);
    size_t pos = url.find('/');
    std::string_view page;
    std::string_view hostname;
    if (pos == std::string::npos)
    {
        page = "/";
        hostname = url;
    }
    else
    {
        page = url.substr(pos);
        hostname = url.substr(0, pos);
    }
    send_get(hostname, page);
    receive_get();
}