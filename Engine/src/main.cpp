#include <iostream>

#include "Resources/ResourcesManager.hpp"
#include "Renderer/Model.hpp"
#include "Renderer/Texture.hpp"

#include "glad/glad.h"
#include <GLFW/glfw3.h>

using namespace Resources;
using namespace Renderer;

int main ()
{
  int screenWidth = 500;
  int screenHeight = 500;

  // Init GLFW
  if (!glfwInit())
  {
    fprintf(stderr, "glfwInit failed.\n");
    return -1;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);

  // Create window
  GLFWwindow *window = glfwCreateWindow(screenWidth, screenHeight, "Fenaitre", NULL, NULL);
  if (!window)
  {
    fprintf(stderr, "glfwCreateWindow failed.\n");
    glfwTerminate();
    return -1;
  }

  glfwSwapInterval(1); // Enable v-sync

  glfwMakeContextCurrent(window);

  // Load OpenGL functions
  if (!gladLoadGL())
  {
    fprintf(stderr, "gladLoadGL failed.\n");
    glfwTerminate();
    return -1;
  }

  GLuint VAO;
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);

  // Create and compile our GLSL program from the shaders

  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);

  // Enable blending
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  // Ressource Test

  {
    ResourcesManager RS;

    //Model m1 = RS.LoadModel("T");
    //Model m2 = RS.LoadModel("T");
    //Model m3 = RS.LoadModel("o");

    Texture t1 = RS.LoadTexture("../Asset/DirtCube.jpg");

    //std::cout << m1.id << std::endl;
    //std::cout << m2.id << std::endl;
    //std::cout << m3.id << std::endl;
  }

  while (!glfwWindowShouldClose(window))
  {
    glfwPollEvents();

    if (glfwGetKey(window, GLFW_KEY_ESCAPE))
      glfwSetWindowShouldClose(window, 1);

    // Set all the pixel of the screen to the same color
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.1f, 0.1f, 0.1f, 1.f);

    // Present buffer
    glfwSwapBuffers(window);

  }
  glfwTerminate();

  return 0;
}