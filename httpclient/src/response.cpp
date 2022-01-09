#include "response.hpp"
#include <algorithm>
#include <cctype>
#include <regex>
#include <stdexcept>
#include <string>
#include <vector>

void add_header(http::response &response, const std::string &header)
{
    std::regex header_pattern{"(\\S*): ([^\\n\\r]*)"};
    std::smatch reg_groups{};
    if (!std::regex_search(header, reg_groups, header_pattern))
    {
        throw std::runtime_error{"Invalid header."};
    }
    std::string name = reg_groups[1].str();
    // TODO May cause problems if headers are not encoded in ascii
    response[name] = reg_groups[2].str();
}
/**
 * @brief Seperates headers to lines for easier parsing.
 *
 * @param message Response from http request.
 * @param index Sets index to first character of where body should be.
 * @return std::vector\\<std::string\>
 */
std::vector<std::string> headers_to_lines(std::string_view message, size_t *index)
{
    // TODO Find stl function

    std::vector<std::string> lines;
    for (size_t &i = *index; i < message.size();)
    {
        std::string line;

        // Take advantage of already done bounds check
        do
        {
            char c = message.at(i);

            // End of line in http
            if (c == '\r')
            {
                // Found '\r\n', skip after '\n' to next character
                i += 2;
                // and end the line
                break;
            }

            line.push_back(c);

            // Next character
            ++i;
        } while (i < message.size());

        // Append line
        lines.push_back(line);

        // Shouldn't go out of bounds if message
        // is sticking to http standards
        if (i >= message.size())
        {
            throw std::runtime_error{"Unexpected out of bounds!"};
        }
        // Another empty line == end of headers
        if (message.at(i) == '\r')
        {
            // Put index after '\r\n' at start of body, if it exists
            i += 2;
            break;
        }
    }

    return lines;
}
std::string to_lower(std::string &&string)
{
    std::transform(string.begin(), string.end(), string.begin(), [](char c) -> char { return std::tolower(c); });
    return string;
}
std::string &http::response::operator[](const std::string &header)
{
    return headers[to_lower(std::string{header})];
}
std::string &http::response::operator[](std::string &&header)
{
    return headers[to_lower(std::move(header))];
}

const http::response http::response::parse(const std::string &message)
{
    if (message.empty())
        throw std::runtime_error{"Invalid message"};

    http::response response{};

    size_t message_index{};
    std::vector<std::string> lines = headers_to_lines(message, &message_index);

    // Parse and add each line to headers
    for (size_t i = 0; i < lines.size(); ++i)
    {
        std::string line = lines.at(i);
        // Status line
        if (i == 0)
        {
            const std::regex status_line{"^(HTTP\\/[1-9]\\.[0-9]) ([0-9]{3})"};
            std::smatch reg_groups{};
            if (!std::regex_search(line, reg_groups, status_line))
            {
                throw std::runtime_error{"Invalid status code from http response"};
            }
            response.http_version = reg_groups[1].str();
            response.status_code = static_cast<statuscode>(std::stoi(reg_groups[2].str()));
        }
        else
        {
            // TODO Supress or no supress
            add_header(response, line);
        }
    }

    // Parse body if it exists
    // TODO Fix stored header names
    if (!response.headers["content-length"].empty())
    {
        int content_length{std::stoi(response.headers["content-length"])};
        response.body = message.substr(message_index);
        int response_body_size = response.body.size();
        // Invalid body to Content-Length
        if (response_body_size != content_length)
        {
            int faulted = response.body.size() - content_length;
            throw std::runtime_error{"!!!Response: Wrong body size to content length[body - length] = " +
                                     std::to_string(faulted)};
        }
    }

    return response;
}
// https://www.rfc-editor.org/rfc/rfc7231#section-6
enum class http::statuscode
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
