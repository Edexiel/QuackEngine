#ifndef QUACKENGINE_TRANSFORMCOMPONENT_HPP
#define QUACKENGINE_TRANSFORMCOMPONENT_HPP

#include "Scene/Components/Component.hpp"
#include <Maths/Quaternion.hpp>
#include <Maths/Vector3.hpp>

class TransformComponent : public Component {
private:
  Maths::Vector3 _position;
  Maths::Vector3 _scale;
  Maths::Quaternion _rotation;

public:
  TransformComponent();

  TransformComponent(const Maths::Vector3 &position,
                     const Maths::Vector3 &scale,
                     const Maths::Quaternion &rotation);

  const Maths::Vector3 &getPosition() const;
  const Maths::Quaternion &getRotation() const;
  const Maths::Vector3 &getScale() const;

  void setPosition(const Maths::Vector3 &position);
  void setRotation(const Maths::Quaternion &rotation);
  void setScale(const Maths::Vector3 &scale);
};

TransformComponent::TransformComponent() {}

TransformComponent::TransformComponent(const Maths::Vector3 &position,
                                       const Maths::Vector3 &scale,
                                       const Maths::Quaternion &rotation)
    : _position(position), _scale(scale), _rotation(rotation) {}

inline const Maths::Vector3 &TransformComponent::getPosition() const {
  return _position;
}

inline const Maths::Vector3 &TransformComponent::getScale() const {
  return _scale;
}

inline const Maths::Quaternion &TransformComponent::getRotation() const {
  return _rotation;
}

inline void TransformComponent::setPosition(const Maths::Vector3 &position) {
  TransformComponent::_position = position;
}

inline void TransformComponent::setScale(const Maths::Vector3 &scale) {
  TransformComponent::_scale = scale;
}

inline void TransformComponent::setRotation(const Maths::Quaternion &rotation) {
  _rotation = rotation;
}

#endif // QUACKENGINE_TRANSFORMCOMPONENT_HPP
