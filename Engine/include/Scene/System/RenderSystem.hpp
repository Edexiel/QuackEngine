#ifndef _RENDER_SYSTEM_
#define _RENDER_SYSTEM_

#include "Scene/Core/System.hpp"

namespace Maths
{
    class Matrix4;
}

class RenderSystem : public System
{
public:
    void Init();
    void Draw(Maths::Matrix4& perspective, Maths::Matrix4& view);

};

#endif