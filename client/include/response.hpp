#pragma once
#include <string_view>
#include "base_message.hpp"
namespace http
{
    struct response : base_message
    {
        // Control Data

        std::string_view age;
        std::string_view expires;
        std::string_view date;
        std::string_view location;
        std::string_view retry_after;
        std::string_view vary;
        std::string_view warning;

        // Validator

        std::string_view etag;
        std::string_view last_modified;

        // Auth challenges

        std::string_view www_authenticate;
        std::string_view proxy_authenticate;

        // Context

        std::string_view accept_ranges;
        std::string_view allow;
        std::string_view server;
    };
    enum class statuscodes
    {
        Continue = 100,
        SwitchingProtocols,
        OK = 200,
        Created,
        Accepted,
        NonAuthoritativeInformation,
        NoContent,
        ResetContent,
        PartialContent,
        MultipleChoices = 300,
        MovedPermanently,
        Found,
        SeeOther,
        NotModified,
        UseProxy,
        TemporaryRedirect = 307,
        BadRequest = 400,
        Unauthorized,
        PaymentRequired,
        Forbidden,
        NotFound,
        MethodNotAllowed,
        NotAcceptable,
        ProxyAuthenticationRequired,
        RequestTimeout,
        Conflict,
        Gone,
        LengthRequired,
        PreconditionFailed,
        PayloadTooLarge,
        URITooLong,
        UnsupportedMediaType,
        RangeNotSatisfiable,
        ExpectationFailed,
        UpgradeRequired = 426,
        InternalServerError = 500,
        NotImplemented,
        BadGateway,
        ServiceUnavailable,
        GatewayTimeout,
        HTTPVersionNotSupported
    };
};