#include "Resources/ResourcesManager.hpp"
#include "Renderer/Model.hpp"
#include "Renderer/Texture.hpp"

#include "glad/gl.h"
#include <GLFW/glfw3.h>

#include <iostream>

using namespace Resources;
using namespace Renderer;

int main(void)
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
  window = glfwCreateWindow(1280, 720, "Fenaitre", NULL, NULL);
  if (!window)
  {
    glfwTerminate();
    return -1;
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
    return -1;
  }

  printf("GL_VENDOR = %s\n",   glGetString(GL_VENDOR));
  printf("GL_RENDERER = %s\n", glGetString(GL_RENDERER));
  printf("GL_VERSION = %s\n",  glGetString(GL_VERSION));


  {
    ResourcesManager RS;

    //Model m1 = RS.LoadModel("T");
    //Model m2 = RS.LoadModel("T");
    //Model m3 = RS.LoadModel("o");

    Texture t1 = RS.LoadTexture("../../Asset/Texture.png");
    Texture t2 = RS.LoadTexture("../../Asset/Texture.png");

    Model m1 = RS.LoadModel("../../Asset/eyeball.fbx");

    //std::cout << m1.id << std::endl;
    //std::cout << m2.id << std::endl;
    //std::cout << m3.id << std::endl;

    RS.ReadFiles();

    std::cout << "Texture 1 ID : " << t1.ID << std::endl;
    std::cout << "Texture 2 ID : " << t2.ID << std::endl;
  }

  /* Loop until the user closes the window */
  while (!glfwWindowShouldClose(window))
  {
    /* Render here */
    glClear(GL_COLOR_BUFFER_BIT);

    /* Swap front and back buffers */
    glfwSwapBuffers(window);

    /* Poll for and process events */
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}