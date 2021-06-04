#include "Engine.hpp"
#include "Scene/Core/World.hpp"
#include "Resources/ResourcesManager.hpp"

#include "Renderer/RendererPlatform.hpp"

#include "Audio/SoundManager.hpp"
#include "Audio/Sound.hpp"

#include "Debug/Log.hpp"
#include "Debug/Assertion.hpp"
#include "Scene/System/RenderSystem.hpp"
#include "Scene/System/LightSystem.hpp"

#include "Thread/ThreadPool.hpp"

#include <filesystem>
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

    auto it = _mapModel.find(path.string());

    if (it != _mapModel.end())
    {
        return (it->second);
    }

    // return null Model if the file doesn't exist
    if (!exists(path))
    {
        Log_Warning("File {} doesn't exist", path.string());
        return ModelRenderer();
    }

    // Create a new Model
    ModelRenderer model = ModelRenderer::LoadModel(path, vertexType);

    if (model.GetNumberMesh() > 0)
    {
        _mapModel.insert({path.string(), model});
        _globalAssetMap.insert({path.string(), &_mapModel.find(path.string())->second});
    }
    return model;
}

void ResourcesManager::ReLoadModel(const std::filesystem::path &path, Renderer::VertexType vertexType)
{
    // Check if the Model already exist

    auto it = _mapModel.find(path.string());

    if (it != _mapModel.end())
    {
        Engine &e = Engine::Instance();
        Renderer::ModelRenderer::ReLoadModel(it->second, path, vertexType);
        e.GetCurrentWorld().GetSystem<RenderSystem>()->UpdateModel(it->second);
        e.GetCurrentWorld().GetSystem<RenderSystem>()->SetMaterials();
        return;
    }

    Assert_Error(true, "Trying to reload a model that doesn't exists: {}", path.string());
}

Animation ResourcesManager::LoadAnimation(const std::filesystem::path &path)
{
    // Check if the Model already exist

    std::string type = GetFileType(path);

    auto it = _mapAnimation.find(path.string());

    if (it != _mapAnimation.end())
    {
        return (it->second);
    }

    if (!exists(path))
    {
        Log_Error("File doesn't exists: {}", path.string());
        return Animation();
    }

    // Create a new Animation
    Animation animation = Animation::LoadAnimation(path);

    if (animation.GetDuration() > 0.0f) // Check if the file has an animation
    {
        animation.Path() = path.string();
        _mapAnimation.insert({path.string(), animation});
        _globalAssetMap.insert({path.string(), &_mapAnimation.find(path.string())->second});
    }

    return animation;

}

Texture ResourcesManager::LoadTexture(const std::filesystem::path &path)
{
    // Check if the Texture already exist
    auto it = _mapTexture.find(path.string());

    // Check if the texture already exist
    if (it != _mapTexture.end())
    {
        return it->second;
    }

    // return null Texture if the file doesn't exist
    if (!exists(path))
    {
        Log_Error("File doesn't exists: {}", path.string());
        return Texture();
    }

    // Create a new Texture

    Texture texture = Texture::LoadTexture(path);
    texture.Path() = path.string();
    _mapTexture.insert({path.string(), texture});
    _textureToName.insert({texture.GetID(), path.string()});
    _globalAssetMap.insert({path.string(), &_mapTexture.find(path.string())->second});

    return texture;
}

Renderer::Shader ResourcesManager::LoadShader(const std::filesystem::path &path)
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
        Log_Error("File doesn't exists: {}", path.string());
        return Shader();
    }

    // Create a new Shader

    Shader shader = Shader::LoadShader(path.string().c_str());
    _mapShader.insert({path.string(), shader});
    _globalAssetMap.insert({path.string(), &_mapShader.find(path.string())->second});

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
        Engine::Instance().GetCurrentWorld().GetSystem<LightSystem>()->AddShaderToUpdate(shader);

    return shader;
}

