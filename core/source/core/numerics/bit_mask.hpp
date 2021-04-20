#pragma once

#include "numbers.hpp"
#include "../collections/array.hpp"

class BitMask
{
public:
    BitMask() : m_mask(Array<U32, 8>())
    {
    }

    explicit BitMask(const Array<U32, 8>& p_mask) : m_mask(p_mask)
    {
    }

    void set(U32 p_index);
    void unset(U32 p_index);

    [[nodiscard]] bool is_empty() const;
    [[nodiscard]] bool is_set(U32 p_index) const;
    [[nodiscard]] bool contains_all(const BitMask& p_other) const;
    [[nodiscard]] bool contains_any(const BitMask& p_other) const;

private:
    static const I32 k_mask_stride = sizeof(U32) * 8 - 1;
    static const I32 k_mask_shift = 5;

    Array<U32, 8> m_mask;
};
