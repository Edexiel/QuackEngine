#ifndef _NOTEDISPLAYSYSTEM_HPP
#define _NOTEDISPLAYSYSTEM_HPP

#include "Scene/Core/System.hpp"
#include "Renderer/Texture.hpp"
#include "Renderer/ProcessBase.hpp"

namespace Component
{
    class Transform;
}

class EnemyComponent;

enum NoteType {M_UP = 0, M_DOWN, M_RIGHT, M_LEFT};

class EnemySystem : public System
{
    Renderer::Texture _listTexture[4];
    float _arrowScale {1};
    float _time {0.0f};
    float _hitCooldown {0.2f};

    bool MoveEnemy(EnemyComponent& enemy, Component::Transform& transform, const Maths::Vector3f& target);
    void HitEnemies(NoteType note);

public:

    void UpHit();
    void DownHit();
    void RightHit();
    void LeftHit();

    float hitRaduis {0.01f};

    EnemySystem();
    void GenerateEnemies(unsigned int numberToGenerate, const Maths::Vector3f& origin, float innerRadius, float outerRadius);
    void Update();
    void Process(const Renderer::Framebuffer &buffer, const Renderer::Mesh &screenMesh, Renderer::Shader& shader);
    float& GetArrowScale();

};

class NoteDisplayProcess : public Renderer::ProcessBase
{
    public:
        NoteDisplayProcess();
        void Process(const Renderer::Framebuffer &buffer, const Renderer::Mesh &screenMesh) override;
};

#endif //_NOTEDISPLAYSYSTEM_HPP
