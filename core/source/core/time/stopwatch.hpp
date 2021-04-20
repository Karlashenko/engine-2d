#pragma once

#include <chrono>

class Stopwatch
{
public:
    Stopwatch();

    void restart();

    [[nodiscard]] F32 get_delta() const;

private:
    std::chrono::time_point<std::chrono::steady_clock> m_start;
};
