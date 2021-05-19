#include "Engine.hpp"

#include "Resources/ResourcesManager.hpp"

#include "Renderer/RendererPlatform.hpp"

#include "Audio/SoundManager.hpp"
#include "Audio/Sound.hpp"

#include "Debug/Log.hpp"
#include "Debug/Assertion.hpp"

#include <fmt/core.h>
#include <fmt/color.h>


using namespace Resources;
using namespace Renderer;

void ResourcesManager::Init()
{
    Material material;

    material.ambient = {1, 1, 1};
    material.diffuse = {1, 1, 1};
    material.specular = {1, 1, 1};
    material.checkLight = true;

    MaterialInterface materialInterface = GenerateMaterial("Default material", material);
}

ModelRenderer ResourcesManager::LoadModel(const std::filesystem::path &path, VertexType vertexType)
{
    // Check if the Model already exist

    auto it = _mapModel.find(path);

    if (it != _mapModel.end())
    {
        return (it->second);
    }

    // return null Texture if the file doesn't exist
    if (!exists(path))
    {
        std::cout << "File : " << path << " doesn't exist" << std::endl;
        return ModelRenderer();
    }

    // Create a new Model
    ModelRenderer model = ModelRenderer::LoadModel(path, vertexType);
    _mapModel.insert({path, model});
    _globalAssetMap.insert({path, &_mapModel.find(path)->second});

    return model;
}

void ResourcesManager::ReLoadModel(const std::filesystem::path &path, Renderer::VertexType vertexType)
{
    // Check if the Model already exist

    auto it = _mapModel.find(path.string());

    if (it != _mapModel.end())
    {
        Renderer::ModelRenderer::ReLoadModel(it->second, path, vertexType);
        Engine::Instance().GetRendererInterface().renderSystem->UpdateModel(it->second);
        Engine::Instance().GetRendererInterface().renderSystem->SetMaterials();
        return;
    }

    Assert_Error(true, fmt::format("Trying to reload a model that doesn't exists: {}\n", path.string()).c_str());
}

Animation ResourcesManager::LoadAnimation(const std::filesystem::path &path)
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

    if (!exists(path))
    {
        fmt::print(fg(fmt::color::red), "[Resource Manager] File doesn't exists: {}\n", path.string());
        return Animation();
    }

    // Create a new Model
    Animation animation = Animation::LoadAnimation(path);
    animation.name = name;
    _mapAnimation.insert({name, animation});
    _globalAssetMap.insert({name, &_mapAnimation.find(name)->second});

    return animation;
}

Texture ResourcesManager::LoadTexture(const std::filesystem::path &path)
{
    // Check if the Texture already exist
    auto it = _mapTexture.find(path);

    // Check if the texture already exist
    if (it != _mapTexture.end())
    {
        return it->second;
    }

    // return null Texture if the file doesn't exist
    if (!exists(path))
    {
        fmt::print(fg(fmt::color::red), "[Resource Manager] File doesn't exists: {}\n", path.string());
        //todo : no
        return Texture();
    }

    // Create a new Texture

    Texture texture = Texture::LoadTexture(path);
    _mapTexture.insert({path, texture});
    _textureToName.insert({texture.GetID(), path});
    _globalAssetMap.insert({path, &_mapTexture.find(path)->second});

    return texture;
}

