#include <iostream>
#include "logger.hpp"
#include "client.hpp"

using std::cout, std::endl;

void start_client(std::string_view, std::shared_ptr<logger::logger>);
int main(int argc, char *argv[])
{
    auto logger = std::make_shared<logger::logger>();
    try
    {
        if (argc > 1)
        {
            start_client(argv[argc - 1], logger);
        }
        else
        {
            start_client("http://localhost.com/", logger);
        }
    }
    catch (std::exception &e)
    {
        logger->logln("Exception: ");
        logger->logln(e.what());
    }
    return 0;
}
void start_client(std::string_view hostname, std::shared_ptr<logger::logger> logger)
{
    http::client client(logger);
    client.get(hostname);
}