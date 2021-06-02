#ifndef _COMPONENT_HPP
#define _COMPONENT_HPP

#include "Scene/Core/Types.hpp"

namespace Component
{
    class ComponentBase
    {
    protected:
        bool _isActive {true};
        Entity _entity {0};

    public:
        static void LinkEntityToComponent(Entity entity, ComponentBase* componentBase);
        Entity GetEntity() const;

        bool IsActive() const;
        void SetActive(bool active);
    };
}

#endif //_COMPONENT_HPP
