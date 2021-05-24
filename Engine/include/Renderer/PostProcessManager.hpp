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

        /***
         * @brief Add a Process to Apply to the screen on Rendering.
         * Work with inheritance the pointer must be allocated before adding.
         * It will be destroyed by the manager when needed.
         * @param process
         */
        void AddProcess(ProcessBase* process);

        /***
         * @brief Apply each Process saved in the manager on the framebuffer
         * @param framebuffer
         */
        void ApplyPostProcess(const Framebuffer& framebuffer);

        void DrawTextureInFramebuffer(unsigned int framebufferIndex, unsigned int textureIndex);
    };

}

#endif //_POSTPROCESSMANAGER_HPP
