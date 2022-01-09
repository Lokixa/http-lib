#pragma once
#include "client.hpp"
#include <string>
#define OPENSSL_API_COMPAT 30000
#define OPENSSL_NO_DEPRECATED

#include <openssl/ssl.h>
#include <openssl/conf.h>

namespace http::tls
{
    struct tlsclient final : public http::client
    {
        tlsclient();
        http::response get(const std::string &url) override;
        void close() override;
        ~tlsclient();

    private:
        SSL_CTX *ctx;
        SSL *ssl;
        long res;
    };
} // namespace http::tls
