#include "Renderer/Shader.hpp"
#include "Renderer/RendererPlatform.hpp"

#include <fstream>
#include <sstream>

using namespace Renderer;

Shader::Shader(const unsigned int& _ID) : ID {_ID} {}

Shader::~Shader()
{
  //RendererPlatform::DeleteShader(ID);
}
void Shader::Use()
{
  RendererPlatform::UseShader(ID);
}
void Shader::SetMatrix4(const char *name, Maths::Matrix4 mat)
{
  RendererPlatform::SetMatrix4(ID, name, mat);
}

Shader Shader::LoadShader(const char* vertexPath, const char* fragmentPath)
{
    std::string VertexShaderCode;
    std::string FragmentShaderCode;

    // Read the Vertex Shader code from the file
    //std::string VertexShaderCode;
    std::ifstream VertexShaderStream(vertexPath, std::ios::in);
    if (VertexShaderStream.is_open())
    {
        std::stringstream sstr;
        sstr << VertexShaderStream.rdbuf();
        VertexShaderCode = sstr.str();
        VertexShaderStream.close();
    }
    else
    {
        printf("Impossible to open %s.\n", vertexPath);
        getchar();
        return {0};
    }

    // Read the Fragment Shader code from the file
    //std::string FragmentShaderCode;
    std::ifstream FragmentShaderStream(fragmentPath, std::ios::in);
    if (FragmentShaderStream.is_open())
    {
        std::stringstream sstr;
        sstr << FragmentShaderStream.rdbuf();
        FragmentShaderCode = sstr.str();
        FragmentShaderStream.close();
    }
    else
    {
        printf("Impossible to open %s.\n", fragmentPath);
        getchar();
        return {0};
    }

    std::cout << VertexShaderCode << std::endl;

    return RendererPlatform::CreateShader(VertexShaderCode.c_str(), FragmentShaderCode.c_str());

}
