#include "Renderer/Shape.hpp"
#include "Renderer/RendererPlatform.hpp"
#include "Scene/Core/World.hpp"

using namespace Renderer;

Mesh Shape::CreateQuad()
{
    const Renderer::Vertex quad[] = {
            // positions          // texture coords
            {{1.0f, 1.0f, 0.0f}, {0, 0, 1}, {1.0f, 1.0f}},   // top right
            {{1.0f, -1.0f, 0.0f}, {0, 0, 1}, {1.0f, 0.0f}},  // bottom right
            {{-1.0f, -1.0f, 0.0f}, {0, 0, 1}, {0.0f, 0.0f}}, // bottom left
            {{-1.0f, 1.0f, 0.0f}, {0, 0, 1}, {0.0f, 1.0f}}   // top left
    };

    unsigned int quadIndices[] = {
            0, 1, 3, // first triangle
            1, 2, 3  // second triangle
    };

    Mesh quadMesh = Renderer::RendererPlatform::CreateMesh(
            quad, sizeof(quad) / sizeof (float ),
            quadIndices, sizeof(quadIndices) / sizeof(unsigned int));

    RendererPlatform::VerticesReading();

    return World::Instance().GetResourcesManager().AddShape(quadMesh);
}