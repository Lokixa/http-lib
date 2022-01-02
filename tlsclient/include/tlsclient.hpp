#pragma once
#include "client.hpp"
#include <string>

namespace http
{
struct response;
struct tlsclient : client
{
    tlsclient();
    response get(const std::string &) override;
    ~tlsclient() override;
};
}; // namespace http