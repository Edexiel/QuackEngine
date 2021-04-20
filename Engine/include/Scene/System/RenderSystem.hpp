#ifndef _RENDER_SYSTEM_
#define _RENDER_SYSTEM_

#include "Scene/Core/System.hpp"
#include "Scene/Component/Model.hpp"
#include "Scene/Component/Transform.hpp"

#include <vector>
#include <unordered_map>

namespace Maths
{
    class Matrix4;
}
namespace Component
{
    class Camera;
}

class RenderSystem : public System
{
    Renderer::Shader _shader;
    Renderer::Mesh _quadMesh;

    std::unordered_map<Renderer::MaterialInterface, std::vector<std::pair<Renderer::Mesh, Entity>>> _mapMaterial;
    unsigned int _lastLinkEntitiesNumbers {0};

public:

    RenderSystem();
    ~RenderSystem() = default;

    /**
     * @brief Draw the scene from the camera point of view
     * @param camera
     */
    void Draw(Component::Camera& camera);
    void DrawTextureInFramebuffer(unsigned int framebufferIndex, unsigned int textureIndex);

    void SetMaterials();

private:

    void DrawMaterials(Component::Camera& camera);

    void AddMesh(Renderer::MaterialInterface materialInterface, const Renderer::Mesh& mesh, Entity entity);


};

#endif