#ifndef _SHADER_LOADER_
#define _SHADER_LOADER_

#include <string>

namespace Resources
{

    class ShaderLoader
    {
    private:

        std::string VertexShaderCode;
        std::string FragmentShaderCode;

        const char* vertexPath;
        const char* fragmentPath;

        unsigned int shaderID;



    public:
        ShaderLoader(unsigned int _shaderID, const char* _vertexPath, const char* _fragmentPath);
        ~ShaderLoader(){};

        static void ReadFile(ShaderLoader& shaderLoader);
        unsigned int Apply();
    };
}

#endif // _SHADER_LOADER_