#include "vertex_array.hpp"

#include <glad/glad.h>
#include <iostream>

VertexArray::VertexArray() : m_renderer_id(0)
{
    glGenVertexArrays(1, &m_renderer_id);
}

VertexArray::VertexArray(const Shared<VertexBuffer>& p_vertex_buffer, const Shared<IndexBuffer>& p_index_buffer) : m_renderer_id(0)
{
    glGenVertexArrays(1, &m_renderer_id);
    set_vertex_buffer(p_vertex_buffer);
    set_index_buffer(p_index_buffer);
}

VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1, &m_renderer_id);
}

const RendererId& VertexArray::get_renderer_id() const
{
    return m_renderer_id;
}

Shared<IndexBuffer> VertexArray::get_index_buffer() const
{
    return m_index_buffer;
}

Shared<VertexBuffer> VertexArray::get_vertex_buffer() const
{
    return m_vertex_buffer;
}

void VertexArray::set_vertex_buffer(const Shared<VertexBuffer>& p_vertex_buffer)
{
    m_vertex_buffer = p_vertex_buffer;

    glBindVertexArray(m_renderer_id);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertex_buffer->get_renderer_id());

    const VertexLayout& layout = m_vertex_buffer->get_layout();
    const List<VertexAttribute>& attributes = layout.get_attributes();

    for (int i = 0; i < attributes.size(); i++) {
        const auto& attribute = attributes[i];

        glEnableVertexAttribArray(i);
        glVertexAttribPointer(i, attribute.count, GL_FLOAT, attribute.is_normalized, layout.get_stride(), (void*) attribute.offset);
    }
}

void VertexArray::set_index_buffer(const Shared<IndexBuffer>& p_index_buffer)
{
    m_index_buffer = p_index_buffer;

    glBindVertexArray(m_renderer_id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, p_index_buffer->get_renderer_id());
}
