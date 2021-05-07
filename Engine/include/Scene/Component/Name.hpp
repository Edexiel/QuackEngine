#ifndef QUACKENGINE_NAME_HPP
#define QUACKENGINE_NAME_HPP
#include <string_view>
#include <cereal/types/string_view.hpp>


namespace Component
{
    struct Name
    {
        std::string name;

        template<class Archive>
        void serialize(Archive & archive)
        {
            archive(name) ;
        }
    };
}

#endif //QUACKENGINE_NAME_HPP
