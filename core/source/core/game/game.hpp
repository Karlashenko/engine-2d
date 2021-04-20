#pragma once

#include "../ui/ui_root.hpp"
#include "../fonts/font.hpp"
#include "../editor/camera_editor.hpp"
#include "../graphics/frame_buffer.hpp"
#include "../graphics/camera.hpp"
#include "../graphics/shader.hpp"
#include "../graphics/texture.hpp"
#include "../graphics/vertex_array.hpp"
#include "../graphics/renderer.hpp"
#include "../platform/window.hpp"
#include "../io/file_system.hpp"
#include "../game/systems/text_render_system.hpp"
#include "../game/systems/sprite_render_system.hpp"

class Game
{
public:
    Game() = delete;
    Game(const Game& p_game) = delete;
    explicit Game(Shared<Window> p_window);

    void update();

private:
    Shared<Window> m_window;
    Shared<FileSystem> m_file_system;
    Shared<Camera> m_game_camera;
    Shared<Camera> m_ui_camera;
    Shared<Renderer> m_renderer;
    Shared<Graphics> m_graphics;
    Shared<SpriteRenderSystem> m_sprite_render_system;
    Shared<TextRenderSystem> m_text_render_system;
    Shared<EntityRegistry> m_registry;
    Shared<Font> m_font;

    Shared<UIRoot> m_ui_root;

    List<Shared<Texture>> m_textures;
};
