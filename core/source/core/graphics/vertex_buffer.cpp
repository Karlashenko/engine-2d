#include "vertex_buffer.hpp"

#include <glad/glad.h>
#include <utility>

VertexBuffer::VertexBuffer() : m_renderer_id(0)
{
    glGenBuffers(1, &m_renderer_id);
}

VertexBuffer::VertexBuffer(void* p_data, U32 p_size, U32 p_usage, VertexLayout p_layout)
    : m_renderer_id(0), m_layout(std::move(p_layout))
{
    glGenBuffers(1, &m_renderer_id);
    glBindBuffer(GL_ARRAY_BUFFER, m_renderer_id);
    glBufferData(GL_ARRAY_BUFFER, p_size, p_data, p_usage);
}

VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1, &m_renderer_id);
}

const RendererId& VertexBuffer::get_renderer_id() const
{
    return m_renderer_id;
}

const VertexLayout& VertexBuffer::get_layout() const
{
    return m_layout;
}

void VertexBuffer::update_data(void* p_data, U32 p_size) const
{
    glBindBuffer(GL_ARRAY_BUFFER, m_renderer_id);
    glBufferSubData(GL_ARRAY_BUFFER, 0, p_size, p_data);
}
