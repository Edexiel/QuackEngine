#ifndef _COMPONENT_MODEL_
#define _COMPONENT_MODEL_

#include "Renderer/ModelRenderer.hpp"
#include "Resources/ResourcesManager.hpp"
#include <Engine.hpp>


namespace Component
{
    struct Model :public ComponentBase
    {
        Renderer::ModelRenderer model;
        Maths::Vector3f offset {0.f,0.f,0.f};

        template<class Archive>
        void save(Archive &archive) const
        {
            std::vector<std::string> materials;
            for (const auto &mat : model.GetMaterialList())
            {
                materials.push_back(mat->GetPath());
            }
            archive(cereal::make_nvp("path", model.GetPath()),
                    cereal::make_nvp("type", model._vertexType),
                    CEREAL_NVP(offset),
                    CEREAL_NVP(materials));
        }

        template<class Archive>
        void load(Archive &archive)
        {
            std::vector<std::string> materials;
            std::string path;

            archive(cereal::make_nvp("path", path),
                    cereal::make_nvp("type", model._vertexType),
                    CEREAL_NVP(offset));

            archive(CEREAL_NVP(materials));

            model.SetPath(path);

            Resources::ResourcesManager &resourcesManager = Engine::Instance().GetResourcesManager();
            model = resourcesManager.LoadModel(model.GetPath(), model._vertexType);
            for (const auto &mat : materials)
            {
                model.AddMaterial(resourcesManager.LoadMaterial(mat));
            }
        }
    };



//        template<class Archive>
//        void load(Archive &archive)
//        {
//            archive(CEREAL_NVP(name), cereal::make_nvp("type", _vertexType));
//            this =
//        }



}


#endif // _COMPONENT_MODEL_