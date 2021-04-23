#ifndef _LIGHTSYSTEM_
#define _LIGHTSYSTEM_

#include "Scene/Core/System.hpp"
#include "Renderer/Shader.hpp"
#include "Scene/Component/Light.hpp"

#include <vector>

class LightSystem : public System
{
private:
    std::vector<Renderer::Shader> _listShaderToUpdate;
    unsigned int _lastEntitiesSize {0};

public:
    LightSystem() = default;
    ~LightSystem() = default;

    void Update(bool force = false);

    void AddShaderToUpdate(const Renderer::Shader& shader);
    void RemoveShaderFromUpdate(const Renderer::Shader& shader);
};


#endif