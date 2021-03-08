#include "glad/gl.h"
#include "Renderer/Framebuffer.hpp"
#include "Renderer/Shader.hpp"

const char* vertexShader = R"GLSL(
                          #version 330 core
                          layout (location = 0) in vec3 aPos;
                          layout (location = 1) in vec2 aTexCoord;
                          layout (location = 2) in vec3 aNormal;

                          out vec2 TexCoord;

                          void main()
                          {
                            gl_Position =vec4(aPos, 1.0);
                            TexCoord = aTexCoord;
                          }
                   )GLSL";
const char* fragmentShader = R"GLSL(
                     #version 330 core
                     out vec4 FragColor;
                     in vec2 TexCoord;

                     uniform sampler2D ourTexture;

                     void main()
                     {
                      FragColor = texture(ourTexture, TexCoord);
                     }
                     )GLSL";

using namespace Renderer;

Framebuffer::Framebuffer(const unsigned int width, const unsigned int height)
{
  _shaderProgram = Shader::CreateProgramShader(vertexShader, fragmentShader);

  glGenFramebuffers(1, &_ID);
  glBindFramebuffer(GL_FRAMEBUFFER, _ID);

  glGenTextures(1, &_texture);
  glBindTexture(GL_TEXTURE_2D, _texture);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _texture, 0);

  glGenRenderbuffers(1, &_rbo);
  glBindRenderbuffer(GL_RENDERBUFFER, _rbo);
  glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, width, height);
  glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, _rbo);

  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

unsigned int Renderer::Framebuffer::GetID() const
{
  return _ID;
}

void Renderer::Framebuffer::Delete()
{
  glDeleteBuffers(1, &_ID);
  glDeleteBuffers(1, &_texture);
  glDeleteBuffers(1, &_rbo);
  glDeleteProgram(_shaderProgram);
}
unsigned int Renderer::Framebuffer::GetTexture() const
{
  return _texture;
}
void Renderer::Framebuffer::BindFramebuffer()
{
  glBindFramebuffer(GL_FRAMEBUFFER, _ID);
}
void Framebuffer::UseProgram()
{
  glUseProgram(_shaderProgram);
}
void Framebuffer::UnbindFramebuffer()
{
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
