cmake_minimum_required(VERSION 3.17)

project(Engine VERSION 0.1.0 LANGUAGES CXX C)

add_library(${PROJECT_NAME} STATIC
        src/Engine.cpp

        src/Input/InputManager.cpp
        src/Input/PlatformInputGLFW.cpp

        src/Thread/TaskSystem.cpp
        src/Thread/ThreadPool.cpp

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
        src/Scene/Component/Animator.cpp
        
        src/Renderer/ProcessBase.cpp
        src/Renderer/PostProcessManager.cpp

        src/Scene/Core/World.cpp
        src/Scene/Component/Model.cpp
        src/Scene/Component/Light.cpp
        src/Scene/Component/Camera.cpp
        src/Scene/Component/RigidBody.cpp

        src/Scene/System/ScriptSystem.cpp
        src/Scene/System/PhysicsSystem.cpp
        src/Scene/System/RenderSystem.cpp
        src/Scene/System/CameraSystem.cpp
        src/Scene/System/LightSystem.cpp

        src/Audio/Sound.cpp
        src/Audio/SoundManager.cpp

        src/Physics/PhysicsEventManager.cpp
        src/Time/TimePlatformGLFW.cpp
        src/Time/TimeManager.cpp)
        

target_include_directories (${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(${PROJECT_NAME} PUBLIC glad glfw assimp stb miniaudio reactphysics3d)
