#ifndef QUACKENGINE_NAME_HPP
#define QUACKENGINE_NAME_HPP

#include <string>
#include <cereal/types/string.hpp>

namespace Component
{
    struct Name
    {
        std::string name;

        template<class Archive>
        void serialize(Archive & archive)
        {
            archive(CEREAL_NVP(name));
        }
    };
}

#endif //QUACKENGINE_NAME_HPP
