cmake_minimum_required(VERSION 3.17)
project(QuackEngine VERSION 0.1.0 LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

find_package(OpenGL REQUIRED)

#Platform Specific
if(UNIX AND NOT APPLE)
    set(LINUX TRUE)
endif()

if(LINUX)
    message(STATUS ">>> Linux ${CMAKE_SYSTEM}")
    # linux stuff here
elseif(WIN32)
    message(STATUS ">>> Not Linux ${CMAKE_SYSTEM}")
    # stuff that should happen on Win32
else()
    message(FATAL_ERROR ">>> Not supported platform ${CMAKE_SYSTEM}")
endif()

set(external_lib "Vendor")

#GLAD
set(GLAD_FOLDER "${external_lib}/glad")
add_library(glad ${GLAD_FOLDER}/include/glad/gl.h ${GLAD_FOLDER}/src/gl.c)
target_include_directories(glad PUBLIC ${GLAD_FOLDER}/include/)

#GLFW
set(GLFW_BUILD_DOCS OFF CACHE BOOL "Build the GLFW documentation" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "Build the GLFW test programs" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "Build the GLFW example programs" FORCE)
#set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "Generate installation target" FORCE)
if(WIN32)
    set(GLFW_USE_HYBRID_HPG ON CACHE BOOL "" FORCE)
endif()

add_subdirectory(${external_lib}/glfw)

#IMGUI
set(IMGUI_IMPL_OPENGL_LOADER_GLAD2 TRUE)

set(IMGUI_FOLDER "${external_lib}/imgui")
add_library(imgui INTERFACE)
target_sources(imgui INTERFACE
        "${IMGUI_FOLDER}/imgui.cpp"
        "${IMGUI_FOLDER}/imgui_demo.cpp"
        "${IMGUI_FOLDER}/imgui_draw.cpp"
        "${IMGUI_FOLDER}/imgui_widgets.cpp"
        "${IMGUI_FOLDER}/imgui_tables.cpp"
        "${IMGUI_FOLDER}/backends/imgui_impl_glfw.cpp"
        "${IMGUI_FOLDER}/backends/imgui_impl_opengl3.cpp"
        )
target_include_directories(imgui INTERFACE ${IMGUI_FOLDER})
target_link_libraries(imgui INTERFACE glfw glad)

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
#set(FLATBUFFERS_BUILD_TESTS OFF CACHE BOOL "" FORCE)
#set(FLATBUFFERS_MAX_PARSING_DEPTH 16)
#add_subdirectory(${external_lib}/flatbuffers ${CMAKE_CURRENT_BINARY_DIR}/flatbuffers-build EXCLUDE_FROM_ALL)


#reactphysics3d
add_subdirectory(${external_lib}/reactphysics3d)


#Editor
add_subdirectory(Editor)

#Engine
add_subdirectory(Engine)

target_include_directories(Editor PRIVATE Engine/include)

#if(debug)
#{
#target_link_libraries(Editor PUBLIC Engine)
#}

#Installer
include(InstallRequiredSystemLibraries)
#set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/License.txt")
set(CPACK_PACKAGE_VERSION_MAJOR "${Tutorial_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${Tutorial_VERSION_MINOR}")
include(CPack)