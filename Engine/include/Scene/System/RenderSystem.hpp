#ifndef _RENDER_SYSTEM_
#define _RENDER_SYSTEM_

#include "Scene/Core/System.hpp"

namespace Renderer
{
    class RenderSystem : public System
    {

        void Init();
        void Draw(float deltaTime);

    };
}

#endif