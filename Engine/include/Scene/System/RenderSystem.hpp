#ifndef _RENDER_SYSTEM_
#define _RENDER_SYSTEM_

#include "Scene/Core/System.hpp"

class RenderSystem : public System
{
public:
    void Init();
    void Draw();

};

#endif