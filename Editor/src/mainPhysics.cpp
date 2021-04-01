#include "GLFW/glfw3.h"
#include "Maths/Quaternion.hpp"

#include "Renderer/RendererPlatform.hpp"
#include "Renderer/Shader.hpp"
#include "Renderer/Framebuffer.hpp"
#include "Renderer/Texture.hpp"
#include "Renderer/Vertex.hpp"
#include "Renderer/Mesh.hpp"
#include "Scene/Component/Light.hpp"
#include "Resources/ResourcesManager.hpp"

#include "Input/PlatformInputGLFW.hpp"
#include "Input/InputManager.hpp"

#include "Audio/SoundManager.hpp"


#include "Scene/Component/Transform.hpp"
#include "Scene/System/TestSystem.hpp"


#include "Scene/Core/World.hpp"

using namespace Renderer;

int main()
{
    GLFWwindow* window    {nullptr};
    unsigned int width = 1280, height = 720;
    /* Initialize the library */
    if (!glfwInit())
        return -1;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(width, height, "RendererPlatform", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    RendererPlatform::LoadGL();

    {
        World &ecs=World::Instance();
        ecs.Init();

        Entity id = ecs.CreateEntity("Test");
        Transform t = {Maths::Vector3f::One(), Maths::Vector3f::One(), Maths::Quaternion{}};
        ecs.AddComponent(id, t);

        Entity idRenderTest = ecs.CreateEntity("Test");
        Transform t2 = {Maths::Vector3f{0,0,10}, Maths::Vector3f::One(), Maths::Quaternion{}};
        Component::Model md = ecs.GetResourcesManager().LoadModel("../../../Dragon_Baked_Actions_fbx_7.4_binary.fbx");

        Material material;

        material.ambient = {1, 1, 1};
        material.diffuse = {1, 1, 1};
        material.specular = {1, 1, 1};
        material.checkLight = true;
        md.AddMaterial(material);
        ecs.AddComponent(idRenderTest, t2);
        ecs.AddComponent(idRenderTest, md);

        Entity lightID = ecs.CreateEntity("Light");
        Entity lightID2 = ecs.CreateEntity("Light");
        Entity lightID3 = ecs.CreateEntity("Light");

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

        ecs.AddComponent(lightID, light);
        ecs.AddComponent(lightID, tl1);

        light.type = Component::Light_Type::L_POINT;
        light.diffuse = {0,1,0};
        light.specular = {0, 1, 0};
        Transform tl2 = {Maths::Vector3f::One() * -100, Maths::Vector3f::One(), Maths::Quaternion{}};

        ecs.AddComponent(lightID2, light);
        ecs.AddComponent(lightID2, tl2);

        light.type = Component::Light_Type::L_DIRECTIONAL;
        light.diffuse = {0,0,1};
        light.specular = {0, 0, 1};
        Transform tl3 = {Maths::Vector3f::Zero(), Maths::Vector3f::One(), Maths::Quaternion{3.1415 / 2, 1, 0, 0}};


        ecs.AddComponent(lightID3, light);
        ecs.AddComponent(lightID3, tl3);

        {
            Entity CameraEntity = ecs.CreateEntity("Camera");

            Component::Camera camera(1280,
                                     720,
                                     1000, -1, 20 * 3.1415/180);

            Transform cameraTrs;
            ecs.AddComponent(CameraEntity, camera);
            ecs.AddComponent(CameraEntity, cameraTrs);

            camera.GetFramebuffer().Bind();
        }

        float count = 0;

        RendererPlatform::EnableDepthBuffer(true);

        //glfwSetWindowShouldClose(window, 1);

        while (!glfwWindowShouldClose(window))
        {

            count += 0.0001f;

            // framebuffer
            {
                if (glfwGetKey(window, GLFW_KEY_ESCAPE))
                {
                    glfwSetWindowShouldClose(window, 1);
                }
                ecs.GetRendererManager().Update();
            }

            glfwSwapBuffers(window);
            glfwPollEvents();
        }
    }
    glfwTerminate();
    return 0;
}