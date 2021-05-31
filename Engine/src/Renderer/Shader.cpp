#include "Renderer/Shader.hpp"
#include "Scene/Component/Light.hpp"
#include "Renderer/RendererPlatform.hpp"

#include "Debug/Assertion.hpp"

#include <fstream>
#include <sstream>
#include "Debug/Log.hpp"

using namespace Renderer;
using namespace Component;

Shader::Shader() : Resources::Asset(Resources::AssetType::A_SHADER)
{}

Shader::Shader(unsigned int id) : Resources::Asset(Resources::AssetType::A_SHADER), _id{id}
{}


unsigned int Shader::GetID() const
{
    return _id;
}

void Shader::Use() const
{
    RendererPlatform::UseShader(_id);
}

void Shader::SetFloat(const char *name, float value) const
{
    RendererPlatform::SetFloat(_id, name, value);
}

void Shader::SetMatrix4(const char *name, const Maths::Matrix4 &mat) const
{
    RendererPlatform::SetMatrix4(_id, name, mat);
}

void Shader::SetVector3f(const char *name, const Maths::Vector3f &vec) const
{
    RendererPlatform::SetVector3f(_id, name, vec);
}

void Shader::SetVector4f(const char *name, const Maths::Vector4f &vec) const
{
    RendererPlatform::SetVector4f(_id, name, vec);
}

void Shader::SetUint(const char *name, unsigned int value) const
{
    RendererPlatform::SetUint(_id, name, value);
}

void Shader::SetSampler(const char *name, int sampler) const
{
    RendererPlatform::SetSampler(_id, name, sampler);
}

void Shader::SetLight(const Component::Light &light, unsigned int index) const
{
    switch (light.type)
    {
        case LightType::L_DIRECTIONAL :
            return RendererPlatform::SetDirectionalLight(_id, index, light);
        case LightType::L_SPOT :
            return RendererPlatform::SetSpotLight(_id, index, light);
        default :
            return RendererPlatform::SetPointLight(_id, index, light);
    }
}

void Shader::SetPointLight(const Component::Light &light, unsigned int index) const
{
    RendererPlatform::SetPointLight(_id, index, light);
}

void Shader::SetDirectionalLight(const Component::Light &light, unsigned int index) const
{
    RendererPlatform::SetDirectionalLight(_id, index, light);
}

void Shader::SetSpotLight(const Component::Light &light, unsigned int index) const
{
    RendererPlatform::SetSpotLight(_id, index, light);
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
        Log_Error("[Shader] Impossible to open {}", vertexPath.string());
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
        Log_Error("[Shader] Impossible to open {}", fragmentPath.string());
        return Shader{0};
    }

    //std::cout << VertexShaderCode << std::endl;

    return RendererPlatform::CreateShader(VertexShaderCode.c_str(), FragmentShaderCode.c_str());

}

Shader Shader::LoadShader(const char *path)
{
    std::string vertexShaderCode("#version 330 core\n#define VERTEX_SHADER\n");
    std::string fragmentShaderCode("#version 330 core\n#define FRAGMENT_SHADER\n");

    // Read the Shader code from the file
    std::ifstream shaderStream(path, std::ios::in);
    if (!shaderStream.is_open())
    {
        printf("Impossible to open %s.\n", path);
        getchar();
        return Shader{0};
    }

    std::stringstream sstr;
    sstr << shaderStream.rdbuf();


    vertexShaderCode += sstr.str();
    fragmentShaderCode += sstr.str();

    shaderStream.close();

    //std::cout << vertexShaderCode << std::endl;
    //std::cout << fragmentShaderCode << std::endl;

    return RendererPlatform::CreateShader(vertexShaderCode.c_str(), fragmentShaderCode.c_str());
}

Shader Shader::LoadObjectShader(const ShaderConstructData &shaderData)
{
    std::string vertexShaderCode = "#version 460 core\n";

    if (shaderData.hasLight)
        vertexShaderCode += "#define LIGHT\n";

    if (shaderData.hasSkeleton)
        vertexShaderCode += "#define SKELETON\n";
    else if (shaderData.hasNormalMap)
        vertexShaderCode += "#define NORMALMAP\n";

    vertexShaderCode += LoadStringFromFile("./Shader/Object/ObjectVertex.vs");

    std::string fragmentShaderCode = "#version 460 core\n";
    if (shaderData.hasLight)
    {
        fragmentShaderCode += "#define NB_MAX_DIRECTIONAL_LIGHT " +
                              std::to_string(MAX_DIRECTIONAL_LIGHT_NB) + "\n";
        fragmentShaderCode += "#define NB_MAX_POINT_LIGHT " +
                              std::to_string(MAX_POINT_LIGHT_NB) + "\n";
        fragmentShaderCode += "#define NB_MAX_SPOT_LIGHT " +
                              std::to_string(MAX_SPOT_LIGHT_NB) + "\n";

        fragmentShaderCode += "#define LIGHT\n";
        if (shaderData.hasNormalMap)
        {
            fragmentShaderCode += "#define NORMALMAP\n";
        }

        if (shaderData.hasDiffuseTexture)
            fragmentShaderCode += "#define TEXTUREDIFFUSE\n";

        if (shaderData.hasSpecularTexture)
            fragmentShaderCode += "#define TEXTURESPECULAR\n";
    }
    if (shaderData.hasColorTexture)
        fragmentShaderCode += "#define TEXTURECOLOR\n";

    fragmentShaderCode += LoadStringFromFile("./Shader/Object/ObjectFragment.fs");

    return RendererPlatform::CreateShader(vertexShaderCode.c_str(), fragmentShaderCode.c_str());

}

std::string Shader::LoadStringFromFile(const std::filesystem::path &path)
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