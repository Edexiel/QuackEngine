#ifndef _RESOURCE_MANAGER_
#define _RESOURCE_MANAGER_

#include <vector>
#include <string>
#include <unordered_map>
#include <filesystem>

#include "Resources/Asset.hpp"

#include "Renderer/Shader.hpp"
#include "Scene/Component/Model.hpp"
#include "Renderer/Texture.hpp"
#include "Renderer/Material.hpp"
#include "Renderer/Animation.hpp"

#include "Audio/Sound.hpp"

#define NO_TYPE_STRING "NoType"
#define DEFAULT_MATERIAL_STRING "Default material"

#define EMPTY_TEXTURE_STRING "NONE"


class World;

namespace Resources
{

    class ResourcesManager
    {
    private:

        std::unordered_map<std::string, Component::Model>     _mapModel;
        std::unordered_map<std::string, Renderer::Texture>    _mapTexture;
        std::unordered_map<std::string, Renderer::Shader>     _mapShader;
        std::unordered_map<unsigned int, Renderer::Shader>    _mapDynamicShader;
        std::unordered_map<std::string, Audio::Sound>         _mapSound;
        std::unordered_map<std::string, Renderer::MaterialInterface>   _mapMaterial;
        std::unordered_map<std::string, Renderer::Animation>  _mapAnimation;

        std::vector<Renderer::Mesh> listLoadedShape; //keep loaded shape saved for GPU memory management
        //TODO  Check if really necessary

        std::unordered_map<unsigned int, std::string> _textureToName;
        std::unordered_map<unsigned int, std::string> _soundToName;

        std::unordered_map<std::string, Asset*> _globalAssetMap;

    public:

        ResourcesManager() = default;
        ~ResourcesManager() = default;

        void Init();

        Component::Model  LoadModel     (const char* path, Renderer::VertexType vertexType = Renderer::VertexType::V_CLASSIC);
        void  ReLoadModel   (const char* path, Renderer::VertexType vertexType);
        Renderer::Animation LoadAnimation     (const char* path);
        Renderer::Texture   LoadTexture   (const char* path);
        Renderer::Shader    LoadShader    (std::filesystem::path path);
        Renderer::Shader    LoadObjectShader    (const Renderer::ShaderConstructData& constructData);

        Renderer::MaterialInterface LoadMaterial(const char* path);
        Renderer::MaterialInterface GenerateMaterial(const char* name, const Renderer::Material& material); // Should be used to load a material from scratch


        Audio::Sound      LoadSound     (const char* path, Audio::SoundType soundType);

        Renderer::Mesh& AddShape(Renderer::Mesh& mesh);

        void LoadFolder(std::filesystem::path path);

        std::vector<std::string> GetModelNameList() const;
        std::vector<std::string> GetMaterialNameList() const;
        std::vector<std::string> GetTextureNameList() const;
        std::vector<std::string> GetAnimationNameList() const;

        std::string GetName(const Renderer::Texture& texture) const;
        std::string GetName(const Audio::Sound& texture) const;

        static std::string GetFileType(const std::string& file);

        const Asset* GetAsset(const std::string& name);
    };
}

#endif
