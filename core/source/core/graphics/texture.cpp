#include "texture.hpp"

#include <glad/glad.h>
#include <stb_image.h>

Texture::Texture()
    : m_renderer_id(0), m_width(0), m_height(0)
{
}

Texture::Texture(U32 p_width, U32 p_height)
    : m_renderer_id(0), m_width(p_width), m_height(p_height)
{
    m_renderer_id = create_blank(p_width, p_height, GL_RGBA8);

    U32 pixels_size = m_width * m_height * sizeof(U8);
    U8* pixels = (U8*) malloc(pixels_size);

    memset(pixels, 255, pixels_size);

    set_data(pixels, GL_RGBA, GL_UNSIGNED_BYTE);

    free(pixels);
}

Texture::Texture(U32 p_width, U32 p_height, void* p_pixels)
    : Texture(p_width, p_height, p_pixels, GL_RGBA8, GL_RGBA)
{
}

Texture::Texture(U32 p_width, U32 p_height, void* p_pixels, U32 p_internal_format, U32 p_format)
    : m_renderer_id(0), m_width(p_width), m_height(p_height)
{
    m_renderer_id = create_blank(p_width, p_height, p_internal_format);
    set_data(p_pixels, p_format, GL_UNSIGNED_BYTE);
}

Texture::~Texture()
{
    glDeleteTextures(1, &m_renderer_id);
}

RendererId Texture::create_blank(U32 p_width, U32 p_height, U32 p_internal_format)
{
    RendererId renderer_id;

    glCreateTextures(GL_TEXTURE_2D, 1, &renderer_id);
    glTextureStorage2D(renderer_id, 1, p_internal_format, p_width, p_height);
    glTextureParameteri(renderer_id, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTextureParameteri(renderer_id, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTextureParameteri(renderer_id, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTextureParameteri(renderer_id, GL_TEXTURE_WRAP_T, GL_REPEAT);

    return renderer_id;
}

void Texture::set_data(void* p_data, U32 p_format, U32 p_data_type) const
{
    glTextureSubImage2D(m_renderer_id, 0, 0, 0, m_width, m_height, p_format, p_data_type, p_data);
}

const RendererId& Texture::get_renderer_id() const
{
    return m_renderer_id;
}

const String& Texture::get_file_path() const
{
    return m_file_path;
}

I32 Texture::get_width() const
{
    return m_width;
}

I32 Texture::get_height() const
{
    return m_height;
}

Vector2 Texture::get_size() const
{
    return Vector2(m_width, m_height);
}

bool Texture::operator==(const Texture& p_texture) const
{
    return m_renderer_id == p_texture.m_renderer_id;
}

bool Texture::operator!=(const Texture& p_texture) const
{
    return m_renderer_id != p_texture.m_renderer_id;
}
