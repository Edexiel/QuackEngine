#ifndef _SHADER_
#define _SHADER_

#include "Maths/Matrix4.hpp"

namespace Renderer
{
    class Shader
    {
    private:

      public:
        unsigned int ID;// TO DO: put the variable in private
        Shader() = default;
        Shader(const unsigned int& _ID);
        ~Shader();

        void Use();
        void SetMatrix4(const char* name, Maths::Matrix4 mat);

        static Shader LoadShader(const char* vertexPath, const char* fragmentPath);
    };
}

#endif //_SHADER_