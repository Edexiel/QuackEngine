//
// Created by g.nisi on 2/26/21.
//

#include <cstdio>

#include "Editor.hpp"

#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "imgui.h"

Editor::Editor()
{
}

Editor::~Editor()
{

}

int Editor::Init()
{
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    //todo: get size from config ini
    window = glfwCreateWindow(1280, 720, "QuackEngine", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    //todo: use interface
    int version = gladLoadGL(glfwGetProcAddress);

    if (version == 0)
    {
        printf("Failed to initialize OpenGL context");
        glfwTerminate();
        return -1;
    }

    printf("GL_VENDOR = %s\n", glGetString(GL_VENDOR));
    printf("GL_RENDERER = %s\n", glGetString(GL_RENDERER));
    printf("GL_VERSION = %s\n", glGetString(GL_VERSION));

}

void Editor::InitImGUI()
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
