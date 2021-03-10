#include "GLFW/glfw3.h"

#include "Renderer/RendererPlatform.hpp"
#include "Renderer/Shader.hpp"
#include "Renderer/Framebuffer.hpp"
#include "Renderer/Texture.hpp"
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

    unsigned int quadIndices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };
    unsigned int triangleIndices[] = {0,2,3};

    // Mesh
    Renderer::Mesh quadMesh = Renderer::RendererPlatform::CreateMesh(
        quad, sizeof(quad), quadIndices, sizeof(quadIndices));
    Renderer::Mesh triangleMesh = Renderer::RendererPlatform::CreateMesh(
        triangle, sizeof(triangle), triangleIndices, sizeof(triangleIndices));
    // shader
    Shader shader(Renderer::RendererPlatform::CreateProgramShader(
        vertexShader, fragmentShader));
    RendererPlatform::UseShader(shader.ID);
    shader.SetMatrix4
        (
        "projection",
        Maths::Matrix4::Perspective(width, height, -1.f, 100.f, 3.14f / 2.f)
        );
    shader.SetMatrix4("view", Maths::Matrix4::Identity());
    // Shader fb
    Shader shaderFb(Renderer::RendererPlatform::CreateProgramShader(
        vertexShaderFb, fragmentShaderFb));
    // Framebuffer
    Renderer::Framebuffer framebuffer =
        Renderer::RendererPlatform::CreateFramebuffer(width, height);

//    Texture
    Texture texture (Texture::LoadTexture("../../../DirtCube.jpg"));
    while (!glfwWindowShouldClose(window))
    {
      // framebuffer
      {
        framebuffer.Bind();
        RendererPlatform::ClearColor({0.0f, 0.5f, 0.5f, 1.f});
        RendererPlatform::Clear();
        shader.Use();
        shader.SetMatrix4("model", Maths::Matrix4::Translate({-1, 0, 1}));
        quadMesh.Draw();
        shader.SetMatrix4("model", Maths::Matrix4::Translate({1, 0, 1}));
        triangleMesh.Draw();
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