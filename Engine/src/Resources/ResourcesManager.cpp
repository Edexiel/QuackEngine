#include "../include/Resources/ResourcesManager.hpp"
#include "../include/Renderer/Model.hpp"
#include "../include/Renderer/Texture.hpp"
#include "../include/Renderer/Shader.hpp"

#include "glad/glad.h"

#include <iostream>

#include "../include/Resources/TextureLoader.hpp"
#include "../include/Resources/ShaderLoader.hpp"

#include <sys/stat.h>

using namespace Resources;
using namespace Renderer;

Model ResourcesManager::LoadModel(const char* path)
{
    // Check if the Model already exist

    std::unordered_map< std::string, Model* >::iterator it = listModel.find(path);

    if (it != listModel.end())
    {
        std::cout << "Model { " << path << " } exist" << std::endl;
        return Model(it->second->id);
    }

    // Create a new Model

    std::cout << "Model { " << path << " } doesn't exist" << std::endl;
    Model* model = new Model(1);
    listModel.insert(std::make_pair(path, model));

    return *model;
}

Texture ResourcesManager::LoadTexture(const char* path)
{
    // Check if the Texture already exist

    std::unordered_map< std::string, Renderer::Texture* >::iterator it = listTexture.find(path);

    if (listTexture.find(path) != listTexture.end())
    {
        return Texture(listTexture.find(path)->second->id);
    }

    // return null Texture if the file doesn't exist
    if (!( access( path, F_OK ) != -1 ))
    {
        std::cout << "File : " << path << " doesn't exist" << std::endl;
        return Texture();
    }

    // Create a new Texture

    Texture* texture = new Texture();
    glGenTextures(1, &texture->id);

    // Multitreadable part
    {
        TextureLoader loader(texture->id, path);
        loader.ReadFile();
        loader.Apply();
    }

    listTexture.insert(std::make_pair(path, texture));

    return *texture;
}

Renderer::Shader ResourcesManager::LoadShader(const char* vertexShader, const char* fragmentShader)
{
  // Check if the file exist
  if (!( access(vertexShader, F_OK ) != -1 ))
  {
    std::cout << "File : " << vertexShader << " doesn't exist" << std::endl;
    return Shader();
  }
  if (!( access(fragmentShader, F_OK ) != -1 ))
  {
    std::cout << "File : " << fragmentShader << " doesn't exist" << std::endl;
    return Shader();
  }

    // find if the Shader already exist

    for (unsigned int i = 0; i < listShader.size(); i++)
    {
        if (listShader[i].fragmentShader == fragmentShader && listShader[i].vertexShader == vertexShader)
        {
            return *listShader[i].shader;
        }
    }

    // Charge new Shader

    Shader* shader = new Shader();

    ShaderLoader shaderLoader(shader->id, vertexShader, fragmentShader);

    ShaderLoader::ReadFile(shaderLoader);
    shaderLoader.Apply();

    listShader.push_back(ReferenceShader{vertexShader, fragmentShader, shader});

    return *shader;
}
