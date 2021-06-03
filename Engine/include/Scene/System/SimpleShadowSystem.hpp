#ifndef _SHADOWCIRCLESYSTEM_HPP
#define _SHADOWCIRCLESYSTEM_HPP

#include "Scene/Core/System.hpp"
#include "Renderer/Shader.hpp"
#include "Scene/Component/SimpleShadow.hpp"

#include "Renderer/ProcessBase.hpp"

namespace Renderer
{
    class Framebuffer;
    class Mesh;
}

class SimpleShadowSystem : public System
{

    std::vector<Renderer::Shader> _listShadowShader;

public:

    SimpleShadowSystem();
    void Process(const Renderer::Framebuffer &buffer, const Renderer::Mesh &screenMesh);
};

class SimpleShadowProcess : public Renderer::ProcessBase
{
    void Process(const Renderer::Framebuffer &buffer, const Renderer::Mesh &screenMesh) override;
};

#endif //QUACKENGINE_SHADOWCIRCLESYSTEM_HPP
