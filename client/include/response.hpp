#pragma once
#include <string_view>
#include "base_message.hpp"
namespace http
{
    struct response : base_message
    {
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