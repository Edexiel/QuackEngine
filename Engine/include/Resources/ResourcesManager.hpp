#ifndef _RESOURCE_MANAGER_
#define _RESOURCE_MANAGER_

#include <vector>
#include <string>
#include <unordered_map>
#include <filesystem>

#include "Resources/Asset.hpp"

#include "Renderer/ModelRenderer.hpp"
#include "Renderer/Shader.hpp"
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

        std::unordered_map<std::string, Renderer::ModelRenderer> _mapModel;
        std::unordered_map<std::string, Renderer::Texture> _mapTexture;
        std::unordered_map<std::string, Renderer::Shader> _mapShader;
        std::unordered_map<unsigned int, Renderer::Shader> _mapDynamicShader;
        std::unordered_map<std::string, Audio::Sound> _mapSound;
        std::unordered_map<std::string, Renderer::MaterialInterface> _mapMaterial;
        std::unordered_map<std::string, Renderer::Animation> _mapAnimation;

        std::vector<Renderer::Mesh> listLoadedShape; //keep loaded shape saved for GPU memory management
        //TODO  Check if really necessary

        std::unordered_map<unsigned int, std::string> _textureToName;
        std::unordered_map<unsigned int, std::string> _soundToName;
        std::unordered_map<std::string, Asset *> _globalAssetMap;

        template<typename T>
        std::vector<std::string> GetList(const std::unordered_map<std::string, T> &map) const;

    public:

        ResourcesManager() = default;
        ~ResourcesManager() = default;

        void Init();

        Renderer::ModelRenderer
        LoadModel(const std::filesystem::path &path, Renderer::VertexType vertexType = Renderer::VertexType::V_CLASSIC);
        void ReLoadModel(const std::filesystem::path &path, Renderer::VertexType vertexType);
        Renderer::Animation LoadAnimation(const std::filesystem::path &path);
        Renderer::Texture LoadTexture(const std::filesystem::path &path);
        Renderer::Shader LoadShader(const std::filesystem::path& path);
        Renderer::Shader LoadObjectShader(const Renderer::ShaderConstructData &constructData);

        Renderer::MaterialInterface LoadMaterial(const std::filesystem::path &path);
        Renderer::MaterialInterface GenerateMaterial(const char *name,
                                                     const Renderer::Material &material); // Should be used to load a material from scratch


        Audio::Sound LoadSound(const std::filesystem::path &path, Audio::SoundType soundType);

        Renderer::Mesh &AddShape(Renderer::Mesh &mesh);

        void LoadFolder(const std::filesystem::path &path);

        std::vector<std::string> GetModelNameList() const;
        std::vector<std::string> GetMaterialNameList() const;
        std::vector<std::string> GetTextureNameList() const;
        std::vector<std::string> GetAnimationNameList() const;

        std::string GetName(const Renderer::Texture &texture) const;
        std::string GetName(const Audio::Sound &texture) const;

        static std::string GetFileType(const std::filesystem::path &path);

        const Asset *GetAsset(const std::string &name);
    };

    template<typename T>
    std::vector<std::string> ResourcesManager::GetList(const std::unordered_map<std::string, T> &map) const
    {
        std::vector<std::string> list;

        for (const auto &it : map)
        {
            list.emplace_back(it.first.c_str());
        }

        return list;
    }
}

#endif
