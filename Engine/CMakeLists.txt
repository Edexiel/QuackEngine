cmake_minimum_required(VERSION 3.17)

project(Engine VERSION 0.1.0 LANGUAGES CXX C)

add_library(${PROJECT_NAME} STATIC
        src/main.cpp
        src/Input/InputManager.cpp
        src/Input/PlatformInputGLFW.cpp
        src/Scene/Scene.cpp
        src/Scene/Entity.cpp
        src/Scene/Component.cpp
        src/Thread/TaskSystem.cpp
        src/Thread/ThreadPool.cpp
        src/Resources/ResourcesManager.cpp
        src/Renderer/Model.cpp
        src/Renderer/Mesh.cpp
        src/Renderer/Shader.cpp
        src/Renderer/Texture.cpp
        src/Renderer/Material.cpp
        src/Renderer/RendererPlatform.cpp
        src/Renderer/Framebuffer.cpp
        src/Renderer/IcoSphere.cpp
        src/Scene/TransformComponent.cpp
        src/Scene/Archetype.cpp
        src/Scene/RendererComponent.cpp
        src/Scene/PhysicsComponent.cpp
        src/Scene/ScriptComponent.cpp
        src/Renderer/Light.cpp
        src/Audio/Sound.cpp
        src/Audio/SoundManager.cpp)

target_include_directories (${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(${PROJECT_NAME} PUBLIC glad glfw assimp stb miniaudio)
