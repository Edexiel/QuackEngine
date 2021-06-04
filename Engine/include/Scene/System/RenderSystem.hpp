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
    struct MaterialMeshData
    {
        Renderer::Mesh mesh;
        Maths::Vector3f offset {0.f,10.f,0.f};
        Entity entity {0};
    };


    std::unordered_map<Renderer::MaterialInterface, std::vector<MaterialMeshData>> _mapMaterial;
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
    void AddMesh(const Renderer::MaterialInterface &materialInterface, const Renderer::Mesh &mesh, Maths::Vector3f offset, Entity entity);

};

#endif