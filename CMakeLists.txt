cmake_minimum_required(VERSION 3.20)

project(PhysicsSimulator)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY
    ${CMAKE_SOURCE_DIR}/bin)

find_package(SFML 3 REQUIRED COMPONENTS Graphics Window System)

file(GLOB SRC_FILES src/collision/*.cpp)

add_executable(physics-simulator ${SRC_FILES})

target_include_directories(physics-simulator PRIVATE include)

target_link_libraries(physics-simulator
    SFML::Graphics
    SFML::Window
    SFML::System
)