#pragma once

#include <GLFW/glfw3.h>

class CameraEditor
{
public:
    explicit CameraEditor(GLFWwindow* p_window);

    virtual ~CameraEditor();

    void update(Matrix& p_transform_0, Matrix& p_transform_1, Matrix& p_transform_2) const;
};
