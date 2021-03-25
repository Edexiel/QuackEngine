//#include "glad/gl.h"
#include "GLFW/glfw3.h"

#include "Renderer/RendererPlatform.hpp"
#include "Renderer/Shader.hpp"
#include "Renderer/Framebuffer.hpp"
#include "Renderer/Texture.hpp"
#include "Renderer/Vertex.hpp"
#include "Renderer/Mesh.hpp"
#include "Renderer/Light.hpp"
#include "Resources/ResourcesManager.hpp"
#include "Renderer/Material.hpp"

#include "Input/PlatformInputGLFW.hpp"
#include "Input/InputManager.hpp"

#include "Audio/SoundManager.hpp"
#include "Audio/Sound.hpp"

#include "Debug/Log.hpp"

//#define MINIAUDIO_IMPLEMENTATION
//#include "miniaudio.h"

#include <cmath>

using namespace Renderer;

const char* vertexShaderFb =
    {
        R"GLSL(
                      #version 330 core
                      layout (location = 0) in vec3 aPos;
                      layout (location = 1) in vec3 aNormal;
                      layout (location = 2) in vec2 aTexCoord;

                      uniform mat4 view;

                      out vec2 TexCoord;

                      void main()
                      {
                      gl_Position = view * vec4(aPos, 1.0);
                      TexCoord = aTexCoord;
                     }
                     )GLSL"
    };
const char* fragmentShaderFb =
    {
                     R"GLSL(
                     #version 330 core
                     out vec4 FragColor;
                     in vec2 TexCoord;

                     uniform sampler2D ourTexture;

                     void main()
                     {
                      FragColor = texture(ourTexture, TexCoord);
                     }
                     )GLSL"
    };

struct MyHero
{
  void IsPressed(){std::cout << "IsPressed\n";};
  void IsReleased(){std::cout << "IsReleased\n";};
  void TestAxis(float bonsoir){std::cout<< bonsoir<< std::endl;};
};

