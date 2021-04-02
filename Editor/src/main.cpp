//
// Created by g.nisi on 03/02/2021.
//

#include "GLFW/glfw3.h"

#include "Input/InputManager.hpp"
#include "Input/PlatformInputGLFW.hpp"
#include "Editor.hpp"
#include "Engine.hpp"
#include "Scene/Core/World.hpp"
#include "Scene/Component/Transform.hpp"
#include "Renderer/RendererInterface.hpp"


int main()
{
    Engine engine;
    Editor editor{engine};
    World &world = World::Instance();

    EngineSettings settings{
            true,
            "QuackEditor",
            {1280, 720},
            WINDOW_MODE::WINDOWED,
            0
    };
    editor.Init(settings);
    GLFWwindow * window = editor.GetWindow();
    Input::PlatformInputGLFW input{window};
    engine.Init(input);

    while (!glfwWindowShouldClose(window))
    {
        //editor.Draw();
        //engine.Update();

        if (glfwGetKey(window, GLFW_KEY_ESCAPE))
        {
            glfwSetWindowShouldClose(window, 1);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

//{
//if (ImGui::BeginMainMenuBar())
//{
//if (ImGui::BeginMenu("Files"))
//{
//if (ImGui::MenuItem("New scene"))
//{
//}
//if (ImGui::MenuItem("Save scene"))
//{
//}
//
//ImGui::Separator();
//if (ImGui::MenuItem("Import object"))
//{
//}
//
//ImGui::EndMenu();
//}
//
//if (ImGui::BeginMenu("Edit"))
//{
//if (ImGui::MenuItem("Undo", "CTRL+Z"))
//{
//}
//if (ImGui::MenuItem("Redo", "CTRL+Y"))
//{
//} // Disabled item
//ImGui::Separator();
//if (ImGui::MenuItem("Cut", "CTRL+X"))
//{
//}
//if (ImGui::MenuItem("Copy", "CTRL+C"))
//{
//}
//if (ImGui::MenuItem("Paste", "CTRL+V"))
//{
//}
//ImGui::EndMenu();
//}
//
//if (ImGui::BeginMenu("Windows"))
//{
//if (ImGui::MenuItem("Viewport", NULL, window_viewport))
//{
//window_viewport = !window_viewport;
//}
//if (ImGui::MenuItem("Logs", NULL, window_log))
//{
//window_log = !window_log;
//}
//ImGui::EndMenu();
//}
//}
//ImGui::EndMainMenuBar();
//}
