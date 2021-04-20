#include "sprite_render_system.hpp"
#include "../components/sprite_component.hpp"
#include "../components/transform_component.hpp"

SpriteRenderSystem::SpriteRenderSystem(const Shared<Renderer>& p_renderer, const Shared<EntityRegistry>& p_registry)
    : m_renderer(p_renderer), m_registry(p_registry)
{
}

void SpriteRenderSystem::update(F32 p_delta_time) const
{
    const auto& view = m_registry->view<TransformComponent, SpriteComponent>();

    for (auto entity : view) {
        auto& transform = view.template get<TransformComponent>(entity);
        const auto& sprite = view.template get<SpriteComponent>(entity);

        m_renderer->draw(glm::scale(transform.get_matrix(), Vector3(sprite.size, 0)), sprite.pivot, sprite.texture, sprite.color, sprite.tiling_factor, 0.0F);
    }
}
