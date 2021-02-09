#ifndef _RESOURCE_MANAGER_
#define _RESOURCE_MANAGER_

#include <vector>
#include <string>
#include <unordered_map>


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
    };

    class ResourcesManager
    {
    private:
        std::unordered_map<std::string, Renderer::Model*   >  listModel;
        std::unordered_map<std::string, Renderer::Texture* >  listTexture;
        std::vector<ReferenceShader >              listShader;

    public: 
        ResourcesManager()   {};
        ~ResourcesManager()  {};

        Renderer::Model   LoadModel     (const char* path);
        Renderer::Texture LoadTexture   (const char* path);
        Renderer::Shader  LoadShader    (const char* vertexShader, const char* fragmentShader);

    };
}


#endif
