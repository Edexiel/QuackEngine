#ifndef _ANIMATION_HPP
#define _ANIMATION_HPP

#include "Renderer/Skeleton.hpp"

namespace Renderer
{
    struct NodeData
    {
        Maths::Matrix4 transform {Maths::Matrix4::Identity()};
        std::string name;
        std::vector<NodeData> listChildren;
    };

    class Animation
    {
        NodeData _rootNode;
        float _duration         {0.0f};
        float _tickPerSecond    {0.0f};

        Skeleton _skeleton;

        void ReadBaseSkeleton(const void* baseMesh);
        static void ReadHierarchy(NodeData& node, const void* src);
        void ReadBones(const void* loadedAnimation);

    public:
        static Animation LoadAnimation(const char* path);

        void Update(float currentTime);

        float GetDuration() const;
        float GetTickPerSecond() const;
        const NodeData& GetRootNode() const;
        const Skeleton& GetSkeleton() const;
    };
}

#endif //_ANIMATION_HPP
