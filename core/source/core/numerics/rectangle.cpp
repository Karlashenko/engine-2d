#include "rectangle.hpp"

Rectangle::Rectangle() : x(0), y(0), width(0), height(0)
{
}

Rectangle::Rectangle(F32 p_x, F32 p_y, F32 p_width, F32 p_height)
    : x(p_x), y(p_y), width(p_width), height(p_height)
{
}

Rectangle::Rectangle(F32 p_x, F32 p_y, const Vector2& p_size)
    : x(p_x), y(p_y), width(p_size.x), height(p_size.y)
{
}

Rectangle::Rectangle(const Vector2& p_position, const Vector2& p_size)
    : x(p_position.x), y(p_position.y), width(p_size.x), height(p_size.y)
{
}

void Rectangle::set_position(const Vector2& p_position)
{
    x = p_position.x;
    y = p_position.y;
}

Vector2 Rectangle::get_position() const
{
    return Vector2(x, y);
}

void Rectangle::set_size(const Vector2& p_size)
{
    width = p_size.x;
    height = p_size.y;
}

Vector2 Rectangle::get_size() const
{
    return Vector2(width, height);
}

F32 Rectangle::get_left() const
{
    return x;
}

F32 Rectangle::get_right() const
{
    return x + width;
}

F32 Rectangle::get_top() const
{
    return y + height;
}

F32 Rectangle::get_bottom() const
{
    return y;
}

bool Rectangle::intersects(const Rectangle& p_rectangle) const
{
    return p_rectangle.get_left() < get_right() &&
           p_rectangle.get_right() > get_left() &&
           p_rectangle.get_top() > get_bottom() &&
           p_rectangle.get_bottom() < get_top();
}

bool Rectangle::contains(const Rectangle& p_rectangle) const
{
    return p_rectangle.get_left() >= get_left() &&
           p_rectangle.get_right() <= get_right() &&
           p_rectangle.get_top() <= get_top() &&
           p_rectangle.get_bottom() >= get_bottom();
}

bool Rectangle::contains(F32 p_x, F32 p_y) const
{
    return p_x <= p_x && p_x < p_x + width &&
           p_y <= p_y && p_y < p_y + height;
}

bool Rectangle::contains(const Vector2& p_point) const
{
    return contains(p_point.x, p_point.y);
}
