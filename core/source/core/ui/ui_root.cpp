#include "ui_root.hpp"

UIRoot::UIRoot(const String& p_name, const Shared<EntityRegistry>& p_registry, const Shared<Window>& p_window)
    : m_window(p_window), UIElement(p_name, p_registry)
{
}

void UIRoot::on_update()
{
    m_rectangle.x = 0;
    m_rectangle.y = 0;
    m_rectangle.set_size(m_window->get_size());
}
