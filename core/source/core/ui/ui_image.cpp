#include "ui_image.hpp"
#include "../game/components/sprite_component.hpp"

UIImage::UIImage(const String& p_name, const Shared<EntityRegistry>& p_registry, const Shared<Texture>& p_texture, const Vector4& p_color)
    : m_texture(p_texture), m_color(p_color), UIElement(p_name, p_registry)
{
    m_registry->emplace<SpriteComponent>(m_entity, m_texture);
}

void UIImage::on_update()
{
    auto& sprite = m_registry->get<SpriteComponent>(m_entity);
    sprite.size = m_rectangle.get_size();
    sprite.color = m_color;
    sprite.pivot = pivot;
}
