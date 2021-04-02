#include "Resources/ResourcesManager.hpp"

#include "Scene/Core/World.hpp"

#include "Renderer/RendererPlatform.hpp"

#include "Audio/SoundManager.hpp"
#include "Audio/Sound.hpp"

#include "Debug/Log.hpp"
#include <iostream>

#define F_OK 0

#ifdef WIN32
# include <io.h>
# define access(path,mode) _access(path,mode)
#endif
#ifdef LINUX
# include <unistd.h>
#endif


using namespace Resources;
using namespace Renderer;
using namespace Component;


void ResourcesManager::Init(World* world)
{
    _world = world;
}

Model ResourcesManager::LoadModel(const char* path)
{
    // Check if the Model already exist

    std::unordered_map<std::string, Model>::iterator it = mapModel.find(path);

    if (it != mapModel.end())
    {
        return (it->second);
    }

  // return null Texture if the file doesn't exist
    if (!( access( path, F_OK ) != -1 ))
    {
        std::cout << "File : " << path << " doesn't exist" << std::endl;
        return Model();
    }

    // Create a new Model
    Model model = Model::LoadModel(path);
    mapModel.insert({path, model});

    return model;
}

Texture ResourcesManager::LoadTexture(const char* path)
{
    // Check if the Texture already exist

    std::unordered_map<std::string, Renderer::Texture>::iterator it = mapTexture.find(path);

    // Check if the texture already exist
    if (it != mapTexture.end())
    {
      return it->second;
    }

    // return null Texture if the file doesn't exist
    if (!( access( path, F_OK ) != -1 ))
    {
        std::cout << "File : " << path << " doesn't exist" << std::endl;
        return Texture();
    }

    // Create a new Texture

    Texture texture = Texture::LoadTexture(path);
    mapTexture.insert({path, texture});

    return texture;
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
            return listShader[i].shader;
        }
    }

    // Charge new Shader

    Shader shader = Shader::LoadShader(vertexShader, fragmentShader);
    listShader.push_back(ReferenceShader{vertexShader, fragmentShader, shader});

    return shader;
}

Renderer::Shader ResourcesManager::LoadObjectShader(const char* vertexShader, const char* fragmentShader)
{
    Shader shader = LoadShader(vertexShader, fragmentShader);

    _world->GetRendererInterface().AddShaderToUpdate(shader);

    return shader;
}


Renderer::Shader  ResourcesManager::LoadObjectShader(const Renderer::ShaderConstructData& constructData)
{
  // Check if the Shader already exist

  auto it = mapDynamicShader.find(constructData.GetKey());

  if (it != mapDynamicShader.end())
  {
    return Shader(it->second.GetID());
  }

  Shader shader = Shader::LoadObjectShader(constructData);
  mapDynamicShader.insert({constructData.GetKey(), shader});

  _world->GetRendererInterface().AddShaderToUpdate(shader);

  return shader;
}

Audio::Sound ResourcesManager::LoadSound(const char* path, Audio::SoundType soundType)
{
  // Check if the Texture already exist

  auto it = mapSound.find(path);

  // Check if the texture already exist
  if (it != mapSound.end())
  {
    return it->second;
  }

  // return null Texture if the file doesn't exist
  if (!( access( path, F_OK ) != -1 ))
  {
    std::cout << "File : " << path << " doesn't exist" << std::endl;
    return Audio::Sound();
  }

  // Create a new Texture

  Audio::Sound sound = _soundManager->CreateSound(path, soundType);
  mapSound.insert({path, sound});

  return sound;
}

Mesh& ResourcesManager::AddShape(Renderer::Mesh& mesh)
{
    listLoadedShape.push_back(mesh);
    return listLoadedShape[listLoadedShape.size() - 1];
}