Renderer::Shader
ResourcesManager::LoadShader(const std::filesystem::path &vertexShader, const std::filesystem::path &fragmentShader)
{
    bool vs, fs = false;
    vs = exists(vertexShader);
    fs = exists(fragmentShader);

    // Check if the file exist
    if (!vs || !fs)
    {
        fmt::print(fg(fmt::color::red), "[Resource Manager] File doesn't exists: ");
        if (!vs)
            fmt::print(fg(fmt::color::red), "Vertex Shader : {}\n", vertexShader.string());
        if (!fs)
            fmt::print(fg(fmt::color::red), "Fragment Shader : {}\n", fragmentShader.string());

        //todo : no
        return Shader();
    }

    // find if the Shader already exist
    for (auto &i : _listShader)
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

Renderer::Shader ResourcesManager::LoadObjectShader(const std::filesystem::path &vertexShader,
                                                    const std::filesystem::path &fragmentShader)
{
    Shader shader = LoadShader(vertexShader, fragmentShader);
    Engine::Instance().GetRendererInterface().lightSystem->AddShaderToUpdate(shader);

    return shader;
}


Renderer::Shader ResourcesManager::LoadObjectShader(const Renderer::ShaderConstructData &constructData)
{
    // Check if the Shader already exist

    auto it = _mapDynamicShader.find(constructData.GetKey());

    if (it != _mapDynamicShader.end())
    {
        return Shader(it->second.GetID());
    }

    Shader shader = Shader::LoadObjectShader(constructData);
    _mapDynamicShader.insert({constructData.GetKey(), shader});

    if (constructData.hasLight)
        Engine::Instance().GetRendererInterface().lightSystem->AddShaderToUpdate(shader);

    return shader;
}

Audio::Sound ResourcesManager::LoadSound(const std::filesystem::path &path, Audio::SoundType soundType)
{
    // Check if the Sound already exist

    auto it = _mapSound.find(path);

    // Check if the sound already exist
    if (it != _mapSound.end())
    {
        return it->second;
    }

    // todo :: return null sound if the file doesn't exist
    if (!exists(path))
    {
        fmt::print(fg(fmt::color::red), "[Resource Manager] File doesn't exists: {}\n", path.string());
        return Audio::Sound();
    }

    Audio::Sound sound = Engine::Instance().GetSoundManager().CreateSound(path, soundType);
    _mapSound.insert({path, sound});
    _soundToName.insert({sound.GetID(), path});

    return sound;
}

Mesh &ResourcesManager::AddShape(Renderer::Mesh &mesh)
{
    listLoadedShape.push_back(mesh);
    return listLoadedShape[listLoadedShape.size() - 1];
}

Renderer::MaterialInterface ResourcesManager::LoadMaterial(const std::filesystem::path &path)
{
    // Check if the Material already exist
    auto it = _mapMaterial.find(path);

    // Check if the texture already exist
    if (it != _mapMaterial.end())
    {
        return it->second;
    }

    // return null Material if the file doesn't exist
    if (!exists(path))
    {
        fmt::print(fg(fmt::color::red), "[Resource Manager] File doesn't exists: {}\n", path.string());
        return nullptr;
    }

    // Create a new Material

    MaterialInterface material = std::make_shared<Material>();

    return material;
}

Renderer::MaterialInterface ResourcesManager::GenerateMaterial(const char *name, const Material &material)
{

    MaterialInterface materialInterface = std::make_shared<Material>(material);

    materialInterface->name = name;

    _mapMaterial.insert({name, materialInterface});

    materialInterface->shader = LoadObjectShader(materialInterface->GetConstructData());
    _globalAssetMap.insert({name, _mapMaterial.find(name)->second.get()});

    fmt::print(fg(fmt::color::green), "[Resource Manager] Loading material: {}\n", name);


    return materialInterface;
}

void ResourcesManager::LoadFolder(const std::filesystem::path &path)
{
    std::vector<std::filesystem::path> results;
    for (auto &p : std::filesystem::recursive_directory_iterator(path))
    {
        if (!p.is_directory())
        {
            std::string extension = p.path().extension();

            if (extension == ".fbx" || extension == ".glb" || extension == ".gltf")
                LoadModel(p.path(), VertexType::V_NORMALMAP);
            else if (extension == ".ogg" || extension == ".mp3" || extension == ".wav")
                LoadSound(p.path(), Audio::SoundType::S_MASTER);
            else if (extension == ".png" || extension == ".jpg" || extension == ".epg")
                LoadTexture(p.path());

        }
    }
}

std::string ResourcesManager::GetFileType(const std::filesystem::path &path)
{
    return path.extension();
}

std::vector<std::string> ResourcesManager::GetModelNameList() const
{
    return GetList(_mapModel);
}

std::vector<std::string> ResourcesManager::GetMaterialNameList() const
{
    return GetList(_mapMaterial);
}

std::vector<std::string> ResourcesManager::GetTextureNameList() const
{
    return GetList(_mapTexture);
}

std::vector<std::string> ResourcesManager::GetAnimationNameList() const
{
    return GetList(_mapAnimation);
}


std::string ResourcesManager::GetName(const Renderer::Texture &texture) const
{
    auto it = _textureToName.find(texture.GetID());
    if (it == _textureToName.end())
        return std::string(EMPTY_TEXTURE_STRING);
    return it->second;
}

std::string ResourcesManager::GetName(const Audio::Sound &sound) const
{
    auto it = _soundToName.find(sound.GetID());
    if (it == _soundToName.end())
        return std::string(EMPTY_TEXTURE_STRING);
    return it->second;
}

const Asset *ResourcesManager::GetAsset(const std::string &name)
{
    return _globalAssetMap.find(name)->second;
}