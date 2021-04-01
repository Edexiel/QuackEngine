#ifndef _MATERIAL_
#define _MATERIAL_

#include "Maths/Vector3.hpp"
#include "Maths/Vector4.hpp"
#include "Renderer/Shader.hpp"
#include "Renderer/Texture.hpp"

namespace Renderer
{
  struct Material
  {

    Shader shader;

    bool checkLight {true};

    Maths::Color4f  color    {1,1,1,1};
    Maths::Vector3f ambient  {1,1,1};
    Maths::Vector3f diffuse  {1,1,1};
    Maths::Vector3f specular {1,1,1};

    float shininess {128};

    Texture colorTexture;
    Texture diffuseTexture;
    Texture specularTexture;
    Texture normalMap;

    void GenerateShader();
    void Apply();
  };
}

#endif //_MATERIAL_