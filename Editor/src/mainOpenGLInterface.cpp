#include <iostream>
#include "GLFW/glfw3.h"
#include "Renderer/RendererPlatform.hpp"
#include "Maths/Matrix4.hpp"
#include "Maths/Quaternion.hpp"

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
  interface.SetProjectionMatrix(Maths::Matrix4::Perspective(1280.f, 720.f, -1.f, 100.f, 3.14f/2.f));
  interface.SetViewMatrix(Maths::Matrix4::OrthoMatrix(1280.f, 720.f, -1.f, 100.f));
  interface.SetModelMatrix(Maths::Matrix4::Identity());

  float vertices[] = {
    //Face
    0.5f,  0.5f, 1.0f,
    0.5f, -0.5f, 1.0f,
    -0.5f, -0.5f, 1.0f,
    -0.5f,  0.5f, 1.0f
  };
  unsigned int indices[] = {
    0, 1, 3, // first triangle
    1, 2, 3  // second triangle
  };

  Maths::Quaternion q{7,4,5,1};
  std::cout << q;

  interface.SetIndices(indices, sizeof(indices));

  float alpha = 1.f;
  float increment = 0.01f;
  while (!glfwWindowShouldClose(window))
  {
    alpha += increment;

    if(alpha <= 1 || alpha >= 5)
      increment = -increment;

    float vertices[] = {
        //Face
        0.5f,  0.5f, alpha,
        0.5f, -0.5f, alpha,
        -0.5f, -0.5f, alpha,
        -0.5f,  0.5f, alpha
    };
    interface.SetVertices(vertices, sizeof(vertices));
    interface.NewFrame();
    glfwSwapBuffers(window);
    glfwPollEvents();
  }


  interface.Delete();
  glfwTerminate();
  return 0;
}