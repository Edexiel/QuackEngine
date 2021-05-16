#ifndef _MATERIAL_
#define _MATERIAL_

#include "Maths/Vector3.hpp"
#include "Maths/Vector4.hpp"
#include "Renderer/Shader.hpp"
#include "Renderer/Texture.hpp"
#include "Resources/Asset.hpp"

#include <memory>

namespace Renderer
{
    struct Material : public Resources::Asset
    {
        Shader shader;

        bool checkLight {true};

        Maths::Color4f  color    {1,1,1,1};
        Maths::Color3f ambient  {1,1,1};
        Maths::Color3f diffuse  {1,1,1};
        Maths::Color3f specular {1,1,1};

        float shininess {128};

        Texture colorTexture;
        Texture diffuseTexture;
        Texture specularTexture;
        Texture normalMap;

        bool hasSkeleton {false};

        std::string name;

        Material();
        void GenerateShader();
        ShaderConstructData GetConstructData() const;
        void Apply();
    };

    typedef std::shared_ptr<Material> MaterialInterface;
}

#endif //_MATERIAL_