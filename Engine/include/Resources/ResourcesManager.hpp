#ifndef _RESOURCE_MANAGER_
#define _RESOURCE_MANAGER_

#include <vector>
#include <string>
#include <unordered_map>

#include "Renderer/Shader.hpp"
#include "Scene/Component/Model.hpp"
#include "Renderer/Texture.hpp"


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
        std::unordered_map<std::string, Component::Model   >  mapModel;
        std::unordered_map<std::string, Renderer::Texture >  mapTexture;
        std::vector<ReferenceShader >                        listShader;

    public: 
        ResourcesManager()  = default;
        ~ResourcesManager() = default;

        Component::Model   LoadModel     (const char* path);
        Renderer::Texture LoadTexture   (const char* path);
        Renderer::Shader  LoadShader    (const char* vertexShader, const char* fragmentShader);

    };
}

#endif
