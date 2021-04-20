#include "ui_element.hpp"

#include <utility>
#include "../game/components/transform_component.hpp"
#include "../game/components/ui_element_component.hpp"

UIElement::UIElement(String p_name, const Shared<EntityRegistry>& p_registry)
    : name(std::move(p_name)), m_registry(p_registry), m_rectangle(Rectangle()), scale(Vector2()), pivot(Vector2()), anchor(Vector2())
{
    m_entity = m_registry->create();
    m_registry->emplace<TransformComponent>(m_entity);
    m_registry->emplace<UIElementComponent>(m_entity);
}

UIElement::~UIElement()
{
    m_registry->destroy(m_entity);
}

void UIElement::update()
{
    m_rectangle.x = x;
    m_rectangle.y = y;
    m_rectangle.width = width;
    m_rectangle.height = height;

    if (m_parent.get()) {
        m_rectangle.x += m_parent->m_rectangle.x + m_parent->m_rectangle.width * relative_x;
        m_rectangle.y += m_parent->m_rectangle.y + m_parent->m_rectangle.height * relative_y;
        m_rectangle.width += m_parent->m_rectangle.width * relative_width;
        m_rectangle.height += m_parent->m_rectangle.height * relative_height;
    }

    auto& transform = m_registry->get<TransformComponent>(m_entity);
    transform.set_position(m_rectangle.get_position());

    on_update();

    for (const auto& child : m_children) {
        child->update();
    }
}

Shared<UIElement> UIElement::get_parent() const
{
    return m_parent;
}

void UIElement::change_parent(const Shared<UIElement>& p_parent)
{
    if (m_parent.get() != nullptr) {
        m_parent->remove_child(shared_from_this());
    }

    m_parent = p_parent;

    if (m_parent.get()) {
        m_parent->add_child(shared_from_this());
    }
}

void UIElement::add_child(const Shared<UIElement>& p_child)
{
    if (p_child->get_parent().get() != this) {
        p_child->change_parent(shared_from_this());
    }

    m_children.emplace_back(p_child);
}

void UIElement::remove_child(const Shared<UIElement>& p_child)
{
    list_remove(m_children, p_child);
}
