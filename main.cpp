#include <iostream>
#include "logger.hpp"
#include "client.hpp"

using std::cout, std::endl;

void start_client(std::string_view);
int main(int argc, char *argv[])
{
    try
    {
        if (argc > 1)
        {
            start_client(std::string{argv[argc - 1]});
        }
        else
        {
            start_client("http://localhost/");
        }
    }
    catch (std::exception &e)
    {
        logger::logln("Exception: ");
        logger::logln(e.what());
    }
    return 0;
}
void start_client(std::string_view hostname)
{
    http::client client{};
    client.get(hostname);
}