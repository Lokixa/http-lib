#include <iostream>
#include "logger.hpp"
#include "client.hpp"
#include <vector>
#include <future>
#include <locale>
#include <string_view>
#include <memory>

using std::cout, std::endl;

class Tests
{
    void start()
    {
        generic_test();
    }
    void generic_test()
    {
        http::client client{logger};
        http::response response = client.get(hostname);
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
    std::string hostname = "http://localhost/";
    Tests(int argc, char *argv[]) : logger{new logger::logger{}}
    {
        if (argc > 1)
        {
            hostname = std::string{argv[argc - 1]};
        }
    };
    int run()
    {
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
    Tests tests{argc, argv};
    return tests.run();
}