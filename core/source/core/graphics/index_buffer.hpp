#pragma once

class IndexBuffer
{
public:
    IndexBuffer(U32* p_indices, U32 p_size, U32 p_usage);
    ~IndexBuffer();

    [[nodiscard]] const RendererId& get_renderer_id() const;

private:
    RendererId m_renderer_id;
};
