#include "NoteDisplaySystem.hpp"

#include "Engine.hpp"
#include "Renderer/RendererPlatform.hpp"
#include "EnemyWeaknessDisplay.hpp"

NoteDisplaySystem::NoteDisplaySystem() :
Renderer::ProcessBase("NoteDisplaySystem", Engine::Instance().GetResourcesManager().LoadShader("../../Game/Asset/Shader/NoteDisplayShader.qsh"))
{}

void NoteDisplaySystem::Process(const Renderer::Framebuffer &buffer, const Renderer::Mesh &screenMesh)
{

    Engine& engine = Engine::Instance();
    World& world = engine.GetCurrentWorld();

    Component::Camera& camera = engine.GetRendererInterface().cameraSystem->GetActiveCamera();

    buffer.Bind();
    _shader.Use();
    buffer.BindTexture();
    _shader.SetMatrix4("view", camera.GetView());
    _shader.SetMatrix4("projection", camera.GetProjection());

    for (Entity entity: _entities)
    {
        std::cout << "Note Display System" << std::endl;

        auto &transform = world.GetComponent<Component::Transform>(entity);
        auto &enemy = world.GetComponent<EnemyWeaknessDisplay>(entity);

        for (unsigned int i = 0; i < enemy.GetNoteList().size(); i++)
        {
            _shader.SetMatrix4("model", transform.GetMatrix());
            screenMesh.Draw();
        }
    }

    Renderer::RendererPlatform::BindFramebuffer(0);
}