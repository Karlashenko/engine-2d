#include "random.hpp"

#include <random>

Random::Random(I32 p_seed) : m_seed(p_seed)
{
}

F32 Random::range(F32 p_min, F32 p_max) const
{
    static std::default_random_engine random_engine(m_seed);
    static std::uniform_real_distribution<> distribution(p_min, p_max);
    return distribution(random_engine);
}

I32 Random::range(I32 p_min, I32 p_max) const
{
    static std::default_random_engine random_engine(m_seed);
    static std::uniform_real_distribution<> distribution(p_min, p_max);
    return distribution(random_engine);
}
