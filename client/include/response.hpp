#pragma once
#include <string>
#include <map>
namespace http
{
    enum class statuscode;
    struct response
    {

        /**     
         * @brief Parses message and appends to itself
         *
         * @param message
         */
        std::map<std::string, std::string> headers;
        std::string body;
        statuscode status_code;
        std::string http_version;
        //TODO Add stream support
        static const response parse(const std::string &);

        // private:
        //     void parse(std::string_view message);
    };
    // https://www.rfc-editor.org/rfc/rfc7231#section-6
    enum class statuscode
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