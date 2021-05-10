#ifndef _SKELETALMESH_HPP
#define _SKELETALMESH_HPP

#include "Renderer/Mesh.hpp"
#include "Maths/Matrix4.hpp"
#include "Maths/Quaternion.hpp"

#include <vector>
#include <unordered_map>

namespace Renderer
{
    class Bone
    {
        bool _animated {false};

        std::vector<std::pair<Maths::Vector3f, double>> _positions;
        std::vector<std::pair<Maths::Quaternion, double>> _rotations;
        std::vector<std::pair<Maths::Vector3f, double>> _scales;

        int _id {-1};
        Maths::Matrix4 _localTransform {Maths::Matrix4::Identity()};
        Maths::Matrix4 _offset {Maths::Matrix4::Identity()};

        std::string _name;

        int GetPositionIndex(float animationTime);
        int GetRotationIndex(float animationTime);
        int GetScaleIndex(float animationTime);

        float GetTimeScaleFactor(float lastTimeStamp, float nextTimeStamp, float animationTime);

        Maths::Matrix4 InterpolatePosition(float animationTime);
        Maths::Matrix4 InterpolateRotation(float animationTime);
        Maths::Matrix4 InterpolateScale(float animationTime);


    public:
        //Bone(const std::string& name, const int id, const void* node);
        Bone(const std::string& name, const int id, const Maths::Matrix4& transform);

        void SetAnimation(const void* node);

        void Update(float animationTime);

        int GetID() const;
        const Maths::Matrix4& GetLocalTransformation() const;
        const Maths::Matrix4& GetOffsetTransformation() const;
        const std::string& GetName() const;
        bool IsAnimated() const;
    };

    struct Skeleton
    {
        std::vector<Bone> listBones;
        std::unordered_map<std::string, int> mapBones;

        const Bone* GetBone(std::string name) const;
        void SetBone(const Bone& bone);
        void SetBoneAnimation(const std::string& name, const void* node);
        void Update(float deltaTime);

        unsigned int GetBonesNb() const;

        void AddBone(const Bone& bone);
    };
}

#endif //_SKELETALMESH_HPP
