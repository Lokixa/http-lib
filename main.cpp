#include "client.hpp"
#include "logger.hpp"
#include "response.hpp"
#include "tlsclient.hpp"

#include <future>
#include <iostream>
#include <locale>
#include <memory>
#include <string_view>
#include <type_traits>
#include <vector>

using std::cout, std::endl;

class Tests
{
    void start()
    {
        generic_test();
    }
    void generic_test()
    {
        http::response response = client->get(*hostname);
        for (auto &&[key, value] : response.headers)
        {
            logger->logln(key + ": " + value);
        }
        logger->logln();
        logger->log(response.body);
    }

    // void async_test()
    // {
    //     std::vector<std::future<void>> futures;
    //     for (size_t i = 0; i < 10; ++i)
    //     {
    //         logger->logln("Starting a task");
    //         futures.push_back(
    //             std::async(generic_test));
    //     }
    //     for (const auto &future : futures)
    //     {
    //         future.wait();
    //     }
    // }

  public:
    std::shared_ptr<logger::logger> logger;
    std::unique_ptr<http::client> client;
    std::unique_ptr<std::string> hostname;
    Tests(std::unique_ptr<http::client> &&client)
        : logger{new logger::logger{}}, client{std::move(client)}, hostname{} {};
    int run(const std::string &hostname)
    {
        this->hostname = std::make_unique<std::string>(hostname);
        try
        {
            start();
        }
        catch (std::exception &e)
        {
            logger->logln("Exception: ");
            logger->logln(e.what());
        }

        return 0;
    }
};
int main(int argc, char *argv[])
{
    std::string hostname = "localhost";
    if (argc > 1)
    {
        hostname = std::string{argv[argc - 1]};
    }
    Tests tests{std::make_unique<http::client>()};
    tests.run("http://" + hostname);
    Tests tlstests{std::make_unique<http::tlsclient>()};
    tlstests.run("https://" + hostname);
    return 0;
}
