#include "request.hpp"
#include <stdexcept>

namespace http
{

    request::request(std::string_view url) : hostname{get_hostname(url)}, resource{get_resource(url)}
    {
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

        if (!user_agent.empty())
        {
            message.append("User-Agent: ");
            message.append(user_agent);
            message.append(crlf);
        }

        if (!hostname.empty())
        {
            message.append("Host: ");
            message.append(hostname);
            message.append(crlf);
        }
        if (!accept_language.empty())
        {
            message.append("Accept-Language: ");
            message.append(accept_language);
            message.append(crlf);
        }

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