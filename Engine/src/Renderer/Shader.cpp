#include "Renderer/Shader.hpp"
#include "Renderer/RendererPlatform.hpp"

using namespace Renderer;

Shader::Shader(const unsigned int& _ID) : ID {_ID} {}
Shader::Shader(const char* vertexShaderSource, const char* fragmentShaderSource):
ID{RendererPlatform::CreateProgramShader(vertexShaderSource, fragmentShaderSource)}{}
Shader::~Shader()
{
  RendererPlatform::DeleteShader(ID);
}
void Shader::Use()
{
  RendererPlatform::UseShader(ID);
}
void Shader::SetMatrix4(const char *name, Maths::Matrix4 mat)
{
  RendererPlatform::SetMatrix4(ID, name, mat);
}
