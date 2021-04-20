#pragma once

#include "../numerics/rectangle.hpp"

struct Glyph
{
    U32 codepoint;
    I32 x;
    I32 y;
    I32 width;
    I32 height;
    I32 offset_x;
    I32 offset_y;
    I32 offset_x2;
    I32 offset_y2;
    I32 advance_x;

    Glyph(U32 p_codepoint, I32 p_x, I32 p_y, I32 p_width, I32 p_height, I32 p_offset_x, I32 p_offset_y, I32 p_offset_x_2, I32 p_offset_y_2, I32 p_advance_x)
        : codepoint(p_codepoint), x(p_x), y(p_y), width(p_width), height(p_height), offset_x(p_offset_x), offset_y(p_offset_y), offset_x2(p_offset_x_2), offset_y2(p_offset_y_2), advance_x(p_advance_x)
    {
    }

    Vector2 get_size() const
    {
        return Vector2(width, height);
    }

    Rectangle get_rectangle() const
    {
        return Rectangle(x, y, width, height);
    }
};
