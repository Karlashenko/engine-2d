#pragma once

#include "../../graphics/renderer.hpp"
#include "../../entities/entity_registry.hpp"

class TextRenderSystem
{
public:
    TextRenderSystem(const Shared<Renderer>& p_renderer, const Shared<EntityRegistry>& p_registry);

    void update(F32 p_delta_time) const;

private:
    Shared<Renderer> m_renderer;
    Shared<EntityRegistry> m_registry;
};
