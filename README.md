# Pathfinding Visualizer (C++ + SFML 3)

An interactive pathfinding visualizer built in **C++** using **SFML 3**.  
Currently supports **Breadth-First Search (BFS)** with animated visualization.  

---

## ✨ Features
- Grid-based interactive editor:
  - **1** = Wall tool  
  - **2** = Start tool  
  - **3** = Goal tool  
  - **C** = Clear grid  
- Pathfinding:
  - **Space** = run BFS (animated expansion)  
  - Explored cells shown in **blue/magenta**  
  - Shortest path highlighted in **yellow**

---

## ⚙️ Build & Run Instructions

This project uses **CMake** and **vcpkg** to manage dependencies.

### 🔹 MacOS (Apple Silicon / Intel)
```bash
# Clone repo
git clone https://github.com/Sayan090807/pathfinding-visualizer.git
cd pathfinding-visualizer

# Bootstrap vcpkg (first time only)
./vcpkg/bootstrap-vcpkg.sh

# Configure build (using preset in CMakePresets.json)
cmake --preset default

# Compile
cmake --build --preset default

# Run
./build/PathfindingVisualizer
