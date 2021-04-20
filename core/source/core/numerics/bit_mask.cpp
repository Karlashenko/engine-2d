#include "bit_mask.hpp"

#include <algorithm>

void BitMask::set(U32 p_index)
{
    auto mask_index = p_index >> k_mask_shift;
    auto mask = 1 << (p_index & k_mask_stride);

    m_mask[mask_index] |= mask;
}

void BitMask::unset(U32 p_index)
{
    auto mask_index = p_index >> k_mask_shift;
    auto mask = 1 << (p_index & k_mask_stride);

    m_mask[mask_index] &= ~mask;
}

bool BitMask::is_set(U32 p_index) const
{
    auto mask_index = p_index >> k_mask_shift;
    auto mask = 1 << (p_index & k_mask_stride);

    return (m_mask[mask_index] & mask) != 0;
}

bool BitMask::contains_all(const BitMask& p_other) const
{
    for (int i = 0; i < 8; i++) {
        if ((m_mask[i] & p_other.m_mask[i]) != p_other.m_mask[i]) {
            return false;
        }
    }

    return true;
}

bool BitMask::contains_any(const BitMask& p_other) const
{
    for (int i = 0; i < 8; i++) {
        if (p_other.m_mask[i] != 0 && (m_mask[i] & p_other.m_mask[i]) == 0) {
            return false;
        }
    }

    return true;
}

bool BitMask::is_empty() const
{
    return array_all_equals<U32, 8>(m_mask, 0);
}
