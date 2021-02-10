#include "../include/Resources/ShaderLoader.hpp"

#include "glad/glad.h"

#include <fstream>
#include <sstream>

using namespace Resources;

void ShaderLoader::ReadFile()
{
    // Read the Vertex Shader code from the file
    //std::string VertexShaderCode;
    std::ifstream VertexShaderStream(vertexPath, std::ios::in);
    if (VertexShaderStream.is_open())
    {
        std::stringstream sstr;
        sstr << VertexShaderStream.rdbuf();
        VertexShaderCode = sstr.str();
        VertexShaderStream.close();
    }
    else
    {
        printf("Impossible to open %s.\n", vertexPath);
        getchar();
        return;
    }

    // Read the Fragment Shader code from the file
    //std::string FragmentShaderCode;
    std::ifstream FragmentShaderStream(fragmentPath, std::ios::in);
    if (FragmentShaderStream.is_open())
    {
        std::stringstream sstr;
        sstr << FragmentShaderStream.rdbuf();
        FragmentShaderCode = sstr.str();
        FragmentShaderStream.close();
    }
        else
    {
        printf("Impossible to open %s.\n", fragmentPath);
        getchar();
        return;
    }

}