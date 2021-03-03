#include "GLFW/glfw3.h"

#include "Renderer/RendererPlatform.hpp"
#include "Renderer/Texture.hpp"
#include "Maths/Matrix4.hpp"

int main()
{
  GLFWwindow* window;

  /* Initialize the library */
  if (!glfwInit())
    return -1;
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  /* Create a windowed mode window and its OpenGL context */
  window = glfwCreateWindow(1280, 720, "RendererPlatform", NULL, NULL);
  if (!window)
  {
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);

  Renderer::RendererPlatform interface;
  interface.SetProjectionMatrix(
      Maths::Matrix4::OrthoMatrix(1280.f, 720.f, -1.f, 100.f)*
                   Maths::Matrix4::Perspective(1280.f, 720.f, -1.f, 100.f, 3.14f/2.f)
                   );
  interface.SetViewMatrix(Maths::Matrix4::Identity());
  interface.SetModelMatrix(Maths::Matrix4::Translate({0,0,1}));
  float triangle[] = {
      // positions          // texture coords
      0.0f,  1.0f, 0.0f,    0.5f, 1.0f,
      1.0f,  0.0f, 0.0f,    1.0f, 0.5f,
      -1.0f, 0.0f, 0.0f,    0.0f, 0.5f
  };

  float quad[] = {
      // positions          // texture coords
      0.5f,  0.5f, 0.0f,    1.0f, 1.0f, // top right
      0.5f, -0.5f, 0.0f,    1.0f, 0.0f, // bottom right
     -0.5f, -0.5f, 0.0f,    0.0f, 0.0f, // bottom left
     -0.5f,  0.5f, 0.0f,    0.0f, 1.0f  // top left
    };
  float framebufferQuad[] = {
      // positions          // texture coords
      1.0f,  1.0f, 0.0f,    1.0f, 1.0f, // top right
      1.0f, -1.0f, 0.0f,    1.0f, 0.0f, // bottom right
      -1.0f, -1.0f, 0.0f,    0.0f, 0.0f, // bottom left
      -1.0f,  1.0f, 0.0f,    0.0f, 1.0f  // top left
  };


  unsigned int triangleIndices[] = {0, 1 ,2};

  unsigned int quadIndices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
      };

  unsigned int framebufferID = interface.CreateMesh(framebufferQuad, sizeof(framebufferQuad), quadIndices, sizeof(quadIndices));
  unsigned int quadID = interface.CreateMesh(quad, sizeof(quad), quadIndices, sizeof(quadIndices));
  unsigned int triangleID = interface.CreateMesh(triangle, sizeof(triangle), triangleIndices, sizeof(triangleIndices));


  //Texture
  const unsigned int texture = Renderer::Texture::LoadTexture("../../../Sonic.png");

  while (!glfwWindowShouldClose(window))
  {
    interface.NewFrame();
    interface.SetModelMatrix(Maths::Matrix4::Identity());
    interface.DrawMesh(framebufferID);

    interface.BindTexture(texture);
    interface.SetModelMatrix(Maths::Matrix4::Translate({-2,0,1}));
    interface.DrawMesh(quadID);
    interface.SetModelMatrix(Maths::Matrix4::Translate({2,0,1}));
    interface.DrawMesh(triangleID);
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  interface.Delete();
  glfwTerminate();
  return 0;
}