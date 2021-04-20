#include "index_buffer.hpp"

#include <glad/glad.h>

IndexBuffer::IndexBuffer(U32* p_indices, U32 p_size, U32 p_usage) : m_renderer_id(0)
{
    glGenBuffers(1, &m_renderer_id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_renderer_id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, p_size, p_indices, p_usage);
}

IndexBuffer::~IndexBuffer()
{
    glDeleteBuffers(1, &m_renderer_id);
}

const RendererId& IndexBuffer::get_renderer_id() const
{
    return m_renderer_id;
}
