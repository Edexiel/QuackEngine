#include "Resources/ResourcesManager.hpp"
#include "Renderer/Model.hpp"
#include "Renderer/Texture.hpp"
#include "Renderer/Shader.hpp"

#include "glad/gl.h"

#include <iostream>
#include <fstream>

#include <sys/stat.h>

using namespace Resources;
using namespace Renderer;

Model ResourcesManager::LoadModel(const char* path)
{
    // Check if the Model already exist

    std::unordered_map< std::string, Model* >::iterator it = listModel.find(path);

    if (it != listModel.end())
    {
        return *(it->second);
    }

  // return null Texture if the file doesn't exist

  std::ifstream file(path);
  if ( !file )
  {
    std::cerr << "File : " << path << " doesn't exist\n";
    return Model();
  }

    // Create a new Model
    Model* model = new Model();
    Loaders::ModelLoader* modelLoader = new Loaders::ModelLoader(model, path);

    // Direct Read in Main Thread
    Loaders::ModelLoader::ReadFile(modelLoader);
    modelLoader->Apply();

    // To Uncomment when Multhithread doable
    //listModelLoader.push_back(modelLoader);
    //taskSystem.AddTask(std::make_shared<Thread::Task<Loaders::ModelLoader*>>(Loaders::ModelLoader::ReadFile, modelLoader));

    listModel.insert(std::make_pair(path, model));

    return *model;
}

Texture ResourcesManager::LoadTexture(const char* path)
{
    // Check if the Texture already exist

    std::unordered_map< std::string, Renderer::Texture* >::iterator it = listTexture.find(path);

    // Check if the texture already exist
    if (listTexture.find(path) != listTexture.end())
    {
        return Texture(listTexture.find(path)->second->_ID);
    }

    // return null Texture if the file doesn't exist
  std::ifstream file(path);
    if ( !file )
    {
      std::cerr << "File : " << path << " doesn't exist\n";
      return Texture();
    }

    // Create a new Texture

    Texture* texture = new Texture();
    glGenTextures(1, &texture->_ID);

    Loaders::TextureLoader* textureLoader = new Loaders::TextureLoader(texture, path);
    taskSystem.AddTask(std::make_shared<Thread::Task<Loaders::TextureLoader*>>(Loaders::TextureLoader::ReadFile, textureLoader));

    listTexture.insert(std::make_pair(path, texture));

    return *texture;
}

Renderer::Shader ResourcesManager::LoadShader(const char* vertexShader, const char* fragmentShader)
{
  // Check if the file exist
  std::ifstream file(vertexShader);
  if ( !file )
  {
    std::cerr << "File : " << vertexShader << " doesn't exist\n";
    return Shader();
  }
  std::ifstream file2(fragmentShader);
  if ( !file2 )
  {
    std::cerr << "File : " << fragmentShader << " doesn't exist\n";
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

    shader->ID = glCreateProgram();

    Loaders::ShaderLoader* shaderLoader = new Loaders::ShaderLoader(shader, vertexShader, fragmentShader);
    taskSystem.AddTask(std::make_shared<Thread::Task<Loaders::ShaderLoader*>>(Loaders::ShaderLoader::ReadFile, shaderLoader));

    listShader.push_back(ReferenceShader{vertexShader, fragmentShader, shader});

    return *shader;
}


void ResourcesManager::ReadFiles()
{
    threadPool.Run(&taskSystem); // Read all files

    // Apply the files in OpenGL
    for (unsigned int i = 0 ; i < listModelLoader.size(); i++)
    {
        listModelLoader[i]->Apply();
        delete listModelLoader[i];
    }
    for (unsigned int i = 0 ; i < listShaderLoader.size(); i++)
    {
        listShaderLoader[i]->Apply();
        delete listShaderLoader[i];
    }
    for (unsigned int i = 0 ; i < listTextureLoader.size(); i++)
    {
        listShaderLoader[i]->Apply();
        delete listTextureLoader[i];
    }
}
