#ifndef _COMPONENT_MODEL_
#define _COMPONENT_MODEL_

namespace Component
{



        template<class Archive>
        void save(Archive &archive)
        {
            archive(CEREAL_NVP(name), cereal::make_nvp("type", _vertexType));
        }

//        template<class Archive>
//        void load(Archive &archive)
//        {
//            archive(CEREAL_NVP(name), cereal::make_nvp("type", _vertexType));
//            this =
//        }



}


#endif // _COMPONENT_MODEL_