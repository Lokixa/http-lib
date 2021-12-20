#include <iostream>
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <future>
#include <chrono>
#include <thread>
#include "libs/logger/logger.hpp"
#include "libs/client/client.hpp"

using namespace boost;
using asio::ip::tcp;
using std::cout, std::endl;

std::mutex connection_mutex;
std::condition_variable cv;
bool launched_server = false;

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