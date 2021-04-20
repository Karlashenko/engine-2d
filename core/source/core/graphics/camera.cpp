#include "camera.hpp"

Camera::Camera(Vector2 p_size, const Vector2& p_pivot) : Camera(p_size.x, p_size.y, p_pivot)
{
}

Camera::Camera(F32 p_width, F32 p_height, const Vector2& p_pivot)
    : m_pivot(p_pivot), m_projection(Matrix(1.0F)), view(Matrix(1.0F))
{
    set_projection(p_width, p_height);
}

Matrix Camera::get_view_projection() const
{
    return m_projection * view;
}

Vector2 Camera::get_position() const
{
    return Vector2(view[3]);
}

void Camera::set_projection(F32 p_width, F32 p_height)
{
    F32 x0 = -p_width * m_pivot.x;
    F32 x1 = x0 + p_width;
    F32 y0 = -p_height * m_pivot.y;
    F32 y1 = y0 + p_height;

    m_projection = glm::ortho(x0, x1, y0, y1);
}

void Camera::set_position(Vector2 p_position)
{
    view = glm::translate(view, Vector3(p_position, 0));
}

void Camera::set_zoom(F32 p_zoom)
{
    view = glm::scale(view, Vector3(p_zoom, p_zoom, 0));
}
