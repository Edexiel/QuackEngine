cmake_minimum_required(VERSION 3.17)


add_library(Engine
        src/main.cpp)

target_include_directories (Engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)