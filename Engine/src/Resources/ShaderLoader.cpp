#include "../include/Resources/ShaderLoader.hpp"

#include "glad/glad.h"

#include <fstream>
#include <sstream>
#include <vector>

using namespace Resources;

ShaderLoader::ShaderLoader(unsigned int _shaderID, const char* _vertexPath, const char* _fragmentPath) : shaderID{_shaderID}, vertexPath{_vertexPath}, fragmentPath{_fragmentPath} {}

void ShaderLoader::ReadFile(ShaderLoader& shaderLoader)
{
    // Read the Vertex Shader code from the file
    //std::string VertexShaderCode;
    std::ifstream VertexShaderStream(shaderLoader.vertexPath, std::ios::in);
    if (VertexShaderStream.is_open())
    {
        std::stringstream sstr;
        sstr << VertexShaderStream.rdbuf();
        shaderLoader.VertexShaderCode = sstr.str();
        VertexShaderStream.close();
    }
    else
    {
        printf("Impossible to open %s.\n", shaderLoader.vertexPath);
        getchar();
        return;
    }

    // Read the Fragment Shader code from the file
    //std::string FragmentShaderCode;
    std::ifstream FragmentShaderStream(shaderLoader.fragmentPath, std::ios::in);
    if (FragmentShaderStream.is_open())
    {
        std::stringstream sstr;
        sstr << FragmentShaderStream.rdbuf();
        shaderLoader.FragmentShaderCode = sstr.str();
        FragmentShaderStream.close();
    }
    else
    {
        printf("Impossible to open %s.\n", shaderLoader.fragmentPath);
        getchar();
        return;
    }
}

unsigned int ShaderLoader::Apply()
{
    // Create the shaders
    GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

    GLint Result = GL_FALSE;
    int InfoLogLength;

    // Compile Vertex Shader
    char const *VertexSourcePointer = VertexShaderCode.c_str();
    glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);
    glCompileShader(VertexShaderID);

    // Check Vertex Shader
    glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if (InfoLogLength > 0)
    {
      std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
      glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
      printf("%s\n", &VertexShaderErrorMessage[0]);
    }

    // Compile Fragment Shader
    char const *FragmentSourcePointer = FragmentShaderCode.c_str();
    glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, NULL);
    glCompileShader(FragmentShaderID);

    // Check Fragment Shader
    glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if (InfoLogLength > 0)
    {
      std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
      glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
      printf("%s\n", &FragmentShaderErrorMessage[0]);
    }

    // Link the program
    shaderID = glCreateProgram();
    glAttachShader(shaderID, VertexShaderID);
    glAttachShader(shaderID, FragmentShaderID);
    glLinkProgram(shaderID);

    // Check the program
    glGetProgramiv(shaderID, GL_LINK_STATUS, &Result);
    glGetProgramiv(shaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if (InfoLogLength > 0)
    {
        std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
        glGetProgramInfoLog(shaderID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
        printf("%s\n", &ProgramErrorMessage[0]);
    }

    glDetachShader(shaderID, VertexShaderID);
    glDetachShader(shaderID, FragmentShaderID);

    glDeleteShader(VertexShaderID);
    glDeleteShader(FragmentShaderID);

    return shaderID;
}