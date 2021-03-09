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

    _shaderProgram = Shader::CreateProgramShader(
    R"GLSL(
                          #version 330 core
                          layout (location = 0) in vec3 aPos;
                          layout (location = 1) in vec3 aNormal;
                          layout (location = 2) in vec2 aTexCoord;

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
                      FragColor = vec4(1.0, 0.0, 0.0, 1.0);
                      //FragColor = texture(ourTexture, TexCoord);
                     }
                     )GLSL");


  glUseProgram(_shaderProgram);
  _projectionLocation = glGetUniformLocation(_shaderProgram, "projection");
  _viewLocation       = glGetUniformLocation(_shaderProgram, "view");
  _modelLocation      = glGetUniformLocation(_shaderProgram, "model");
}
void RendererPlatform::SetProjectionMatrix(const Maths::Matrix4& projectionMatrix)
{
  glUniformMatrix4fv(_projectionLocation, 1, GL_FALSE, projectionMatrix.e);
}
void RendererPlatform::SetViewMatrix(const Maths::Matrix4& viewMatrix)
{

  glUniformMatrix4fv(_viewLocation, 1, GL_FALSE, viewMatrix.e);
}
void RendererPlatform::SetModelMatrix(const Maths::Matrix4& modelMatrix)
{
  glUniformMatrix4fv(_modelLocation, 1, GL_FALSE, modelMatrix.e);
}

unsigned int RendererPlatform::CreateMesh(const Vertex* vertices, unsigned int verticesSize, const unsigned int* indices, unsigned int indicesSize)
{
  unsigned int vao, vbo;

  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, verticesSize, vertices, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)offsetof(Vertex, position));
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)offsetof(Vertex, normal));
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)offsetof(Vertex, uv));
  glEnableVertexAttribArray(2);

  unsigned int ebo;
  glGenBuffers(1, &ebo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize, indices, GL_STATIC_DRAW);

  _meshes.push_back(Mesh(vao, vbo, ebo, indicesSize / sizeof(unsigned int), 0));
  return _meshes.size() - 1;
}

void RendererPlatform::Delete()
{
  if(!_meshes.empty())
  {
    for(Mesh mesh : _meshes)
    {
        mesh.Delete();
    }
  }
  glDeleteProgram(_shaderProgram);
}
void RendererPlatform::BindTexture(const unsigned int &texture)
{
  glBindTexture(GL_TEXTURE_2D, texture);
}
void RendererPlatform::DrawMesh(const unsigned int &MeshID)
{
  if(_meshes.empty() || _meshes.size() - 1 < MeshID)
    return;
  glBindVertexArray(_meshes[MeshID]._vao);
  glDrawElements(GL_TRIANGLES, _meshes[MeshID]._nbVertices, GL_UNSIGNED_INT, 0);
}

void RendererPlatform::DrawMesh(const Mesh &mesh)
{
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)offsetof(Vertex, position));
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)offsetof(Vertex, normal));
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)offsetof(Vertex, uv));
  glEnableVertexAttribArray(2);

  glBindBuffer(GL_ARRAY_BUFFER, mesh._vbo);
  glBindVertexArray(mesh._vao);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh._ebo);

  glDrawElements(GL_TRIANGLES, mesh._nbIndices, GL_UNSIGNED_INT, (const void*)0);
}

void RendererPlatform::UseProgram()
{
  glUseProgram(_shaderProgram);
}
void RendererPlatform::ClearColor(const Maths::Vector4 &color)
{
  glClearColor(color.r, color.g, color.b, color.a);
}
void RendererPlatform::Clear()
{
  glClear(GL_COLOR_BUFFER_BIT);
}
unsigned int RendererPlatform::CreateVertices(const float *vertices, unsigned int verticesSize)
{
  unsigned int vao, vbo;

  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, verticesSize, vertices, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)offsetof(Vertex, position));
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)offsetof(Vertex, normal));
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)offsetof(Vertex, uv));
  glEnableVertexAttribArray(2);

  return vao;
}
void RendererPlatform::DrawVertices(unsigned int vertices, unsigned int nbVertices)
{
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)offsetof(Vertex, position));
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)offsetof(Vertex, normal));
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)offsetof(Vertex, uv));
  glEnableVertexAttribArray(2);

  glBindVertexArray(vertices);
  glDrawArrays(GL_TRIANGLES, 0, nbVertices);
}
