#include "request.hpp"
#include <stdexcept>

namespace http
{
    const char *crlf = "\r\n";
    request::request(std::string_view url) : host{get_hostname(url)},
                                             resource{get_resource(url)}
    {
    }
    void try_append_header(std::string &string, std::string_view header_name, std::string_view header)
    {
        if (!header.empty())
        {
            string.append(header_name);
            string.append(header);
            string.append(crlf);
        }
    }

    std::string request::get()
    {
        std::string message;

        message.append("GET ");
        if (resource.empty())
        {
            throw std::runtime_error{"Resource cannot be empty."};
        }
        message.append(resource);
        message.append(" ");
        message.append(HTTP_VERSION);
        message.append(crlf);

        try_append_header(message, "User-Agent: ", user_agent);
        try_append_header(message, "Host: ", host);
        try_append_header(message, "Accept-Language: ", accept_language);
        try_append_header(message, "Connection: ", connection);

        // To end message
        message.append(crlf);

        return message;
    }
    std::string_view request::get_hostname(std::string_view url)
    {
        size_t after_prefix = url.find("://") + 3;
        if (after_prefix == url.npos)
        {
            throw std::runtime_error{"Invalid url: No \'://\'"};
        }
        std::string_view hostname = url.substr(after_prefix);
        hostname.remove_suffix(hostname.size() - hostname.find('/'));
        return hostname;
    }
    std::string_view request::get_resource(std::string_view url)
    {
        size_t after_prefix = url.find("://") + 3;
        size_t after_hostname = url.find_first_of("/", after_prefix);
        return url.substr(after_hostname);
    }

};