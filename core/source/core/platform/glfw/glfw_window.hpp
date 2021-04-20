#pragma once

#include <GLFW/glfw3.h>
#include "../window.hpp"

class GLFWWindow final : public Window
{
public:
    using GLFWWindowHandle = GLFWwindow;

    GLFWWindowHandle* handle;

    GLFWWindow() = delete;
    GLFWWindow(const char* p_title, I32 p_width, I32 p_height, bool p_fullscreen);

    ~GLFWWindow() override;

    void update() const;

    [[nodiscard]] Vector2 get_size() const override;
    [[nodiscard]] bool is_vsync_enabled() const override;
    [[nodiscard]] bool is_fullscreen() const override;
    void set_vsync_enabled(bool p_is_vsync_enabled) override;
    void set_fullscreen(bool p_is_fullscreen) override;

    [[nodiscard]] bool should_close() const;

private:
    bool m_is_fullscreen;
    bool m_is_vsync_enabled;
    I32 m_width;
    I32 m_height;

    static void on_window_size_changed(GLFWWindowHandle* p_window, I32 p_width, I32 p_height);
};
