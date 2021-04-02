//
// Created by g.nisi on 03/02/2021.
//

#include "GLFW/glfw3.h"

#include "Input/InputManager.hpp"
#include "Input/PlatformInputGLFW.hpp"
#include "Editor.hpp"
#include "Engine.hpp"
#include "Renderer/Material.hpp"
#include "Scene/Core/World.hpp"
#include "Scene/Component/Transform.hpp"
#include "Renderer/RendererInterface.hpp"

using namespace Renderer;
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


    Entity id = world.CreateEntity("Test");
    Transform t = {Maths::Vector3f::One(), Maths::Vector3f::One(), Maths::Quaternion{}};
    world.AddComponent(id, t);

    Entity idRenderTest = world.CreateEntity("Test");
    Transform t2 = {Maths::Vector3f{0,0,10}, Maths::Vector3f::One(), Maths::Quaternion{}};
    Component::Model md = world.GetResourcesManager().LoadModel("../../../eyeball.fbx");

    Material material;

    material.ambient = {1, 1, 1};
    material.diffuse = {1, 1, 1};
    material.specular = {1, 1, 1};
    material.checkLight = true;
    md.AddMaterial(material);
    world.AddComponent(idRenderTest, t2);
    world.AddComponent(idRenderTest, md);

    Entity lightID = world.CreateEntity("Light");
    Entity lightID2 = world.CreateEntity("Light");
    Entity lightID3 = world.CreateEntity("Light");

    Component::Light light;


    light.type = Component::Light_Type::L_SPOT;
    light.ambient = {0.0f, 0.1f, 0.0f};
    light.diffuse = {1,0,0};
    light.specular = {1, 0, 0};
    light.constant = 1.0f;
    light.linear = 0.0014f;
    light.quadratic = 0.000007f;

    light.outerSpotAngle = 10.5;
    light.spotAngle = 8.5;


    Transform tl1 = {Maths::Vector3f::One(), Maths::Vector3f::One(), Maths::Quaternion{}};

    world.AddComponent(lightID, light);
    world.AddComponent(lightID, tl1);

    light.type = Component::Light_Type::L_POINT;
    light.diffuse = {0,1,0};
    light.specular = {0, 1, 0};
    Transform tl2 = {Maths::Vector3f::One() * -100, Maths::Vector3f::One(), Maths::Quaternion{}};

    world.AddComponent(lightID2, light);
    world.AddComponent(lightID2, tl2);

    light.type = Component::Light_Type::L_DIRECTIONAL;
    light.diffuse = {0,0,1};
    light.specular = {0, 0, 1};
    Transform tl3 = {Maths::Vector3f::Zero(), Maths::Vector3f::One(), Maths::Quaternion{3.1415 / 2, 1, 0, 0}};


    world.AddComponent(lightID3, light);
    world.AddComponent(lightID3, tl3);

    while (!glfwWindowShouldClose(window))
    {
        editor.Draw();

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
