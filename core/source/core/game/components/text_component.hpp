#pragma once

#include <utility>
#include "../../fonts/font.hpp"

class TextComponent final
{
public:
    U32 space_width;
    U32 line_height;

    TextComponent(const Shared<Font>& p_font, String p_text)
        : m_font(p_font), m_text(std::move(p_text))
    {
        space_width = m_font->get_size() * 0.4F;
        line_height = m_font->get_size() * 1.2F;

        m_glyphs = m_font->get_glyphs(m_text);
    }

    [[nodiscard]] Shared<Font> get_font() const
    {
        return m_font;
    }

    [[nodiscard]] const String& get_text() const
    {
        return m_text;
    }

    [[nodiscard]] const List<Glyph>& get_glyphs() const
    {
        return m_glyphs;
    }

private:
    List<Glyph> m_glyphs;
    Shared<Font> m_font;
    String m_text;
};
