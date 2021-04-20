#pragma once

#include "../../graphics/texture.hpp"

struct SpriteComponent
{
    Shared<Texture> texture;
    Vector2 size;
    Vector2 pivot;
    Vector4 color;
    F32 tiling_factor;

    explicit SpriteComponent(const Shared<Texture>& p_texture)
        : texture(p_texture), size(p_texture->get_size()), pivot(Vector2(0.5)), color(Vector4(1)), tiling_factor(1)
    {
    }
};
