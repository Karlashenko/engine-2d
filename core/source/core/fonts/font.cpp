#include "font.hpp"

#include <utf8.h>

Font::Font(U32 p_size, const HashMap<U32, Glyph>& p_glyphs, const Shared<Texture>& p_texture)
    : m_size(p_size), m_glyphs(p_glyphs), m_texture(p_texture)
{
}

U32 Font::get_size() const
{
    return m_size;
}

Shared<Texture> Font::get_texture() const
{
    return m_texture;
}

const Glyph& Font::get_glyph(U32 p_codepoint) const
{
    if (!m_glyphs.contains(p_codepoint)) {
        // std::cout << "Missing glyph for codepoint: " << p_codepoint << std::endl;
        return m_glyphs.at(63);
    }

    return m_glyphs.at(p_codepoint);
}

List<Glyph> Font::get_glyphs(const String& p_string) const
{
    auto begin = p_string.begin();
    auto end = p_string.end();

    List<Glyph> glyphs = List<Glyph>();

    while (begin != end) {
        U32 codepoint = utf8::next(begin, end);
        glyphs.emplace_back(get_glyph(codepoint));
    }

    return glyphs;
}
