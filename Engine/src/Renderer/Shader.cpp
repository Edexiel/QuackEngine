#include "Renderer/Shader.hpp"
#include "Scene/Component/Light.hpp"
#include "Renderer/RendererPlatform.hpp"

#include "Debug/Assertion.hpp"

#include <fstream>
#include <sstream>

using namespace Renderer;
using namespace Component;

Shader::Shader(unsigned int ID) : _ID {ID} {}

Shader::~Shader()
{
  //RendererPlatform::DeleteShader(_ID);
}

unsigned int Shader::GetID() const
{
  return _ID;
}

void Shader::Use()
{
  RendererPlatform::UseShader(_ID);
}

void Shader::SetFloat(const char* name, float value)
{
  RendererPlatform::SetFloat(_ID, name, value);
}

void Shader::SetMatrix4(const char *name, const Maths::Matrix4& mat)
{
  RendererPlatform::SetMatrix4(_ID, name, mat);
}

void Shader::SetVector3f(const char* name, const Maths::Vector3f& vec)
{
    RendererPlatform::SetVector3f(_ID, name, vec);
}

void Shader::SetVector4f(const char* name, const Maths::Vector4f& vec)
{
    RendererPlatform::SetVector4f(_ID, name, vec);
}

void Shader::SetUint(const char *name, unsigned int value)
{
    RendererPlatform::SetUint(_ID, name, value);
}

void Shader::SetSampler(const char* name, int sampler)
{
    RendererPlatform::SetSampler(_ID, name, sampler);
}

void Shader::SetLight(Component::Light& light, unsigned int index)
{
  switch (light.type) 
  {
    case Light_Type::L_DIRECTIONAL : return RendererPlatform::SetDirectionalLight(_ID, index, light);
    case Light_Type::L_SPOT : return RendererPlatform::SetSpotLight(_ID, index, light);
    default : return RendererPlatform::SetPointLight(_ID, index, light);
  }
}

void Shader::SetPointLight(Component::Light &light, unsigned int index)
{
    RendererPlatform::SetPointLight(_ID, index, light);
}

void Shader::SetDirectionalLight(Component::Light &light, unsigned int index)
{
    RendererPlatform::SetDirectionalLight(_ID, index, light);
}

void Shader::SetSpotLight(Component::Light &light, unsigned int index)
{
    RendererPlatform::SetSpotLight(_ID, index, light);
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

    //std::cout << VertexShaderCode << std::endl;

    return RendererPlatform::CreateShader(VertexShaderCode.c_str(), FragmentShaderCode.c_str());

}

Shader Shader::LoadObjectShader(const ShaderConstructData& shaderData)
{
  std::string FragmentShaderCode = "#version 330 core\n";
  if (shaderData.hasLight)
  {
    FragmentShaderCode += "#define NB_MAX_DIRECTIONAL_LIGHT " +
                          std::to_string(MAX_DIRECTIONAL_LIGHT_NB) + "\n";
    FragmentShaderCode += "#define NB_MAX_POINT_LIGHT " +
                          std::to_string(MAX_POINT_LIGHT_NB) + "\n";
    FragmentShaderCode += "#define NB_MAX_SPOT_LIGHT " +
                          std::to_string(MAX_SPOT_LIGHT_NB) + "\n";

    FragmentShaderCode +=
        LoadStringFromFile("../../Engine/Shader/Object/Light/FragmentStartLight.fs");
  }
  else
  {
      FragmentShaderCode +=
              LoadStringFromFile("../../Engine/Shader/Object/Base/FragmentStart.fs");
  }

  FragmentShaderCode += CreateMaterial(shaderData);
  FragmentShaderCode += "uniform Material material;\n\n";
  FragmentShaderCode += CreateColorFunctions(shaderData);

  if (shaderData.hasLight)
  {
    if (shaderData.hasNormalMap)
    {
      FragmentShaderCode +=
          LoadStringFromFile("../../Engine/Shader/Object/Light/FragmentNormalMapLight.fs");
      FragmentShaderCode += LoadStringFromFile(
          "../../Engine/Shader/Object/Light/FragmentMainLightNormal.fs");
    }
    else
    {
      FragmentShaderCode +=
          LoadStringFromFile("../../Engine/Shader/Object/Light/FragmentBasicLight.fs");
      FragmentShaderCode += LoadStringFromFile(
          "../../Engine/Shader/Object/Light/FragmentMainLight.fs");
    }
  }
  else
    FragmentShaderCode += LoadStringFromFile("../../Engine/Shader/Object/Base/FragmentMain.fs");

  //std::cout << FragmentShaderCode << std::endl;


  std::string VertexShaderCode;

  // Read the Vertex Shader code from the file
  if (shaderData.hasNormalMap)
    VertexShaderCode = LoadStringFromFile("../../Engine/Shader/Object/Light/vertexNormalMap.vs");
  else
    VertexShaderCode = LoadStringFromFile("../../Engine/Shader/Object/Base/Vertex.vs");


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
    frag += LoadStringFromFile("../../Engine/Shader/Object/FragmentColor/FragmentTextureColor.fs");
  else
    frag += LoadStringFromFile("../../Engine/Shader/Object/FragmentColor/FragmentColor.fs");

  if (shaderData.hasLight)
  {
      if (shaderData.hasDiffuseTexture)
          frag += LoadStringFromFile("../../Engine/Shader/Object/Light/Texture/FragmentAmbientDiffuseColor.fs");
      else
          frag += LoadStringFromFile("../../Engine/Shader/Object/Light/Color/FragmentAmbientDiffuseColor.fs");

      if (shaderData.hasSpecularTexture)
          frag += LoadStringFromFile("../../Engine/Shader/Object/Light/Texture/FragmentSpecularColor.fs");
      else
          frag += LoadStringFromFile("../../Engine/Shader/Object/Light/Color/FragmentSpecularColor.fs");
  }
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
        return {0};
    }
    return fileData;
}