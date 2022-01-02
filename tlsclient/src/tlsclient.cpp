#include "tlsclient.hpp"
#include "response.hpp"

namespace http
{

tlsclient::tlsclient() : client{} {};
response tlsclient::get(const std::string &url)
{
    return this->client::get(url);
}
tlsclient::~tlsclient()
{
    this->close();
}

}; // namespace http
