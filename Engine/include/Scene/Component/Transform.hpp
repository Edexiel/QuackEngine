#ifndef QUACKENGINE_TRANSFORM_HPP
#define QUACKENGINE_TRANSFORM_HPP

#include <Maths/Quaternion.hpp>
#include <Maths/Vector3.hpp>
#include "Scene/Core/System.hpp"

namespace Component
{
    struct Transform
    {
        Maths::Vector3f position{0, 0, 0};
        Maths::Vector3f scale{1, 1, 1};
        Maths::Quaternion rotation{1, 0, 0, 0};

//        Maths::Vector3f forward{0, 0, 1};
//        Maths::Vector3f right{1, 0, 0};

        inline Maths::Matrix4 GetMatrix() const
        {
            return Maths::Matrix4::Translate(position) * rotation.ToMatrix() * Maths::Matrix4::Scale(scale);
        };

        template<class Archive>
        void serialize(Archive & archive)
        {
            archive(CEREAL_NVP(position),CEREAL_NVP(scale),CEREAL_NVP(rotation));
        }
    };
}
//struct Transform : public Component
//{
//private:
//    Maths::Vector3f _position;
//    Maths::Vector3f _scale;
//    Maths::Quaternion _rotation;
//
//public:
//    Transform();
//
//    Transform(const Maths::Vector3f &position,
//              const Maths::Vector3f &scale,
//              const Maths::Quaternion &rotation);
//
//    const Maths::Vector3f &getPosition() const;
//    const Maths::Quaternion &getRotation() const;
//    const Maths::Vector3f &getScale() const;
//
//    void setPosition(const Maths::Vector3f &position);
//    void setRotation(const Maths::Quaternion &rotation);
//    void setScale(const Maths::Vector3f &scale);
//};
//
//Transform::Transform()
//{}
//
//Transform::Transform(const Maths::Vector3f &position,
//                     const Maths::Vector3f &scale,
//                     const Maths::Quaternion &rotation)
//        : _position(position), _scale(scale), _rotation(rotation)
//{}
//
//inline const Maths::Vector3f &Transform::getPosition() const
//{
//    return _position;
//}
//
//inline const Maths::Vector3f &Transform::getScale() const
//{
//    return _scale;
//}
//
//inline const Maths::Quaternion &Transform::getRotation() const
//{
//    return _rotation;
//}
//
//inline void Transform::setPosition(const Maths::Vector3f &position)
//{
//    Transform::_position = position;
//}
//
//inline void Transform::setScale(const Maths::Vector3f &scale)
//{
//    Transform::_scale = scale;
//}
//
//inline void Transform::setRotation(const Maths::Quaternion &rotation)
//{
//    _rotation = rotation;
//}

#endif // QUACKENGINE_TRANSFORM_HPP
