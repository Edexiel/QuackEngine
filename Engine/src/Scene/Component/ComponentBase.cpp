#include "Scene/Component/ComponentBase.hpp"

using namespace Component;

void ComponentBase::LinkEntityToComponent(Entity entity, ComponentBase *componentBase)
{
    if (componentBase->_entity == 0)
        componentBase->_entity = entity;
}

Entity ComponentBase::GetEntity() const
{
    return _entity;
}

bool ComponentBase::IsActive() const
{
    return _isActive;
}

void ComponentBase::SetActive(bool active)
{
    _isActive = active;
}