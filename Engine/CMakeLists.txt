cmake_minimum_required(VERSION 3.17)

project(Engine VERSION 0.1.0 LANGUAGES CXX C)

add_library(${PROJECT_NAME} STATIC
        src/Engine.cpp

        src/Input/InputManager.cpp
        src/Input/PlatformInputGLFW.cpp

#        src/Thread/TaskSystem.cpp
#        src/Thread/ThreadPool.cpp

        src/Resources/ResourcesManager.cpp
        src/Renderer/Mesh.cpp
        src/Renderer/Shader.cpp
        src/Renderer/Texture.cpp
        src/Renderer/Material.cpp
        src/Renderer/RendererPlatform.cpp
        src/Renderer/Framebuffer.cpp
        src/Renderer/IcoSphere.cpp
        src/Renderer/RendererInterface.cpp
        src/Renderer/Shape.cpp
        src/Renderer/Skeleton.cpp
        src/Renderer/Animation.cpp
        src/Renderer/ModelRenderer.cpp
        src/Renderer/UI/Font.cpp
        src/Renderer/UI/Text.cpp
        src/Renderer/UI/DialogBox.cpp
        src/Scene/Component/Animator.cpp

        src/Renderer/ProcessBase.cpp
        src/Renderer/PostProcessManager.cpp

        src/Scene/Core/World.cpp
        src/Scene/Component/ComponentBase.cpp
        src/Scene/Component/Camera.cpp
        src/Scene/Component/RigidBody.cpp

        src/Scene/System/ScriptSystem.cpp
        src/Scene/System/PhysicsSystem.cpp
        src/Scene/System/RenderSystem.cpp
        src/Scene/System/CameraSystem.cpp
        src/Scene/System/LightSystem.cpp
        src/Scene/System/CharacterControllerSystem.cpp
        src/Scene/System/CameraGameplaySystem.cpp

        src/Audio/Sound.cpp
        src/Audio/SoundManager.cpp

        src/Physics/PhysicsEventManager.cpp
        src/Physics/PhysicsCollisionCallback.cpp
        src/Tools/Type.cpp
        src/Tools/Random.cpp

        src/Time/TimePlatformGLFW.cpp
        src/Time/TimeManager.cpp

        src/Renderer/PostProcess/KernelPostProcess.cpp
        src/Scene/System/AnimatorSystem.cpp
        include/Scene/System/AnimatorSystem.hpp
        src/Renderer/Particle.cpp
        src/Scene/Component/ParticleEmitter.cpp
        src/Scene/System/ParticleSystem.cpp
        src/Tools/Random.cpp
        src/Scene/Component/SimpleShadow.cpp src/Scene/System/SimpleShadowSystem.cpp)


target_include_directories (${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(${PROJECT_NAME} PUBLIC glad glfw cereal fmt reactphysics3d freetype)
target_link_libraries(${PROJECT_NAME} PRIVATE assimp stb miniaudio)
