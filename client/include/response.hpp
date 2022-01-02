#pragma once
#include <map>
#include <string>
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
    std::string my_string;
    // TODO Add stream support
    static const response parse(const std::string &);

    // private:
    //     void parse(std::string_view message);
};
}; // namespace http
