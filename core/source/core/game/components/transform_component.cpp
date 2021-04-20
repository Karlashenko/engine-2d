#include "transform_component.hpp"

TransformComponent::TransformComponent()
    : m_position(Vector2()), m_scale(Vector2()), m_matrix(Matrix(1)), m_rotation(0), m_is_dirty(true)
{
}

TransformComponent::TransformComponent(const Vector2& p_position, const Vector2& p_scale, F32 p_rotation)
    : m_position(p_position), m_scale(p_scale), m_matrix(Matrix(1)), m_rotation(p_rotation), m_is_dirty(true)
{
    set_scale(m_scale);
    set_position(m_position);
    set_rotation(m_rotation);
}

void TransformComponent::set_position(const Vector2& p_position)
{
    m_is_dirty = true;
    m_position = p_position;
}

void TransformComponent::set_rotation(F32 p_rotation)
{
    m_is_dirty = true;
    m_rotation = p_rotation;
}

void TransformComponent::set_scale(const Vector2& p_scale)
{
    m_is_dirty = true;
    m_scale = p_scale;
}

const Vector2& TransformComponent::get_position() const
{
    return m_position;
}

const Vector2& TransformComponent::get_scale() const
{
    return m_scale;
}

F32 TransformComponent::get_rotation() const
{
    return m_rotation;
}

const Matrix& TransformComponent::get_matrix()
{
    if (m_is_dirty) {
        m_matrix = glm::scale(m_matrix, Vector3(m_scale, 0));
        m_matrix = glm::rotate(m_matrix, m_rotation, Vector3(0, 0, 1));
        m_matrix = glm::translate(Matrix(1), Vector3(m_position, 0));
        m_is_dirty = false;
    }

    return m_matrix;
}
