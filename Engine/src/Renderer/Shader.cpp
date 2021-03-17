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

void Shader::SetFloat(const char* name, float value)
{
  RendererPlatform::SetFloat(ID, name, value);
}

void Shader::SetMatrix4(const char *name, const Maths::Matrix4& mat)
{
  RendererPlatform::SetMatrix4(ID, name, mat);
}

void Shader::SetVector3f(const char* name, const Maths::Vector3f vec)
{
    RendererPlatform::SetVector3f(ID, name, vec);
}

void Shader::SetVector4f(const char* name, const Maths::Vector4f vec)
{
    RendererPlatform::SetVector4f(ID, name, vec);
}

void Shader::SetSampler(const char* name, int sampler)
{
    RendererPlatform::SetSampler(ID, name, sampler);
}

Shader Shader::LoadShader(const char* vertexPath, const char* fragmentPath)
{
    std::string VertexShaderCode;
    std::string FragmentShaderCode;

    // Read the Vertex Shader code from the file
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

    std::cout << FragmentShaderCode << std::endl;

    return RendererPlatform::CreateShader(VertexShaderCode.c_str(), FragmentShaderCode.c_str());

}

Shader Shader::LoadShader(const ShaderConstructData& shaderData)
{
  std::string FragmentShaderCode = "#version 330 core\n";
  if (shaderData.hasLight)
  {
    FragmentShaderCode += "#define NB_DIRECTIONAL_LIGHT " +
                          std::to_string(shaderData.nbDirectionalLight) + "\n";
    FragmentShaderCode += "#define NB_POINT_LIGHT " +
                          std::to_string(shaderData.nbPointLight) + "\n";
    FragmentShaderCode += "#define NB_SPOT_LIGHT " +
                          std::to_string(shaderData.nbSpotLight) + "\n";

    FragmentShaderCode +=
        LoadStringFromFile("../../Engine/Shader/FragmentLight/FragmentStartLight.fs");
  }
  else
  {
      FragmentShaderCode +=
              LoadStringFromFile("../../Engine/Shader/FragmentStart.fs");
  }

  FragmentShaderCode += CreateMaterial(shaderData);
  FragmentShaderCode += "uniform Material material;\n\n";
  FragmentShaderCode += CreateColorFunctions(shaderData);

  if (shaderData.hasLight)
  {
    FragmentShaderCode +=
        LoadStringFromFile("../../Engine/Shader/FragmentLight/FragmentBasicLight.fs");
    FragmentShaderCode += LoadStringFromFile(
        "../../Engine/Shader/FragmentLight/FragmentMainLight.fs");
  }
  else
    FragmentShaderCode += LoadStringFromFile("../../Engine/Shader/FragmentMain.fs");

  std::cout << FragmentShaderCode << std::endl;


  // Read the Vertex Shader code from the file
  std::string VertexShaderCode = LoadStringFromFile("../../Engine/Shader/vertex.vs");


  return RendererPlatform::CreateShader(VertexShaderCode.c_str(), FragmentShaderCode.c_str());

}

std::string Shader::CreateMaterial(const ShaderConstructData& shaderData)
{
  std::string frag;

    frag += "struct Material \n{\n  vec4 color;\n";

    if (shaderData.hasColorTexture)
      frag += "  sampler2D colorTexture;\n";
    
    if (shaderData.hasDiffuseTexture)
      frag += "  sampler2D diffuseTexture;\n";
    
    if (shaderData.hasSpecularTexture)
      frag += "  sampler2D specularTexture;\n";

    if (shaderData.hasNormalMap)
      frag += "  sampler2D normalMap;\n";

    frag += "  vec3 ambient;\n  vec3 diffuse;\n  vec3 specular;\n  float shininess;\n};\n\n";

  return frag;
}

std::string Shader::CreateColorFunctions(const ShaderConstructData& shaderData)
{
  std::string frag;

  if (shaderData.hasColorTexture)
    frag += LoadStringFromFile("../../Engine/Shader/FragmentColor/FragmentTextureColor.fs");
  else
    frag += LoadStringFromFile("../../Engine/Shader/FragmentColor/FragmentColor.fs");

  if (shaderData.hasDiffuseTexture)
    frag += LoadStringFromFile("../../Engine/Shader/FragmentLight/Texture/FragmentAmbientDiffuseColor.fs");
  else
    frag += LoadStringFromFile("../../Engine/Shader/FragmentLight/Color/FragmentAmbientDiffuseColor.fs");

  if (shaderData.hasSpecularTexture)
    frag += LoadStringFromFile("../../Engine/Shader/FragmentLight/Texture/FragmentSpecularColor.fs");
  else
    frag += LoadStringFromFile("../../Engine/Shader/FragmentLight/Color/FragmentSpecularColor.fs");

    return frag;
}

std::string Shader::LoadStringFromFile(const char* path)
{
    std::string fileData;
    std::ifstream fileStream(path, std::ios::in);
    if (fileStream.is_open())
    {
        std::stringstream sstr;
        sstr << fileStream.rdbuf();
        fileData = sstr.str() + '\n';
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