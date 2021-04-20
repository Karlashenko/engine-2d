#include "game.hpp"
#include "components/text_component.hpp"
#include "components/sprite_component.hpp"
#include "components/transform_component.hpp"
#include "../algorithm/random.hpp"
#include "../fonts/font_builder.hpp"
#include "../ui/ui_image.hpp"

#include <utility>

Game::Game(Shared<Window> p_window) : m_window(std::move(p_window))
{
    m_file_system = create_shared<FileSystem>(R"(D:\Projects\C++\Redshift\game\content)");

    m_game_camera = create_shared<Camera>(m_window->get_size(), Vector2(0.5));
    m_game_camera->set_zoom(0.25);
    m_game_camera->set_position(Vector2(0));

    m_ui_camera = create_shared<Camera>(m_window->get_size(), Vector2(0));
    m_ui_camera->set_zoom(1);
    m_ui_camera->set_position(Vector2(0));

    m_graphics = create_shared<Graphics>(m_file_system);
    m_renderer = create_shared<Renderer>(m_graphics);

    m_textures = List<Shared<Texture>>();
    m_textures.emplace_back(create_shared<Texture>(1, 1));
    m_textures.emplace_back(m_graphics->create_texture("textures/2.png"));
    m_textures.emplace_back(m_graphics->create_texture("textures/3.png"));
    m_textures.emplace_back(m_graphics->create_texture("textures/4.png"));

    FontBuilder font_builder = FontBuilder(2048, 2048, 48);
    font_builder.add_glyphs(m_file_system->read_bytes("fonts/Roboto-Regular.ttf"), {CharacterRange::create_basic_latin()});
    m_font = font_builder.build();

    m_registry = create_shared<EntityRegistry>();
    m_sprite_render_system = create_shared<SpriteRenderSystem>(m_renderer, m_registry);
    m_text_render_system = create_shared<TextRenderSystem>(m_renderer, m_registry);

    auto random = Random(42);
    for (int i = 0; i < 0; i++) {
        auto entity = m_registry->create();

        Vector2 position = Vector2(5 * random.range(0.0F, 1.0F), 5 * random.range(0.0F, 1.0F));

        I32 random_texture_index = random.range(1, 4);
        m_registry->emplace<TransformComponent>(entity, position, m_textures[random_texture_index]->get_size(), 0);
        m_registry->emplace<SpriteComponent>(entity, m_textures[random_texture_index]);
    }

    auto entity = m_registry->create();
    m_registry->emplace<TransformComponent>(entity, Vector2(0, 0), Vector2(2), 0);
    m_registry->emplace<TextComponent>(entity, m_font, m_file_system->read_string("sample.txt"));

    m_ui_root = create_shared<UIRoot>("root", m_registry, m_window);

    const Shared<UIImage>& ui_top = create_shared<UIImage>("top", m_registry, m_textures[0], Vector4(0.8));
    ui_top->pivot = Vector2(0, 1);
    ui_top->relative_y = 1;
    ui_top->relative_width = 1;
    ui_top->height = 100;

    const Shared<UIImage>& ui_left = create_shared<UIImage>("left", m_registry, m_textures[0], Vector4(0.8, 1, 0.8, 0.8));
    ui_left->pivot = Vector2(0, 0);
    ui_left->relative_width = 0.33;
    ui_left->relative_height = 1;
    ui_left->y = -110;

    const Shared<UIImage>& ui_right = create_shared<UIImage>("right", m_registry, m_textures[0], Vector4(0.8, 0.8, 1, 0.8));
    ui_right->pivot = Vector2(1, 0);
    ui_right->relative_x = 1;
    ui_right->relative_width = 0.33;
    ui_right->relative_height = 1;
    ui_right->y = -110;

    const Shared<UIImage>& ui_center = create_shared<UIImage>("center", m_registry, m_textures[0], Vector4(0.8, 1, 1, 0.8));
    ui_center->pivot = Vector2(0.5, 0);
    ui_center->relative_x = 0.5;
    ui_center->relative_width = 0.33;
    ui_center->relative_height = 1;
    ui_center->y = -110;

    for (int i = 0; i < 5; i++) {
        const Shared<UIImage>& center_child = create_shared<UIImage>("center_child_" + std::to_string(i), m_registry, m_textures[0], Vector4(0.8, 1, 1, 0.8));
        center_child->pivot = Vector2(0.5, 0);
        center_child->relative_x = 0;
        center_child->relative_y = 0.2 * i;
        center_child->relative_width = 1;
        center_child->relative_height = 0.2;
        center_child->width = -20;
        center_child->height = -10;
        ui_center->add_child(center_child);
    }

    m_ui_root->add_child(ui_left);
    m_ui_root->add_child(ui_right);
    m_ui_root->add_child(ui_top);
    m_ui_root->add_child(ui_center);
    m_ui_root->update();
}

void Game::update()
{
    m_renderer->set_viewport(m_window->get_size());
    m_renderer->clear();
    m_renderer->reset_stats();

    m_renderer->begin(m_game_camera->get_view_projection());
    m_sprite_render_system->update(0);
    m_text_render_system->update(0);
    m_renderer->draw(glm::scale(Matrix(1), Vector3(50)), Vector2(0.5f), m_textures[0], Vector4(1, 0, 0, 1), 1, 0);
    m_renderer->flush();

    m_renderer->begin(m_ui_camera->get_view_projection());
    m_sprite_render_system->update(0);
    m_renderer->flush();

    // printf("Quads: %d\n", m_renderer->get_stats().quads);
    // printf("Draws: %d\n", m_renderer->get_stats().draw_calls);
}
