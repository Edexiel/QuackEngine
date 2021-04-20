#include <Widgets/AssetWidget.hpp>
#include "Scene/Core/World.hpp"
#include "Renderer/Framebuffer.hpp"

AssetWidget::AssetWidget() :
_camera{Component::Camera(1280,720,1000, -1, 20 * 3.1415 / 180)}
{
    _title = "AssetProperties";

    _camera.SetView(Maths::Matrix4::Identity());
}

void AssetWidget::UpdateVisible()
{
    ImGui::BeginChild("ViewportRender");
    ImVec2 wsize = ImGui::GetWindowSize();

    _camera.Resize(wsize.x, wsize.x);
    World::Instance().GetRendererInterface().renderSystem->Draw(_camera);

    ImGui::Image((ImTextureID)(size_t)_camera.GetFramebuffer().GetTexture(), {wsize.x, wsize.x}, ImVec2(0, 1), ImVec2(1, 0));

    ImGui::EndChild();

}

