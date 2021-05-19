#ifndef _SHADER_
#define _SHADER_

#include "Maths/Matrix4.hpp"
#include <filesystem>


namespace Component
{
    class Light;
}

namespace Renderer
{
    struct ShaderConstructData
    {
        bool hasLight{false};
        bool hasColorTexture{false};
        bool hasDiffuseTexture{false};
        bool hasSpecularTexture{false};
        bool hasNormalMap{false};
        bool hasSkeleton{false};

        unsigned int GetKey() const
        {
            return hasLight + hasColorTexture * 10 + hasDiffuseTexture * 100 + hasSpecularTexture * 1000 +
                   hasNormalMap * 10000 + hasSkeleton * 100000;

            /* De rien
            std::uint8_t key;
            key |= hasLight << 1;
            key |= hasColorTexture << 2;
            key |= hasDiffuseTexture << 3;
            key |= hasSpecularTexture << 4;
            key |= hasNormalMap << 5;
            key |= hasSkeleton << 6;
             */
        };
    };

    class Shader
    {
        unsigned int ID{0};

    public:

        Shader() = default;
        explicit Shader(unsigned int id);
        ~Shader() = default;

        unsigned int GetID() const;
        void Use() const;
        void SetFloat(const char *name, float value) const;
        void SetMatrix4(const char *name, const Maths::Matrix4 &mat) const;
        void SetVector3f(const char *name, const Maths::Vector3f &vec) const;
        void SetVector4f(const char *name, const Maths::Vector4f &vec) const;
        void SetUint(const char *name, unsigned int value) const;
        void SetSampler(const char *name, int sampler) const;
        void SetLight(const Component::Light &light, unsigned int index) const;
        void SetPointLight(const Component::Light &light, unsigned int index) const;
        void SetDirectionalLight(const Component::Light &light, unsigned int index) const;
        void SetSpotLight(const Component::Light &light, unsigned int index) const;

        static Shader LoadShader(const std::filesystem::path &vertexShader, const std::filesystem::path &fragmentPath);
        static Shader LoadObjectShader(const ShaderConstructData &shaderData);

    private:
        static std::string CreateMaterial(const ShaderConstructData &shaderData);
        static std::string CreateColorFunctions(const ShaderConstructData &shaderData);
        static std::string LoadStringFromFile(const std::filesystem::path& path);
    };
}

#endif //_SHADER_