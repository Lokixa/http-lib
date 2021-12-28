#pragma once
#include <mutex>
#include <iostream>

// TODO Rethink logger scope
class logger final
{
    static std::mutex in_use_mutex;

    // Singleton class
    logger() = delete;
    logger(logger &) = delete;
    logger(logger &&) = delete;

public:
    static void log(std::string_view text)
    {
        in_use_mutex.lock();
        std::cout << text;
        in_use_mutex.unlock();
    }
    static void logln(std::string_view text)
    {
        in_use_mutex.lock();
        std::cout << text << '\n';
        in_use_mutex.unlock();
    }
};
std::mutex logger::in_use_mutex{};