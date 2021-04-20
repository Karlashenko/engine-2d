#pragma once

#include "vertex_buffer.hpp"
#include "index_buffer.hpp"

class VertexArray final
{
public:
    VertexArray();
    VertexArray(const Shared<VertexBuffer>& p_vertex_buffer, const Shared<IndexBuffer>& p_index_buffer);

    ~VertexArray();

    void set_vertex_buffer(const Shared<VertexBuffer>& p_vertex_buffer);
    void set_index_buffer(const Shared<IndexBuffer>& p_index_buffer);
    [[nodiscard]] const RendererId& get_renderer_id() const;
    [[nodiscard]] Shared<IndexBuffer> get_index_buffer() const;
    [[nodiscard]] Shared<VertexBuffer> get_vertex_buffer() const;

private:
    U32 m_renderer_id;
    Shared<IndexBuffer> m_index_buffer;
    Shared<VertexBuffer> m_vertex_buffer;
};
