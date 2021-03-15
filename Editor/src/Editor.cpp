//
// Created by g.nisi on 2/26/21.
//

#include <cstdio>

#include "Editor.hpp"

#include "Widgets/ExplorerWidget.hpp"
#include "Widgets/LogWidget.hpp"
#include "Widgets/PropertiesWidget.hpp"
#include "Widgets/SceneWidget.hpp"
#include "Widgets/ViewportWidget.hpp"

#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "imgui.h"

//todo : init from config.ini
void Editor::initWidgets()
{
    _widgets.emplace_back(new ExplorerWidget());
    _widgets.emplace_back(new LogWidget());
    _widgets.emplace_back(new PropertiesWidget());
    _widgets.emplace_back(new SceneWidget());
    _widgets.emplace_back(new ViewportWidget());
}

void Editor::initImGUI()
{
    // Init ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void) io;
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

void Editor::update()
{
    for (const auto &widget : _widgets)
    {
        widget->update();
    }
}

void Editor::draw()
{
    for (const auto &widget : _widgets)
    {
        widget->draw();
    }
}
