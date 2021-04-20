#pragma once

#include "glyph.hpp"
#include "../graphics/texture.hpp"

class Font
{
public:
    Font() = delete;
    Font(U32 p_size, const HashMap<U32, Glyph>& p_glyphs, const Shared<Texture>& p_texture);

    [[nodiscard]] U32 get_size() const;
    [[nodiscard]] Shared<Texture> get_texture() const;
    [[nodiscard]] const Glyph& get_glyph(U32 p_codepoint) const;
    [[nodiscard]] List<Glyph> get_glyphs(const String& p_string) const;

private:
    HashMap<U32, Glyph> m_glyphs;
    Shared<Texture> m_texture;
    U32 m_size;
};
