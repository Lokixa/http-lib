#pragma once
#include <string_view>

namespace http
{
    struct base_message
    {
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

        // Caching

        std::string_view cache_control;

        // Connection options

        std::string_view connection;
        std::string_view keep_alive;

        // end [https://www.rfc-editor.org/rfc/rfc7231]
    };
};