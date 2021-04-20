#include <core/platform/glfw/glfw_window.hpp>
#include <core/graphics/renderer.hpp>
#include <core/game/game.hpp>

int main(int p_argc, char** p_argv)
{
    Shared<GLFWWindow> window = create_shared<GLFWWindow>("Redshift", 1920, 1080, false);
    Shared<Game> game = create_shared<Game>(window);

    while (!window->should_close()) {
        game->update();
        window->update();
    }

    return 0;
}
