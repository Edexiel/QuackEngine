#ifndef _SHADER_
#define _SHADER_

#include "Maths/Matrix4.hpp"

namespace Renderer
{
    struct Shader
    {
        unsigned int ID;

        Shader() = default;
        Shader(const unsigned int& _ID);
        Shader(const char* vertexShaderSource, const char* fragmentShaderSource);
        ~Shader() = default;
    };
}

#endif //_SHADER_