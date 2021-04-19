#ifndef _RESOURCE_MANAGER_
#define _RESOURCE_MANAGER_

#include <vector>
#include <string>
#include <unordered_map>

#include "Renderer/Shader.hpp"
#include "Scene/Component/Model.hpp"
#include "Renderer/Texture.hpp"

#include "Audio/Sound.hpp"


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

      World* _world;

      std::unordered_map<std::string, Component::Model   > mapModel;
      std::unordered_map<std::string, Renderer::Texture > mapTexture;
      std::vector<ReferenceShader >                       listShader;
      std::unordered_map<unsigned int, Renderer::Shader>  mapDynamicShader;
      std::unordered_map<std::string, Audio::Sound>       mapSound;

      std::vector<Renderer::Mesh> listLoadedShape; //keep loaded shape saved for GPU memory management

      Audio::SoundManager* _soundManager;

    public:

      ResourcesManager() = default;
      ResourcesManager(Audio::SoundManager* soundManager) : _soundManager{soundManager} {}; // To redo when the scene is complete
      ~ResourcesManager() = default;

      Component::Model  LoadModel     (const char* path, Renderer::VertexType vertexType = Renderer::VertexType::V_CLASSIC);
      Renderer::Texture LoadTexture   (const char* path);
      Renderer::Shader  LoadShader    (const char* vertexShader, const char* fragmentShader);
      Renderer::Shader  LoadObjectShader    (const char* vertexShader, const char* fragmentShader);
      Renderer::Shader  LoadObjectShader    (const Renderer::ShaderConstructData& constructData);

      Audio::Sound      LoadSound     (const char* path, Audio::SoundType soundType);

      Renderer::Mesh& AddShape(Renderer::Mesh& mesh);

    };
}

#endif
