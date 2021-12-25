#pragma once
#include <string>

#ifndef HTTP_VERSION
#define HTTP_VERSION "HTTP/1.1"
#endif
#ifndef USER_AGENT
#define USER_AGENT "httplib"
#endif
namespace http
{
    struct request
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

        std::string_view resource;
        std::string_view hostname;

        // [https://www.rfc-editor.org/rfc/rfc7231]
        // Representation Metadata

        std::string_view content_type;
        std::string_view content_encoding;
        std::string_view content_language;
        std::string_view content_location;
        std::string_view content_length;
        std::string_view content_range;
        std::string_view trailer;
        std::string_view transfer_encoding;

        // Content Negotiation

        std::string_view accept;
        std::string_view accept_charset;
        std::string_view accept_encoding;
        std::string_view accept_language;

        // Control

        std::string_view cache_control;
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

        // Authentication Credentials

        std::string_view authorization;
        std::string_view proxy_authorization;

        // Request Context

        std::string_view from;
        std::string_view referer;
        std::string_view user_agent = USER_AGENT;

        // end [https://www.rfc-editor.org/rfc/rfc7231]

        request(std::string_view url);

        std::string get();

        static std::string_view get_hostname(std::string_view url);
        static std::string_view get_resource(std::string_view url);

    private:
        const char *crlf = "\r\n";
    };
};