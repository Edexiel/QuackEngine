#ifndef _POSTPROCESSMANAGER_HPP
#define _POSTPROCESSMANAGER_HPP

#include <vector>
#include <memory>

#include "ProcessBase.hpp"

namespace Renderer
{

    class PostProcessManager
    {
        Shader _shader;
        Mesh _quadMesh;

        std::vector<std::unique_ptr<ProcessBase>> _listProcess;

    public:
        void Init();
        void AddProcess(ProcessBase* process);

        void ApplyPostProcess(Framebuffer& framebuffer);

        void DrawTextureInFramebuffer(unsigned int framebufferIndex, unsigned int textureIndex);
    };

}

#endif //_POSTPROCESSMANAGER_HPP
