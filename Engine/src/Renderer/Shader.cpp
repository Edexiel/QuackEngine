#include "Renderer/Shader.hpp"
#include "Renderer/Light.hpp"
#include "Renderer/RendererPlatform.hpp"

#include "Debug/Assertion.hpp"

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

void Shader::SetLight(const Light& light, unsigned int index)
{
  switch (light.type) 
  {
    case Light_Type::L_DIRECTIONAL : return RendererPlatform::SetDirectionalLight(ID, index, light);
    case Light_Type::L_SPOT : return RendererPlatform::SetSpotLight(ID, index, light);
    default : return RendererPlatform::SetPointLight(ID, index, light);
  }
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
        LoadStringFromFile("../../Engine/Shader/Light/FragmentStartLight.fs");
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
    if (shaderData.hasNormalMap)
    {
      FragmentShaderCode +=
          LoadStringFromFile("../../Engine/Shader/Light/FragmentNormalMapLight.fs");
      FragmentShaderCode += LoadStringFromFile(
          "../../Engine/Shader/Light/FragmentMainLightNormal.fs");
    }
    else
    {
      FragmentShaderCode +=
          LoadStringFromFile("../../Engine/Shader/Light/FragmentBasicLight.fs");
      FragmentShaderCode += LoadStringFromFile(
          "../../Engine/Shader/Light/FragmentMainLight.fs");
    }
  }
  else
    FragmentShaderCode += LoadStringFromFile("../../Engine/Shader/Base/FragmentMain.fs");

  std::cout << FragmentShaderCode << std::endl;


  std::string VertexShaderCode;

  // Read the Vertex Shader code from the file
  if (shaderData.hasNormalMap)
    VertexShaderCode = LoadStringFromFile("../../Engine/Shader/Light/vertexNormalMap.vs");
  else
    VertexShaderCode = LoadStringFromFile("../../Engine/Shader/Base/Vertex.vs");


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
    frag += LoadStringFromFile("../../Engine/Shader/Light/Texture/FragmentAmbientDiffuseColor.fs");
  else
    frag += LoadStringFromFile("../../Engine/Shader/Light/Color/FragmentAmbientDiffuseColor.fs");

  if (shaderData.hasSpecularTexture)
    frag += LoadStringFromFile("../../Engine/Shader/Light/Texture/FragmentSpecularColor.fs");
  else
    frag += LoadStringFromFile("../../Engine/Shader/Light/Color/FragmentSpecularColor.fs");

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
        Assert_Error(true, (std::string("Impossible to open %s.\n") + path).c_str());
        getchar();
        return {0};
    }
    return fileData;
}