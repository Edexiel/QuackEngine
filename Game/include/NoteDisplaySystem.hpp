#ifndef _NOTEDISPLAYSYSTEM_HPP
#define _NOTEDISPLAYSYSTEM_HPP

#include "Scene/Core/System.hpp"
#include "Renderer/Texture.hpp"
#include "Renderer/ProcessBase.hpp"

enum NoteType {M_UP = 0, M_DOWN, M_RIGHT, M_LEFT};

class NoteDisplaySystem : public System, public Renderer::ProcessBase
{
    Renderer::Texture _listTexture[4];

public:
    NoteDisplaySystem();
    void Process(const Renderer::Framebuffer &buffer, const Renderer::Mesh &screenMesh) override;

};

#endif //_NOTEDISPLAYSYSTEM_HPP
