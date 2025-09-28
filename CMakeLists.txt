cmake_minimum_required(VERSION 3.15)
project(PathfindingVisualizer CXX)

set(CMAKE_CXX_STANDARD 17)

# List the SFML 3 components explicitly
find_package(SFML CONFIG REQUIRED COMPONENTS System Window Graphics)

add_executable(PathfindingVisualizer src/main.cpp)

# Link against the imported targets (namespaced in SFML 3)
target_link_libraries(PathfindingVisualizer PRIVATE
    SFML::System
    SFML::Window
    SFML::Graphics
)
