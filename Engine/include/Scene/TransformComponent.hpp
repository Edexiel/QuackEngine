#ifndef QUACKENGINE_TRANSFORMCOMPONENT_HPP
#define QUACKENGINE_TRANSFORMCOMPONENT_HPP

#include "Scene/Component.hpp"
#include <Maths/Quaternion.hpp>
#include <Maths/Vector3.hpp>

class TransformComponent : public Component
{
private:
    Maths::Vector3 _position;
    Maths::Vector3 scale;
    Maths::Quaternion rotation;

public:
    TransformComponent();

    TransformComponent(const Maths::Vector3 &position, const Maths::Vector3 &scale, const Maths::Quaternion &rotation);

    const Maths::Vector3 &getPosition() const;
    const Maths::Quaternion &getRotation() const;
    const Maths::Vector3 &getScale() const;

    void setPosition(const Maths::Vector3 &position);
    void setRotation(const Maths::Quaternion &rotation);
    void setScale(const Maths::Vector3 &scale);


};

TransformComponent::TransformComponent()
{

}

TransformComponent::TransformComponent(const Maths::Vector3 &position, const Maths::Vector3 &scale,
                                       const Maths::Quaternion &rotation) : position(position),
                                                                            scale(scale),
                                                                            rotation(rotation) {}

inline const Maths::Vector3 &TransformComponent::getPosition() const
{
    return position;
}

inline const Maths::Vector3 &TransformComponent::getScale() const
{
    return scale;
}

inline const Maths::Quaternion &TransformComponent::getRotation() const
{
    return rotation;
}

inline void TransformComponent::setPosition(const Maths::Vector3 &position)
{
    TransformComponent::position = position;
}


inline void TransformComponent::setScale(const Maths::Vector3 &scale)
{
    TransformComponent::scale = scale;
}


inline void TransformComponent::setRotation(const Maths::Quaternion &rotation)
{
    _rotation = rotation;
}


#endif // QUACKENGINE_TRANSFORMCOMPONENT_HPP
