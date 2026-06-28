cmake_minimum_required(VERSION 3.20)

project(PhysicsSimulator)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY
    ${CMAKE_SOURCE_DIR}/bin)

#  External libreries

# - SFML
find_package(SFML 3 REQUIRED COMPONENTS Graphics Window System)
# OpenGL
find_package(OpenGL REQUIRED)

# - ImGui
set(IMGUI_DIR ${CMAKE_SOURCE_DIR}/external/imgui)
set(IMGUI_SFML_DIR ${CMAKE_SOURCE_DIR}/external/imgui-sfml)

add_library(imgui
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
)

target_include_directories(imgui PUBLIC
    external/imgui
)

add_library(imgui-sfml
    ${IMGUI_SFML_DIR}/imgui-SFML.cpp
)

target_include_directories(imgui PUBLIC ${IMGUI_DIR})
target_include_directories(imgui-sfml PUBLIC ${IMGUI_DIR} ${IMGUI_SFML_DIR})

target_link_libraries(imgui-sfml PUBLIC imgui SFML::Graphics SFML::Window SFML::System)

# Main App
file(GLOB SRC_FILES src/*.cpp src/*/*.cpp)

add_executable(physics-simulator ${SRC_FILES})

target_include_directories(physics-simulator PRIVATE
    ${CMAKE_SOURCE_DIR}/src
)

# Linking
target_link_libraries(physics-simulator
    imgui
    imgui-sfml
    SFML::Graphics
    SFML::Window
    SFML::System
    OpenGL::GL
)