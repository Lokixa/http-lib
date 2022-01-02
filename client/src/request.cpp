#include "request.hpp"
#include <regex>
#include <stdexcept>

namespace http
{
const std::string_view HTTP_VERSION = "HTTP/1.1";
const std::string_view USER_AGENT = "http-lib/0.0.1";
const std::string_view crlf = "\r\n";
request::request(const std::string &url) : headers{}
{
    if (url.empty())
    {
        throw std::runtime_error{"Invalid URL."};
    }
    std::regex url_reg{"(http[s]?):\\/\\/([\\w\\.]*)(\\/[\\w\\/]*)?"};
    std::smatch groups{};
    if (!std::regex_search(url, groups, url_reg))
    {
        throw std::runtime_error{"Couldn't find http protocol parameters in URL."};
    }
    headers["Protocol"] = groups[1].str();
    headers["Host"] = groups[2].str();
    std::string resource = groups[3].str();
    if (resource.empty())
        headers["Resource"] = "/";
    else
        headers["Resource"] = resource;
}
std::string &request::operator[](const std::string &header)
{
    return headers[header];
}

std::string &request::operator[](const std::string &&header)
{
    return headers[std::move(header)];
}
void append_header_map(std::string &message, std::map<std::string, std::string> headers)
{
    for (const auto &[key, value] : headers)
    {
        message.append(key + ": " + value);
        message.append(crlf);
    }
}

std::string request::get()
{
    std::string message;

    message.append("GET ");
    message.append(this->headers["Resource"]);
    message.append(" ");
    message.append(HTTP_VERSION);
    message.append(crlf);

    if (this->headers["User-Agent"].empty())
    {
        this->headers["User-Agent"] = USER_AGENT;
    }
    append_header_map(message, this->headers);

    // To end message
    message.append(crlf);

    return message;
}

}; // namespace http