#include "../include/Resources/ResourcesManager.hpp"
#include "../include/Renderer/Model.hpp"
#include "../include/Renderer/Texture.hpp"
#include "../include/Renderer/Shader.hpp"

#include <iostream>

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
        std::cout << "Model { " << path << " } exist" << std::endl;
        return Texture(listTexture.find(path)->second->id);
    }

    // Create a new Texture

    std::cout << "Model { " << path << " } doesn't exist" << std::endl;
    Texture* texture = new Texture(1);
    listTexture.insert(std::make_pair(path, texture));

    return *texture;
}

Renderer::Shader ResourcesManager::LoadShader(const char* vertexShader, const char* fragmentShader)
{
    // find if the Shader already exist

    for (unsigned int i = 0; i < listShader.size(); i++)
    {
        if (listShader[i].fragmentShader == fragmentShader && listShader[i].vertexShader == vertexShader)
        {
            return {1};
        }
    }

    // Charge new Shader
    return Shader(0);
}
