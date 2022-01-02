#include "tlsclient.hpp"
#include "response.hpp"

namespace http
{

tlsclient::tlsclient() : client{} {};
// TODO(#4): Implement tls
response tlsclient::get(const std::string &url)
{
    return this->client::get(url);
}
tlsclient::~tlsclient()
{
    this->close();
}

}; // namespace http
