#ifndef _KERNELPOSTPROCESS_HPP
#define _KERNELPOSTPROCESS_HPP

#include "Renderer/ProcessBase.hpp"

namespace Renderer
{
    struct KernelPostProcess : public ProcessBase
    {
        union
        {
            struct
            {
                float leftTop;
                float leftMiddle;
                float leftBottom;
                float middleTop;
                float center;
                float middleBottom;
                float rightTop;
                float rightMiddle;
                float rightBottom;
            };
            float array [9] {1};
        };
        float offset {1/100.f};

        KernelPostProcess() = default;
        KernelPostProcess(const std::string& name);
        void Process(const Framebuffer &buffer, const Mesh &screenMesh) final;
    };
}

#endif //_KERNELPOSTPROCESS_HPP
