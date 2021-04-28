//
// Created by g.nisi on 3/10/21.
//

#include "Widgets/ViewportWidget.hpp"
#include "Scene/Core/World.hpp"
#include "Renderer/Framebuffer.hpp"
#include "Renderer/RendererInterface.hpp"
#include "Engine.hpp"

#include "GLFW/glfw3.h"

using namespace Renderer;

ViewportWidget::ViewportWidget()
{
    _title = "Viewport";

}

void ViewportWidget::UpdateVisible()
{
    ImGui::BeginChild("ViewportRender");
    // Get the size of the child (i.e. the whole draw size of the windows).
    const ImVec2 wsize = ImGui::GetWindowSize();

    RendererInterface &rendererInterface = Engine::Instance().GetRendererInterface();

    rendererInterface.cameraSystem->GetActiveCamera().Resize(wsize.x, wsize.y);
    Framebuffer f = rendererInterface.GetSceneUpdatedFramebuffer();

    ImGui::Image((ImTextureID) (size_t) f.GetTexture(), wsize, ImVec2(0, 1), ImVec2(1, 0));

    ViewportWidget::LockCursor();

    ImGui::EndChild();
}

void ViewportWidget::LockCursor()
{
    ImGuiIO& io = ImGui::GetIO();
//    if(ImGui::IsMouseDoubleClicked(0) && ImGui::IsItemHovered(0))
//    {
//        io.ConfigFlags |= ImGuiConfigFlags_NoMouse;
//        ImGui::SetMouseCursor(ImGuiMouseCursor_None);
//        std::cout << "Oui\n";
//    }


    GLFWwindow *window = Engine::Instance().GetWindow();
    if(glfwGetKey(window, GLFW_KEY_F2) == GLFW_PRESS)
    {
//        io.ConfigFlags |= ImGuiConfigFlags_NoMouse;
//        ImGui::SetMouseCursor(ImGuiMouseCursor_None);

        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }
    else if(glfwGetKey(window, GLFW_KEY_F3) == GLFW_PRESS)
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
}
