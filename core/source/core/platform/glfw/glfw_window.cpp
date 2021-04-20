#include "glfw_window.hpp"

#include <glad/glad.h>
#include <iostream>

GLFWWindow::GLFWWindow(const char* p_title, I32 p_width, I32 p_height, bool p_fullscreen) :
    m_is_vsync_enabled(false),
    m_is_fullscreen(p_fullscreen),
    m_width(p_width),
    m_height(p_height)
{
    if (!glfwInit()) {
        std::cout << "Failed to initialize GLFW" << std::endl;
        exit(EXIT_FAILURE);
    }

    handle = glfwCreateWindow(m_width, m_height, p_title, m_is_fullscreen ? glfwGetPrimaryMonitor() : nullptr, nullptr);
    glfwMakeContextCurrent(handle);

    glfwSwapInterval(1);
    glfwSetWindowSizeCallback(handle, on_window_size_changed);
}

GLFWWindow::~GLFWWindow()
{
    glfwTerminate();
}

bool GLFWWindow::should_close() const
{
    return glfwWindowShouldClose(handle) == GLFW_TRUE;
}

void GLFWWindow::update() const
{
    glfwSwapBuffers(handle);
    glfwPollEvents();
}

void GLFWWindow::on_window_size_changed(GLFWWindowHandle* p_window, I32 p_width, I32 p_height)
{
}

Vector2 GLFWWindow::get_size() const
{
    int width, height;
    glfwGetWindowSize(handle, &width, &height);

    return Vector2(width, height);
}

void GLFWWindow::set_vsync_enabled(bool p_is_vsync_enabled)
{
    m_is_vsync_enabled = p_is_vsync_enabled;
    glfwSwapInterval(p_is_vsync_enabled ? 1 : 0);
}

bool GLFWWindow::is_vsync_enabled() const
{
    return m_is_vsync_enabled;
}

void GLFWWindow::set_fullscreen(bool p_is_fullscreen)
{
    m_is_fullscreen = p_is_fullscreen;

    if (!m_is_fullscreen) {
        glfwSetWindowMonitor(handle, nullptr, 100, 100, 1920, 1080, 0);
        return;
    }

    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);

    glfwSetWindowMonitor(handle, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
}

bool GLFWWindow::is_fullscreen() const
{
    return m_is_fullscreen;
}
