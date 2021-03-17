#ifndef _SHADER_
#define _SHADER_

#include "Maths/Matrix4.hpp"

namespace Renderer
{
    struct ShaderConstructData
    {
      unsigned int nbPointLight;
      unsigned int nbDirectionalLight;
      unsigned int nbSpotLight;
    };

    class Shader
    {
      public:
        unsigned int ID;// TO DO: put the variable in private
        Shader() = default;
        Shader(const unsigned int& _ID);
        ~Shader();

        void Use();
        void SetMatrix4(const char* name, Maths::Matrix4 mat);

        static Shader LoadShader(const char* vertexPath, const char* fragmentPath);
        static Shader LoadShader(const ShaderConstructData& shaderData);

    private:
      static std::string LoadStringFromFile(const char* path);
    };
}

#endif //_SHADER_