#include "GLFW/glfw3.h"
#include "glad/gl.h"

#include "Renderer/RendererPlatform.hpp"
#include "Renderer/Shader.hpp"
#include "Renderer/Framebuffer.hpp"
#include "Renderer/Texture.hpp"
#include "Renderer/Vertex.hpp"
#include "Renderer/Mesh.hpp"
#include "Resources/ResourcesManager.hpp"

using namespace Renderer;
const char* vertexShader =
    {
                      R"GLSL(
                      #version 330 core
                      layout (location = 0) in vec3 aPos;
                      layout (location = 1) in vec3 aNormal;
                      layout (location = 2) in vec2 aTexCoord;

                      uniform mat4 projection;
                      uniform mat4 view;
                      uniform mat4 model;

                      out vec2 TexCoord;

                      void main()
                      {
                      gl_Position = projection * view * model * vec4(aPos, 1.0);
                      TexCoord = aTexCoord;
                     }
                     )GLSL"
    };

const char* fragmentShader =
    {
        R"GLSL(
                     #version 330 core
                     out vec4 FragColor;
                     in vec2 TexCoord;

                     uniform sampler2D ourTexture;

                     void main()
                     {
                      FragColor = vec4(1,0,0,1);// texture(ourTexture, TexCoord);
                     }
                     )GLSL"
    };

const char* vertexShaderFb =
    {
        R"GLSL(
                      #version 330 core
                      layout (location = 0) in vec3 aPos;
                      layout (location = 1) in vec3 aNormal;
                      layout (location = 2) in vec2 aTexCoord;

                      out vec2 TexCoord;

                      void main()
                      {
                      gl_Position = vec4(aPos, 1.0);
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


    const Renderer::Vertex quad[] = {
        // positions          // texture coords
        {{0.5f, 0.5f, 0.0f}, {0, 0, 1}, {1.0f, 1.0f}},   // top right
        {{0.5f, -0.5f, 0.0f}, {0, 0, 1}, {1.0f, 0.0f}},  // bottom right
        {{-0.5f, -0.5f, 0.0f}, {0, 0, 1}, {0.0f, 0.0f}}, // bottom left
        {{-0.5f, 0.5f, 0.0f}, {0, 0, 1}, {0.0f, 1.0f}}   // top left
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

    // shader

    Shader shader = rm.LoadShader("../../../vertex.vs", "../../../fragment.fs");

    //Shader shader(Renderer::RendererPlatform::CreateShader(
    //    vertexShader, fragmentShader));
    RendererPlatform::UseShader(shader.ID);
    shader.SetMatrix4
        (
        "projection",
        Maths::Matrix4::Perspective(width, height, -1.f, 100.f, 3.14f / 2.f)
        );
    shader.SetMatrix4("view", Maths::Matrix4::Identity());
    // Shader fb
    Shader shaderFb(Renderer::RendererPlatform::CreateShader(
        vertexShaderFb, fragmentShaderFb));
    // Framebuffer
    Renderer::Framebuffer framebuffer =
        Renderer::RendererPlatform::CreateFramebuffer(width, height);



    Renderer::Mesh quadMesh = Renderer::RendererPlatform::CreateMesh(
        quad, sizeof(quad) / sizeof (float ), quadIndices, sizeof(quadIndices) / sizeof(unsigned int));


//    Texture
    Model model =  Model::LoadModel("../../../fbx/Dragon_Baked_Actions_fbx_7.4_binary.fbx");
    Texture texture = rm.LoadTexture("../../../DirtCube.jpg");


    float count = 0;

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    while (!glfwWindowShouldClose(window))
    {
      count += 0.001f;

      // framebuffer
      {
        framebuffer.Bind();
        RendererPlatform::ClearColor({0.0f, 0.5f, 0.5f, 1.f});
        RendererPlatform::Clear();
        shaderFb.Use();
        texture.Bind();

        RendererPlatform::VerticesReading();
        //quadMesh.Draw();

        shader.Use();
        shader.SetMatrix4("projection", Maths::Matrix4::Perspective(width, height, -1, 10000, 20 * M_PI/180));
        shader.SetMatrix4("view", Maths::Matrix4::Identity());
        shader.SetMatrix4("model", Maths::Matrix4::Translate({0,-10,150}) * Maths::Matrix4::RotateY(count) * Maths::Matrix4::RotateX(-90 * M_PI / 180));

        texture.Bind();
        model.Draw();

        RendererPlatform::BindFramebuffer(0);
      }

      RendererPlatform::ClearColor({0.2f, 0.2f, 0.2f, 1.f});
      RendererPlatform::Clear();
      shaderFb.Use();
      framebuffer.BindTexture();
      quadMesh.Draw();
      glfwSwapBuffers(window);
      glfwPollEvents();
    }
  }
  glfwTerminate();
  return 0;
}