#pragma once

#include "ui_element.hpp"
#include "../platform/window.hpp"

class UIRoot final : public UIElement
{
public:
    UIRoot(const String& p_name, const Shared<EntityRegistry>& p_registry, const Shared<Window>& p_window);

protected:
    void on_update() override;

private:
    Shared<Window> m_window;
};
