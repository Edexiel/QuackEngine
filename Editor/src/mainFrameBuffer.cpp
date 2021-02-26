#include "glad/gl.h"
#include "GLFW/glfw3.h"
#include <iostream>

#include "Renderer/Framebuffer.hpp"

const char *vertexShaderSource = R"GLSL(
                                   #version 330 core
                                   layout (location = 0) in vec3 aPos;
                                   layout (location = 1) in vec3 aColor;
                                   layout (location = 2) in vec2 aTexCoord;

                                   out vec3 ourColor;
                                   out vec2 TexCoord;

                                   void main()
                                   {
                                      gl_Position = vec4(aPos, 1.0);
                                      ourColor = aColor;
                                      TexCoord = aTexCoord;
                                   }
                                   )GLSL";
const char *fragmentShaderSource = R"GLSL(
                                     #version 330 core
                                     out vec4 FragColor;
                                     in vec3 ourColor;
                                     in vec2 TexCoord;
                                     uniform sampler2D ourTexture;

                                     void main()
                                     {
                                        FragColor = texture(ourTexture, TexCoord);
                                     }
                                   )GLSL";

const char *fragmentShaderFramebuffer = R"GLSL(
                                     #version 330 core
                                     out vec4 FragColor;
                                     in vec3 ourColor;
                                     in vec2 TexCoord;
                                     uniform sampler2D ourTexture;

                                     void main()
                                     {
                                        FragColor = vec4(1, 0, 0, 1);
                                     }
                                   )GLSL";

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
  window = glfwCreateWindow(1280, 720, "FrameBuffer", NULL, NULL);
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


  //Framebuffer
  Renderer::Framebuffer framebuffer(1280, 720);


  float vertices[] = {
    // positions          // colors           // texture coords (note that we changed them to 2.0f!)
    0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
    0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
    -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left
  };
  unsigned int indices[] = {
    0, 1, 3, // first triangle
    1, 2, 3  // second triangle
  };
  unsigned int VBO, VAO, EBO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);

  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  // position attribute
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  // color attribute
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);
  // texture coord attribute
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
  glEnableVertexAttribArray(2);

  // vertexShader
  unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);

  //fragmentShader
  unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragmentShader);

  //fragmentShaderfb
  unsigned int fragmentShaderfb = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShaderfb, 1, &fragmentShaderFramebuffer, NULL);
  glCompileShader(fragmentShaderfb);

  //shaderProgram
  unsigned int shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);

  //shaderProgramFramebuffer
  unsigned int shaderProgramfb = glCreateProgram();
  glAttachShader(shaderProgramfb, vertexShader);
  glAttachShader(shaderProgramfb, fragmentShaderfb);
  glLinkProgram(shaderProgramfb);

<<<<<<< HEAD
=======

>>>>>>> a9b5049fd88c40e6b962091755758a4207d3cf50
  while (!glfwWindowShouldClose(window))
  {
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer.GetID());
    glClearColor(0.5f, 0.5f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shaderProgramfb);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glBindTexture(GL_TEXTURE_2D, framebuffer.GetTexture());
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteProgram(shaderProgram);
  glDeleteProgram(shaderProgramfb);

  framebuffer.Delete();


  glfwTerminate();
  return 0;
}