#pragma once

class Rectangle
{
public:
    F32 x;
    F32 y;
    F32 width;
    F32 height;

    Rectangle();
    Rectangle(F32 p_x, F32 p_y, F32 p_width, F32 p_height);
    Rectangle(F32 p_x, F32 p_y, const Vector2& p_size);
    Rectangle(const Vector2& p_position, const Vector2& p_size);

    [[nodiscard]] Vector2 get_position() const;
    void set_position(const Vector2& p_position);

    void set_size(const Vector2& p_size);
    [[nodiscard]] Vector2 get_size() const;

    [[nodiscard]] F32 get_left() const;
    [[nodiscard]] F32 get_right() const;
    [[nodiscard]] F32 get_top() const;
    [[nodiscard]] F32 get_bottom() const;

    [[nodiscard]] bool intersects(const Rectangle& p_rectangle) const;
    [[nodiscard]] bool contains(const Rectangle& p_rectangle) const;
    [[nodiscard]] bool contains(const Vector2 & p_point) const;
    [[nodiscard]] bool contains(F32 p_x, F32 p_y) const;
};
