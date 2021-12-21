#pragma once
#include <string_view>
#include <mutex>

// TODO Rethink logger scope
class logger
{
    std::shared_ptr<std::mutex> in_use_mutex;

public:
    logger() : in_use_mutex{new std::mutex{}} {}
    logger(logger &logger) : in_use_mutex{logger.in_use_mutex} {}
    logger(logger &&logger) : in_use_mutex{std::move(logger.in_use_mutex)} {}
    void operator()(std::string_view text)
    {
        if (text.empty())
            return;
        in_use_mutex->lock();
        printf("%s\n", text.data());
        in_use_mutex->unlock();
    }
    void write(std::string_view text)
    {

        if (text.empty())
            return;
        in_use_mutex->lock();
        printf("%s", text.data());
        in_use_mutex->unlock();
    }
};