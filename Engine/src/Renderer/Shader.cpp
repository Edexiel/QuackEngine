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

    return RendererPlatform::CreateShader(VertexShaderCode.c_str(), FragmentShaderCode.c_str());

}

Shader Shader::LoadShader(const ShaderConstructData& shaderData)
{
  std::string FragmentShaderCode;

  FragmentShaderCode += LoadStringFromFile("../../Game/Asset/Shader/FragmentStart.fs");
  FragmentShaderCode += LoadStringFromFile("../../Game/Asset/Shader/FragmentBasicLight.fs");

  FragmentShaderCode += "void main()\n{\nvec3 fragmentColor = vec3(0,0,0);\n\n";


  for (int  i = 0; i < shaderData.nbDirectionalLight; i++ )
  {
    FragmentShaderCode += "fragmentColor += GetColorAfterDirectionalLight(directionalLights["+ std::to_string(i)  + "], vec3(Position), normalize(vec3(Normal)));\n";
  }
  for (int  i = 0; i < shaderData.nbPointLight; i++ )
  {
    FragmentShaderCode += "fragmentColor += GetColorAfterPointLight(pointLights["+ std::to_string(i)  + "], vec3(Position), normalize(vec3(Normal)));\n";
  }
  for (int  i = 0; i < shaderData.nbSpotLight; i++ )
  {
    FragmentShaderCode += "fragmentColor += GetColorAfterSpotLight(spotLights["+ std::to_string(i)  + "], vec3(Position), normalize(vec3(Normal)));\n";
  }

  FragmentShaderCode += "FragColor = texture(ourTexture, TexCoord) * vec4(fragmentColor, 1.f);\n}";

  std::cout << FragmentShaderCode << std::endl;


  // Read the Vertex Shader code from the file
  std::string VertexShaderCode = LoadStringFromFile("../../Game/Asset/Shader/vertex.vs");


  return RendererPlatform::CreateShader(VertexShaderCode.c_str(), FragmentShaderCode.c_str());

}

std::string Shader::LoadStringFromFile(const char* path)
{
    std::string fileData;
    std::ifstream fileStream(path, std::ios::in);
    if (fileStream.is_open())
    {
        std::stringstream sstr;
        sstr << fileStream.rdbuf();
        fileData = sstr.str();
        fileStream.close();
    }
    else
    {
        printf("Impossible to open %s.\n", path);
        getchar();
        return {0};
    }
    return fileData;
}