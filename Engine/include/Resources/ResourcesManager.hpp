#ifndef _RESOURCE_MANAGER_
#define _RESOURCE_MANAGER_

#include <vector>
#include <string>
#include <unordered_map>

#include "Renderer/Shader.hpp"
#include "Scene/Component/Model.hpp"
#include "Renderer/Texture.hpp"
#include "Renderer/Material.hpp"

#include "Audio/Sound.hpp"

#define DEFAULT_MATERIAL_STRING "Default material"


class World;

namespace Resources
{
    struct ReferenceShader
    {
        std::string vertexShader;
        std::string fragmentShader;

        Renderer::Shader shader;
    };

    class ResourcesManager
    {
    private:

      std::unordered_map<std::string, Component::Model   >  _mapModel;
      std::unordered_map<std::string, Renderer::Texture >   _mapTexture;
      std::vector<ReferenceShader >                         _listShader;
      std::unordered_map<unsigned int, Renderer::Shader>    _mapDynamicShader;
      std::unordered_map<std::string, Audio::Sound>         _mapSound;
      std::unordered_map<std::string, Renderer::MaterialInterface>   _mapMaterial;

      std::vector<Renderer::Mesh> listLoadedShape; //keep loaded shape saved for GPU memory management

    public:

       ResourcesManager() = default;
      ~ResourcesManager() = default;

      void Init();

      Component::Model  LoadModel     (const char* path, Renderer::VertexType vertexType = Renderer::VertexType::V_CLASSIC);
      Renderer::Texture LoadTexture   (const char* path);
      Renderer::Shader  LoadShader    (const char* vertexShader, const char* fragmentShader);
      Renderer::Shader  LoadObjectShader    (const char* vertexShader, const char* fragmentShader);
      Renderer::Shader  LoadObjectShader    (const Renderer::ShaderConstructData& constructData);

      Renderer::MaterialInterface LoadMaterial(const char* path);
      Renderer::MaterialInterface GenerateMaterial(const char* name, const Renderer::Material& material); // Should be used to load a material from scratch


      Audio::Sound      LoadSound     (const char* path, Audio::SoundType soundType);

      Renderer::Mesh& AddShape(Renderer::Mesh& mesh);

      void LoadFolder(const char* path);

      std::vector<std::string> GetModelNameList() const;
      std::vector<std::string> GetMaterialNameList() const;


        static std::string GetFileType(const std::string& file);

    };
}

#endif
