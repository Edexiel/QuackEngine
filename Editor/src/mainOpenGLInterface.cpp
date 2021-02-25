#include "Renderer/OpenGLInterface.hpp"
#include "GLFW/glfw3.h"


int main()
{
  GLFWwindow* window = Renderer::OpenGLInterface::InitWindow("OpenGLInterface", 1280, 720);
  Renderer::OpenGLInterface openGLInterface(window);

  while(!glfwWindowShouldClose(window))
  {
    openGLInterface.Update(window);
  }

  glfwTerminate();
  return 0;
}