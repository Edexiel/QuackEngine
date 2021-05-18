#ifndef _PROCESSBASE_HPP
#define _PROCESSBASE_HPP

#include "Renderer/Shader.hpp"
#include "Renderer/Mesh.hpp"

namespace Renderer
{
    class Framebuffer;
    class ProcessBase
    {
    protected:

        std::string _name;
        Shader _shader;


    public:

        ProcessBase() = default;
        ProcessBase(const std::string& name, const Shader& shader);

        virtual void Process(const Framebuffer& buffer, const Mesh& screenMesh);
    };
}

#endif //_PROCESSBASE_HPP
