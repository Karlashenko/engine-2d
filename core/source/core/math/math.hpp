#pragma once

#include <limits>

class Math
{
public:
    static constexpr F32 k_pi = 3.14159265358979323846;
    static constexpr F32 k_tau = k_pi * 2;
    static constexpr F32 k_radians = k_pi / 180;
    static constexpr F32 k_degrees = 180 / k_pi;
    static constexpr F32 k_epsilon = FLT_EPSILON;

    static F32 abs(F32 p_value);
    static F32 to_degrees(F32 p_radians);
    static F32 to_radians(F32 p_degrees);
    static F32 max(F32 p_value_a, F32 p_value_b);
    static F32 min(F32 p_value_a, F32 p_value_b);
    static F32 lerp(F32 p_value_a, F32 p_value_b, F32 p_amount);
    static F32 distance(F32 p_value_a, F32 p_value_b);
    static F32 clamp(F32 p_value, F32 p_min, F32 p_max);
    static F32 clamp01(F32 p_value);
    static bool equals(F32 p_value_a, F32 p_value_b);

private:
    Math() = default;
};