Renderer::Font ResourcesManager::LoadFont(const std::filesystem::path &path)
{
    // Check if the Texture already exist
    auto it = _mapFont.find(path.string());

    // Check if the shader already exist
    if (it != _mapFont.end())
    {
        return it->second;
    }

    // return null Shader if the file doesn't exist
    if (!std::filesystem::exists(path.string()))
    {
        Log_Error("File doesn't exists: {}", path.string());
        return Font();
    }

    // Create a new Shader

    Font font = Font::LoadFont(path.string().c_str());

    font.Path() = path.string();
    _mapFont.insert({path.string(), font});
    _globalAssetMap.insert({path.string(), &_mapFont.find(path.string())->second});

    return font;
}

Audio::Sound ResourcesManager::LoadSound(const std::filesystem::path &path, Audio::SoundType soundType)
{
    // Check if the Sound already exist

    auto it = _mapSound.find(path.string());

    // Check if the sound already exist
    if (it != _mapSound.end())
    {
        return it->second;
    }

    if (!exists(path))
    {
        Log_Error("File doesn't exists: {}", path.string());
        return Audio::Sound();
    }

    Audio::Sound sound = Engine::Instance().GetSoundManager().CreateSound(path, soundType);
    _mapSound.insert({path.string(), sound});
    _soundToName.insert({sound.GetID(), path.string()});

    return sound;
}

Mesh &ResourcesManager::AddShape(Renderer::Mesh &mesh)
{
    listLoadedShape.push_back(mesh);
    return listLoadedShape[listLoadedShape.size() - 1];
}

Renderer::MaterialInterface ResourcesManager::LoadMaterial(const std::filesystem::path &name)
{
    // Check if the Material already exist
    auto it = _mapMaterial.find(name.string());

    // Check if the texture already exist
    if (it != _mapMaterial.end())
    {
        return it->second;
    }

    // return null Material if the file doesn't exist
    if (!exists(name))
    {
        Log_Error("File doesn't exists: {}", name.string());
        return nullptr;
    }

    // Create a new Material

    MaterialInterface material = std::make_shared<Material>();

    return material;
}

Renderer::MaterialInterface ResourcesManager::GenerateMaterial(const std::string &name, const Material &material)
{

    MaterialInterface materialInterface = std::make_shared<Material>(material);

    materialInterface->Path() = name;

    _mapMaterial.insert({name, materialInterface});

    materialInterface->shader = LoadObjectShader(materialInterface->GetConstructData());
    _globalAssetMap.insert({name, _mapMaterial.find(name)->second.get()});

    Log_Info("Loading material: {}", name);


    return materialInterface;
}

void ResourcesManager::DestroyMaterial(const std::string &name)
{
    _mapMaterial.erase(name);
    _globalAssetMap.erase(name);
}

void ResourcesManager::LoadFolder(const std::filesystem::path &path)
{
    std::vector<std::filesystem::path> results;

    for (auto &p : std::filesystem::recursive_directory_iterator(path))
    {
        if (!p.is_directory())
        {
            std::string path = p.path().string();
            std::replace(path.begin(), path.end(), '\\', '/');

            std::string extension = p.path().extension().string();

            if (extension == ".glb" || extension == ".gltf")
                LoadModel(path, VertexType::V_NORMALMAP);
            if (extension == ".fbx")
            {
                LoadModel(path, VertexType::V_NORMALMAP);
                LoadAnimation(path);
            }
            else if (extension == ".ogg" || extension == ".mp3" || extension == ".wav")
                LoadSound(path, Audio::SoundType::S_MASTER);
            else if (extension == ".png" || extension == ".jpg" || extension == ".jpeg")
                LoadTexture(path);
            else if (extension == ".qsh")
                LoadShader(p.path().string().c_str());
        }
    }

}

std::string ResourcesManager::GetFileType(const std::filesystem::path &path)
{
    return path.extension().string();
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
    auto it = _globalAssetMap.find(name);
    if (it == _globalAssetMap.cend())
        return nullptr;
    return it->second;
}

void ResourcesManager::Clear()
{
    _mapModel.clear();
    _mapTexture.clear();
    _mapShader.clear();
    _mapDynamicShader.clear();
    _mapSound.clear();
    _mapMaterial.clear();
    _mapAnimation.clear();

    _textureToName.clear();
    _soundToName.clear();
    _globalAssetMap.clear();

}