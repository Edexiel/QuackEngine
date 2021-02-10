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

        unsigned int bindShaderVertex;
        unsigned int bindShaderFragment;

    public:
        ShaderLoader(const unsigned int& _bindShaderVertex, const unsigned int& _bindShaderFragment, const char* _vertexPath, const char* _fragmentPath);
        ~ShaderLoader(){};

        void ReadFile();
        unsigned int Apply();
    };
}

#endif // _SHADER_LOADER_