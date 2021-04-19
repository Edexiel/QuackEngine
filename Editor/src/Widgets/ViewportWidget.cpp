//
// Created by g.nisi on 3/10/21.
//

#include "Widgets/ViewportWidget.hpp"
#include "Scene/Core/World.hpp"
#include "Renderer/Framebuffer.hpp"

using namespace Renderer;
ViewportWidget::ViewportWidget()
{
    _title="Viewport";
}

void ViewportWidget::UpdateVisible()
{
    ImGui::BeginChild("ViewportRender");
    // Get the size of the child (i.e. the whole draw size of the windows).
    ImVec2 wsize = ImGui::GetWindowSize();

    World::Instance().GetRendererInterface().cameraSystem->GetActiveCamera().Resize(wsize.x, wsize.y);
    Framebuffer f = World::Instance().GetRendererInterface().GetSceneUpdatedFramebuffer();

    ImGui::Image((ImTextureID)(size_t)f.GetTexture(), wsize, ImVec2(0, 1), ImVec2(1, 0));

    ImGui::EndChild();
}