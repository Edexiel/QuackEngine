cmake_minimum_required(VERSION 3.17)
project(QuackEngine VERSION 0.1.0 LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(QUACK_BUILD_TESTS "Build Tests" OFF)

include(CheckIPOSupported)
check_ipo_supported(RESULT supported OUTPUT error)

option(FORCE_COLORED_OUTPUT "Always produce ANSI-colored output (GNU/Clang only)." FALSE)
if (${FORCE_COLORED_OUTPUT})
    if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
        add_compile_options(-fdiagnostics-color=always)
    elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
        add_compile_options(-fcolor-diagnostics)
    endif ()
endif ()

if (QUACK_BUILD_EDITOR)
    set(QUACK_EDITOR TRUE)

endif ()

message(STATUS ">>> COMPILING IN  ${CMAKE_BUILD_TYPE}")
message(STATUS ">>> BUILD TEST IS ${QUACK_BUILD_TESTS}")


#Platform Specific
if (UNIX AND NOT APPLE)
    set(LINUX TRUE)
endif ()

if (LINUX)
    message(STATUS ">>> Linux ${CMAKE_SYSTEM}")
    # linux stuff here
    add_definitions(-DLINUX)
elseif (WIN32)
    add_definitions(-DWIN32)
    message(STATUS ">>> Not Linux ${CMAKE_SYSTEM}")
    # stuff that should happen on Win32
else ()
    message(FATAL_ERROR ">>> Not supported platform ${CMAKE_SYSTEM}")
endif ()

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
if (WIN32)
    set(GLFW_USE_HYBRID_HPG ON CACHE BOOL "" FORCE)
endif ()

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
        "${IMGUI_FOLDER}/misc/cpp/imgui_stdlib.cpp"
        )
target_include_directories(imgui INTERFACE ${IMGUI_FOLDER})
#target_link_libraries(imgui INTERFACE glfw glad)

#IMGUIZMO
#set(IMGUI_IMPL_OPENGL_LOADER_GLAD2 TRUE)

set(IMGUIZMO_FOLDER "${external_lib}/ImGuizmo")
add_library(ImGuizmo INTERFACE)
target_sources(ImGuizmo INTERFACE
        "${IMGUIZMO_FOLDER}/ImCurveEdit.cpp"
        "${IMGUIZMO_FOLDER}/ImGradient.cpp"
        "${IMGUIZMO_FOLDER}/ImGuizmo.cpp"
        "${IMGUIZMO_FOLDER}/ImSequencer.cpp"
        )
target_include_directories(ImGuizmo INTERFACE ${IMGUIZMO_FOLDER})

#STB
add_library(stb INTERFACE)
target_include_directories(stb INTERFACE ${external_lib}/stb)

#miniaudio
add_library(miniaudio INTERFACE)
target_include_directories(miniaudio INTERFACE ${external_lib}/miniaudio)

#assimp
set(ASSIMP_BUILD_ASSIMP_TOOLS OFF CACHE BOOL "" FORCE)
set(ASSIMP_INJECT_DEBUG_POSTFIX OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_ALL_IMPORTERS_BY_DEFAULT OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_ALL_EXPORTERS_BY_DEFAULT OFF CACHE BOOL "" FORCE)
set(ASSIMP_INSTALL OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_GLTF_IMPORTER ON CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_FBX_IMPORTER ON CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_ASSBIN_EXPORTER ON CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_ASSXML_EXPORTER ON CACHE BOOL "" FORCE)
add_subdirectory(${external_lib}/assimp)

#Cereal
set(SKIP_PERFORMANCE_COMPARISON ON CACHE BOOL "Skip performance comparison(requires boost)" FORCE)
set(BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(JUST_INSTALL_CEREAL ON CACHE BOOL "" FORCE)
add_subdirectory(${external_lib}/cereal)

#reactphysics3d
add_subdirectory(${external_lib}/reactphysics3d)
target_compile_options(reactphysics3d PRIVATE -w --no-warnings)

#fmt
add_subdirectory(${external_lib}/fmt)

#gtest
if (QUACK_BUILD_TESTS)
    add_subdirectory(${external_lib}/googletest)
    add_subdirectory(Test)
endif ()

add_subdirectory(Editor)

#Runner
add_subdirectory(Runner)


#Engine
add_subdirectory(Engine)

#Game
add_subdirectory(Game)

set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/install)

install(CODE "file(REMOVE_RECURSE ${CMAKE_INSTALL_PREFIX}/${CMAKE_BUILD_TYPE})")

install(TARGETS Editor RUNTIME DESTINATION ${CMAKE_BUILD_TYPE})
install(TARGETS Engine RUNTIME DESTINATION ${CMAKE_BUILD_TYPE})

if (${CMAKE_BUILD_TYPE} STREQUAL "Release")
    install(DIRECTORY "${PROJECT_SOURCE_DIR}/Game/Asset" DESTINATION ${CMAKE_BUILD_TYPE})
else ()
    install(CODE "file(CREATE_LINK ${PROJECT_SOURCE_DIR}/Game/Asset ${CMAKE_INSTALL_PREFIX}/${CMAKE_BUILD_TYPE}/Asset SYMBOLIC)")
endif ()

#install(TARGETS Runner
#        CONFIGURATIONS Release
#        RUNTIME DESTINATION Release/bin)

#if( supported )
#    message(STATUS "IPO / LTO enabled")
#    set_property(TARGET Editor PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)
#    set_property(TARGET Engine PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)
#    set_property(TARGET Game PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)
#else()
#    message(STATUS "IPO / LTO not supported: <${error}>")
#endif()






#if(NOT MSVC)
##    target_compile_options(Runner PRIVATE -Wall -Wextra -pedantic)
#    target_compile_options(Editor PRIVATE -Wall -Wextra -pedantic)
#    target_compile_options(Engine PRIVATE -Wall -Wextra -pedantic)
#    target_compile_options(Game PRIVATE -Wall -Wextra -pedantic)
#endif()

##Installer
#include(InstallRequiredSystemLibraries)
##set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/License.txt")
#set(CPACK_PACKAGE_VERSION_MAJOR "${Tutorial_VERSION_MAJOR}")
#set(CPACK_PACKAGE_VERSION_MINOR "${Tutorial_VERSION_MINOR}")
#SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Quack Engine project")
#SET(CPACK_PACKAGE_VENDOR "Quack Team")
#SET(CPACK_PACKAGE_EXECUTABLES "Hello" "Hello")
#include(CPack)
