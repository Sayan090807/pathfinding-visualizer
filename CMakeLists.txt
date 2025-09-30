cmake_minimum_required(VERSION 3.15)
project(PathfindingVisualizer CXX)

set(CMAKE_CXX_STANDARD 17)

# List the SFML 3 components explicitly
find_package(SFML CONFIG REQUIRED COMPONENTS System Window Graphics)

# Executable with sources + headers
add_executable(PathfindingVisualizer
    src/main.cpp
    src/Grid.cpp
    src/BFS.cpp
    include/Colors.hpp
    include/Grid.hpp
    include/Tools.hpp
)

# Tell compiler where to find headers
target_include_directories(PathfindingVisualizer PRIVATE include)

# Link against SFML 3
target_link_libraries(PathfindingVisualizer PRIVATE
    SFML::System
    SFML::Window
    SFML::Graphics
)
