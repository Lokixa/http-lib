#pragma once
#include "base_message.hpp"

// TODO Change to const or refactor
#ifndef USER_AGENT
#define USER_AGENT "http-lib/0.0.1"
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

        // Control

        std::string_view expect;
        std::string_view host;
        std::string_view max_forwards;
        std::string_view pragma;
        std::string_view range;
        std::string_view transfer_codings;

        // Conditional

        std::string_view if_match;
        std::string_view if_none_match;
        std::string_view if_modified_since;
        std::string_view if_unmodified_since;
        std::string_view if_range;

        // Content Negotiation

        std::string_view accept;
        std::string_view accept_charset;
        std::string_view accept_encoding;
        std::string_view accept_language;

        // Authentication Credentials

        std::string_view authorization;
        std::string_view proxy_authorization;

        // Request Context

        std::string_view from;
        std::string_view referer;
        std::string_view user_agent = USER_AGENT;

        request(std::string_view url);

        std::string get();

        static std::string_view get_hostname(std::string_view url);
        static std::string_view get_resource(std::string_view url);

    private:
        std::string_view resource;
    };
};