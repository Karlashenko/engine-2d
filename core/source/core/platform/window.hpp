#pragma once

class Window
{
public:
    virtual ~Window() = default;

    [[nodiscard]] virtual Vector2 get_size() const = 0;
    [[nodiscard]] virtual bool is_vsync_enabled() const = 0;
    [[nodiscard]] virtual bool is_fullscreen() const = 0;

    virtual void set_vsync_enabled(bool p_is_vsync_enabled) = 0;
    virtual void set_fullscreen(bool p_is_fullscreen) = 0;
};
