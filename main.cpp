#include <iostream>
#include <future>
#include <chrono>
#include <thread>
#include "libs/logger/logger.hpp"
#include "libs/client/client.hpp"

using std::cout, std::endl;

logger LOG;
void start_client();
void start_client(std::string_view hostname);
int main(int argc, char *argv[])
{
    try
    {
        if (argc > 1)
        {
            start_client(argv[argc - 1]);
        }
        else
        {
            start_client();
        }
    }
    catch (std::exception &e)
    {
        cout << e.what() << endl;
    }
    return 0;
}
void start_client()
{
    try
    {
        http::client client(LOG);
        client.get("127.0.0.1");
    }
    catch (std::exception &e)
    {
        LOG(e.what());
    }
}
void start_client(std::string_view hostname)
{
    try
    {
        http::client client(LOG);
        client.get(hostname);
    }
    catch (std::exception &e)
    {
        LOG(e.what());
    }
}