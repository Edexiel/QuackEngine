#include "Renderer/RendererPlatform.hpp"

#define _USE_MATH_DEFINES
#include <cmath>

#include <vector>

#include "glad/gl.h"
#include "GLFW/glfw3.h"

#include "Renderer/Vertex.hpp"
#include "Renderer/Framebuffer.hpp"

#include "Renderer/Mesh.hpp"
#include "Renderer/Shader.hpp"
#include "Renderer/Texture.hpp"
#include "Scene/Component/Light.hpp"

#include "Maths/Vector3.hpp"

#include "Debug/Assertion.hpp"

using namespace Renderer;
using namespace Component;

void RendererPlatform::CloseWindow()
{
    glfwTerminate();
}

int RendererPlatform::LoadGl()
{
  int version = gladLoadGL(glfwGetProcAddress);

  printf("GL_VENDOR = %s\n",   glGetString(GL_VENDOR));
  printf("GL_RENDERER = %s\n", glGetString(GL_RENDERER));
  printf("GL_VERSION = %s\n",  glGetString(GL_VERSION));

  return version;
}

void RendererPlatform::BindTexture(unsigned int texture, unsigned int index)
{
  glActiveTexture(GL_TEXTURE0 + index);
  glBindTexture(GL_TEXTURE_2D, (Gluint)texture);
}
void RendererPlatform::ClearColor(const Maths::Vector4f &color)
{
  glClearColor(color.r, color.g, color.b, color.a);
}

void RendererPlatform::Clear()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void RendererPlatform::EnableDepthBuffer(bool isEnable)
{
  if(isEnable)
  {
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
  }
  else
  {
    glDisable(GL_DEPTH_TEST);
    glDepthFunc(GL_ALWAYS);
  }
}

Mesh RendererPlatform::CreateMesh(const Vertex *vertices, unsigned int verticesSize, const unsigned int *indices, unsigned int indicesSize)
{
  unsigned int vao{0}, vbo{0};
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, verticesSize * sizeof(Vertex), vertices, GL_STATIC_DRAW);
  
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

  //VerticesReading();

  return Mesh(vao, vbo, ebo, verticesSize, indicesSize);
}

void RendererPlatform::DrawMesh(unsigned int vao, unsigned int vbo, unsigned int ebo, unsigned int nbIndices)
{
  glBindVertexArray(vao);

  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

  VerticesReading();

  glDrawElements(GL_TRIANGLES, nbIndices, GL_UNSIGNED_INT, (const void*)0);

}

void RendererPlatform::DrawMeshNormalMap(unsigned int vao, unsigned int vbo, unsigned int ebo, unsigned int nbIndices)
{
  glBindVertexArray(vao);

  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

  VerticesReadingNormalMapping();

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
  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
  glDisableVertexAttribArray(2);
  glDisableVertexAttribArray(3);
  glDisableVertexAttribArray(4);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)offsetof(Vertex, position));
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)offsetof(Vertex, normal));
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)offsetof(Vertex, uv));
  glEnableVertexAttribArray(2);
}

void RendererPlatform::VerticesReadingNormalMapping()
{
  //std::cout << sizeof(float) << std::endl;

  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
  glDisableVertexAttribArray(2);
  glDisableVertexAttribArray(3);
  glDisableVertexAttribArray(4);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (const GLvoid*)(0 * sizeof(float)));
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (const GLvoid*)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 14 * sizeof(float) , (const GLvoid*)(6 * sizeof(float)));
  glEnableVertexAttribArray(2);
  glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (const GLvoid*)(8 * sizeof(float)));
  glEnableVertexAttribArray(3);
  glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (const GLvoid*)(11 * sizeof(float)));
  glEnableVertexAttribArray(4);
}


void RendererPlatform::UseShader(unsigned int shaderProgram)
{
  glUseProgram(shaderProgram);
}

void RendererPlatform::DeleteShader(unsigned int shaderProgram)
{
  glDeleteProgram(shaderProgram);
}

void RendererPlatform::SetFloat(unsigned int shaderProgram, const char* name, float value)
{
  glUniform1f(glGetUniformLocation(shaderProgram, name), value);
}

void RendererPlatform::SetMatrix4(unsigned int shaderProgram, const char *name,
                                  const Maths::Matrix4 &mat)
{
  glUniformMatrix4fv(glGetUniformLocation(shaderProgram, name),1, GL_FALSE, mat.e);
}

void RendererPlatform::SetVector3f(unsigned int shaderProgram, const char* name, const Maths::Vector3f& vec)
{
  glUniform3fv(glGetUniformLocation(shaderProgram, name), 1, vec.e);
}

void RendererPlatform::SetVector4f(unsigned int shaderProgram, const char* name, const Maths::Vector4f& vec)
{
  glUniform4fv(glGetUniformLocation(shaderProgram, name), 1, vec.e);
}

void RendererPlatform::SetUint(unsigned int shaderProgram, const char* name, unsigned int value)
{
    glUniform1ui(glGetUniformLocation(shaderProgram, name), value);
}

