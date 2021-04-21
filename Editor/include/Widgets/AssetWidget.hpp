#ifndef _ASSETWIDGET_HPP
#define _ASSETWIDGET_HPP

#include "Widgets/Widget.hpp"
#include "Scene/Component/Camera.hpp"
#include <vector>

namespace Renderer
{
    class Texture;
}

class AssetWidget : public Widget
{
private:
    Component::Camera _camera;

public:
    AssetWidget();

    void UpdateVisible() final;

private:
    static void DisplayMaterial();
    static void DisplayTexture();
    static void DisplayModel();
    static void DisplaySound();

private:
    static std::string SelectInList(const std::vector<std::string>& list, const char* currentTexture, const char* comboName);
    static bool SelectTexture(Renderer::Texture& texture, const std::vector<std::string>& list, const char* currentTexture, const char* comboName);

};

#endif //_ASSETWIDGET_HPP
