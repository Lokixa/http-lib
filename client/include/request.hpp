#pragma once
#include <string>
#include "base_message.hpp"

#ifndef HTTP_VERSION
#define HTTP_VERSION "HTTP/1.1"
#endif
#ifndef USER_AGENT
#define USER_AGENT "httplib"
#endif
namespace http
{
    struct request : base_message
    {
        // TODO Implement
        // [https://www.rfc-editor.org/rfc/rfc7231#section-4]
        // enum class methods
        // {
        //     GET,
        //     HEAD,
        //     POST,
        //     PUT,
        //     DELETE,
        //     CONNECT,
        //     OPTIONS,
        //     TRACE
        // };

        std::string_view hostname;
        std::string_view resource;

        std::string_view user_agent = USER_AGENT;

        request(std::string_view url);

        std::string get();

        static std::string_view get_hostname(std::string_view url);
        static std::string_view get_resource(std::string_view url);
    };
};