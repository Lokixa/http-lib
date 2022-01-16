#pragma once
#include <iostream>
#include <mutex>
#include <string_view>

namespace logger
{
class logger final
{
    std::mutex in_use_mutex;

    // Singleton class
    logger(logger &) = delete;
    logger(logger &&) = delete;

  public:
    logger() : in_use_mutex{}
    {
    }
    void log(std::string_view text)
    {
        in_use_mutex.lock();
        std::cout << text;
        in_use_mutex.unlock();
    }
    void logln()
    {
        log("\n");
    }
    void logln(std::string_view text)
    {
        in_use_mutex.lock();
        std::cout << text << '\n';
        in_use_mutex.unlock();
    }
};
}; // namespace logger
