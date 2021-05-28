#ifndef QUACKENGINE_NAME_HPP
#define QUACKENGINE_NAME_HPP

#include <string>
#include <cereal/types/string.hpp>

#include "Scene/Component/ComponentBase.hpp"

namespace Component
{
    struct Name : public ComponentBase
    {
        Name() = default;
        Name(const std::string& name) {this->name = name;}
        std::string name;

        template<class Archive>
        void serialize(Archive & archive)
        {
            archive(CEREAL_NVP(name));
        }
    };
}

#endif //QUACKENGINE_NAME_HPP
