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

    std::vector<Renderer::MaterialInterface> _listMaterial;

    std::unordered_map<Renderer::MaterialInterface, std::vector<std::pair<Renderer::Mesh, Entity>>> _mapMaterial;

public:

    RenderSystem();
    ~RenderSystem() = default;

    void SetMaterials();
    void DrawMaterials();

    void Draw(Component::Camera& camera);
    void DrawTextureInFramebuffer(unsigned int framebufferIndex, unsigned int textureIndex);

    void AddMaterial(Renderer::MaterialInterface materialInterface);
    void RemoveMaterial(Renderer::MaterialInterface materialInterface);

    void AddMesh(Renderer::MaterialInterface materialInterface, Renderer::Mesh mesh, Entity entity);


};

#endif