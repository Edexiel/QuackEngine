#include "Renderer/Shape.hpp"
#include "Renderer/RendererPlatform.hpp"
#include "Engine.hpp"

#include <cmath>

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
            quadIndices, sizeof(quadIndices) / sizeof(unsigned int), VertexType::V_CLASSIC);

    RendererPlatform::VerticesReading();

    return quadMesh;
}

Mesh Shape::CreateCube()
{
    const Vertex vertices[] {
            //Front
            {{1.0f, 1.0f, -1.0f}, {0, 0, -1}, {1.0f, 1.0f}},//0
            {{1.0f, -1.0f, -1.0f}, {0, 0, -1}, {1.0f, 0.0f}},//1
            {{-1.0f, -1.0f, -1.0f}, {0, 0, -1}, {0.0f, 0.0f}},//2
            {{-1.0f, 1.0f, -1.0f}, {0, 0, -1}, { 0.0f, 1.0f}},//3

            //Back
            {{1.0f, 1.0f, 1.0f}, {0, 0, 1}, {1.0f, 1.0f}},//4
            {{1.0f, -1.0f, 1.0f}, {0, 0, 1}, {1.0f, 0.0f}},//5
            {{-1.0f, -1.0f, 1.0f}, {0, 0, 1}, {0.0f, 0.0f}},//6
            {{-1.0f, 1.0f, 1.0f}, {0, 0, 1}, { 0.0f, 1.0f }},//7

            //Left
            {{-1.0f, 1.0f, 1.0f}, {-1, 0, 0}, {1.0f, 1.0f}},//8
            {{-1.0f, 1.0f, -1.0f}, {-1, 0, 0}, {1.0f, 0.0f}},//9
            {{-1.0f, -1.0f, -1.0f}, {-1, 0, 0}, {0.0f, 0.0f}},//10
            {{-1.0f, -1.0f, 1.0f}, {-1, 0, 0}, { 0.0f, 1.0f }},//11

            //Right
            {{1.0f, 1.0f, 1.0f}, {1, 0, 0}, {1.0f, 1.0f}},//12
            {{1.0f, 1.0f, -1.0f}, {1, 0, 0}, {1.0f, 0.0f}},//13
            {{1.0f, -1.0f, -1.0f}, {1, 0, 0}, {0.0f, 0.0f}},//14
            {{1.0f, -1.0f, 1.0f}, {1, 0, 0}, { 0.0f, 1.0f }},//15

            //Top
            {{1.0f, 1.0f, 1.0f}, {0, 1, 0}, {1.0f, 1.0f}},//16
            {{1.0f, 1.0f, -1.0f}, {0, 1, 0}, {1.0f, 0.0f}},//17
            {{-1.0f, 1.0f, -1.0f}, {0, 1, 0}, {0.0f, 0.0f}},//18
            {{-1.0f, 1.0f, 1.0f}, {0, 1, 0}, { 0.0f, 1.0f }},//19

            //Down
            {{1.0f, -1.0f, 1.0f}, {0, -1, 0}, {1.0f, 1.0f}},//20
            {{1.0f, -1.0f, -1.0f}, {0, -1, 0}, {1.0f, 0.0f}},//21
            {{-1.0f, -1.0f, -1.0f}, {0, -1, 0}, {0.0f, 0.0f}},//22
            {{-1.0f, -1.0f, 1.0f}, {0, -1, 0}, { 0.0f, 1.0f }}//23
    };
    const unsigned int indices[]{
            //Back
            0, 1, 3,
            1, 2, 3,
            //Front
            4, 5, 7,
            5, 6, 7,
            //Left
            8, 9, 11,
            9, 10, 11,
            //Right
            12, 13, 15,
            13, 14, 15,
            //Top
            16, 17, 19,
            17, 18, 19,
            //Down
            20, 21, 23,
            21, 22, 23
    };

    return RendererPlatform::CreateMesh(vertices, sizeof (vertices)/sizeof (vertices[0]), indices, sizeof(indices)/sizeof(indices[0]), VertexType::V_CLASSIC);
}

Mesh Shape::CreateSphere(int sectorCount, int stackCount)
{
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    float sectorStep = 2 * Pi<float>() / (float)sectorCount;
    float stackStep = Pi<float>() / (float)stackCount;
    float sectorAngle, stackAngle;

    //Vertices
    for(int i = 0; i <= stackCount; ++i)
    {
        stackAngle = Pi<float>() / 2.f - (float)i * stackStep; // starting from pi/2 to -pi/2
        float xy = cosf(stackAngle);           // r * cos(u)
        float z = sinf(stackAngle);            // r * sin(u)

        for (int j = 0; j <= sectorCount; ++j)
        {
            sectorAngle = (float)j * sectorStep; // starting from 0 to 2pi

            float x = xy * cosf(sectorAngle);
            float y = xy * sinf(sectorAngle);

            vertices.push_back({{x, y, z}, {x, y, z},{(float)j / (float)sectorCount, (float)i / (float)stackCount}});
        }
    }

    //Indices
    unsigned int k1, k2;
    for(int i = 0; i < stackCount; ++i)
    {
        k1 = i * (sectorCount + 1);
        k2 = k1 + sectorCount + 1;

        for(int j = 0; j < sectorCount; ++j, ++k1, ++k2)
        {
            // 2 triangles per sector excluding 1st and last stacks
            if(i != 0)
            {
                indices.push_back(k1);
                indices.push_back(k2);
                indices.push_back(k1+1);
            }

            if(i != (stackCount-1))
            {
                indices.push_back(k1+1);
                indices.push_back(k2);
                indices.push_back(k2+1);
            }
        }
    }

    return RendererPlatform::CreateMesh(vertices.data(), vertices.size(), indices.data(), indices.size(), VertexType::V_CLASSIC);
}