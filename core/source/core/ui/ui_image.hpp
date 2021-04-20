#pragma once

#include "ui_element.hpp"
#include "../graphics/texture.hpp"

class UIImage : public UIElement
{
public:
    UIImage(const String& p_name, const Shared<EntityRegistry>& p_registry, const Shared<Texture>& p_texture, const Vector4& p_color);

protected:
    void on_update() override;

private:
    Vector4 m_color;
    Shared<Texture> m_texture;
};
