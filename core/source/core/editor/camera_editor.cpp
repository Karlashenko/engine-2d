#include "camera_editor.hpp"

#include "../../../libraries/imgui/imgui.h"
#include "../../../libraries/imgui/imgui_impl_opengl3.h"
#include "../../../libraries/imgui/imgui_impl_glfw.h"

CameraEditor::CameraEditor(GLFWwindow* p_window)
{
    ImGui::CreateContext();

    ImGui_ImplOpenGL3_Init();
    ImGui_ImplGlfw_InitForOpenGL(p_window, true);

    ImGui::StyleColorsDark();
}

CameraEditor::~CameraEditor()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void CameraEditor::update(Matrix& p_transform_0, Matrix& p_transform_1, Matrix& p_transform_2) const
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();

    ImGui::NewFrame();
    ImGui::Begin("Properties");

    ImGui::SliderFloat2("Camera", &p_transform_0[3].x, -1920.0F, 1920.0F);
    ImGui::SliderFloat2("Transform 1", &p_transform_1[3].x, -1920.0F, 1920.0F);
    ImGui::SliderFloat2("Transform 2", &p_transform_2[3].x, -1920.0F, 1920.0F);

    ImGui::End();
    ImGui::Render();

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
