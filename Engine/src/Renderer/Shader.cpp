#include "../include/Renderer/Shader.hpp"
#include "glad/gl.h"
#include "GLFW/glfw3.h"

using namespace Renderer;

Shader::Shader(const unsigned int& _ID) : ID {_ID} {}
Shader::Shader(const char* vertexShaderSource, const char* fragmentShaderSource)
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
  ID = glCreateProgram();
  glAttachShader(ID, vertexShader);
  glAttachShader(ID, fragmentShader);
  glLinkProgram(ID);

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

}
unsigned int Shader::CreateProgramShader(const char* vertexShaderSource, const char* fragmentShaderSource)
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
