#include "Scene/System/RenderSystem.hpp"

#include "Scene/Core/Types.hpp"
#include "Scene/Component/Transform.hpp"
#include "Scene/Component/Model.hpp"

#include "Scene/Core/World.hpp"

void RenderSystem::Init()
{

}


void RenderSystem::Draw(float deltaTime)
{
    for (Entity entity: _entities) {
        auto &t = World::Instance().GetComponent<Transform>(entity);
        auto &m = World::Instance().GetComponent<Component::Model>(entity);


        //material.shader.SetMatrix4("projection", );
        //material.shader.SetMatrix4("view", Maths::Matrix4::Translate({0, 0, 0}));
        //material.shader.SetMatrix4("model", Maths::Matrix4::Translate({0,0,10}) * Maths::Matrix4::RotateY(count) * Maths::Matrix4::RotateX(-3.1415 / 2) * Maths::Matrix4::Scale({1,1,1}));

        m.Draw(Maths::Matrix4::Perspective(1280, 720, -1, 10000, 20 * 3.1415/180),
               Maths::Matrix4::Translate({0, 0, 0}),
               Maths::Matrix4::Translate(t.position) * t.rotation.ToMatrix() * Maths::Matrix4::Scale(t.scale));
    }
}