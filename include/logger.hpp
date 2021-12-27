#pragma once
#include <string_view>
#include <mutex>

// TODO Rethink logger scope
class logger
{
    static std::mutex in_use_mutex;

public:
    logger() = delete;
    logger(logger &) = delete;
    logger(logger &&) = delete;
    static void log(std::string_view text)
    {
        in_use_mutex.lock();
        printf("%s", text.data());
        in_use_mutex.unlock();
    }
    static void logln(std::string_view text)
    {
        log(std::string{text} + '\n');
    }
    static void log(char c)
    {
        in_use_mutex.lock();
        putc(c, stdout);
        in_use_mutex.unlock();
    }
};
std::mutex logger::in_use_mutex{};