#ifndef _RENDER_SYSTEM_
#define _RENDER_SYSTEM_

#include "Scene/Core/System.hpp"
#include "Scene/Component/Model.hpp"

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

public:
    void Init();
    void Update(Component::Camera& camera);
    void Draw(Component::Camera& camera);

};

#endif