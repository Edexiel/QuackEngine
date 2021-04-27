#ifndef _ANIMATION_HPP
#define _ANIMATION_HPP

#include "Renderer/Skeleton.hpp"

namespace Renderer
{
    struct Animation
    {
        Skeleton skeleton;

        Animation LoadAnimation(const char* path);
    };
}

#endif //_ANIMATION_HPP
