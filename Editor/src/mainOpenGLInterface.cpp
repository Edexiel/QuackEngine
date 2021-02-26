#include "GLFW/glfw3.h"
#include "Renderer/OpenGLInterface.hpp"

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
  window = glfwCreateWindow(1280, 720, "OpenGLInterface", NULL, NULL);
  if (!window)
  {
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);

  Renderer::OpenGLInterface interface;

  float vertices[] = {
    // positions         // texture coords (note that we changed them to 2.0f!)
    0.5f,  0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f,
    -0.5f,  0.5f, 0.0f
  };
  unsigned int indices[] = {
    0, 1, 3, // first triangle
    1, 2, 3  // second triangle
  };


  interface.SetVertices(vertices, sizeof(vertices));
  interface.SetIndices(indices, sizeof(indices));

  while (!glfwWindowShouldClose(window))
  {
    interface.NewFrame();
    glfwSwapBuffers(window);
    glfwPollEvents();
  }


  interface.Delete();
  glfwTerminate();
  return 0;
}