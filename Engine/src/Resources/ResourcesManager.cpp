#include "Resources/ResourcesManager.hpp"

#include "Engine.hpp"

#include "Renderer/RendererPlatform.hpp"

#include "Audio/SoundManager.hpp"
#include "Audio/Sound.hpp"

#include "Debug/Log.hpp"

#include <filesystem>
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



Model ResourcesManager::LoadModel(const char* path, VertexType vertexType)
{
    // Check if the Model already exist

    auto it = _mapModel.find(path);

    if (it != _mapModel.end())
    {
        return (it->second);
    }

  // return null Texture if the file doesn't exist
    if (access(path, F_OK) == -1)
    {
        std::cout << "File : " << path << " doesn't exist" << std::endl;
        return Model();
    }

    // Create a new Model
    Model model = Model::LoadModel(path, vertexType);
    _mapModel.insert({path, model});

    return model;
}

Texture ResourcesManager::LoadTexture(const char* path)
{
    // Check if the Texture already exist

    auto it = _mapTexture.find(path);

    // Check if the texture already exist
    if (it != _mapTexture.end())
    {
      return it->second;
    }

    // return null Texture if the file doesn't exist
    if (access(path, F_OK) == -1)
    {
        std::cout << "File : " << path << " doesn't exist" << std::endl;
        return Texture();
    }

    // Create a new Texture

    Texture texture = Texture::LoadTexture(path);
    _mapTexture.insert({path, texture});

    return texture;
}

Renderer::Shader ResourcesManager::LoadShader(const char* vertexShader, const char* fragmentShader)
{
  // Check if the file exist
  if (access(vertexShader, F_OK) == -1)
  {
    std::cout << "File : " << vertexShader << " doesn't exist" << std::endl;
    return Shader();
  }
  if (access(fragmentShader, F_OK) == -1)
  {
    std::cout << "File : " << fragmentShader << " doesn't exist" << std::endl;
    return Shader();
  }

    // find if the Shader already exist

    for (auto & i : _listShader)
    {
        if (i.fragmentShader == fragmentShader && i.vertexShader == vertexShader)
        {
            return i.shader;
        }
    }

    // Charge new Shader

    Shader shader = Shader::LoadShader(vertexShader, fragmentShader);
    _listShader.push_back(ReferenceShader{vertexShader, fragmentShader, shader});

    return shader;
}

Renderer::Shader ResourcesManager::LoadObjectShader(const char* vertexShader, const char* fragmentShader)
{
    Shader shader = LoadShader(vertexShader, fragmentShader);
    Engine::Instance().GetRendererInterface().lightSystem->AddShaderToUpdate(shader);

    return shader;
}


Renderer::Shader  ResourcesManager::LoadObjectShader(const Renderer::ShaderConstructData& constructData)
{
  // Check if the Shader already exist

  auto it = _mapDynamicShader.find(constructData.GetKey());

  if (it != _mapDynamicShader.end())
  {
    return Shader(it->second.GetID());
  }

  Shader shader = Shader::LoadObjectShader(constructData);
  _mapDynamicShader.insert({constructData.GetKey(), shader});

  if(constructData.hasLight)
      Engine::Instance().GetRendererInterface().lightSystem->AddShaderToUpdate(shader);

  return shader;
}

Audio::Sound ResourcesManager::LoadSound(const char* path, Audio::SoundType soundType)
{
  // Check if the Sound already exist

  auto it = _mapSound.find(path);

  // Check if the sound already exist
  if (it != _mapSound.end())
  {
    return it->second;
  }

  // return null sound if the file doesn't exist
  if (access(path, F_OK) == -1)
  {
    std::cout << "File : " << path << " doesn't exist" << std::endl;
    return Audio::Sound();
  }

  Audio::Sound sound = Engine::Instance().GetSoundManager().CreateSound(path, soundType);
  _mapSound.insert({path, sound});

  return sound;
}

Mesh& ResourcesManager::AddShape(Renderer::Mesh& mesh)
{
    listLoadedShape.push_back(mesh);
    return listLoadedShape[listLoadedShape.size() - 1];
}

Renderer::MaterialInterface ResourcesManager::LoadMaterial(const char *path)
{

    // Check if the Material already exist

    auto it = _mapMaterial.find(path);

    // Check if the texture already exist
    if (it != _mapMaterial.end())
    {
        return it->second;
    }

    // return null Material if the file doesn't exist
    if (access(path, F_OK) == -1)
    {
        std::cout << "File : " << path << " doesn't exist" << std::endl;
        return nullptr;
    }

    // Create a new Material

    MaterialInterface material = std::make_shared<Material>();

    return material;
}

Renderer::MaterialInterface ResourcesManager::GenerateMaterial(const char* name, const Material& material)
{
    MaterialInterface materialInterface = std::make_shared<Material>(material);

    _mapMaterial.insert({name, materialInterface});

    materialInterface->shader = LoadObjectShader(materialInterface->GetConstructData());

    std::cout << "materialLoading : " << name << std::endl;

    return materialInterface;
}

void ResourcesManager::LoadFolder(const char *path)
{
    std::vector<std::string> r;
    for(auto& p : std::filesystem::recursive_directory_iterator(path))
    {
        if (!p.is_directory())
            r.push_back(p.path().string());
    }

    std::string type;

    for (auto & i : r)
    {
        std::cout << i << std::endl;
        type = GetFileType(i);
        if (type == "fbx")
            LoadModel(i.c_str(), VertexType::V_NORMALMAP);
        else if (type == "ogg" || type == "mp3" || type == "wav")
            LoadSound(i.c_str(), Audio::SoundType::S_MASTER);
        else if (type == "png" || type == "jpg" || type == "epg")
            LoadTexture(i.c_str());
    }
}

std::string ResourcesManager::GetFileType(const std::string& file)
{
    return file.substr(file.size() - 3);
}