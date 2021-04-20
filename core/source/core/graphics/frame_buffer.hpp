#pragma once

#include "texture.hpp"

class FrameBuffer final
{
public:
    FrameBuffer() = delete;
    FrameBuffer(U32 p_width, U32 p_height);
    FrameBuffer(const Vector2& p_size);
    ~FrameBuffer();

    [[nodiscard]] const U32& get_renderer_id() const;
    [[nodiscard]] const Texture& get_color_texture() const;
    [[nodiscard]] const Texture& get_depth_texture() const;

    void resize(U32 p_width, U32 p_height);

private:
    U32 m_renderer_id;
    U32 m_width;
    U32 m_height;
    Texture m_color_texture;
    Texture m_depth_texture;

    void delete_renderer_objects() const;
};
