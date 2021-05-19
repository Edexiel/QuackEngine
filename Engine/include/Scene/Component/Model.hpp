#ifndef _COMPONENT_MODEL_
#define _COMPONENT_MODEL_

#include "Renderer/ModelRenderer.hpp"

namespace Component
{
    struct Model
    {
        Renderer::ModelRenderer model;

        template<class Archive>
        void save(Archive &archive) const
        {
            archive(CEREAL_NVP(model.name), cereal::make_nvp("type", model._vertexType));
        }

        template<class Archive>
        void load(Archive &archive)
        {
            archive(CEREAL_NVP(model.name), cereal::make_nvp("type", model._vertexType));
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