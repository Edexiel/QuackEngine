#include "Enemy/EnemyManagerSystem.hpp"

#include "Engine.hpp"

#include "Scene/Core/World.hpp"
#include "Scene/Component/Transform.hpp"
#include "Scene/System/CameraSystem.hpp"

#include "Renderer/RendererPlatform.hpp"

#include "Enemy/EnemyComponent.hpp"
#include "Tools/Random.hpp"

EnemyManagerSystem::EnemyManagerSystem()
{

    Engine &engine = Engine::Instance();
    _listTexture[0] = engine.GetResourcesManager().LoadTexture("./Asset/Texture/Arrow/Up.png");
    _listTexture[1] = engine.GetResourcesManager().LoadTexture("./Asset/Texture/Arrow/Down.png");
    _listTexture[2] = engine.GetResourcesManager().LoadTexture("./Asset/Texture/Arrow/Right.png");
    _listTexture[3] = engine.GetResourcesManager().LoadTexture("./Asset/Texture/Arrow/Left.png");

    Input::InputManager& inputManager = engine.GetInputManager();

    inputManager.BindEvent("Up Hit", Input::Key::KEY_UP);
    inputManager.RegisterEvent("Up Hit", Input::Action::PRESS, this, &EnemyManagerSystem::UpHit);

    inputManager.BindEvent("Down Hit", Input::Key::KEY_DOWN);
    inputManager.RegisterEvent("Down Hit", Input::Action::PRESS, this, &EnemyManagerSystem::DownHit);

    inputManager.BindEvent("Right Hit", Input::Key::KEY_RIGHT);
    inputManager.RegisterEvent("Right Hit", Input::Action::PRESS, this, &EnemyManagerSystem::RightHit);

    inputManager.BindEvent("Left Hit", Input::Key::KEY_LEFT);
    inputManager.RegisterEvent("Left Hit", Input::Action::PRESS, this, &EnemyManagerSystem::LeftHit);
}

void
EnemyManagerSystem::GenerateEnemies(unsigned int numberToGenerate, const Maths::Vector3f &origin, float innerRadius,
                                    float outerRadius)
{
    World &world = Engine::Instance().GetCurrentWorld();

    srand((unsigned int) Engine::Instance().GetTimeManager().GetTime());

    for (unsigned int i = 0; i < numberToGenerate; i++)
    {
        Entity id = world.CreateEntity("Enemy");

        Component::Transform trs;
        Maths::Vector3f direction{Random::Range(0.f, 1.0f), 0, Random::Range(0.0f, 1.0f)};
        direction.Normalize();
        trs.position = origin * innerRadius;
        world.AddComponent(id, trs);

        EnemyComponent enemyWeaknessDisplay;
        enemyWeaknessDisplay.AddNote(NoteType::M_DOWN);
        enemyWeaknessDisplay.AddNote(NoteType::M_LEFT);
        enemyWeaknessDisplay.AddNote(NoteType::M_RIGHT);
        enemyWeaknessDisplay.AddNote(NoteType::M_UP);
        world.AddComponent(id, enemyWeaknessDisplay);
    }
}

void EnemyManagerSystem::HitEnemies(NoteType note)
{
    Engine& engine = Engine::Instance();

    if (engine.GetTimeManager().GetTime() - _time < _hitCooldown)
        return;

    _time = (float) Engine::Instance().GetTimeManager().GetTime();

    std::vector<Entity> entityToDestroy;
    for (Entity entity: _entities)
    {
        auto &enemy = Engine::Instance().GetCurrentWorld().GetComponent<EnemyComponent>(entity);
        enemy.RemoveNote(note);

        if (enemy.GetNoteList().empty())
            entityToDestroy.push_back(entity);
    }
    for (unsigned int i = 0; i < entityToDestroy.size(); i++)
    {
        engine.GetCurrentWorld().DestroyEntity(entityToDestroy[i]);
    }
}

void EnemyManagerSystem::UpHit()
{
    HitEnemies(NoteType::M_UP);
}

void EnemyManagerSystem::DownHit()
{
    HitEnemies(NoteType::M_DOWN);
}

void EnemyManagerSystem::RightHit()
{
    HitEnemies(NoteType::M_RIGHT);
}

void EnemyManagerSystem::LeftHit()
{
    HitEnemies(NoteType::M_LEFT);
}

void EnemyManagerSystem::Process(const Renderer::Framebuffer &buffer, const Renderer::Mesh &screenMesh,
                                 Renderer::Shader &shader)
{
    Engine &engine = Engine::Instance();
    World &world = engine.GetCurrentWorld();

    Component::Camera &camera = world.GetSystem<CameraSystem>()->GetActiveCamera();

    buffer.Bind();
    shader.Use();
    shader.SetMatrix4("view", camera.GetView());
    shader.SetMatrix4("projection", camera.GetProjection());
    buffer.BindTexture(0);

    shader.SetSampler("frame", 0);
    shader.SetSampler("noteTexture", 1);

    Renderer::RendererPlatform::SetTransparency(true);
    Renderer::RendererPlatform::EnableDepthBuffer(false);

    Maths::Matrix4 invertView = camera.GetView().GetInvert();
    Component::Transform cameraTransform = world.GetComponent<Component::Transform>(camera.GetEntity());

    for (Entity entity: _entities)
    {
        auto &transform = world.GetComponent<Component::Transform>(entity);
        auto &enemy = world.GetComponent<EnemyComponent>(entity);

        MoveEnemy(enemy, transform, {0, 0, 0});

        if (!enemy.GetNoteList().empty())
        {
            _listTexture[enemy.GetNoteList()[0]].Bind(1);
            shader.SetMatrix4("model",
            Maths::Matrix4::Translate(transform.position)
            *
            Maths::Matrix4::LookAtMatrix(transform.position,  transform.position + cameraTransform.Forward(), {0,1,0}).GetInvert()
            * Maths::Matrix4::Scale(transform.scale * _arrowScale));

            screenMesh.Draw();

        }
    }

    Renderer::RendererPlatform::BindFramebuffer(0);
}


float &EnemyManagerSystem::GetArrowScale()
{
    return _arrowScale;
}

void
EnemyManagerSystem::MoveEnemy(EnemyComponent &enemy, Component::Transform &transform, const Maths::Vector3f &target)
{
    Maths::Vector3f direction = target - transform.position;

    if (direction.Length() <= hitRaduis)
        return;

    direction.Normalize();
    transform.position =
            transform.position + direction * Engine::Instance().GetTimeManager().GetDeltaTime() * enemy.speed;
    transform.rotation = Maths::Quaternion::LookAt(transform.position, target);
}

NoteDisplayProcess::NoteDisplayProcess() :
        Renderer::ProcessBase("EnemyManagerSystem",
                              Engine::Instance().GetResourcesManager().LoadShader
                                      ("../../Game/Asset/Shader/NoteDisplayShader.qsh"))
{}

void NoteDisplayProcess::Process(const Renderer::Framebuffer &buffer, const Renderer::Mesh &screenMesh)
{
    Engine::Instance().GetCurrentWorld().GetSystem<EnemyManagerSystem>()->Process(buffer, screenMesh, _shader);
}