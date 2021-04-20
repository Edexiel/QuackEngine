//
// Created by g.nisi on 2/26/21.
//

#include <cstdio>

#include "Editor.hpp"
#include "Engine.hpp"

#include "Renderer/RendererPlatform.hpp"

#include "Widgets/ExplorerWidget.hpp"
#include "Widgets/LogWidget.hpp"
#include "Widgets/PropertiesWidget.hpp"
#include "Widgets/SceneWidget.hpp"
#include "Widgets/ViewportWidget.hpp"
#include "Widgets/ViewerWidget.hpp"
#include "Widgets/AssetWidget.hpp"


#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "imgui.h"
#include "Debug/Assertion.hpp"

Editor::Editor(Engine &engine) : _engine{engine}
{}


Editor::~Editor()
{
    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(_window);
    glfwTerminate();
}

void Editor::Init(const EngineSettings &settings)
{
    InitGlfw(settings);
    InitWidgets();
    InitImGui();
}

void Editor::InitGlfw(const EngineSettings &settings)
{
    Assert_Fatal_Error(!glfwInit(), "GLFW was not correctly initialized, aborting");

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, settings.debug);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWmonitor *monitor;

    /**
     * Screen mode selection, can be
     * WINDOWED
     * FULLSCREEN
     * WINDOWED FULLSCREEN
     *
     * If there are multiple monitors, we can select it and execute the screen mode in that screen
     */
    switch (settings.mode)
    {
        case WINDOW_MODE::WINDOWED:
        {
            monitor = nullptr;
            break;
        }

        case WINDOW_MODE::FULLSCREEN:
        {
            int count;
            GLFWmonitor **monitors = glfwGetMonitors(&count);

            if (settings.monitor < count)
            {
                monitor = monitors[settings.monitor];
                break;
            }

            monitor = glfwGetPrimaryMonitor();
            break;
        }

        case WINDOW_MODE::WINDOWED_FULLSCREEN:
        {
            //todo: stuff
            //flemme, je verrais plus tard //... Mais enfin Guigui! ça dépasse l'entendement!
            monitor = nullptr;
            break;
        }
    }

    _window = glfwCreateWindow(settings.windowSize[0],
                               settings.windowSize[1],
                               settings.windowTitle.c_str(), monitor, nullptr);
    if (!_window)
    {
        glfwTerminate();
        Assert_Fatal_Error(true, "GLFW's window was not correctly initialized, aborting");
    }

    glfwMakeContextCurrent(_window);

    int version = Renderer::RendererPlatform::LoadGl();

    if (version == 0)
    {
        glfwTerminate();
        Assert_Fatal_Error(true, "Failed to initialize OpenGL context");
    }

}

//todo : init from config.ini
void Editor::InitWidgets()
{
    _widgets.emplace_back(std::make_unique<ExplorerWidget>());
    _widgets.emplace_back(std::make_unique<LogWidget>());
    _widgets.emplace_back(std::make_unique<PropertiesWidget>());
    _widgets.emplace_back(std::make_unique<SceneWidget>());
    _widgets.emplace_back(std::make_unique<ViewportWidget>());
    _widgets.emplace_back(std::make_unique<ViewerWidget>());
    _widgets.emplace_back(std::make_unique<AssetWidget>());
}

void Editor::InitImGui()
{
    // Init ImGui
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

    ImGui_ImplGlfw_InitForOpenGL(_window, true);
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
    // glViewport(0, 0, display_w, display_h);
    // glClearColor(1.f,0.f,0.f,0.f);
    // glClear(GL_COLOR_BUFFER_BIT);

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    const ImGuiIO &io = ImGui::GetIO();

    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        GLFWwindow *backup_current_context = glfwGetCurrentContext();
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        glfwMakeContextCurrent(backup_current_context);
    }
}

GLFWwindow *Editor::GetWindow() const
{
    return _window;
}





