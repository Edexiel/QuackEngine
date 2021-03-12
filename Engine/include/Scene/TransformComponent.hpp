#ifndef QUACKENGINE_TRANSFORMCOMPONENT_HPP
#define QUACKENGINE_TRANSFORMCOMPONENT_HPP

#include "Scene/Component.hpp"
#include <Maths/Quaternion.hpp>
#include <Maths/Vector3.hpp>

class TransformComponent : public Component {
private:
  Maths::Vector3f _position;
  Maths::Vector3f _scale;
  Maths::Quaternion _rotation;

public:
  TransformComponent();

  TransformComponent(const Maths::Vector3f &position,
                     const Maths::Vector3f &scale,
                     const Maths::Quaternion &rotation);

  const Maths::Vector3f &getPosition() const;
  const Maths::Quaternion &getRotation() const;
  const Maths::Vector3f &getScale() const;

  void setPosition(const Maths::Vector3f &position);
  void setRotation(const Maths::Quaternion &rotation);
  void setScale(const Maths::Vector3f &scale);
};

TransformComponent::TransformComponent() {}

TransformComponent::TransformComponent(const Maths::Vector3f &position,
                                       const Maths::Vector3f &scale,
                                       const Maths::Quaternion &rotation)
    : _position(position), _scale(scale), _rotation(rotation) {}

inline const Maths::Vector3f &TransformComponent::getPosition() const {
  return _position;
}

inline const Maths::Vector3f &TransformComponent::getScale() const {
  return _scale;
}

inline const Maths::Quaternion &TransformComponent::getRotation() const {
  return _rotation;
}

inline void TransformComponent::setPosition(const Maths::Vector3f &position) {
  TransformComponent::_position = position;
}

inline void TransformComponent::setScale(const Maths::Vector3f &scale) {
  TransformComponent::_scale = scale;
}

inline void TransformComponent::setRotation(const Maths::Quaternion &rotation) {
  _rotation = rotation;
}

#endif // QUACKENGINE_TRANSFORMCOMPONENT_HPP
