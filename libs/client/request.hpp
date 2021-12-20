#pragma once
#include <string>
namespace http
{
    struct request
    {
        std::string_view method;
        std::string_view page;
        std::string_view http_version;
        std::string_view user_agent;
        std::string_view hostname;
        std::string_view accept_language;

        operator std::string() const
        {
            std::string message;

            message.append("GET ");
            message.append(page);
            message.append(" ");
            message.append("HTTP/");
            message.append(http_version);
            message.append(crlf);

            message.append("User-Agent: ");
            message.append(user_agent);
            message.append(crlf);

            message.append("Host: ");
            message.append(hostname);
            message.append(crlf);

            message.append("Accept-Language: ");
            message.append(accept_language);
            message.append(crlf);

            // To end message
            message.append(crlf);

            return message;
        }

    private:
        const char *crlf = "\r\n";
    };
};