#include "renderer.hpp"

#include <glad/glad.h>
#include <iostream>
#include <utility>
#include "../math/math.hpp"

Renderer::Renderer(Shared<Graphics> p_graphics)
    : m_graphics(std::move(p_graphics)), m_quad_counter(0)
{
    m_vertex_array = create_unique<VertexArray>();
    m_vertex_array->set_vertex_buffer(create_vertex_buffer());
    m_vertex_array->set_index_buffer(create_index_buffer());

    m_vertices = (Vertex*) malloc(k_max_quads * k_vertices_per_quad * sizeof(Vertex));
    m_vertices_iterator = m_vertices;

    m_textures = List<Shared<Texture>>();
    m_textures.reserve(m_graphics->get_max_texture_units());

    m_default_shader = m_graphics->create_shader("shaders/default.vert", "shaders/default.frag");
    m_shader = m_default_shader;

    m_white_texture = create_shared<Texture>(1, 1);
    m_mask_texture = m_white_texture;

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(0.1, 0.1, 0.1, 1.0);
}

Renderer::~Renderer()
{
    glDeleteVertexArrays(1, &m_vertex_array->get_renderer_id());
    free(m_vertices);
}

Shared<VertexBuffer> Renderer::create_vertex_buffer()
{
    VertexLayout layout = VertexLayout();
    layout.add(2, false);
    layout.add(4, false);
    layout.add(2, false);
    layout.add(1, false);
    layout.add(1, false);

    return create_shared<VertexBuffer>(nullptr, k_max_quads * k_vertices_per_quad * sizeof(Vertex), GL_DYNAMIC_DRAW, layout);
}

Shared<IndexBuffer> Renderer::create_index_buffer()
{
    U32 indices_count = k_max_quads * k_indices_per_quad;
    U32 indices_size = indices_count * sizeof(U32);

    U32* indices = (U32*) malloc(indices_size);

    U32 offset = 0;
    for (U32 i = 0; i < indices_count; i += k_indices_per_quad) {
        indices[i + 0] = offset + 0;
        indices[i + 1] = offset + 1;
        indices[i + 2] = offset + 2;
        indices[i + 3] = offset + 2;
        indices[i + 4] = offset + 3;
        indices[i + 5] = offset + 0;

        offset += k_vertices_per_quad;
    }

    Shared<IndexBuffer> index_buffer = create_shared<IndexBuffer>(indices, indices_size, GL_STATIC_DRAW);

    free(indices);

    return index_buffer;
}

void Renderer::begin(const Matrix& p_view_projection)
{
    glUseProgram(m_shader->get_renderer_id());
    m_shader->set_uniform_matrix("u_ViewProjection", p_view_projection);
}

void Renderer::draw(
    const Matrix& p_transform,
    const Vector2& p_pivot,
    const Shared<Texture>& p_texture,
    const Vector4& p_color,
    F32 p_tiling_factor,
    F32 p_sorting_layer)
{
    draw(p_transform, p_pivot, p_texture, k_quad_texture_coordinates, p_color, p_tiling_factor, p_sorting_layer);
}

void Renderer::draw(
    const Matrix& p_transform,
    const Vector2& p_pivot,
    const Shared<Texture>& p_texture,
    const Rectangle& p_rectangle,
    const Vector4& p_color,
    F32 p_tiling_factor,
    F32 p_sorting_layer)
{
    F32 x0 = Math::clamp01(p_rectangle.get_left()   / p_texture->get_width());
    F32 y0 = Math::clamp01(p_rectangle.get_bottom() / p_texture->get_height());
    F32 x1 = Math::clamp01(p_rectangle.get_right()  / p_texture->get_width());
    F32 y1 = Math::clamp01(p_rectangle.get_top()    / p_texture->get_height());

    Array<Vector2, 4> texture_coordinates = {
        Vector2(x0, y0),
        Vector2(x1, y0),
        Vector2(x1, y1),
        Vector2(x0, y1),
    };

    draw(p_transform, p_pivot, p_texture, texture_coordinates, p_color, p_tiling_factor, p_sorting_layer);
}

void Renderer::draw(
    const Matrix& p_transform,
    const Vector2& p_pivot,
    const Shared<Texture>& p_texture,
    const Array<Vector2, 4>& p_texture_coordinates,
    const Vector4& p_color,
    F32 p_tiling_factor,
    F32 p_sorting_layer)
{
    if (m_quad_counter >= k_max_quads || m_textures.size() >= m_graphics->get_max_texture_units()) {
        flush();
    }

    I32 texture_index = list_index_of<Shared<Texture>>(m_textures, p_texture);

    if (texture_index == -1) {
        texture_index = m_textures.size();
        m_textures.emplace_back(p_texture);
    }

    for (int i = 0; i < k_vertices_per_quad; i++) {
        m_vertices_iterator->position = p_transform * Vector4(k_quad_texture_coordinates[i] - p_pivot, 0, 1);
        m_vertices_iterator->color = p_color;
        m_vertices_iterator->texture_coordinates = p_texture_coordinates[i];
        m_vertices_iterator->texture_index = texture_index;
        m_vertices_iterator->tiling_factor = p_tiling_factor;
        m_vertices_iterator++;
    }

    m_quad_counter += 1;
}

void Renderer::flush()
{
    if (m_quad_counter == 0) {
        return;
    }

    glBindVertexArray(m_vertex_array->get_renderer_id());

    for (int i = 0; i < m_vertex_array->get_vertex_buffer()->get_layout().get_attributes().size(); i++) {
        glEnableVertexAttribArray(i);
    }

    m_vertex_array->get_vertex_buffer()->update_data(m_vertices, m_quad_counter * k_vertices_per_quad * sizeof(Vertex));

    for (int i = 0; i < m_textures.size(); i++) {
        glBindTextureUnit(i, m_textures[i]->get_renderer_id());
    }

    glDrawElements(GL_TRIANGLES, m_quad_counter * k_indices_per_quad, GL_UNSIGNED_INT, nullptr);

    m_stats.quads += m_quad_counter;
    m_stats.indices += m_quad_counter * k_indices_per_quad;
    m_stats.vertices += m_quad_counter * k_vertices_per_quad;
    m_stats.textures += m_textures.size();
    m_stats.draw_calls += 1;

    m_textures.clear();
    m_vertices_iterator = m_vertices;
    m_quad_counter = 0;
}

void Renderer::reset_stats()
{
    m_stats = RendererStats();
}

const RendererStats& Renderer::get_stats() const
{
    return m_stats;
}

void Renderer::clear() const
{
    glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::set_shader(const Shared<Shader>& p_shader)
{
    m_shader = p_shader;
}

void Renderer::reset_shader()
{
    m_shader = m_default_shader;
}

void Renderer::set_mask_texture(const Shared<Texture>& p_mask_texture)
{
    m_mask_texture = p_mask_texture;
}

void Renderer::reset_mask_texture()
{
    m_mask_texture = m_white_texture;
}

void Renderer::set_viewport(U32 p_width, U32 p_height) const
{
    glViewport(0, 0, p_width, p_height);
}

void Renderer::set_viewport(const Vector2& size) const
{
    glViewport(0, 0, size.x, size.y);
}
