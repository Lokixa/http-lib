#include "tlsclient.hpp"
#include "response.hpp"
#include "request.hpp"
#include <stdexcept>

namespace http::tls
{
    void handleFailure(const char *reason)
    {
        throw std::runtime_error{reason};
    }
    // TODO Remove or make use of
    void print_cn_name(const char *text, X509_NAME *name) {}
    void print_san_name(const char *text, X509 *cert) {}
    int verify_callback(int preverify, X509_STORE_CTX *x509_ctx)
    {
        int depth = X509_STORE_CTX_get_error_depth(x509_ctx);
        int err = X509_STORE_CTX_get_error(x509_ctx);

        X509 *cert = X509_STORE_CTX_get_current_cert(x509_ctx);
        X509_NAME *iname = cert ? X509_get_issuer_name(cert) : NULL;
        X509_NAME *sname = cert ? X509_get_subject_name(cert) : NULL;

        print_cn_name("Issuer (cn)", iname);
        print_cn_name("Subject (cn)", sname);

        if (depth == 0)
        {
            /* If depth is 0, its the server's certificate. Print the SANs too */
            print_san_name("Subject (san)", cert);
        }

        return preverify;
    }
    ///////////////////////////////////////////

    tlsclient::tlsclient() : ctx{NULL}, ssl{NULL}
    {
        (void)SSL_library_init();

        SSL_load_error_strings();

        /* ERR_load_crypto_strings(); */

        if (CONF_modules_load_file(NULL, NULL,
                                   CONF_MFLAGS_IGNORE_MISSING_FILE) <= 0)
        {
            throw std::runtime_error{"FATAL: error loading configuration file\n"};
        }
        const SSL_METHOD *method = SSLv23_method();
        if (!(NULL != method))
            handleFailure("Method");

        ctx = SSL_CTX_new(method);
        if (!(ctx != NULL))
            handleFailure("Context");

        /* Cannot fail ??? */
        SSL_CTX_set_verify(ctx, SSL_VERIFY_PEER, verify_callback);

        /* Cannot fail ??? */
        SSL_CTX_set_verify_depth(ctx, 4);

        /* Cannot fail ??? */
        const long flags = SSL_OP_NO_SSLv2 | SSL_OP_NO_SSLv3 | SSL_OP_NO_COMPRESSION;
        SSL_CTX_set_options(ctx, flags);

        res = SSL_CTX_set_default_verify_paths(ctx);
        if (!(1 == res))
            handleFailure("Set default paths");
    }
    void tlsclient::close()
    {

        if (ctx)
            SSL_CTX_free(ctx);
    }
    http::response tlsclient::get(const std::string &url)
    {
        http::request req{url};
        req["Connection"] = "close";

        BIO *web = BIO_new_ssl_connect(ctx);
        if (!(web != NULL))
            handleFailure("Couldn't new ssl connect");

        res = BIO_set_conn_hostname(web, (req["Host"] + ":443").c_str());
        if (!(1 == res))
            handleFailure("Couldn't set conn_hostname");

        BIO_get_ssl(web, &ssl);
        if (!(ssl != NULL))
            handleFailure("Couldn't get ssl");

        const char *const PREFERRED_CIPHERS = "HIGH:!aNULL:!kRSA:!PSK:!SRP:!MD5:!RC4";
        res = SSL_set_cipher_list(ssl, PREFERRED_CIPHERS);
        if (!(1 == res))
            handleFailure("Couldn't set cipher list");

        res = SSL_set_tlsext_host_name(ssl, req["Host"].c_str());
        if (!(1 == res))
            handleFailure("Couldn't set tlsext_host_name");

        res = BIO_do_connect(web);
        if (!(1 == res))
            handleFailure("Couldn't connect");

        res = BIO_do_handshake(web);
        if (!(1 == res))
            handleFailure("Couldn't handshake");

        /* Step 1: verify a server certificate was presented during the negotiation */
        X509 *cert = SSL_get_peer_certificate(ssl);
        if (cert)
        {
            X509_free(cert);
        } /* Free immediately */
        if (NULL == cert)
            handleFailure("Null cert");

        /* Step 2: verify the result of chain verification */
        /* Verification performed according to RFC 4158    */
        res = SSL_get_verify_result(ssl);
        if (!(X509_V_OK == res))
            handleFailure("Couldn't verify res");

        // TODO: hostname verification

        BIO_puts(web, req.get().c_str());

        int len = 0;
        std::string http_response;
        char buff[1536] = {};
        do
        {
            len = BIO_read(web, buff, sizeof(buff));

            if (len > 0)
                http_response.append(buff, len);

        } while (len > 0 || BIO_should_retry(web));

        if (web)
            BIO_free_all(web);
        return http::response::parse(http_response);
    }
    tlsclient::~tlsclient()
    {
        this->close();
    }

} // namespace http::tls
