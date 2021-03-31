#include "GLFW/glfw3.h"
#include "reactphysics3d/reactphysics3d.h"

#include "Renderer/RendererPlatform.hpp"
#include "Renderer/Shader.hpp"
#include "Renderer/Framebuffer.hpp"
#include "Renderer/Texture.hpp"
#include "Renderer/Vertex.hpp"
#include "Renderer/Mesh.hpp"
#include "Renderer/Light.hpp"
#include "Renderer/Material.hpp"

#include "Resources/ResourcesManager.hpp"

#include "Maths/Quaternion.hpp"


#include <cmath>

using namespace Renderer;

const char* vertexShaderFb =
    {
        R"GLSL(
                      #version 330 core
                      layout (location = 0) in vec3 aPos;
                      layout (location = 1) in vec3 aNormal;
                      layout (location = 2) in vec2 aTexCoord;

                      uniform mat4 view;

                      out vec2 TexCoord;

                      void main()
                      {
                      gl_Position = view * vec4(aPos, 1.0);
                      TexCoord = aTexCoord;
                     }
                     )GLSL"
    };
const char* fragmentShaderFb =
    {
        R"GLSL(
                     #version 330 core
                     out vec4 FragColor;
                     in vec2 TexCoord;

                     uniform sampler2D ourTexture;

                     void main()
                     {
                      FragColor = texture(ourTexture, TexCoord);
                     }
                     )GLSL"
    };


class TestCollision: public rp3d::EventListener
{
    virtual void onContact(const CallbackData& callbackData) override
    {
        std::cout << "Bonjour\n";
    }
};

