#include "Renderer/Shader.hpp"
#include "Scene/Component/Light.hpp"
#include "Renderer/RendererPlatform.hpp"

#include "Debug/Assertion.hpp"

#include <fstream>
#include <sstream>
#include <fmt/core.h>
#include <fmt/color.h>

using namespace Renderer;
using namespace Component;

Shader::Shader(unsigned int id) : ID {id} {}


unsigned int Shader::GetID() const
{
  return ID;
}

void Shader::Use() const
{
  RendererPlatform::UseShader(ID);
}

void Shader::SetFloat(const char* name, float value) const
{
  RendererPlatform::SetFloat(ID, name, value);
}

void Shader::SetMatrix4(const char *name, const Maths::Matrix4& mat) const
{
  RendererPlatform::SetMatrix4(ID, name, mat);
}

void Shader::SetVector3f(const char* name, const Maths::Vector3f& vec) const
{
    RendererPlatform::SetVector3f(ID, name, vec);
}

void Shader::SetVector4f(const char* name, const Maths::Vector4f& vec) const
{
    RendererPlatform::SetVector4f(ID, name, vec);
}

void Shader::SetUint(const char *name, unsigned int value) const
{
    RendererPlatform::SetUint(ID, name, value);
}

void Shader::SetSampler(const char* name, int sampler) const
{
    RendererPlatform::SetSampler(ID, name, sampler);
}

void Shader::SetLight(const Component::Light& light, unsigned int index) const
{
  switch (light.type) 
  {
    case Light_Type::L_DIRECTIONAL : return RendererPlatform::SetDirectionalLight(ID, index, light);
    case Light_Type::L_SPOT : return RendererPlatform::SetSpotLight(ID, index, light);
    default : return RendererPlatform::SetPointLight(ID, index, light);
  }
}

void Shader::SetPointLight(const Component::Light &light, unsigned int index) const
{
    RendererPlatform::SetPointLight(ID, index, light);
}

void Shader::SetDirectionalLight(const Component::Light &light, unsigned int index) const
{
    RendererPlatform::SetDirectionalLight(ID, index, light);
}

void Shader::SetSpotLight(const Component::Light &light, unsigned int index) const
{
    RendererPlatform::SetSpotLight(ID, index, light);
}

Shader Shader::LoadShader(const std::filesystem::path &vertexPath, const std::filesystem::path &fragmentPath)
{
    std::string VertexShaderCode;
    std::string FragmentShaderCode;

    // Read the Vertex Shader code from the file
    std::ifstream vertexShaderStream(vertexPath, std::ios::in);
    if (vertexShaderStream.is_open())
    {
        std::stringstream sstr;
        sstr << vertexShaderStream.rdbuf();
        VertexShaderCode = sstr.str();
        vertexShaderStream.close();
    }
    else
    {
        fmt::print(fg(fmt::color::red),"[Shader] Impossible to open {}\n",vertexPath.string());
        return Shader{0};
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
        fmt::print(fg(fmt::color::red),"[Shader] Impossible to open {}\n",fragmentPath.string());
        return Shader{0};
    }

    //std::cout << VertexShaderCode << std::endl;

    return RendererPlatform::CreateShader(VertexShaderCode.c_str(), FragmentShaderCode.c_str());

}

Shader Shader::LoadObjectShader(const ShaderConstructData& shaderData)
{
    std::string vertexShaderCode;

    // Read the Vertex Shader code from the file
    if (shaderData.hasNormalMap)
    {
        vertexShaderCode = LoadStringFromFile("../../Engine/Shader/Object/Light/VertexNormalMap.vs");
    }
    else
    {
        if (shaderData.hasSkeleton)
            vertexShaderCode = LoadStringFromFile("../../Engine/Shader/Object/Skeletal/SkeletalVertex.vs");
        else
            vertexShaderCode = LoadStringFromFile("../../Engine/Shader/Object/Base/Vertex.vs");
    }


    std::string fragmentShaderCode = "#version 330 core\n";
  if (shaderData.hasLight)
  {
      fragmentShaderCode += "#define NB_MAX_DIRECTIONAL_LIGHT " +
                            std::to_string(MAX_DIRECTIONAL_LIGHT_NB) + "\n";
      fragmentShaderCode += "#define NB_MAX_POINT_LIGHT " +
                            std::to_string(MAX_POINT_LIGHT_NB) + "\n";
      fragmentShaderCode += "#define NB_MAX_SPOT_LIGHT " +
                            std::to_string(MAX_SPOT_LIGHT_NB) + "\n";

      fragmentShaderCode +=
        LoadStringFromFile("../../Engine/Shader/Object/Light/FragmentStartLight.fs");
  }
  else
  {
      fragmentShaderCode +=
              LoadStringFromFile("../../Engine/Shader/Object/Base/FragmentStart.fs");
  }

    fragmentShaderCode += CreateMaterial(shaderData);
    fragmentShaderCode += "uniform Material material;\n\n";
    fragmentShaderCode += CreateColorFunctions(shaderData);

  if (shaderData.hasLight)
  {
    if (shaderData.hasNormalMap)
    {
        fragmentShaderCode +=
          LoadStringFromFile("../../Engine/Shader/Object/Light/FragmentNormalMapLight.fs");
        fragmentShaderCode += LoadStringFromFile(
          "../../Engine/Shader/Object/Light/FragmentMainLightNormal.fs");
    }
    else
    {
        fragmentShaderCode +=
          LoadStringFromFile("../../Engine/Shader/Object/Light/FragmentBasicLight.fs");
        fragmentShaderCode += LoadStringFromFile(
          "../../Engine/Shader/Object/Light/FragmentMainLight.fs");
    }
  }
  else
      fragmentShaderCode += LoadStringFromFile("../../Engine/Shader/Object/Base/FragmentMain.fs");

  //std::cout << FragmentShaderCode << std::endl;

  return RendererPlatform::CreateShader(vertexShaderCode.c_str(), fragmentShaderCode.c_str());

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

std::string Shader::LoadStringFromFile(const std::filesystem::path& path)
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
        Assert_Error(true, (std::string("Impossible to open %s.\n") + path.string()).c_str());
        return {0};
    }
    return fileData;
}