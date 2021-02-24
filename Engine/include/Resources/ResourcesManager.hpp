#ifndef _RESOURCE_MANAGER_
#define _RESOURCE_MANAGER_

#include <vector>
#include <string>
#include <unordered_map>

#include "Thread/ThreadPool.hpp"

#include "Resources/Loaders/ModelLoader.hpp"
#include "Resources/Loaders/ShaderLoader.hpp"
#include "Resources/Loaders/TextureLoader.hpp"


namespace Renderer
{
    class Model;
    class Texture;
    class Shader;
}

namespace Resources
{
    struct ReferenceShader
    {
        std::string vertexShader;
        std::string fragmentShader;

        Renderer::Shader* shader;
    };

    class ResourcesManager
    {
    private:
        std::unordered_map<std::string, Renderer::Model*   >  listModel;
        std::unordered_map<std::string, Renderer::Texture* >  listTexture;
        std::vector<ReferenceShader >                         listShader;

        Thread::TaskSystem taskSystem;
        Thread::ThreadPool threadPool;

        std::vector<Loaders::ModelLoader*> listModelLoader;
        std::vector<Loaders::ShaderLoader*> listShaderLoader;
        std::vector<Loaders::TextureLoader*> listTextureLoader;

    public: 
        ResourcesManager() = default;
        ~ResourcesManager() = default;

        Renderer::Model   LoadModel     (const char* path);
        Renderer::Texture LoadTexture   (const char* path);
        Renderer::Shader  LoadShader    (const char* vertexShader, const char* fragmentShader);

        void ReadFiles();

    };
}


#endif
