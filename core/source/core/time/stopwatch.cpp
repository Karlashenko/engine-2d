#include "stopwatch.hpp"

Stopwatch::Stopwatch()
{
    restart();
}

void Stopwatch::restart()
{
    m_start = std::chrono::high_resolution_clock::now();
}

F32 Stopwatch::get_delta() const
{
    auto now = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::duration<float, std::milli>>(now - m_start).count();
}