void RendererPlatform::SetSampler(unsigned int shaderProgram, const char* name, int value)
{
  glUniform1i(glGetUniformLocation(shaderProgram, name), value);
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


void RendererPlatform::SetSpotLight(unsigned int shaderID, unsigned int index, Component::Light& light)
{
    std::string set             = "spotLights[" + std::to_string(index);

    int location = glGetUniformLocation(shaderID, (set + "].position").c_str());
    glUniform3f(location, light.position.x, light.position.y, light.position.z);

    location = glGetUniformLocation(shaderID, (set + "].direction").c_str());
    glUniform3f(location, light.direction.x, light.direction.y, light.direction.z);

    location = glGetUniformLocation(shaderID, (set + "].ambient").c_str());
    glUniform3f(location, light.ambient.x, light.ambient.y, light.ambient.z);

    location = glGetUniformLocation(shaderID, (set + "].diffuse").c_str());
    glUniform3f(location, light.diffuse.x, light.diffuse.y, light.diffuse.z);

    location = glGetUniformLocation(shaderID, (set + "].specular").c_str());
    glUniform3f(location, light.specular.x, light.specular.y, light.specular.z);

    location = glGetUniformLocation(shaderID, (set + "].spotAngle").c_str());
    glUniform1f(location, light.spotAngle);

    location = glGetUniformLocation(shaderID, (set + "].outerSpotAngle").c_str());
    glUniform1f(location, light.outerSpotAngle);

    location = glGetUniformLocation(shaderID, (set + "].constant").c_str());
    glUniform1f(location, light.constant);

    location = glGetUniformLocation(shaderID, (set + "].linear").c_str());
    glUniform1f(location, light.linear);

    location = glGetUniformLocation(shaderID, (set + "].quadratic").c_str());
    glUniform1f(location, light.quadratic);
}

void RendererPlatform::SetDirectionalLight(unsigned int shaderID, unsigned int index, Component::Light &light)
{
  std::string set = "directionalLights[" + std::to_string(index);

  int location = glGetUniformLocation(shaderID, (set + "].direction").c_str());
  glUniform3f(location, light.direction.x, light.direction.y, light.direction.z);

  location = glGetUniformLocation(shaderID, (set + "].ambient").c_str());
  glUniform3f(location, light.ambient.x, light.ambient.y, light.ambient.z);

  location = glGetUniformLocation(shaderID, (set + "].diffuse").c_str());
  glUniform3f(location, light.diffuse.x, light.diffuse.y, light.diffuse.z);

  location = glGetUniformLocation(shaderID, (set + "].specular").c_str());
  glUniform3f(location, light.specular.x, light.specular.y, light.specular.z);

}

void RendererPlatform::SetPointLight(unsigned int shaderID, unsigned int index, Light &light)
{
  std::string set  = "pointLights[" + std::to_string(index);

  int location = glGetUniformLocation(shaderID, (set + "].position").c_str());
  glUniform3f(location, light.position.x, light.position.y, light.position.z);

  location = glGetUniformLocation(shaderID, (set + "].ambient").c_str());
  glUniform3f(location, light.ambient.x, light.ambient.y, light.ambient.z);

  location = glGetUniformLocation(shaderID, (set + "].diffuse").c_str());
  glUniform3f(location, light.diffuse.x, light.diffuse.y, light.diffuse.z);

  location = glGetUniformLocation(shaderID, (set + "].specular").c_str());
  glUniform3f(location, light.specular.x, light.specular.y, light.specular.z);

  location = glGetUniformLocation(shaderID, (set + "].constant").c_str());
  glUniform1f(location, light.constant);

  location = glGetUniformLocation(shaderID, (set + "].linear").c_str());
  glUniform1f(location, light.linear);

  location = glGetUniformLocation(shaderID, (set + "].quadratic").c_str());
  glUniform1f(location, light.quadratic);

}
Mesh RendererPlatform::CreateQuad()
{
  const Vertex vertices[4]{
      // positions          // texture coords
      {{1.0f, 1.0f, 0.0f}, {0, 0, -1}, {1.0f, 1.0f}},   // top right
      {{1.0f, -1.0f, 0.0f}, {0, 0, -1}, {1.0f, 0.0f}},  // bottom right
      {{-1.0f, -1.0f, 0.0f}, {0, 0, -1}, {0.0f, 0.0f}}, // bottom left
      {{-1.0f, 1.0f, 0.0f}, {0, 0, -1}, {0.0f, 1.0f}}   // top left
  };

  unsigned int indices[6]{
      0, 1, 3, // first triangle
      1, 2, 3  // second triangle
  };
  return CreateMesh(vertices, 4, indices, 6);
}
Mesh RendererPlatform::CreateCube()
{
  const Vertex vertices[] {
    //Front
    {{1.0f, 1.0f, -1.0f}, {0, 0, -1}, {1.0f, 1.0f}},//0
    {{1.0f, -1.0f, -1.0f}, {0, 0, -1}, {1.0f, 0.0f}},//1
    {{-1.0f, -1.0f, -1.0f}, {0, 0, -1}, {0.0f, 0.0f}},//2
    {{-1.0f, 1.0f, -1.0f}, {0, 0, -1}, { 0.0f, 1.0f}},//3

    //Back
    {{1.0f, 1.0f, 1.0f}, {0, 0, 1}, {1.0f, 1.0f}},//4
    {{1.0f, -1.0f, 1.0f}, {0, 0, 1}, {1.0f, 0.0f}},//5
    {{-1.0f, -1.0f, 1.0f}, {0, 0, 1}, {0.0f, 0.0f}},//6
    {{-1.0f, 1.0f, 1.0f}, {0, 0, 1}, { 0.0f, 1.0f }},//7

    //Left
    {{-1.0f, 1.0f, 1.0f}, {-1, 0, 0}, {1.0f, 1.0f}},//8
    {{-1.0f, 1.0f, -1.0f}, {-1, 0, 0}, {1.0f, 0.0f}},//9
    {{-1.0f, -1.0f, -1.0f}, {-1, 0, 0}, {0.0f, 0.0f}},//10
    {{-1.0f, -1.0f, 1.0f}, {-1, 0, 0}, { 0.0f, 1.0f }},//11

    //Right
    {{1.0f, 1.0f, 1.0f}, {1, 0, 0}, {1.0f, 1.0f}},//12
    {{1.0f, 1.0f, -1.0f}, {1, 0, 0}, {1.0f, 0.0f}},//13
    {{1.0f, -1.0f, -1.0f}, {1, 0, 0}, {0.0f, 0.0f}},//14
    {{1.0f, -1.0f, 1.0f}, {1, 0, 0}, { 0.0f, 1.0f }},//15

    //Top
    {{1.0f, 1.0f, 1.0f}, {0, 1, 0}, {1.0f, 1.0f}},//16
    {{1.0f, 1.0f, -1.0f}, {0, 1, 0}, {1.0f, 0.0f}},//17
    {{-1.0f, 1.0f, -1.0f}, {0, 1, 0}, {0.0f, 0.0f}},//18
    {{-1.0f, 1.0f, 1.0f}, {0, 1, 0}, { 0.0f, 1.0f }},//19

    //Down
    {{1.0f, -1.0f, 1.0f}, {0, -1, 0}, {1.0f, 1.0f}},//20
    {{1.0f, -1.0f, -1.0f}, {0, -1, 0}, {1.0f, 0.0f}},//21
    {{-1.0f, -1.0f, -1.0f}, {0, -1, 0}, {0.0f, 0.0f}},//22
    {{-1.0f, -1.0f, 1.0f}, {0, -1, 0}, { 0.0f, 1.0f }}//23
  };
  const unsigned int indices[]{
      //Back
      0, 1, 3,
      1, 2, 3,
      //Front
      4, 5, 7,
      5, 6, 7,
      //Left
      8, 9, 11,
      9, 10, 11,
      //Right
      12, 13, 15,
      13, 14, 15,
      //Top
      16, 17, 19,
      17, 18, 19,
      //Down
      20, 21, 23,
      21, 22, 23
      };

  return CreateMesh(vertices, sizeof (vertices)/sizeof (vertices[0]), indices, sizeof(indices)/sizeof(indices[0]));
}
Mesh RendererPlatform::CreateSphere(int sectorCount, int stackCount)
{
  std::vector<Vertex> vertices;
  std::vector<unsigned int> indices;

  float sectorStep = 2 * (float)M_PI / (float)sectorCount;
  float stackStep = (float)M_PI / (float)stackCount;
  float sectorAngle, stackAngle;

  //Vertices
  for(int i = 0; i <= stackCount; ++i)
  {
    stackAngle = (float)M_PI / 2.f - (float)i * stackStep; // starting from pi/2 to -pi/2
    float xy = cosf(stackAngle);           // r * cos(u)
    float z = sinf(stackAngle);            // r * sin(u)

    for (int j = 0; j <= sectorCount; ++j)
    {
      sectorAngle = (float)j * sectorStep; // starting from 0 to 2pi

      float x = xy * cosf(sectorAngle);
      float y = xy * sinf(sectorAngle);

      vertices.push_back({{x, y, z}, {x, y, z},{(float)j / (float)sectorCount, (float)i / (float)stackCount}});
    }
  }

  //Indices
  unsigned int k1, k2;
  for(int i = 0; i < stackCount; ++i)
  {
    k1 = i * (sectorCount + 1);
    k2 = k1 + sectorCount + 1;

    for(int j = 0; j < sectorCount; ++j, ++k1, ++k2)
    {
      // 2 triangles per sector excluding 1st and last stacks
      if(i != 0)
      {
        indices.push_back(k1);
        indices.push_back(k2);
        indices.push_back(k1+1);
      }

      if(i != (stackCount-1))
      {
        indices.push_back(k1+1);
        indices.push_back(k2);
        indices.push_back(k2+1);
      }
    }
  }

  return CreateMesh(vertices.data(), vertices.size(), indices.data(), indices.size());
}


