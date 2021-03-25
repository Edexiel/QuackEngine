#ifndef _SHADER_
#define _SHADER_

#include "Maths/Matrix4.hpp"

namespace Renderer
{
    class Light;

    struct ShaderConstructData
    {
      bool hasLight {false};

      unsigned int nbPointLight       {0};
      unsigned int nbDirectionalLight {0};
      unsigned int nbSpotLight        {0};

      bool hasColorTexture;
      bool hasDiffuseTexture;
      bool hasSpecularTexture;

      bool hasNormalMap;

      unsigned int GetKey() const
      {
        return hasLight + nbPointLight * 10 + hasColorTexture * 100 + nbDirectionalLight * 1000 + hasDiffuseTexture * 10000 + hasSpecularTexture * 100000 + nbSpotLight * 1000000 + hasNormalMap * 10000000;
      };
    };

    class Shader
    {
      unsigned int _ID;

      public:

        Shader() = default;
        Shader(unsigned int ID);
        ~Shader();

        unsigned int GetID() const;
        void Use();
        void SetFloat(const char* name, float value);
        void SetMatrix4(const char* name, const Maths::Matrix4& mat);
        void SetVector3f(const char* name, const Maths::Vector3f vec);
        void SetVector4f(const char* name, const Maths::Vector4f vec);
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