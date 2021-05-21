#ifndef _COMPONENT_MODEL_
#define _COMPONENT_MODEL_

#include "Renderer/ModelRenderer.hpp"
#include "Resources/ResourcesManager.hpp"
#include <Engine.hpp>


namespace Component
{
    struct Model
    {
        Renderer::ModelRenderer model;

        template<class Archive>
        void save(Archive &archive) const
        {
            archive(cereal::make_nvp("path",model.name), cereal::make_nvp("type", model._vertexType));
        }

        template<class Archive>
        void load(Archive &archive)
        {
            archive(cereal::make_nvp("path",model.name), cereal::make_nvp("type", model._vertexType));
            Resources::ResourcesManager &resourcesManager = Engine::Instance().GetResourcesManager();
            model = resourcesManager.LoadModel(model.name,model._vertexType);
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