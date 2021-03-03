#include "glad/gl.h"
#include "GLFW/glfw3.h"
#include <iostream>

#include "Renderer/RendererPlatform.hpp"
#include "Renderer/Shader.hpp"

using namespace Renderer;
struct Vertex
{
  float position[3];
  float uv[2];
};

RendererPlatform::RendererPlatform()
{
  gladLoadGL(glfwGetProcAddress);

  printf("GL_VENDOR = %s\n",   glGetString(GL_VENDOR));
  printf("GL_RENDERER = %s\n", glGetString(GL_RENDERER));
  printf("GL_VERSION = %s\n",  glGetString(GL_VERSION));

    impl._program = Shader::CreateProgramShader(
    R"GLSL(
                          #version 330 core
                          layout (location = 0) in vec3 aPos;
                          layout (location = 1) in vec2 aTexCoord;
                          uniform mat4 projection;
                          uniform mat4 view;
                          uniform mat4 model;

                          out vec2 TexCoord;

                          void main()
                          {
                            gl_Position = projection * view * model * vec4(aPos, 1.0);
                            TexCoord = aTexCoord;
                          }
                   )GLSL",
    R"GLSL(
                     #version 330 core
                     out vec4 FragColor;
                     in vec2 TexCoord;

                     uniform sampler2D ourTexture;

                     void main()
                     {
                      FragColor = texture(ourTexture, TexCoord);
                     }
                     )GLSL");


  glUseProgram(impl._program);
  impl._projectionLocation = glGetUniformLocation(impl._program, "projection");
  impl._viewLocation       = glGetUniformLocation(impl._program, "view");
  impl._modelLocation      = glGetUniformLocation(impl._program, "model");
}
void RendererPlatform::SetProjectionMatrix(const Maths::Matrix4& projectionMatrix)
{
  glUniformMatrix4fv(impl._projectionLocation, 1, GL_FALSE, projectionMatrix.e);
}
void RendererPlatform::SetViewMatrix(const Maths::Matrix4& viewMatrix)
{

  glUniformMatrix4fv(impl._viewLocation, 1, GL_FALSE, viewMatrix.e);
}
void RendererPlatform::SetModelMatrix(const Maths::Matrix4& modelMatrix)
{
  glUniformMatrix4fv(impl._modelLocation, 1, GL_FALSE, modelMatrix.e);
}

unsigned int RendererPlatform::CreateMesh(const float* vertices, const unsigned int& verticesSize, const unsigned int* indices, const unsigned int indicesSize)
{
  unsigned int vao, vbo;

  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, verticesSize, vertices, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)offsetof(Vertex, position));
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)offsetof(Vertex, uv));
  glEnableVertexAttribArray(1);

  unsigned int ebo;
  glGenBuffers(1, &ebo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize, indices, GL_STATIC_DRAW);

  impl._meshes.push_back(Mesh(vao, vbo, ebo, indicesSize / sizeof(unsigned int)));
  return impl._meshes.size() - 1;
}

void RendererPlatform::NewFrame()
{
  glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
}



void RendererPlatform::Delete()
{
  if(!impl._meshes.empty())
  {
    for(Mesh mesh : impl._meshes)
    {
      glDeleteVertexArrays(1, &mesh._vao);
      glDeleteBuffers(1, &mesh._vbo);
      glDeleteBuffers(1, &mesh._ebo);
    }
  }
  glDeleteProgram(impl._program);
}
void RendererPlatform::BindTexture(const unsigned int &texture)
{
  glBindTexture(GL_TEXTURE_2D, texture);
}
void RendererPlatform::DrawMesh(const unsigned int &MeshID)
{
  if(impl._meshes.empty() || impl._meshes.size() - 1 < MeshID)
    return;
  glUseProgram(impl._program);
  glBindVertexArray(impl._meshes[MeshID]._vao);
  glDrawElements(GL_TRIANGLES, impl._meshes[MeshID]._nbVertices, GL_UNSIGNED_INT, 0);
}
