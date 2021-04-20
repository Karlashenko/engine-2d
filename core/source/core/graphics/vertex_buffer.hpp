#pragma once

#include "vertex_layout.hpp"

class VertexBuffer
{
public:
    VertexBuffer();
    VertexBuffer(void* p_data, U32 p_size, U32 p_usage, VertexLayout p_layout);
    ~VertexBuffer();

    [[nodiscard]] const RendererId& get_renderer_id() const;
    [[nodiscard]] const VertexLayout& get_layout() const;

    void update_data(void* p_data, U32 p_size) const;

private:
    RendererId m_renderer_id;
    VertexLayout m_layout;
};
