#pragma once

class TransformComponent
{
public:
    TransformComponent();
    TransformComponent(const Vector2& p_position, const Vector2& p_scale, F32 p_rotation);

    void set_position(const Vector2& p_position);
    void set_scale(const Vector2& p_scale);
    void set_rotation(F32 p_rotation);

    [[nodiscard]] const Vector2& get_position() const;
    [[nodiscard]] const Vector2& get_scale() const;
    [[nodiscard]] F32 get_rotation() const;

    [[nodiscard]] const Matrix& get_matrix();

private:
    Vector2 m_position;
    Vector2 m_scale;
    F32 m_rotation;
    Matrix m_matrix;
    bool m_is_dirty;
};
