#include "Renderer/OpenGLInterface.hpp"
#include "glad/gl.h"
#include "GLFW/glfw3.h"

#include <iostream>

using namespace Renderer;
OpenGLInterface::OpenGLInterface(GLFWwindow* window)
{
  if (!window)
  {
    glfwTerminate();
    return;
  }
  /* Make the window's context current */
  glfwMakeContextCurrent(window);

  /* load Glad OpenGL */
  int version = gladLoadGL(glfwGetProcAddress);
//printf("OpenGL version : %d.%d\n", GLAD_VERSION_MAJOR(version), GLAD_VERSION_MINOR(version));

  if (version == 0)
  {
    printf("Failed to initialize OpenGL context");
    glfwTerminate();
    return;
  }

  printf("GL_VENDOR = %s\n",   glGetString(GL_VENDOR));
  printf("GL_RENDERER = %s\n", glGetString(GL_RENDERER));
  printf("GL_VERSION = %s\n",  glGetString(GL_VERSION));
}
GLFWwindow* OpenGLInterface::InitWindow(const char* windowName, const unsigned int& width, const unsigned int& height)
{
  if (!glfwInit())
    return nullptr;

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  return glfwCreateWindow(width, height, windowName, NULL, NULL);
}
void OpenGLInterface::Update(GLFWwindow* window)
{
  glfwPollEvents();
  glfwSwapBuffers(window);
}
