#include "Editor.hpp"

#include "Widgets/ExplorerWidget.hpp"
#include "Widgets/LogWidget.hpp"
#include "Widgets/PropertiesWidget.hpp"
#include "Widgets/SceneWidget.hpp"
#include "Widgets/ViewportWidget.hpp"
#include "Widgets/ViewerWidget.hpp"
#include "Widgets/AssetWidget.hpp"
#include "Widgets/ToolboxWidget.hpp"


#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#include "imgui.h"


Editor::Editor(GLFWwindow *window)
{
    InitWidgets();
    InitImGui(window);
}

Editor::~Editor()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

//todo : init from config.ini
void Editor::InitWidgets()
{
    _widgets.emplace_back(std::make_unique<LogWidget>());
    _widgets.emplace_back(std::make_unique<ExplorerWidget>());
    _widgets.emplace_back(std::make_unique<PropertiesWidget>());
    _widgets.emplace_back(std::make_unique<SceneWidget>());
    _widgets.emplace_back(std::make_unique<ViewportWidget>());
    _widgets.emplace_back(std::make_unique<ViewerWidget>());
    _widgets.emplace_back(std::make_unique<AssetWidget>());
    _widgets.emplace_back(std::make_unique<ToolboxWidget>());
}

void Editor::InitImGui(GLFWwindow *window)
{
    // T_INIT ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();

    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
    // io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;     // Enable
    // Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
    // io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;      // Enable Multi-Viewport
    // Platform Windows
    // io.ConfigViewportsNoAutoMerge = true;
    // io.ConfigViewportsNoTaskBarIcon = true;

    // ImGui style
    ImGui::StyleColorsDark();
    // ImGui::StyleColorsClassic();

    ImGuiStyle &style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 460");
}

void Editor::Draw()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::DockSpaceOverViewport(ImGui::GetMainViewport(), ImGuiDockNodeFlags_PassthruCentralNode);

    for (const auto &widget : _widgets)
    {
        widget->Draw();
    }

    ImGui::Render();

    //int display_w, display_h;
    //glfwGetFramebufferSize(_window, &display_w, &display_h);
//     glViewport(0, 0, display_w, display_h);
//     glClearColor(1.f,0.f,0.f,0.f);
//     glClear(GL_COLOR_BUFFER_BIT);

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

//    const ImGuiIO &io = ImGui::GetIO();
//
//    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
//    {
//        GLFWwindow *backup_current_context = glfwGetCurrentContext();
//        ImGui::UpdatePlatformWindows();
//        ImGui::RenderPlatformWindowsDefault();
//        glfwMakeContextCurrent(backup_current_context);
//    }
}




