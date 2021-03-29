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

    Mesh quad   = RendererPlatform::CreateQuad();
    Mesh sphere = RendererPlatform::CreateSphere();
    Mesh cube   = RendererPlatform::CreateCube();

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
    reactphysics3d::PhysicsWorld::WorldSettings settings;
    settings.defaultVelocitySolverNbIterations = 20;
    settings.isSleepingEnabled = false;
    settings.gravity = reactphysics3d::Vector3(0, -9.81, 0);

    reactphysics3d::PhysicsCommon physicsCommon;
    reactphysics3d::PhysicsWorld* world = physicsCommon.createPhysicsWorld(settings);
    reactphysics3d::Vector3 positionSphere{0,1,10};
    reactphysics3d::Quaternion rotationSphere = reactphysics3d::Quaternion::identity();

    reactphysics3d::Vector3 positionCube{0,-1,10};
    reactphysics3d::Quaternion rotationCube = reactphysics3d::Quaternion::identity();

    reactphysics3d::Transform transformSphere(positionSphere, rotationSphere);
    reactphysics3d::Transform transformCube(positionCube, rotationCube);

    reactphysics3d::RigidBody * rbSphere = world->createRigidBody(transformSphere);
    reactphysics3d::RigidBody * rbCube = world->createRigidBody(transformCube);

    rbSphere->setType(reactphysics3d::BodyType::DYNAMIC);
    rbCube->setType(reactphysics3d::BodyType::STATIC);

    reactphysics3d::SphereShape* sphereShape = physicsCommon.createSphereShape(1.f);
    Maths::Vector3f scaleCube{1, 1, 1};
    reactphysics3d::BoxShape* cubeShape = physicsCommon.createBoxShape({scaleCube.x * 0.5f, scaleCube.y * 0.5f, scaleCube.z * 0.5f});

    reactphysics3d::Collider* colliderSphere = rbSphere->addCollider(sphereShape, transformSphere);
    reactphysics3d::Collider* colliderCube = rbCube->addCollider(cubeShape, transformCube);

    while (!glfwWindowShouldClose(window))
    {
      world->update(1.f/144.f);
      reactphysics3d::Transform ts = rbSphere->getTransform();
      Maths::Vector3f posSphere {ts.getPosition().x, ts.getPosition().y, ts.getPosition().z};
      Maths::Quaternion rotSphere {ts.getOrientation().w, ts.getOrientation().x, ts.getOrientation().y, ts.getOrientation().z};

      reactphysics3d::Transform tc = rbCube->getTransform();
      Maths::Vector3f posCube {tc.getPosition().x, tc.getPosition().y, tc.getPosition().z};
      Maths::Quaternion rotCube {tc.getOrientation().w, tc.getOrientation().x, tc.getOrientation().y, tc.getOrientation().z};

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
        material.shader.SetMatrix4("model", Maths::Matrix4::Translate(posSphere) * rotSphere.ToMatrix() * Maths::Matrix4::Scale({1,1,1}));

        shader.SetLight(light, 0);

        sphere.Draw();
        material.shader.SetMatrix4("model", Maths::Matrix4::Translate(posCube) * rotCube.ToMatrix() * Maths::Matrix4::Scale(scaleCube));
        cube.Draw();

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