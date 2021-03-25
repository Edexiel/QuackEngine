#ifndef _RESOURCE_MANAGER_
#define _RESOURCE_MANAGER_

#include <vector>
#include <string>
#include <unordered_map>

#include "Renderer/Shader.hpp"
#include "Renderer/Model.hpp"
#include "Renderer/Texture.hpp"

#include "Audio/Sound.hpp"


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
      std::unordered_map<std::string, Renderer::Model   > mapModel;
      std::unordered_map<std::string, Renderer::Texture > mapTexture;
      std::vector<ReferenceShader >                       listShader;
      std::unordered_map<unsigned int, Renderer::Shader>  mapDynamicShader;
      std::unordered_map<std::string, Audio::Sound>       mapSound;

      Audio::SoundManager* _soundManager;

    public:
      ResourcesManager()  = default;
      ResourcesManager(Audio::SoundManager* soundManager) : _soundManager{soundManager} {}; // To redo when the scene is complete
      ~ResourcesManager() = default;

      Renderer::Model   LoadModel     (const char* path);
      Renderer::Texture LoadTexture   (const char* path);
      Renderer::Shader  LoadShader    (const char* vertexShader, const char* fragmentShader);
      Renderer::Shader  LoadShader    (const Renderer::ShaderConstructData& constructData);

      Audio::Sound      LoadSound     (const char* path, Audio::SoundType soundType);

    };
}

#endif
