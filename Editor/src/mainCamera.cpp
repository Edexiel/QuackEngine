#include "GLFW/glfw3.h"

#include "Renderer/RendererPlatform.hpp"
#include "Renderer/Shader.hpp"
#include "Renderer/Framebuffer.hpp"
#include "Renderer/Texture.hpp"
#include "Renderer/Vertex.hpp"
#include "Renderer/Mesh.hpp"
#include "Renderer/Light.hpp"

#include "Resources/ResourcesManager.hpp"

#include "Scene/Camera.hpp"
#include "Input/InputManager.hpp"
#include "Input/PlatformInputGLFW.hpp"

#include <cmath>

using namespace Renderer;

int main()
{
  GLFWwindow* window;
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

  {

    // loadGL
    RendererPlatform::LoadGL();

    Resources::ResourcesManager rm;

    // shader

    ShaderConstructData shd = {1,1,0, 0, 1, 0,0};

    //Shader shader = rm.LoadShader("../../Game/Asset/Shader/vertex.vs", "../../Game/Asset/Shader/fragment.fs");

    Shader shader = Shader::LoadShader(shd);

    //Shader shader(Renderer::RendererPlatform::CreateShader(
    //    vertexShader, fragmentShader));
    RendererPlatform::UseShader(shader.ID);

    RendererPlatform::EnableDepthBuffer(true);

    //InputManager
    Input::PlatformInputGLFW platformInputGLFW(window);
    Input::InputManager inputManager (platformInputGLFW);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    //Camera
    Scene::Camera cam(width, height, 1000, -1, 45.f * 3.14f/180.f);
    cam.SetPosition({0,0,3});
    cam.SetRotation(Maths::Quaternion({0,1,0}, 3.14f/2.f));
    cam.SetRotationSpeed(0.1f);
    cam.SetTranslationSpeed(0.01f);
    cam.CreateView();

    inputManager.BindEvent("CameraMoveForward", Input::Key::KEY_W, Input::Action::PRESS);
    inputManager.BindEvent("CameraMoveBackward", Input::Key::KEY_S, Input::Action::PRESS);
    inputManager.BindEvent("CameraMoveRight", Input::Key::KEY_D, Input::Action::PRESS);
    inputManager.BindEvent("CameraMoveLeft", Input::Key::KEY_A, Input::Action::PRESS);

    inputManager.BindEvent("StopCameraMoveForward", Input::Key::KEY_W, Input::Action::RELEASE);
    inputManager.BindEvent("StopCameraMoveBackward", Input::Key::KEY_S, Input::Action::RELEASE);
    inputManager.BindEvent("StopCameraMoveRight", Input::Key::KEY_D, Input::Action::RELEASE);
    inputManager.BindEvent("StopCameraMoveLeft", Input::Key::KEY_A, Input::Action::RELEASE);

    inputManager.RegisterEvent("CameraMoveForward",&cam, &Scene::Camera::MoveForward);
    inputManager.RegisterEvent("CameraMoveBackward",&cam, &Scene::Camera::MoveBackward);
    inputManager.RegisterEvent("CameraMoveRight",&cam, &Scene::Camera::MoveRight);
    inputManager.RegisterEvent("CameraMoveLeft",&cam, &Scene::Camera::MoveLeft);

    inputManager.RegisterEvent("StopCameraMoveForward",&cam, &Scene::Camera::StopMoveForward);
    inputManager.RegisterEvent("StopCameraMoveBackward",&cam, &Scene::Camera::StopMoveBackward);
    inputManager.RegisterEvent("StopCameraMoveRight",&cam, &Scene::Camera::StopMoveRight);
    inputManager.RegisterEvent("StopCameraMoveLeft",&cam, &Scene::Camera::StopMoveLeft);

    shader.SetMatrix4("projection", cam.GetProjection());
    shader.SetMatrix4("view", cam.GetView());


    Renderer::Mesh cube = RendererPlatform::CreateCube();



//    Texture
    Texture texture = rm.LoadTexture("../../../Eye_D.jpg");

    Renderer::Light light;

    light.model = Maths::Matrix4::Translate({0,0, 0});
    light.ambient = {0.0f, 0.1f, 0.0f};
    light.diffuse = {0.7f, 0.7f, 0.7f};
    light.specular = {1.0f, 1.0f, 1.0f};
    light.constant = 1.0f;
    light.linear = 0.0014f;
    light.quadratic = 0.000007f;

    light.outerSpotAngle = 10.5;
    light.spotAngle = 8.5;


    RendererPlatform::EnableDepthBuffer(true);

    float count = 0;

    while (!glfwWindowShouldClose(window))
    {
      inputManager.Update();

      if (glfwGetKey(window, GLFW_KEY_ESCAPE))
      {
        glfwSetWindowShouldClose(window, 1);
      }

      count += 0.01f;

      RendererPlatform::ClearColor({0.0f, 0.5f, 0.5f, 1.f});
      RendererPlatform::Clear();
      texture.Bind();

      RendererPlatform::VerticesReading();
      //quadMesh.Draw();
//      light.model = Maths::Matrix4::Translate({cos(count) * 30, sin(count) * 30, 0});

      shader.Use();
      shader.SetVector4f("material.color", {1,1,1, 1});
//      shader.SetMatrix4("projection", Maths::Matrix4::Perspective(width, height, -1, 10000, 20 * 3.1415 /180));
      shader.SetMatrix4("model", Maths::Matrix4::Translate({0,0,3}));

      cam.Update();
      cam.MouseMovement(inputManager.mousePosition.pos, inputManager.mousePosition.prevPos);
      cam.CreateView();
      shader.SetMatrix4("projection", cam.GetProjection());
      shader.SetMatrix4("view", cam.GetView());

      RendererPlatform::SetPointLight(shader.ID, 0, light);
      cube.Draw();

      glfwSwapBuffers(window);
    }
  }
  glfwTerminate();
  return 0;
}