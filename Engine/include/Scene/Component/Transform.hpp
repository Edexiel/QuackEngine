#ifndef QUACKENGINE_TRANSFORM_HPP
#define QUACKENGINE_TRANSFORM_HPP

#include "Component.hpp"
#include <Maths/Quaternion.hpp>
#include <Maths/Vector3.hpp>

class Transform : public Component
{
private:
    Maths::Vector3f _position;
    Maths::Vector3f _scale;
    Maths::Quaternion _rotation;

public:
    Transform();

    Transform(const Maths::Vector3f &position,
              const Maths::Vector3f &scale,
              const Maths::Quaternion &rotation);

    const Maths::Vector3f &getPosition() const;
    const Maths::Quaternion &getRotation() const;
    const Maths::Vector3f &getScale() const;

    void setPosition(const Maths::Vector3f &position);
    void setRotation(const Maths::Quaternion &rotation);
    void setScale(const Maths::Vector3f &scale);
};

Transform::Transform()
{}

Transform::Transform(const Maths::Vector3f &position,
                     const Maths::Vector3f &scale,
                     const Maths::Quaternion &rotation)
        : _position(position), _scale(scale), _rotation(rotation)
{}

inline const Maths::Vector3f &Transform::getPosition() const
{
    return _position;
}

inline const Maths::Vector3f &Transform::getScale() const
{
    return _scale;
}

inline const Maths::Quaternion &Transform::getRotation() const
{
    return _rotation;
}

inline void Transform::setPosition(const Maths::Vector3f &position)
{
    Transform::_position = position;
}

inline void Transform::setScale(const Maths::Vector3f &scale)
{
    Transform::_scale = scale;
}

inline void Transform::setRotation(const Maths::Quaternion &rotation)
{
    _rotation = rotation;
}

#endif // QUACKENGINE_TRANSFORM_HPP
