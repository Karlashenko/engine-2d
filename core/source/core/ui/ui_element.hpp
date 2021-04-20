#pragma once

#include "../entities/entity_registry.hpp"
#include "../entities/entity.hpp"
#include "../numerics/rectangle.hpp"

class UIElement : public std::enable_shared_from_this<UIElement>
{
public:
    String name;
    F32 x = 0;
    F32 y = 0;
    F32 width = 0;
    F32 height = 0;
    F32 relative_x = 0;
    F32 relative_y = 0;
    F32 relative_width = 0;
    F32 relative_height = 0;
    bool ignore_layout = false;
    Vector2 scale;
    Vector2 pivot;
    Vector2 anchor;

    UIElement(String p_name, const Shared<EntityRegistry>& p_registry);
    virtual ~UIElement();

    void update();

    [[nodiscard]] Shared<UIElement> get_parent() const;
    void change_parent(const Shared<UIElement>& p_parent);

    void add_child(const Shared<UIElement>& p_child);
    void remove_child(const Shared<UIElement>& p_child);

protected:
    Entity m_entity;
    Shared<EntityRegistry> m_registry;
    Rectangle m_rectangle;

    virtual void on_update()
    {
    }

private:
    Shared<UIElement> m_parent;
    List<Shared<UIElement>> m_children;
};
