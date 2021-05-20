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

void ResourcesManager::Init()
{
    Material material;

    material.ambient = {1, 1, 1};
    material.diffuse = {1, 1, 1};
    material.specular = {1, 1, 1};
    material.checkLight = true;

    MaterialInterface materialInterface = GenerateMaterial("Default material", material);
}

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
    _globalAssetMap.insert({path, &_mapModel.find(path)->second});

    return model;
}

void ResourcesManager::ReLoadModel(const char *path, Renderer::VertexType vertexType)
{
    // Check if the Model already exist

    auto it = _mapModel.find(path);

    if (it != _mapModel.end())
    {
        Model::ReLoadModel(it->second, path, vertexType);
        Engine::Instance().GetRendererInterface().renderSystem->UpdateModel(it->second);
        Engine::Instance().GetRendererInterface().renderSystem->SetMaterials();
        return;
    }

    Assert_Error(true, (std::string("The model : ") + path + " to reload doesn't exist").c_str());
}

Animation ResourcesManager::LoadAnimation(const char* path)
{
    // Check if the Model already exist

    std::string type = GetFileType(path);
    std::string name = path;

    if (type != "anm")
    {
        // Change the type of the file
        name.erase(name.cend() - 3, name.cend());
        name += "anm";
    }

    auto it = _mapAnimation.find(name);

    if (it != _mapAnimation.end())
    {
        return (it->second);
    }

    // return null Texture if the file doesn't exist
    if (access(path, F_OK) == -1)
    {
        std::cout << "File : " << path << " doesn't exist" << std::endl;
        return Animation();
    }

    // Create a new Model
    Animation animation = Animation::LoadAnimation(path);
    animation.name = name;
    _mapAnimation.insert({name, animation});
    _globalAssetMap.insert({name, &_mapAnimation.find(name)->second});

    return animation;
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
    _textureToName.insert({texture.GetID(), path});
    _globalAssetMap.insert({path, &_mapTexture.find(path)->second});

    return texture;
}

Renderer::Shader ResourcesManager::LoadShader(std::filesystem::path path)
{
    // Check if the Texture already exist
    auto it = _mapShader.find(path.string());

    // Check if the shader already exist
    if (it != _mapShader.end())
    {
        return it->second;
    }

    // return null Shader if the file doesn't exist
    if (!std::filesystem::exists(path.string()))
    {
        std::cout << "File : " << path << " doesn't exist" << std::endl;
        return Shader();
    }

    // Create a new Shader

    Shader shader = Shader::LoadShader(path.string().c_str());
    _mapShader.insert({path.string(), shader});
    _globalAssetMap.insert({path.string(), &_mapShader.find(path.string())->second});

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
  _soundToName.insert({sound.GetID(), path});

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

    materialInterface->name = name;

    _mapMaterial.insert({name, materialInterface});

    materialInterface->shader = LoadObjectShader(materialInterface->GetConstructData());
    _globalAssetMap.insert({name, _mapMaterial.find(name)->second.get()});

    std::cout << "materialLoading : " << name << std::endl;

    return materialInterface;
}

void ResourcesManager::LoadFolder(std::filesystem::path path)
{
    std::string type;
    for(auto& p : std::filesystem::recursive_directory_iterator(path))
    {
        if (!p.is_directory())
        {
            std::cout << p.path() << std::endl;
            type = p.path().extension().string();
            if (type == ".fbx" || type == ".glb")
                LoadModel(p.path().string().c_str(), VertexType::V_NORMALMAP);
            else if (type == ".ogg" || type == ".mp3" || type == ".wav")
                LoadSound(p.path().string().c_str(), Audio::SoundType::S_MASTER);
            else if (type == ".png" || type == ".jpg" || type == ".jepg")
                LoadTexture(p.path().string().c_str());
            else if (type == ".qsh")
                Shader::LoadShader(p.path().string().c_str());
        }
    }
}

std::string ResourcesManager::GetFileType(const std::string& file)
{
    if (file.size() < 3)
        return std::string(NO_TYPE_STRING);

    return file.substr(file.size() - 3);
}

std::vector<std::string> ResourcesManager::GetModelNameList() const
{
    std::vector<std::string> list;

    for (auto it : _mapModel)
    {
        list.emplace_back(it.first.c_str());
    }

    return list;
}

std::vector<std::string> ResourcesManager::GetMaterialNameList() const
{
    std::vector<std::string> list;

    for (auto it : _mapMaterial)
    {
        list.emplace_back(it.first.c_str());
    }

    return list;
}

std::vector<std::string> ResourcesManager::GetTextureNameList() const
{
    std::vector<std::string> list;

    for (const auto& it : _mapTexture)
    {
        list.emplace_back(it.first.c_str());
    }

    return list;
}

std::vector<std::string> ResourcesManager::GetAnimationNameList() const
{
    std::vector<std::string> list;

    for (const auto& it : _mapAnimation)
    {
        list.emplace_back(it.first.c_str());
    }

    return list;
}

std::string ResourcesManager::GetName(const Renderer::Texture& texture) const
{
    auto it = _textureToName.find(texture.GetID());
    if(it == _textureToName.end())
        return std::string(EMPTY_TEXTURE_STRING);
    return it->second;
}

std::string ResourcesManager::GetName(const Audio::Sound& sound) const
{
    auto it = _soundToName.find(sound.GetID());
    if(it == _soundToName.end())
        return std::string(EMPTY_TEXTURE_STRING);
    return it->second;
}

const Asset *ResourcesManager::GetAsset(const std::string& name)
{
    return _globalAssetMap.find(name)->second;
}