#include "math.hpp"

F32 Math::abs(F32 p_value)
{
    return p_value > 0 ? p_value : -p_value;
}

F32 Math::to_degrees(F32 p_radians)
{
    return p_radians * k_degrees;
}

F32 Math::to_radians(F32 p_degrees)
{
    return p_degrees * k_radians;
}

F32 Math::max(F32 p_value_a, F32 p_value_b)
{
    return p_value_a >= p_value_b ? p_value_a : p_value_b;
}

F32 Math::min(F32 p_value_a, F32 p_value_b)
{
    return p_value_a <= p_value_b ? p_value_a : p_value_b;
}

F32 Math::lerp(F32 p_value_a, F32 p_value_b, F32 p_amount)
{
    return p_value_a + (p_value_b - p_value_a) * p_amount;
}

F32 Math::distance(F32 p_value_a, F32 p_value_b)
{
    return abs(p_value_a - p_value_b);
}

F32 Math::clamp(F32 p_value, F32 p_min, F32 p_max)
{
    if (p_value < p_min) {
        return p_min;
    }

    if (p_value > p_max) {
        return p_max;
    }

    return p_value;
}

F32 Math::clamp01(F32 p_value)
{
    return clamp(p_value, 0, 1);
}

bool Math::equals(F32 p_value_a, F32 p_value_b)
{
    return abs(p_value_b - p_value_b) < k_epsilon;
}
