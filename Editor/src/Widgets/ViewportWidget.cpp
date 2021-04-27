//
// Created by g.nisi on 3/10/21.
//

#include "Widgets/ViewportWidget.hpp"
#include "Scene/Core/World.hpp"
#include "Renderer/Framebuffer.hpp"
#include "Renderer/RendererInterface.hpp"
#include "Engine.hpp"

using namespace Renderer;

ViewportWidget::ViewportWidget()
{
    _title = "Viewport";

}

void ViewportWidget::UpdateVisible()
{
//    ImGuiIO& io = ImGui::GetIO();

//    if(ImGui::IsMouseReleased(0) && ImGui::IsItemHovered())
//    {
//        io.ConfigFlags |= ImGuiConfigFlags_NoMouse;
//        ImGui::SetMouseCursor(ImGuiMouseCursor_None);
//        std::cout << "Click!\n";
//    }

    ImGui::BeginChild("ViewportRender");
    // Get the size of the child (i.e. the whole draw size of the windows).
    const ImVec2 wsize = ImGui::GetWindowSize();

    RendererInterface &rendererInterface = Engine::Instance().GetRendererInterface();

    rendererInterface.cameraSystem->GetActiveCamera().Resize(wsize.x, wsize.y);
    Framebuffer f = rendererInterface.GetSceneUpdatedFramebuffer();

    ImGui::Image((ImTextureID) (size_t) f.GetTexture(), wsize, ImVec2(0, 1), ImVec2(1, 0));

    ImGui::EndChild();
}