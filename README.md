## 📖 About

This is an interactive tool built in **C++** using **SFML 3** that demonstrates how common graph search algorithms work on a grid.  
It allows users to draw obstacles, set start and goal positions, and watch algorithms explore the grid step by step in real time.  

## Usage & Controls

Once the application is running, you can interact with the grid using your mouse and keyboard:

### Mouse
- **Left Click**: Apply the currently selected tool to the hovered cell  
  - If using **Wall Tool**, toggles a wall on/off  
  - If using **Start Tool**, sets the start position  
  - If using **Goal Tool**, sets the goal position  

### Keyboard
- **1** → Select Wall Tool  
- **2** → Select Start Tool  
- **3** → Select Goal Tool  
- **C** → Clear the entire grid and reset the search  
- **Spacebar** → Run Breadth-First Search (BFS) from Start to Goal  

### Visualization Guide
- **Gray** = empty cells  
- **Dark gray** = walls  
- **Teal** = start  
- **Orange** = goal  
- **Blue / Purple** = cells being explored  
- **Yellow** = shortest path after search completes


## ⚙️ Build & Run Instructions

This project uses **CMake** and **vcpkg** to manage dependencies.

### 🔹 macOS (Apple Silicon / Intel)
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
```

### 🔹 Windows (Visual Studio 2022)
```powershell
# Clone repo
git clone https://github.com/Sayan090807/pathfinding-visualizer.git
cd pathfinding-visualizer

# Bootstrap vcpkg (first time only)
.\vcpkg\bootstrap-vcpkg.bat

# Configure with VS generator (defined in CMakePresets.json)
cmake --preset vs2022

# Build inside Visual Studio OR from terminal
cmake --build --preset vs2022

# Run (inside build-vs/Debug or build-vs/Release)
.\build-vs\Debug\PathfindingVisualizer.exe
```
