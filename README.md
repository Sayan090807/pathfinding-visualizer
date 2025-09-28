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
