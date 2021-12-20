#include "client.hpp"
#include "request.hpp"

using boost::asio::ip::tcp;
using namespace http;
const char *crlf = "\r\n";
void client::send(std::string_view message)
{
    size_t len = boost::asio::write(socket, boost::asio::buffer(message));
    // LOG("Wrote: " + std::to_string(len));
}
//TODO Add checking for page validity and clear whitespace
void client::send_get(std::string_view hostname, std::string_view page)
{
    request req;
    req.method = "GET";
    req.page = page;
    req.http_version = VERSION;
    req.user_agent = USER_AGENT;
    req.hostname = hostname;
    req.accept_language = "en";
    std::string request = req;
    LOG(request);
    send(request);
}
void client::receive_get()
{
    for (;;)
    {
        boost::array<wchar_t, 512> buf;
        size_t len = boost::asio::read(socket, boost::asio::buffer(buf), err_code);
        // LOG("Read: " + std::to_string(len));
        if (err_code == boost::asio::error::eof)
        {
            LOG(std::wstring_view{buf.data(), len});
            break;
        }
        else if (err_code)
        {
            throw boost::system::system_error(err_code);
        }
        LOG(std::wstring_view{buf.data(), len});
    }
}
client::~client()
{
    context.stop();
    socket.close();
}

void client::get(std::string_view url)
{
    auto endpoints = resolver.resolve(url, "http", err_code);
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