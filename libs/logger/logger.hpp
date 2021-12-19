#pragma once
#include <string_view>
#include <mutex>

class logger
{
    std::mutex in_use_mutex;

public:
    void operator()(std::string_view text)
    {
        if (text.empty())
            return;
        in_use_mutex.lock();
        printf("%s\n", text.data());
        in_use_mutex.unlock();
    }
};