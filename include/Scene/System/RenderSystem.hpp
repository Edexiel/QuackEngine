#ifndef _RENDER_SYSTEM_
#define _RENDER_SYSTEM_

#include "Scene/Core/System.hpp"
#include "Scene/Component/Transform.hpp"

#include "Renderer/Material.hpp"
#include "Renderer/Mesh.hpp"

#include <vector>
#include <unordered_map>

namespace Maths
{
    class Matrix4;
}

namespace Component
{
    class Transform;
    class Model;
    class Camera;
}
namespace Renderer
{
    class ModelRenderer;
}

class RenderSystem : public System
{
    std::unordered_map<Renderer::MaterialInterface, std::vector<std::pair<Renderer::Mesh, Entity>>> _mapMaterial;
    unsigned int _lastLinkEntitiesNumbers{0};

public:

    RenderSystem() = default;
    ~RenderSystem() = default;

    /**
     * @brief Draw the scene from the camera point of view
     * @param camera
     */
    void Draw(Component::Camera &camera);
    void Draw(const Maths::Matrix4 &projection, const Maths::Matrix4 &view);

    void UpdateModel(const Renderer::ModelRenderer &newModel);

    void SetMaterials();

    void Clear();

private:
    void DrawMaterials(const Maths::Matrix4 &projection, const Maths::Matrix4 &view);
    void AddMesh(const Renderer::MaterialInterface &materialInterface, const Renderer::Mesh &mesh, Entity entity);

};

#endif