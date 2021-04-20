#pragma once

#include "font.hpp"

struct CharacterRange
{
    U32 start;
    U32 end;

    CharacterRange(const U32& p_start, const U32& p_end) : start(p_start), end(p_end)
    {
    }

    [[nodiscard]] U32 get_count() const
    {
        return end - start + 1;
    }

    static CharacterRange create_basic_latin()
    {
        return CharacterRange(0x0000, 0x007F);
    }

    static CharacterRange create_cyrillic()
    {
        return CharacterRange(0x0400, 0x04FF);
    }

    static CharacterRange create_cjk_symbols_and_punctuation()
    {
        return CharacterRange(0x4E00, 0x9FFF);
    }
};