int main()
{
  GLFWwindow* window;
  unsigned int width = 1280, height = 720;
  /* Initialize the library */
  if (!glfwInit())
    return -1;
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  /* Create a windowed mode window and its OpenGL context */
  window = glfwCreateWindow(width, height, "RendererPlatform", NULL, NULL);
  if (!window)
  {
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);
  {
    // loadGL
    RendererPlatform::LoadGL();

    Resources::ResourcesManager rm;

    // Shader fb
    Shader shaderFb(Renderer::RendererPlatform::CreateShader(
        vertexShaderFb, fragmentShaderFb));
    // Framebuffer
    Renderer::Framebuffer framebuffer =
        Renderer::RendererPlatform::CreateFramebuffer(width, height);

    Mesh quad    = RendererPlatform::CreateQuad();
    Mesh sphere  = RendererPlatform::CreateSphere();
    Mesh floor   = RendererPlatform::CreateCube();
    Mesh trigger = RendererPlatform::CreateCube();

    RendererPlatform::VerticesReading();

    Renderer::Light light(Renderer::Light_Type::L_POINT);

    light.model = Maths::Matrix4::RotateX(-3.1415 / 2) * Maths::Matrix4::Translate({0,0, 0});
    light.ambient = {0.0f, 0.1f, 0.0f};
    light.diffuse = {0.7f, 0.7f, 0.7f};
    light.specular = {1.0f, 1.0f, 1.0f};
    light.constant = 1.0f;
    light.linear = 0.0014f;
    light.quadratic = 0.000007f;

    light.outerSpotAngle = 10.5;
    light.spotAngle = 8.5;

    ShaderConstructData shd = {1,1,0, 0, 0, 0, 0, 0};

    Shader shader = Shader::LoadShader(shd);

    RendererPlatform::UseShader(shader.ID);
    shader.SetMatrix4
        (
            "projection",
            Maths::Matrix4::Perspective(width, height, -1.f, 100.f, 3.1415f / 2.f)
        );
    shader.SetMatrix4("view", Maths::Matrix4::Identity());

    Material material;
    material.shader = shader;

    material.ambient = {1, 1, 1};
    material.diffuse = {1, 1, 1};
    material.specular = {1, 1, 1};
    material.shininess = 256;


    float count = 0;

    RendererPlatform::EnableDepthBuffer(true);

// reactphysics3d
    rp3d::PhysicsWorld::WorldSettings settings;
    settings.defaultVelocitySolverNbIterations = 20;
    settings.isSleepingEnabled = false;
    settings.gravity = reactphysics3d::Vector3(0, -9.81, 0);

    rp3d::PhysicsCommon physicsCommon;
    rp3d::PhysicsWorld* world = physicsCommon.createPhysicsWorld(settings);

    rp3d::Vector3 positionSphere{0,10,10};
    rp3d::Quaternion rotationSphere = reactphysics3d::Quaternion::identity();

    rp3d::Vector3 positionFloor{0, -1, 10};
    rp3d::Quaternion rotationFloor = reactphysics3d::Quaternion::identity();

    rp3d::Vector3 positionTrigger{0, 1, 10};
    rp3d::Quaternion rotationTrigger = reactphysics3d::Quaternion::identity();

    rp3d::Transform transformSphere(positionSphere, rotationSphere);
    rp3d::Transform transformFloor(positionFloor, rotationFloor);
    rp3d::Transform transformTrigger(positionTrigger, rotationTrigger);

    rp3d::RigidBody * rbSphere = world->createRigidBody(transformSphere);
    rp3d::RigidBody * rbFloor = world->createRigidBody(transformFloor);
    rp3d::RigidBody * rbTrigger = world->createRigidBody(transformTrigger);

    rbSphere->setType(reactphysics3d::BodyType::DYNAMIC);
    rbFloor->setType(reactphysics3d::BodyType::STATIC);
    rbTrigger->setType(reactphysics3d::BodyType::STATIC);

    rp3d::SphereShape* sphereShape = physicsCommon.createSphereShape(1.f);
    Maths::Vector3f scaleFloor{5, 0.25, 5};
    rp3d::BoxShape* floorShape = physicsCommon.createBoxShape({scaleFloor.x, scaleFloor.y, scaleFloor.z});

    Maths::Vector3f scaleTrigger{1.0f, 1.0f, 1.0f};
    rp3d::BoxShape* triggerShape = physicsCommon.createBoxShape({scaleTrigger.x, scaleTrigger.y, scaleTrigger.z});

    rp3d::Collider* colliderSphere = rbSphere->addCollider(sphereShape, rp3d::Transform::identity());
    rp3d::Collider* colliderFloor = rbFloor->addCollider(floorShape, rp3d::Transform::identity());
    rp3d::Collider* colliderTrigger = rbFloor->addCollider(triggerShape, rp3d::Transform::identity());

    rp3d::Material& materialFloor = colliderFloor->getMaterial();
    materialFloor.setBounciness(0.2f);

    while (!glfwWindowShouldClose(window))
    {
      world->update(1.f/144.f);
      rp3d::Transform ts = rbSphere->getTransform();
      Maths::Vector3f posSphere {ts.getPosition().x, ts.getPosition().y, ts.getPosition().z};
      Maths::Quaternion rotSphere {ts.getOrientation().w, ts.getOrientation().x, ts.getOrientation().y, ts.getOrientation().z};

      rp3d::Transform tf = rbFloor->getTransform();
      Maths::Vector3f posFloor {tf.getPosition().x, tf.getPosition().y, tf.getPosition().z};
      Maths::Quaternion rotFloor {tf.getOrientation().w, tf.getOrientation().x, tf.getOrientation().y, tf.getOrientation().z};

      rp3d::Transform tt = rbTrigger->getTransform();
      Maths::Vector3f posTrigger {tt.getPosition().x, tt.getPosition().y, tt.getPosition().z};
      Maths::Quaternion rotTrigger {tt.getOrientation().w, tt.getOrientation().x, tt.getOrientation().y, tt.getOrientation().z};

      count += 0.01f;

      if (glfwGetKey(window, GLFW_KEY_ESCAPE))
      {
        glfwSetWindowShouldClose(window, 1);
      }
      // framebuffer
      {
        framebuffer.Bind();
        RendererPlatform::ClearColor({0.0f, 0.5f, 0.5f, 1.f});
        RendererPlatform::Clear();

        light.model = Maths::Matrix4::Translate({cos(count) * 30, sin(count) * 30, 0});


        material.Apply();

        material.shader.SetMatrix4("projection", Maths::Matrix4::Perspective(width, height, -1, 10000, 20 * 3.1415/180));
        material.shader.SetMatrix4("view", Maths::Matrix4::Translate({0, -5, 0}) * Maths::Quaternion({1,0,0}, -3.14f/6.f).ToMatrix());

        shader.SetLight(light, 0);

        material.shader.SetMatrix4("model", Maths::Matrix4::Translate(posSphere) * rotSphere.ToMatrix() * Maths::Matrix4::Scale({1,1,1}));
        sphere.Draw();

        material.shader.SetMatrix4("model", Maths::Matrix4::Translate(posFloor) * rotFloor.ToMatrix() * Maths::Matrix4::Scale(scaleFloor));
        floor.Draw();

        material.shader.SetMatrix4("model", Maths::Matrix4::Translate(posTrigger) * rotTrigger.ToMatrix() * Maths::Matrix4::Scale(scaleTrigger));
        trigger.Draw();

        RendererPlatform::BindFramebuffer(0);
      }

      RendererPlatform::ClearColor({0.2f, 0.2f, 0.2f, 1.f});
      RendererPlatform::Clear();
      shaderFb.Use();
      shaderFb.SetMatrix4("view", Maths::Matrix4::Identity());
      framebuffer.BindTexture();
      quad.Draw();
      glfwSwapBuffers(window);
      glfwPollEvents();
    }
  }
  glfwTerminate();
  return 0;
}