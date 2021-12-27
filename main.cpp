#include <iostream>
#include "logger.hpp"
#include "client.hpp"
#include <future>

using std::cout, std::endl;

void start(std::string_view);
int main(int argc, char *argv[])
{
    try
    {
        if (argc > 1)
        {
            start(std::string{argv[argc - 1]});
        }
        else
        {
            start("http://localhost/");
        }
    }
    catch (std::exception &e)
    {
        logger::logln("Exception: ");
        logger::logln(e.what());
    }
    return 0;
}
void generic_test(std::string_view hostname);
void async_test(std::string_view hostname);
void start(std::string_view hostname)
{
    async_test(hostname);
}
void generic_test(std::string_view hostname)
{
    http::client client{};
    client.get(hostname);
}

// More to test out external singleton classes
void async_test(std::string_view hostname)
{
    std::vector<std::future<void>> futures;
    for (size_t i = 0; i < 10; ++i)
    {
        logger::logln("Starting a task");
        futures.push_back(
            std::async(generic_test, hostname));
    }
    for (const auto &future : futures)
    {
        future.wait();
    }
}