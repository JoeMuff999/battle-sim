#include <iostream>
#include <chrono>
#include <ctime>
#include <thread>

#ifndef TIME_HPP
#define TIME_HPP

namespace Time
{
    const float MS_PER_FRAME = 1000.0 / 30.0;

    std::chrono::_V2::steady_clock::time_point getTime()
    {
        return std::chrono::steady_clock::now();
    }

    const float getTimeBetween(std::chrono::_V2::steady_clock::time_point curr, std::chrono::_V2::steady_clock::time_point prev)
    {
        std::chrono::duration<float> elapsed_seconds = curr - prev;
        return elapsed_seconds.count();
    }

    const float getElapsedTime(std::chrono::_V2::steady_clock::time_point prevTimePoint)
    {
        auto currTime = std::chrono::steady_clock::now();
        std::chrono::duration<float> elapsed_seconds = currTime - prevTimePoint;

        return elapsed_seconds.count();
    }

    void sleepForMilliseconds(const float floatSleepTime)
    {
        int intSleepTime = static_cast<int>(floatSleepTime);
        std::this_thread::sleep_for(std::chrono::milliseconds(intSleepTime));
    }
}
#endif
