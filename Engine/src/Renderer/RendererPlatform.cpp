#include "glad/gl.h"
#include "GLFW/glfw3.h"
#include <iostream>

#include "Renderer/RendererPlatform.hpp"
#include "Renderer/Shader.hpp"
#include "Renderer/Vertex.hpp"
#include "Renderer/Framebuffer.hpp"

using namespace Renderer;


RendererPlatform::RendererPlatform()
{
  gladLoadGL(glfwGetProcAddress);

  printf("GL_VENDOR = %s\n",   glGetString(GL_VENDOR));
  printf("GL_RENDERER = %s\n", glGetString(GL_RENDERER));
  printf("GL_VERSION = %s\n",  glGetString(GL_VERSION));
}
void RendererPlatform::BindTexture(const unsigned int &texture)
{
  glBindTexture(GL_TEXTURE_2D, texture);
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
  glBindVertexArray(vertices);

  glDrawArrays(GL_TRIANGLES, 0, nbVertices);
}
Mesh RendererPlatform::CreateMesh(const Vertex *vertices, unsigned int verticesSize, const unsigned int *indices, unsigned int indicesSize)
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

  return Mesh(vao, vbo, ebo, indicesSize / sizeof(unsigned int));
}
void RendererPlatform::DrawMesh(const Mesh& mesh)
{
  glBindVertexArray(mesh._vao);
  glDrawElements(GL_TRIANGLES, mesh._nbVertices, GL_UNSIGNED_INT, 0);
}
void RendererPlatform::DeleteMesh(Mesh &mesh)
{
  glDeleteVertexArrays (1, &mesh._vao);
  glDeleteBuffers      (1, &mesh._vbo);
  glDeleteBuffers      (1, &mesh._ebo);
}
void RendererPlatform::UseShader(unsigned int shaderProgram)
{
  glUseProgram(shaderProgram);
}
void RendererPlatform::DeleteShader(unsigned int shaderProgram)
{
  glDeleteProgram(shaderProgram);
}
void RendererPlatform::SetMatrix4(unsigned int shaderProgram, const char *name,
                                  const Maths::Matrix4 &mat)
{
  glUniformMatrix4fv(glGetUniformLocation(shaderProgram, name),1, GL_FALSE, mat.e);
}
unsigned int
RendererPlatform::CreateProgramShader(const char *vertexShaderSource,
                                      const char *fragmentShaderSource)
{
  // vertexShader
  unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);

  //fragmentShader
  unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragmentShader);
  //programShader
  unsigned int programShader = glCreateProgram();
  glAttachShader(programShader, vertexShader);
  glAttachShader(programShader, fragmentShader);
  glLinkProgram(programShader);

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  return programShader;
}
Framebuffer RendererPlatform::CreateFramebuffer(unsigned int width,
                                         unsigned int height)
{
  unsigned int ID, texture, rbo;
  glGenFramebuffers(1, &ID);
  glBindFramebuffer(GL_FRAMEBUFFER, ID);

  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);

  glGenRenderbuffers(1, &rbo);
  glBindRenderbuffer(GL_RENDERBUFFER, rbo);
  glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, width, height);
  glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rbo);

  glBindFramebuffer(GL_FRAMEBUFFER, 0);

  return Framebuffer(ID, texture, rbo, width, height);
}
void RendererPlatform::BindFramebuffer(unsigned int ID)
{
  glBindFramebuffer(GL_FRAMEBUFFER, ID);
}

void RendererPlatform::DeleteBuffer(unsigned int buffer)
{
  glDeleteBuffers(1, &buffer);
}
void RendererPlatform::DeleteTexture(unsigned int texture)
{
  glDeleteTextures(1, &texture);
}
