#include "Renderer/Material.hpp"
#include "Scene/Core/World.hpp"

using namespace Renderer;

void Material::GenerateShader()
{

    ShaderConstructData scd{checkLight, colorTexture.GetID() != 0,
                            diffuseTexture.GetID() != 0,
                            specularTexture.GetID() != 0,
                            normalMap.GetID() != 0};

    shader = World::Instance().GetResourcesManager().LoadObjectShader(scd);
}

void Material::Apply()
{
  shader.Use();
  shader.SetVector4f("material.color", color);
  shader.SetVector3f("material.ambient", ambient);
  shader.SetVector3f("material.diffuse", diffuse);
  shader.SetVector3f("material.specular", specular);
  shader.SetFloat("material.shininess", shininess);

  if (colorTexture.GetID() != 0)
  {
    colorTexture.Bind(0);
    shader.SetSampler("material.colorTexture", 0);
  }

  if (diffuseTexture.GetID() != 0)
  {
    diffuseTexture.Bind(1);
    shader.SetSampler("material.diffuseTexture", 1);
  }

  if (specularTexture.GetID() != 0)
  {
    specularTexture.Bind(2);
    shader.SetSampler("material.specularTexture", 2);
  }

  if (normalMap.GetID() != 0)
  {
    normalMap.Bind(3);
    shader.SetSampler("material.normalMap", 3);
  }




}