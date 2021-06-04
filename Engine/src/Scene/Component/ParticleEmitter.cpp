#include "Engine.hpp"

#include "Scene/Core/World.hpp"
#include "Renderer/Texture.hpp"

#include "Renderer/Framebuffer.hpp"

#include "Scene/System/CameraSystem.hpp"

#include "Scene/Component/ParticleEmitter.hpp"
#include "Scene/Component/Transform.hpp"

#include "Renderer/RendererPlatform.hpp"

#include "Tools/Random.hpp"

#include <cmath>

using namespace Component;
using namespace Renderer;

ParticleEmitter::ParticleEmitter()
{
    _shader = Engine::Instance().GetResourcesManager().LoadShader("./Shader/PostProcess/FadingParticle.qsh");
}

ParticleEmitter::ParticleEmitter(unsigned int size, float duration, const Texture& texture) :
        _duration(duration), _texture(texture)
{
    _shader = Engine::Instance().GetResourcesManager().LoadShader("./Shader/PostProcess/FadingParticle.qsh");

    _listParticle.resize(size);

    for (unsigned int i = 0; i < _listParticle.size(); i++)
    {
        _listParticle[i].life = (float)i / (float)size;
    }
}

ParticleEmitter::ParticleEmitter(unsigned int size, float duration) : _duration(duration)
{
    _shader = Engine::Instance().GetResourcesManager().LoadShader("./Shader/PostProcess/FadingParticle.qsh");

    _listParticle.resize(size);

    for (unsigned int i = 0; i < _listParticle.size(); i++)
    {
        _listParticle[i].life = (float)i / (float)size;
    }
}

void ParticleEmitter::Process(const Renderer::Framebuffer &buffer, const Renderer::Mesh &screenMesh)
{

    Engine& engine = Engine::Instance();
    World& world = engine.GetCurrentWorld();

    float deltaTime = (float)Engine::Instance().GetTimeManager().GetDeltaTime();
    float minus = deltaTime / _duration;

    buffer.Bind();
    _shader.Use();

    if (_texture.GetID() != 0)
    {
        _shader.SetFloat("hasTexture", 0.f);
        _texture.Bind();
    }
    else
    {
        _shader.SetFloat("hasTexture", 1.f);
    }

    Component::Camera& camera = world.GetSystem<CameraSystem>()->GetActiveCamera();
    auto& camTrs = world.GetComponent<Component::Transform>(camera.GetEntity());
    auto& trs = world.GetComponent<Component::Transform>(_entity);

    _shader.SetMatrix4("projection", camera.GetProjection());
    _shader.SetMatrix4("view", camera.GetView());

    Maths::Matrix4 scale = Maths::Matrix4::Scale(camTrs.scale);
    Maths::Matrix4 lookAtCam = Maths::Matrix4::LookAtMatrixRotation(trs.position, trs.position - camTrs.Forward(), {0.f,1.f,0.f});

    Renderer::RendererPlatform::EnableDepthBuffer(false);
    Renderer::RendererPlatform::SetTransparency(true);

    for (unsigned int i = 0; i < _listParticle.size(); i++)
    {
        _listParticle[i].life += minus;
        if (_listParticle[i].life >= 1.0f)
        {
            ResetParticle(_listParticle[i]);
        }

        DrawParticle(_listParticle[i], screenMesh, scale, lookAtCam);
    }
}

void ParticleEmitter::ResetParticle(Particle &particle)
{
    particle.life = 0;
    auto& trs = Engine::Instance().GetCurrentWorld().GetComponent<Component::Transform>(_entity);

    particle.start = trs.position;
    Maths::Vector2f rotate = Maths::Vector2f::Rotate({1.f, 0.f}, Random::Range(_angleStart, _angleEnd));
    particle.end = particle.start + Maths::Vector3f (rotate.x, rotate.y, 0.f) * Random::Range(_lengthStart, _lengthEnd);
}

void ParticleEmitter::DrawParticle(const Renderer::Particle& particle, const Renderer::Mesh &screenMesh,
                                   const Maths::Matrix4& scale, const Maths::Matrix4& emitterRotation)
{
    _shader.SetVector4f("color", Maths::Color4f::Lerp(_colorStart, _colorEnd, particle.life));
    _shader.SetMatrix4("model", emitterRotation *
                       Maths::Matrix4::Translate(Maths::Vector3f::Lerp(particle.start, particle.end, particle.life))*
                       scale);
    screenMesh.Draw();
}

float &ParticleEmitter::AngleStart()
{
    return _angleStart;
}

float &ParticleEmitter::AngleEnd()
{
    return _angleEnd;
}

float &ParticleEmitter::LengthStart()
{
    return _lengthStart;
}

float &ParticleEmitter::LengthEnd()
{
    return _lengthEnd;
}

float ParticleEmitter::GetDuration()
{
    return _duration;
}

void ParticleEmitter::SetDuration(float duration)
{
    _duration = duration;
    for (unsigned int i = 0; i < _listParticle.size(); i++)
    {
        _listParticle[i].life = (float)i / (float)_listParticle.size();
    }
}

Maths::Color4f &ParticleEmitter::ColorStart()
{
    return _colorStart;
}

Maths::Color4f &ParticleEmitter::ColorEnd()
{
    return _colorEnd;
}

Renderer::Texture &ParticleEmitter::GetTexture()
{
    return _texture;
}

int ParticleEmitter::GetSize()
{
    return _listParticle.size();
}

void ParticleEmitter::SetSize(unsigned int size)
{
    if (size == _listParticle.size())
        return;

    _listParticle.clear();
    _listParticle.resize(size);

    for (unsigned int i = 0; i < _listParticle.size(); i++)
    {
        ResetParticle(_listParticle[i]);
        _listParticle[i].life = (float)i / (float)size;
    }
}