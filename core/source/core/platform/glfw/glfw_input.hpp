#pragma once

#include <GLFW/glfw3.h>
#include "../input.hpp"

class GLFWInput final : public Input
{
public:
    using GLFWWindowHandle = GLFWwindow;

    ~GLFWInput() override = default;
};
