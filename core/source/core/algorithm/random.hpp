#pragma once

class Random
{
public:
    explicit Random(I32 p_seed);

    [[nodiscard]] F32 range(F32 p_min, F32 p_max) const;
    [[nodiscard]] I32 range(I32 p_min, I32 p_max) const;

private:
    I32 m_seed;
};
