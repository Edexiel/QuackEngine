#include "glad/gl.h"
#include "GLFW/glfw3.h"

#include "Renderer/RendererPlatform.hpp"
#include "Renderer/Vertex.hpp"
#include "Renderer/Framebuffer.hpp"

#include "Renderer/Mesh.hpp"
#include "Renderer/Shader.hpp"
#include "Renderer/Texture.hpp"

using namespace Renderer;

int RendererPlatform::LoadGL()
{
  int version = gladLoadGL(glfwGetProcAddress);

  printf("GL_VENDOR = %s\n",   glGetString(GL_VENDOR));
  printf("GL_RENDERER = %s\n", glGetString(GL_RENDERER));
  printf("GL_VERSION = %s\n",  glGetString(GL_VERSION));

  return version;
}

void RendererPlatform::BindTexture(unsigned int texture)
{
  glBindTexture(GL_TEXTURE_2D, (Gluint)texture);
}

void RendererPlatform::ClearColor(const Maths::Vector4 &color)
{
  glClearColor(color.r, color.g, color.b, color.a);
}

void RendererPlatform::Clear()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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
  glBufferData(GL_ARRAY_BUFFER, verticesSize * sizeof(float), vertices, GL_STATIC_DRAW);
  
  unsigned int ebo;
  glGenBuffers(1, &ebo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize * sizeof(unsigned int), indices, GL_STATIC_DRAW);

  return Mesh(vao, vbo, ebo, verticesSize, indicesSize);
}

Mesh RendererPlatform::CreateMesh(const float *vertices, unsigned int verticesSize, const unsigned int *indices, unsigned int indicesSize)
{
  unsigned int vao, vbo, ebo;

  glGenVertexArrays(1, &vao);
  glGenBuffers(1, &vbo);
  glGenBuffers(1, &ebo);

  glBindVertexArray(vao);

  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, verticesSize * sizeof(float), vertices, GL_STATIC_DRAW);
  

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize * sizeof(unsigned int), indices, GL_STATIC_DRAW);


  return Mesh(vao, vbo, ebo, verticesSize, indicesSize);
}

void RendererPlatform::DrawMesh(unsigned int vao, unsigned int vbo, unsigned int ebo, unsigned int nbIndices)
{
  glBindVertexArray(vao);

  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);


  glDrawElements(GL_TRIANGLES, nbIndices, GL_UNSIGNED_INT, (const void*)0);

}

void RendererPlatform::DeleteMesh(unsigned int vao, unsigned int vbo, unsigned int ebo)
{
  glDeleteVertexArrays (1, &vao);
  glDeleteBuffers      (1, &vbo);
  glDeleteBuffers      (1, &ebo);
}

void RendererPlatform::VerticesReading()
{
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)offsetof(Vertex, position));
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)offsetof(Vertex, normal));
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)offsetof(Vertex, uv));
  glEnableVertexAttribArray(2);
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

Shader RendererPlatform::CreateShader(const char *vertexShaderSource,
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
  //shaderID
  unsigned int shaderID = glCreateProgram();
  glAttachShader(shaderID, vertexShader);
  glAttachShader(shaderID, fragmentShader);
  glLinkProgram(shaderID);


  GLint Result = GL_FALSE;
  int InfoLogLength;

  // Check the program
  glGetProgramiv(shaderID, GL_LINK_STATUS, &Result);
  glGetProgramiv(shaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
  if (InfoLogLength > 0)
  {
    std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
    glGetProgramInfoLog(shaderID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
    printf("%s\n", &ProgramErrorMessage[0]);
  }

  glDetachShader(shaderID, vertexShader);
  glDetachShader(shaderID, fragmentShader);

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  return {shaderID};
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

  return Framebuffer(ID, rbo, texture, width, height);
}
void RendererPlatform::BindFramebuffer(unsigned int ID)
{
  glBindFramebuffer(GL_FRAMEBUFFER, ID);
}

void RendererPlatform::DeleteTexture(unsigned int texture)
{
  glDeleteTextures(1, &texture);
}

void RendererPlatform::DeleteFramebuffer(unsigned int fbo, unsigned int rbo,
                                         unsigned int texture)
{
  glDeleteBuffers(1, &fbo);
  glDeleteRenderbuffers(1, &rbo);
  glDeleteTextures(1, &texture);
}

void RendererPlatform::TextureParameter()
{
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

Texture RendererPlatform::CreateTexture()
{
  unsigned int IDTexture;

  glGenTextures(1, &IDTexture);
  glBindTexture(GL_TEXTURE_2D, IDTexture);

  return {IDTexture};
}

void RendererPlatform::SetTextureImage2D(unsigned char *image, unsigned int nrChannels, unsigned int width, unsigned int height)
{
  if (nrChannels == 4)
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
  else
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);

  glGenerateMipmap(GL_TEXTURE_2D);
}