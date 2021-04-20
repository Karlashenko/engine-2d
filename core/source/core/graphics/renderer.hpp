#pragma once

#include <utility>

#include "shader.hpp"
#include "texture.hpp"
#include "vertex_array.hpp"
#include "camera.hpp"
#include "graphics.hpp"
#include "vertex.hpp"
#include "../numerics/rectangle.hpp"
#include "renderer_stats.hpp"

class Renderer final
{
public:
    explicit Renderer(Shared<Graphics> p_graphics);
    ~Renderer();

    void clear() const;
    void begin(const Matrix& p_view_projection);

    void draw(const Matrix& p_transform,
              const Vector2& p_pivot,
              const Shared<Texture>& p_texture,
              const Vector4& p_color,
              F32 p_tiling_factor,
              F32 p_sorting_layer);

    void draw(const Matrix& p_transform,
              const Vector2& p_pivot,
              const Shared<Texture>& p_texture,
              const Rectangle& p_rectangle,
              const Vector4& p_color,
              F32 p_tiling_factor,
              F32 p_sorting_layer);

    void draw(const Matrix& p_transform,
              const Vector2& p_pivot,
              const Shared<Texture>& p_texture,
              const Array<Vector2, 4>& p_texture_coordinates,
              const Vector4& p_color,
              F32 p_tiling_factor,
              F32 p_sorting_layer);

    void flush();

    void reset_stats();
    const RendererStats& get_stats() const;

    void set_viewport(const Vector2& size) const;
    void set_viewport(U32 p_width, U32 p_height) const;

    void set_shader(const Shared<Shader>& p_shader);
    void reset_shader();

    void set_mask_texture(const Shared<Texture>& p_mask_texture);
    void reset_mask_texture();

private:
    static const U32 k_max_quads = 20000;
    static const U32 k_vertices_per_quad = 4;
    static const U32 k_indices_per_quad = 6;
    static constexpr Array<Vector2, 4> k_quad_texture_coordinates = {Vector2(0, 0), Vector2(1, 0), Vector2(1, 1), Vector2(0, 1)};

    Vertex* m_vertices = nullptr;
    Vertex* m_vertices_iterator = nullptr;

    Shared<Graphics> m_graphics;
    Unique<VertexArray> m_vertex_array;
    List<Shared<Texture>> m_textures;
    Shared<Shader> m_default_shader;
    Shared<Shader> m_shader;
    Shared<Texture> m_white_texture;
    Shared<Texture> m_mask_texture;
    U32 m_quad_counter;
    RendererStats m_stats;

    static Shared<IndexBuffer> create_index_buffer();
    static Shared<VertexBuffer> create_vertex_buffer();
};