int main()
{

  //Audio::SoundManager sd;
  //Audio::Sound sound = sd.CreateSound("../../../inactive.ogg");


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


    const Renderer::Vertex quad[] = {
        // positions          // texture coords
        {{1.0f, 1.0f, 0.0f}, {0, 0, 1}, {1.0f, 1.0f}},   // top right
        {{1.0f, -1.0f, 0.0f}, {0, 0, 1}, {1.0f, 0.0f}},  // bottom right
        {{-1.0f, -1.0f, 0.0f}, {0, 0, 1}, {0.0f, 0.0f}}, // bottom left
        {{-1.0f, 1.0f, 0.0f}, {0, 0, 1}, {0.0f, 1.0f}}   // top left
    };
    const Renderer::Vertex triangle[] = {
        // positions          // texture coords
        {{0.0f, 1.0f, 0.0f}, {0, 0, 1}, {1.0f, 1.0f}},   // top right
        {{1.0f, -1.0f, 0.0f}, {0, 0, 1}, {1.0f, 0.0f}},  // bottom right
        {{-1.0f, -1.0f, 0.0f}, {0, 0, 1}, {0.0f, 0.0f}}, // bottom left
    };

    const Renderer::Vertex quad2[] = {
        // positions          // texture coords
        {{0.5f, 0.8f, 0.0f}, {0, 0, 1}, {1.0f, 1.0f}},   // top right
        {{0.9f, -0.4f, 0.0f}, {0, 0, 1}, {1.0f, 0.0f}},  // bottom right
        {{-0.75f, -0.6f, 0.0f}, {0, 0, 1}, {0.0f, 0.0f}}, // bottom left
        {{-0.5f, 0.58f, 0.0f}, {0, 0, 1}, {0.0f, 1.0f}}   // top left
    };

    unsigned int quadIndices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    Resources::ResourcesManager rm;

    // Shader fb
    Shader shaderFb(Renderer::RendererPlatform::CreateShader(
        vertexShaderFb, fragmentShaderFb));
    // Framebuffer
    Renderer::Framebuffer framebuffer =
        Renderer::RendererPlatform::CreateFramebuffer(width, height);



    Renderer::Mesh quadMesh = Renderer::RendererPlatform::CreateMesh(
        quad, sizeof(quad) / sizeof (float ), quadIndices, sizeof(quadIndices) / sizeof(unsigned int));
    RendererPlatform::VerticesReading();


    Renderer::Light light(Renderer::Light_Type::L_POINT);

    light.model = Maths::Matrix4::RotateX(-3.1415 / 2) * Maths::Matrix4::Translate({0,0, 0});
    light.ambient = {0.0f, 0.1f, 0.0f};
    light.diffuse = {0.7f, 0.7f, 0.7f};
    light.specular = {1.0f, 1.0f, 1.0f};
    light.constant = 1.0f;
    light.linear = 0.0014f;
    light.quadratic = 0.000007f;

    light.outerSpotAngle = 10.5;
    light.spotAngle = 8.5;



    ShaderConstructData shd = {1,1,0, 0, 0, 0, 0, 0};

    //Shader shader = rm.LoadShader("../../Game/Asset/Shader/vertex.vs", "../../Game/Asset/Shader/fragment.fs");

    Shader shader = Shader::LoadShader(shd);

    RendererPlatform::UseShader(shader.ID);
    shader.SetMatrix4
        (
            "projection",
            Maths::Matrix4::Perspective(width, height, -1.f, 100.f, 3.1415f / 2.f)
        );
    shader.SetMatrix4("view", Maths::Matrix4::Identity());

    Model model =  Model::LoadModel("../../../eyeball.fbx", VertexType::V_NORMALMAP);
    //Texture texture = rm.LoadTexture("../../../Dragon_Bump_Col2.jpg");
    //Texture textureDiffuse = rm.LoadTexture("../../../Dragon_Bump_Col2Diffuse.jpg");
    //Texture textureSpecular = rm.LoadTexture("../../../Dragon_Bump_Col2Specular.jpg");

    Material material;
    material.shader = shader;

    material.ambient = {1, 1, 1};
    material.diffuse = {1, 1, 1};
    material.specular = {1, 1, 1};
    material.shininess = 256;

    //material.colorTexture = texture;
    //material.diffuseTexture = textureDiffuse;
    //material.specularTexture = textureSpecular;
    //material.normalMap = rm.LoadTexture("../../../Dragon_Nor_mirror2.jpg");


    float count = 0;

    RendererPlatform::EnableDepthBuffer(true);

    //glfwSetWindowShouldClose(window, 1);

    //test inputManager
    Input::PlatformInputGLFW platformInput(window);
    Input::InputManager inputManager(platformInput);

    inputManager.BindEvent("Hero", Input::MouseButton::MOUSE_BUTTON_1);
    inputManager.BindEvent("Hero", Input::MouseButton::MOUSE_BUTTON_2);
    inputManager.BindEventAxis("Axis", Input::Key::KEY_W, 1.0f);
    inputManager.BindEventAxis("Axis", Input::Key::KEY_S, -1.0f);
    MyHero hero;
    inputManager.RegisterEvent("Hero",Input::Action::PRESS, &hero, &MyHero::IsPressed);
    inputManager.RegisterEvent("Hero",Input::Action::RELEASE, &hero, &MyHero::IsReleased);
    inputManager.RegisterEventAxis("Axis",&hero, &MyHero::TestAxis);

    while (!glfwWindowShouldClose(window))
    {
        /*frameNB++;

        std::cout << "Freq : " << glfwGetTime() - lastFrameTime << std::endl;
        lastFrameTime = glfwGetTime();

        if (frameNB == 99)
        {
            start = glfwGetTime();
        }
        if (frameNB >= 100) {
            avg = (glfwGetTime() - start) / (frameNB - 99);
            std::cout << "average = " << avg << std::endl;
        }*/

      inputManager.Update();
      count += 0.01f;

      // framebuffer
      {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE))
        {
          glfwSetWindowShouldClose(window, 1);
        }

        if (glfwGetKey(window, GLFW_KEY_R))
        {
            //sound.Restart();
        }
        if (glfwGetKey(window, GLFW_KEY_P))
        {
            //sound.Play();
        }
        if (glfwGetKey(window, GLFW_KEY_S))
        {
            //sound.Stop();
        }

          if (glfwGetKey(window, GLFW_KEY_K))
          {
              //sound.SetVolume(sound.GetVolume() + 0.01);
              //sd.SetVolume(Audio::SoundType::S_EFFECT, sd.GetVolume(Audio::SoundType::S_EFFECT) + 0.01);
          }
          if (glfwGetKey(window, GLFW_KEY_M))
          {
              //sound.SetVolume(sound.GetVolume() - 0.01);
              //sd.SetVolume(Audio::SoundType::S_EFFECT, sd.GetVolume(Audio::SoundType::S_EFFECT) - 0.01);
          }


        framebuffer.Bind();
        RendererPlatform::ClearColor({0.0f, 0.5f, 0.5f, 1.f});
        RendererPlatform::Clear();

        //quadMesh.Draw();
        light.model = Maths::Matrix4::Translate({cosf(count) * 30, sinf(count) * 30, 0});
        //light.model = Maths::Matrix4::RotateY(count);

        material.Apply();

        //shader.Use();
        //shader.SetVector4f("material.color", {1,1,1, 1});

        material.shader.SetMatrix4("projection", Maths::Matrix4::Perspective(width, height, -1, 10000, 20 * 3.1415/180));
        material.shader.SetMatrix4("view", Maths::Matrix4::Translate({0, 0, 0}));
        material.shader.SetMatrix4("model", Maths::Matrix4::Translate({0,0,10}) * Maths::Matrix4::RotateY(count) * Maths::Matrix4::RotateX(-3.1415 / 2) * Maths::Matrix4::Scale({1,1,1}));

        //RendererPlatform::SetPointLight(shader.ID, 0, light);
        //RendererPlatform::SetDirectionalLight(shader.ID, 0, light);

        shader.SetLight(light, 0);

        model.Draw();


        RendererPlatform::BindFramebuffer(0);
      }

      RendererPlatform::ClearColor({0.2f, 0.2f, 0.2f, 1.f});
      RendererPlatform::Clear();
      shaderFb.Use();
      shaderFb.SetMatrix4("view", Maths::Matrix4::Identity());
      framebuffer.BindTexture();
      quadMesh.Draw();
      glfwSwapBuffers(window);
      glfwPollEvents();
    }
    //ma_device_uninit(&device);
    //ma_decoder_uninit(&decoder);
  }
  glfwTerminate();
  return 0;
}