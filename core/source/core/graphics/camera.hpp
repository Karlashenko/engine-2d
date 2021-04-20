#pragma once

class Camera final
{
public:
    Matrix view;

    Camera() = delete;
    explicit Camera(Vector2 p_size, const Vector2& p_pivot);
    Camera(F32 p_width, F32 p_height, const Vector2& p_pivot);

    [[nodiscard]] Matrix get_view_projection() const;
    [[nodiscard]] Vector2 get_position() const;
    void set_projection(F32 p_width, F32 p_height);
    void set_position(Vector2 p_position);
    void set_zoom(F32 p_zoom);

private:
    Matrix m_projection;
    Vector2 m_pivot;
};
