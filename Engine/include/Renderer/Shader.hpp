#ifndef _SHADER_
#define _SHADER_

namespace Renderer
{
    struct Shader
    {
        unsigned int ID;

        Shader() = default;
        Shader(const unsigned int& _ID);
        Shader(const char* vertexShaderSource, const char* fragmentShaderSource);
        ~Shader() = default;

        static unsigned int CreateProgramShader(const char* vertexShaderSource, const char* fragmentShaderSource);
        void Use();
    };
}

#endif //_SHADER_