#ifndef _SHADER_
#define _SHADER_

#include "Maths/Matrix4.hpp"

namespace Renderer
{
    class Light;

    struct ShaderConstructData
    {
      bool hasLight {false};

      bool hasColorTexture;
      bool hasDiffuseTexture;
      bool hasSpecularTexture;

      bool hasNormalMap;

      unsigned int GetKey() const
      {
        return hasLight + hasColorTexture * 10 + hasDiffuseTexture * 100 + hasSpecularTexture * 1000 + hasNormalMap * 10000;
      };
    };

    class Shader
    {
        unsigned int _ID;

      public:
        Shader() = default;
        Shader(const unsigned int& _ID);
        ~Shader();

        unsigned int GetID() const;

        void Use();
        void SetFloat(const char* name, float value);
        void SetMatrix4(const char* name, const Maths::Matrix4& mat);
        void SetVector3f(const char* name, const Maths::Vector3f vec);
        void SetVector4f(const char* name, const Maths::Vector4f vec);
        void SetUint(const char* name, unsigned int value);
        void SetSampler(const char* name, int sampler);
        void SetLight(const Light& light, unsigned int index);

        static Shader LoadShader(const char* vertexPath, const char* fragmentPath);
        static Shader LoadShader(const ShaderConstructData& shaderData);

      private:
        static std::string CreateMaterial(const ShaderConstructData& shaderData);
        static std::string CreateColorFunctions(const ShaderConstructData& shaderData);
        static std::string LoadStringFromFile(const char* path);
    };
}

#endif //_SHADER_