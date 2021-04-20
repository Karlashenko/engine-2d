#pragma once

#include <stb_truetype.h>
#include "glyph.hpp"
#include "character_range.hpp"
#include "../io/file_system.hpp"

class FontBuilder final
{
public:
    FontBuilder() = delete;
    FontBuilder(U32 p_texture_width, U32 p_texture_height, U32 p_glyph_height);

    void add_glyphs(List<U8> p_font_data, const List<CharacterRange>& p_character_ranges);

    [[nodiscard]] Shared<Font> build() const;

private:
    U32 m_texture_width;
    U32 m_texture_height;
    U32 m_glyph_height;
    U8* m_pixels = nullptr;
    U32 m_pixels_size;
    stbtt_pack_context* m_stbtt_context = nullptr;
    HashMap<U32, Glyph> m_glyphs;
};
