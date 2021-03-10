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
        Shader(const char* vertexShaderSource, const char* fragmentShaderSource);
        ~Shader();

        void Use();
        void SetMatrix4(const char* name, Maths::Matrix4 mat);
    };
}

#endif //_SHADER_