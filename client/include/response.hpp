#pragma once
#include <map>
#include <string>
namespace http
{
enum class statuscode;
struct response final
{

    /**
     * @brief Parses message and appends to itself
     *
     * @param message
     */
    std::string body;
    statuscode status_code;
    std::string http_version;
    std::string &operator[](const std::string &);
    std::string &operator[](std::string &&);
    // TODO(#3): Add stream support
    static const response parse(const std::string &);
    const std::map<std::string, std::string> get_headers() const
    {
        return headers;
    }

  private:
    std::map<std::string, std::string> headers;
};
}; // namespace http
