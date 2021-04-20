#pragma once

struct RendererStats
{
    U32 draw_calls;
    U32 quads;
    U32 vertices;
    U32 indices;
    U32 textures;

    RendererStats() : draw_calls(0), quads(0), vertices(0), indices(0), textures(0)
    {
    }

    RendererStats(const U32& p_draw_calls, const U32& p_quads, const U32& p_vertices, const U32& p_indices, const U32& p_textures)
        : draw_calls(p_draw_calls), quads(p_quads), vertices(p_vertices), indices(p_indices), textures(p_textures)
    {
    }
};
