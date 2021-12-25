#pragma once
#include <string_view>
#include <mutex>

// TODO Rethink logger scope
namespace logger
{
    class logger
    {
        std::mutex in_use_mutex;

    public:
        logger() : in_use_mutex{} {}
        void logln()
        {
            in_use_mutex.lock();
            putc('\n', stdout);
            in_use_mutex.unlock();
        }
        void logln(std::string_view text)
        {
            in_use_mutex.lock();
            printf("%s\n", text.data());
            in_use_mutex.unlock();
        }
        void log(std::string_view text)
        {
            if (text.empty())
                return;
            in_use_mutex.lock();
            printf("%s", text.data());
            in_use_mutex.unlock();
        }
        void log(char c)
        {
            in_use_mutex.lock();
            putc(c, stdout);
            in_use_mutex.unlock();
        }
    };
};