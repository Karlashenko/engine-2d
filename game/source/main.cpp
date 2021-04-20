#include <core/game/game.hpp>
#include <core/platform/glfw/glfw_window.hpp>
#include <steam/steam_api.h>

int main(int p_argc, char** p_argv)
{
    SteamAPI_Init();

    Shared<GLFWWindow> window = create_shared<GLFWWindow>("Redshift", 1920, 1080, false);
    window->set_vsync_enabled(false);

    Shared<Game> game = create_shared<Game>(window);

    while (!window->should_close()) {
        game->update();
        window->update();
    }

    return 0;
}
