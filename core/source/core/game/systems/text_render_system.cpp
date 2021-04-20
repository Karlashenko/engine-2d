#include "text_render_system.hpp"

#include "../components/text_component.hpp"
#include "../components/transform_component.hpp"
#include "../../string/codepoint.hpp"

TextRenderSystem::TextRenderSystem(const Shared<Renderer>& p_renderer, const Shared<EntityRegistry>& p_registry)
    : m_renderer(p_renderer), m_registry(p_registry)
{
}

void TextRenderSystem::update(F32 p_delta_time) const
{
    auto view = m_registry->view<TransformComponent, TextComponent>();

    for (auto[entity, transform, text] : view.each()) {
        Vector2 stride = Vector2();

        for (auto glyph : text.get_glyphs()) {
            if (glyph.codepoint == Codepoint::c_space) {
                stride.x += text.space_width;
                continue;
            }

            if (glyph.codepoint == Codepoint::c_new_line) {
                stride.y += text.line_height;
                stride.x = 0;
                continue;
            }

            Matrix matrix = transform.get_matrix();
            matrix = glm::translate(matrix, Vector3(stride.x, -(glyph.offset_y2 + stride.y), 0));
            matrix = glm::scale(matrix, Vector3(glyph.get_size(), 0));

            m_renderer->draw(matrix, Vector2(0), text.get_font()->get_texture(), glyph.get_rectangle(), Vector4(1), 1, 0);

            stride.x += glyph.advance_x;
        }
    }
}
