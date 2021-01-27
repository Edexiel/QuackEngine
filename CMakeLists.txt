cmake_minimum_required(VERSION 3.17)
project(QuackEngine VERSION 0.1.0 LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 14)
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
add_definitions(-DGLFW_INCLUDE_NONE)

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
set(ASSIMP_BUILD_TESTS OFF)
set(ASSIMP_BUILD_ALL_IMPORTERS_BY_DEFAULT OFF)
set(ASSIMP_NO_EXPORT ON)
set(ASSIMP_BUILD_GLTF_IMPORTER ON)
set(ASSIMP_BUILD_FBX_IMPORTER ON)
add_subdirectory(${external_lib}/assimp)


#Engine
add_subdirectory(Engine)
#Editor
add_subdirectory(Editor)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE glad glfw assimp)

#Installer
include(InstallRequiredSystemLibraries)
#set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/License.txt")
set(CPACK_PACKAGE_VERSION_MAJOR "${Tutorial_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${Tutorial_VERSION_MINOR}")
include(CPack)