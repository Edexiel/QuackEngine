#include "glad/gl.h"
#include "GLFW/glfw3.h"
#include <iostream>

#include "Renderer/OpenGLInterface.hpp"
#include "Renderer/Shader.hpp"

using namespace Renderer;

OpenGLInterface::OpenGLInterface()
{
  gladLoadGL(glfwGetProcAddress);

  printf("GL_VENDOR = %s\n",   glGetString(GL_VENDOR));
  printf("GL_RENDERER = %s\n", glGetString(GL_RENDERER));
  printf("GL_VERSION = %s\n",  glGetString(GL_VERSION));

  impl = new OpenGLInterfaceImp();
  impl->_program = Shader::CreateProgramShader(
    R"GLSL(
                          #version 330 core
                          layout (location = 0) in vec3 aPos;


                          void main()
                          {
                            gl_Position = vec4(aPos, 1.0);
                          }
                   )GLSL",
    R"GLSL(
                     #version 330 core
                     out vec4 FragColor;

                     void main()
                     {
                      FragColor = vec4(1, 0, 0, 1);
                     }
                     )GLSL");

  glGenVertexArrays(1, &impl->_vao);
  glGenBuffers(1, &impl->_vbo);
  glGenBuffers(1, &impl->_ebo);
  glBindVertexArray(impl->_vao);

}
OpenGLInterface::~OpenGLInterface()
{
  delete impl;
}
void OpenGLInterface::SetProjectionMatrix(const Maths::Matrix4& projectionMatrix)
{
  impl->_projectionMatrix = projectionMatrix;
}
void OpenGLInterface::SetViewMatrix(const Maths::Matrix4& viewMatrix)
{
  impl->_viewMatrix = viewMatrix;
}
void OpenGLInterface::SetModelMatrix(const Maths::Matrix4& modelMatrix)
{
  impl->_modelMatrix = modelMatrix;
}

//template<int N>
void OpenGLInterface::SetVertices(const float* vertices, const unsigned int& size)
{
  glBindBuffer(GL_ARRAY_BUFFER, impl->_vbo);
  glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
}
void OpenGLInterface::SetIndices(const unsigned int* indices, const unsigned int& size)
{
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, impl->_ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
}
void OpenGLInterface::NewFrame()
{
  glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  glUseProgram(impl->_program);
  glBindVertexArray(impl->_vao);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}



void OpenGLInterface::Delete()
{
  glDeleteVertexArrays(1, &impl->_vao);
  glDeleteBuffers(1, &impl->_vbo);
  glDeleteProgram(impl->_program);
}