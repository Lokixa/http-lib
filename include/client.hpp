#pragma once
#include "response.hpp"
#include <string>
namespace http
{
    struct client
    {
        virtual ~client(){};

        virtual http::response get(const std::string &) = 0;
        virtual void close() = 0;
    };
}