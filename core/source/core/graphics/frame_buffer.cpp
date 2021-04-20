#include "frame_buffer.hpp"

#include <glad/glad.h>

FrameBuffer::FrameBuffer(U32 p_width, U32 p_height) : m_renderer_id(0), m_width(p_width), m_height(p_height)
{
    resize(m_width, m_height);
}

FrameBuffer::FrameBuffer(const Vector2& p_size) : m_renderer_id(0), m_width(p_size.x), m_height(p_size.y)
{
    resize(m_width, m_height);
}

FrameBuffer::~FrameBuffer()
{
    delete_renderer_objects();
}

const U32& FrameBuffer::get_renderer_id() const
{
    return m_renderer_id;
}

const Texture& FrameBuffer::get_color_texture() const
{
    return m_color_texture;
}

const Texture& FrameBuffer::get_depth_texture() const
{
    return m_depth_texture;
}

void FrameBuffer::resize(U32 p_width, U32 p_height)
{
    if (m_renderer_id > 0) {
        delete_renderer_objects();
    }

    glCreateFramebuffers(1, &m_renderer_id);
    glBindFramebuffer(GL_FRAMEBUFFER, m_renderer_id);

//    m_color_texture = Texture(p_width, p_height, GL_RGBA8);
//    m_depth_texture = Texture(p_width, p_height, GL_DEPTH24_STENCIL8);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_color_texture.get_renderer_id(), 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, m_depth_texture.get_renderer_id(), 0);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        std::cout << "Frame buffer is incomplete" << std::endl;
        delete_renderer_objects();
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FrameBuffer::delete_renderer_objects() const
{
    glDeleteBuffers(1, &m_renderer_id);
    glDeleteTextures(1, &m_color_texture.get_renderer_id());
    glDeleteTextures(1, &m_depth_texture.get_renderer_id());
}
