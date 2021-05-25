#ifndef QUACKENGINE_NAME_HPP
#define QUACKENGINE_NAME_HPP
#include <string_view>

#include "Scene/Component/ComponentBase.hpp"

namespace Component
{
    struct Name : public ComponentBase
    {
        Name() = default;
        Name(const std::string& name) {this->name = name;}
        std::string name;
    };
}

#endif //QUACKENGINE_NAME_HPP
