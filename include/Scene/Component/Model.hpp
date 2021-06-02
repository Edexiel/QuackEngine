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

        template<class Archive>
        void save(Archive &archive) const
        {
            std::vector<std::string> materials;
            for (const auto &mat : model.GetMaterialList())
            {
                materials.push_back(mat->Path());
            }
            archive(cereal::make_nvp("path", model.GetPath()),
                    cereal::make_nvp("type", model._vertexType),
                    CEREAL_NVP(materials));
        }

        template<class Archive>
        void load(Archive &archive)
        {
            std::vector<std::string> materials;

            archive(cereal::make_nvp("path", model.Path()),
                    cereal::make_nvp("type", model._vertexType));
            archive(CEREAL_NVP(materials));

            Resources::ResourcesManager &resourcesManager = Engine::Instance().GetResourcesManager();
            model = resourcesManager.LoadModel(model.Path(), model._vertexType);
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