#pragma once
#include <map>
#include <string>

namespace http
{
struct request
{
    // TODO(#5): Implement fully
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

    request(const std::string &url);

    std::string &operator[](const std::string &header);
    std::string &operator[](const std::string &&header);

    std::string get();

  private:
    std::map<std::string, std::string> headers;
};
}; // namespace http
