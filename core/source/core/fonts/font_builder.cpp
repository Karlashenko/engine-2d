#include "font_builder.hpp"

#include <algorithm>
#include <stb_image.h>

#include "../algorithm/algorithm.hpp"

FontBuilder::FontBuilder(U32 p_texture_width, U32 p_texture_height, U32 p_glyph_height)
    : m_texture_width(p_texture_width), m_texture_height(p_texture_height), m_glyph_height(p_glyph_height)
{
    m_texture_width = p_texture_width;
    m_texture_height = p_texture_height;

    m_pixels_size = m_texture_width * m_texture_height * sizeof(U8);
    m_pixels = (U8*) malloc(m_pixels_size);

    m_stbtt_context = new stbtt_pack_context();
    stbtt_PackBegin(m_stbtt_context, m_pixels, m_texture_width, m_texture_height, m_texture_width, 1, nullptr);
}

void FontBuilder::add_glyphs(List<U8> p_font_data, const List<CharacterRange>& p_character_ranges)
{
    stbtt_fontinfo font_info = stbtt_fontinfo();
    stbtt_InitFont(&font_info, p_font_data.data(), 0);

    I32 ascent;
    I32 descent;
    I32 line_gap;
    stbtt_GetFontVMetrics(&font_info, &ascent, &descent, &line_gap);

    F32 font_scale_factor = stbtt_ScaleForPixelHeight(&font_info, m_glyph_height);

    for (auto& character_range : p_character_ranges) {
        U32 characters_count = character_range.get_count();
        auto* characters = new stbtt_packedchar[characters_count];

        stbtt_PackFontRange(m_stbtt_context, p_font_data.data(), 0, m_glyph_height, character_range.start, characters_count, characters);

        for (U32 index = 0; index < characters_count; index++) {
            stbtt_packedchar character = characters[index];
            U32 codepoint = character_range.start + index;

            if (character.xadvance < 0) {
                std::cout << "Font texture cannot fit all characters." << std::endl;
                exit(1);
            }

            Glyph glyph = Glyph(
                codepoint,
                character.x0,
                m_texture_height - (character.y0 + character.y1 - character.y0),
                character.x1 - character.x0,
                character.y1 - character.y0,
                character.xoff,
                character.yoff,
                character.xoff2,
                character.yoff2,
                character.xadvance
            );

            m_glyphs.insert(std::make_pair(codepoint, glyph));
        }

        delete[] characters;
    }
}

Shared<Font> FontBuilder::build() const
{
    bitmap_flip_vertical(m_pixels, m_texture_width, m_texture_height, 1);

    U8* rgba_pixels = (U8*) malloc(m_pixels_size * 4 * sizeof(U8));

    for (int i = 0; i < m_pixels_size; i++) {
        rgba_pixels[i * 4 + 0] = 255;
        rgba_pixels[i * 4 + 1] = 255;
        rgba_pixels[i * 4 + 2] = 255;
        rgba_pixels[i * 4 + 3] = m_pixels[i];
    }

    Shared<Texture> texture = create_shared<Texture>(m_texture_width, m_texture_height, rgba_pixels);

    free(rgba_pixels);
    free(m_pixels);
    stbtt_PackEnd(m_stbtt_context);

    return create_shared<Font>(m_glyph_height, m_glyphs, texture);
}
