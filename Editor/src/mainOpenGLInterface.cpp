#include "GLFW/glfw3.h"

#include "Renderer/RendererPlatform.hpp"
#include "Renderer/Shader.hpp"
#include "Renderer/Framebuffer.hpp"
#include "Renderer/Vertex.hpp"
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
                      FragColor = vec4(1.0, 0.0, 0.0, 1.0);
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
    // Create RendererPlatform
    Renderer::RendererPlatform interface;

    const Renderer::Vertex quad[] = {
        // positions          // texture coords
        {{0.5f, 0.5f, 0.0f}, {0, 0, 1}, {1.0f, 1.0f}},   // top right
        {{0.5f, -0.5f, 0.0f}, {0, 0, 1}, {1.0f, 0.0f}},  // bottom right
        {{-0.5f, -0.5f, 0.0f}, {0, 0, 1}, {0.0f, 0.0f}}, // bottom left
        {{-0.5f, 0.5f, 0.0f}, {0, 0, 1}, {0.0f, 1.0f}}   // top left
    };

    unsigned int quadIndices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };
    // Mesh
    Renderer::Mesh quadMesh = Renderer::RendererPlatform::CreateMesh(
        quad, sizeof(quad), quadIndices, sizeof(quadIndices));
    // shader
    Shader shader(Renderer::RendererPlatform::CreateProgramShader(
        vertexShader, fragmentShader));
    RendererPlatform::UseShader(shader.ID);
    RendererPlatform::SetMatrix4(
        shader.ID, "projection",
        Maths::Matrix4::Perspective(width, height, -1.f, 100.f, 3.14f / 2.f));
    RendererPlatform::SetMatrix4(shader.ID, "view", Maths::Matrix4::Identity());
    RendererPlatform::SetMatrix4(shader.ID, "model",
                                 Maths::Matrix4::Translate({0, 0, 1}));
    // Shader fb
    Shader shaderFb(Renderer::RendererPlatform::CreateProgramShader(
        vertexShaderFb, fragmentShaderFb));
    // Framebuffer
    Renderer::Framebuffer framebuffer =
        Renderer::RendererPlatform::CreateFramebuffer(width, height);
    while (!glfwWindowShouldClose(window)) {
      // framebuffer
      {
        RendererPlatform::BindFramebuffer(framebuffer.GetID());
        interface.ClearColor({0.0f, 0.5f, 0.5f, 1.f});
        interface.Clear();
        Renderer::RendererPlatform::UseShader(shader.ID);
        quadMesh.Draw();
        RendererPlatform::BindFramebuffer(0);
      }
      interface.ClearColor({0.2f, 0.2f, 0.2f, 1.f});
      interface.Clear();
      RendererPlatform::UseShader(shaderFb.ID);
      RendererPlatform::BindTexture(framebuffer.GetTexture());
      quadMesh.Draw();
      glfwSwapBuffers(window);
      glfwPollEvents();
    }

//    RendererPlatform::DeleteFramebuffer(
//        framebuffer.GetID(), framebuffer.GetRbo(), framebuffer.GetTexture());
  }
  glfwTerminate();
  return 0;
}