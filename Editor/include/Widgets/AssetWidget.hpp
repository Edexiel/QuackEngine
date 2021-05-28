#ifndef _ASSETWIDGET_HPP
#define _ASSETWIDGET_HPP

#include "Widgets/Widget.hpp"
#include "Scene/Component/Camera.hpp"
#include <vector>
#include <Scene/Component/Model.hpp>

namespace Renderer
{
    class Texture;
}
namespace Resources
{
    class Asset;
}

class AssetWidget : public Widget
{
private:

    static void DisplayMaterial(const Resources::Asset* asset);
    static void DisplayTexture(const Resources::Asset* asset);
    static void DisplayModel(const Resources::Asset* asset);
    static void DisplaySound(const Resources::Asset* asset);

    static std::string SelectInList(const std::vector<std::string>& list, const char* currentlySelected, const char* comboName);
    static bool SelectTexture(Renderer::Texture& texture, const std::vector<std::string>& list, const char* currentTexture, const char* comboName);


public:
    AssetWidget();

    void UpdateVisible() final;

};

#endif //_ASSETWIDGET_HPP
