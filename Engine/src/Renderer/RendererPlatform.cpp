#include "glad/gl.h"
#include "GLFW/glfw3.h"
#include <iostream>

#include "Renderer/RendererPlatform.hpp"
#include "Renderer/Shader.hpp"

using namespace Renderer;

RendererPlatform::RendererPlatform()
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
                          uniform mat4 projection;
                          uniform mat4 view;
                          uniform mat4 model;

                          void main()
                          {
                            gl_Position = view * projection * model * vec4(aPos, 1.0);
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


  glUseProgram(impl->_program);
  impl->_projectionLocation = glGetUniformLocation(impl->_program, "projection");
  impl->_viewLocation       = glGetUniformLocation(impl->_program, "view");
  impl->_modelLocation      = glGetUniformLocation(impl->_program, "model");

  glGenVertexArrays(1, &impl->_vao);
  glGenBuffers(1, &impl->_vbo);
  glGenBuffers(1, &impl->_ebo);
  glBindVertexArray(impl->_vao);

}
RendererPlatform::~RendererPlatform()
{
  delete impl;
}
void RendererPlatform::SetProjectionMatrix(const Maths::Matrix4& projectionMatrix)
{
  glUniformMatrix4fv(impl->_projectionLocation, 1, GL_FALSE, projectionMatrix.e);
}
void RendererPlatform::SetViewMatrix(const Maths::Matrix4& viewMatrix)
{
  glUniformMatrix4fv(impl->_viewLocation, 1, GL_FALSE, viewMatrix.e);
}
void RendererPlatform::SetModelMatrix(const Maths::Matrix4& modelMatrix)
{
  glUniformMatrix4fv(impl->_modelLocation, 1, GL_FALSE, modelMatrix.e);
}

//template<int N>
void RendererPlatform::SetVertices(const float* vertices, const unsigned int& size)
{
  glBindBuffer(GL_ARRAY_BUFFER, impl->_vbo);
  glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
}
void RendererPlatform::SetIndices(const unsigned int* indices, const unsigned int& size)
{
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, impl->_ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
}
void RendererPlatform::NewFrame()
{
  glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  glUseProgram(impl->_program);
  glBindVertexArray(impl->_vao);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}



void RendererPlatform::Delete()
{
  glDeleteVertexArrays(1, &impl->_vao);
  glDeleteBuffers(1, &impl->_vbo);
  glDeleteProgram(impl->_program);
}