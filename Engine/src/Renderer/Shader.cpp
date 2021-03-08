#include "glad/gl.h"
#include "GLFW/glfw3.h"

#include "Renderer/Shader.hpp"
#include "Renderer/RendererPlatform.hpp"

using namespace Renderer;

Shader::Shader(const unsigned int& _ID) : ID {_ID} {}
Shader::Shader(const char* vertexShaderSource, const char* fragmentShaderSource):
ID{RendererPlatform::CreateProgramShader(vertexShaderSource, fragmentShaderSource)}{}