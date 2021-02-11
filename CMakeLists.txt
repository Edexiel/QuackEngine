cmake_minimum_required(VERSION 3.17)
project(QuackEngine VERSION 0.1.0 LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

#find_package(OpenGL REQUIRED)
#OpenGL::GL

set(external_lib "Vendor")

#GLAD
set(GLAD_FOLDER "${external_lib}/glad")
add_library(glad ${GLAD_FOLDER}/include/glad/glad.h ${GLAD_FOLDER}/src/glad.c)
target_include_directories(glad PUBLIC ${GLAD_FOLDER}/include/)

#GLFW
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(${external_lib}/glfw)

#IMGUI
set(IMGUI_FOLDER "${external_lib}/imgui")
set(IMGUI_SOURCES
        "${IMGUI_FOLDER}/imgui.cpp"
        "${IMGUI_FOLDER}/imgui_demo.cpp"
        "${IMGUI_FOLDER}/imgui_draw.cpp"
        "${IMGUI_FOLDER}/imgui_widgets.cpp"
        "${IMGUI_FOLDER}/backends/imgui_impl_glfw.cpp"
        "${IMGUI_FOLDER}/backends/imgui_impl_opengl3.cpp"
        )
add_library(imgui INTERFACE)
target_sources(imgui INTERFACE ${IMGUI_SOURCES})
target_include_directories(imgui INTERFACE ${IMGUI_FOLDER})

#STB
add_library(stb INTERFACE)
target_include_directories(stb INTERFACE ${external_lib}/stb)

#assimp
set(ASSIMP_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_ALL_IMPORTERS_BY_DEFAULT OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_ALL_EXPORTERS_BY_DEFAULT OFF CACHE BOOL "" FORCE)
#set(ASSIMP_NO_EXPORT OFF)
set(ASSIMP_BUILD_GLTF_IMPORTER ON CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_FBX_IMPORTER ON CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_ASSBIN_EXPORTER ON CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_ASSXML_EXPORTER ON CACHE BOOL "" FORCE)
set(ASSIMP_INSTALL OFF CACHE BOOL "" FORCE)
add_subdirectory(${external_lib}/assimp)

#flatbuffer
set(FLATBUFFERS_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(FLATBUFFERS_MAX_PARSING_DEPTH 16)
add_subdirectory(${external_lib}/flatbuffers ${CMAKE_CURRENT_BINARY_DIR}/flatbuffers-build EXCLUDE_FROM_ALL)

#reactphysics3d
add_subdirectory(${external_lib}/reactphysics3d)


#Editor
project(Engine VERSION 0.1.0 LANGUAGES CXX C)
add_library(Editor Editor/src/main.cpp)
target_include_directories (Editor PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
        {CMAKE_CURRENT_SOURCE_DIR}/include/Resources
        {CMAKE_CURRENT_SOURCE_DIR}/include/Renderer)
target_link_libraries(Editor PUBLIC glad glfw )

#Engine
project(Engine VERSION 0.1.0 LANGUAGES CXX C)

file(GLOB SOURCE_FILES
        Engine/src/Resources/ResourcesManager.cpp
        Engine/src/Renderer/Model.cpp
        Engine/src/Renderer/Mesh.cpp
        Engine/src/Renderer/Shader.cpp
        Engine/src/Renderer/Texture.cpp
        Engine/src/Resources/TextureLoader.cpp
        Engine/src/Resources/ShaderLoader.cpp
        Engine/src/Resources/ModelLoader.cpp)

add_executable(Engine Engine/src/main.cpp ${SOURCE_FILES})
target_include_directories (Engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Engine/include)
target_link_libraries(Engine PUBLIC glad glfw assimp flatbuffers)


#if()

#add_executable(${PROJECT_NAME} main.cpp)

#Installer
include(InstallRequiredSystemLibraries)
#set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/License.txt")
set(CPACK_PACKAGE_VERSION_MAJOR "${Tutorial_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${Tutorial_VERSION_MINOR}")
include(CPack)