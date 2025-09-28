#include <SFML/Graphics.hpp>
#include <optional>     // needed for pollEvent in SFML 3
#include <vector>
#include <queue>        // for BFS frontier
#include <algorithm>    // for std::fill

// ------------------------------
// Step 4.5: BFS Pathfinding with animation + unreachable detection
// ------------------------------

enum class Cell { Empty, Wall, Start, Goal, Visited, Frontier, Path };
enum class Tool { Wall, Start, Goal };

int main() {
    // ------------------------------
    // Window setup
    // ------------------------------
    sf::RenderWindow window(sf::VideoMode({640u, 360u}), "Pathfinding Visualizer");
    window.setFramerateLimit(60);

    // ------------------------------
    // Grid setup
    // ------------------------------
    const int GRID_W = 64;
    const int GRID_H = 36;
    const int CELL   = 10;

    std::vector<Cell> grid(GRID_W * GRID_H, Cell::Empty);
    auto idx = [&](int x, int y) { return y * GRID_W + x; };

    // ------------------------------
    // Color function (Cell → Color)
    // ------------------------------
    auto colorFor = [&](Cell c) -> sf::Color {
        switch (c) {
            case Cell::Empty:    return {0,0,0};       // black
            case Cell::Wall:     return {255,255,255}; // white
            case Cell::Start:    return {0,255,0};     // green
            case Cell::Goal:     return {255,0,0};     // red
            case Cell::Visited:  return {0,0,255};     // blue
            case Cell::Frontier: return {255,0,255};   // magenta
            case Cell::Path:     return {255,255,0};   // yellow
        }
        return sf::Color::White;
    };

    // ------------------------------
    // Input + search state
    // ------------------------------
    Tool currentTool = Tool::Wall;
    int hoverX = -1, hoverY = -1;

    bool searching = false;
    bool finished  = false;

    std::queue<std::pair<int,int>> frontier;
    std::vector<int> parent(GRID_W * GRID_H, -1);

    int goalIndex = -1;

    // BFS speed control
    int bfsStepCounter = 0;
    const int STEP_DELAY = 5; // expand every 5 frames

    // ------------------------------
    // Main loop
    // ------------------------------
    while (window.isOpen()) {
        // ------------------------------
        // Event handling
        // ------------------------------
        while (auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) window.close();

            // Keyboard input
            if (event->is<sf::Event::KeyPressed>()) {
                auto key = event->getIf<sf::Event::KeyPressed>();

                // Switch painting tool
                if (key->code == sf::Keyboard::Key::Num1) currentTool = Tool::Wall;
                if (key->code == sf::Keyboard::Key::Num2) currentTool = Tool::Start;
                if (key->code == sf::Keyboard::Key::Num3) currentTool = Tool::Goal;

                // Clear grid
                if (key->code == sf::Keyboard::Key::C) {
                    std::fill(grid.begin(), grid.end(), Cell::Empty);
                    searching = finished = false;
                    frontier = {};
                    parent.assign(GRID_W * GRID_H, -1);
                }

                // Start BFS
                if (key->code == sf::Keyboard::Key::Space) {
                    searching = true;
                    finished  = false;
                    frontier = {};
                    parent.assign(GRID_W * GRID_H, -1);

                    // Find start + goal
                    int startIndex = -1;
                    goalIndex = -1;
                    for (int i = 0; i < (int)grid.size(); ++i) {
                        if (grid[i] == Cell::Start) startIndex = i;
                        if (grid[i] == Cell::Goal)  goalIndex  = i;
                    }

                    // Push start into BFS
                    if (startIndex != -1 && goalIndex != -1) {
                        int sx = startIndex % GRID_W;
                        int sy = startIndex / GRID_W;
                        frontier.push({sx, sy});
                    } else {
                        searching = false; // no valid start/goal
                    }
                }
            }

            // Mouse input (edit mode only)
            if (!searching && event->is<sf::Event::MouseButtonPressed>()) {
                auto mouse = event->getIf<sf::Event::MouseButtonPressed>();
                if (mouse->button == sf::Mouse::Button::Left && hoverX >= 0 && hoverY >= 0) {
                    if (currentTool == Tool::Wall) {
                        grid[idx(hoverX, hoverY)] =
                            (grid[idx(hoverX, hoverY)] == Cell::Wall) ? Cell::Empty : Cell::Wall;
                    }
                    else if (currentTool == Tool::Start) {
                        for (auto &c : grid) if (c == Cell::Start) c = Cell::Empty;
                        grid[idx(hoverX, hoverY)] = Cell::Start;
                    }
                    else if (currentTool == Tool::Goal) {
                        for (auto &c : grid) if (c == Cell::Goal) c = Cell::Empty;
                        grid[idx(hoverX, hoverY)] = Cell::Goal;
                    }
                }
            }
        }

        // ------------------------------
        // Track hover cell
        // ------------------------------
        sf::Vector2i pixel = sf::Mouse::getPosition(window);
        hoverX = pixel.x / CELL;
        hoverY = pixel.y / CELL;
        if (hoverX < 0 || hoverX >= GRID_W || hoverY < 0 || hoverY >= GRID_H) {
            hoverX = hoverY = -1;
        }

        // ------------------------------
        // BFS Step (animate)
        // ------------------------------
        if (searching && !finished) {
            if (frontier.empty()) {
                // No more cells → unreachable goal
                finished = true;
            } else {
                bfsStepCounter++;
                if (bfsStepCounter >= STEP_DELAY) {
                    bfsStepCounter = 0; // reset counter

                    auto [x, y] = frontier.front();
                    frontier.pop();
                    int i = y * GRID_W + x;

                    if (i == goalIndex) {
                        // Goal found → backtrack path
                        int cur = i;
                        while (parent[cur] != -1) {
                            if (grid[cur] != Cell::Start && grid[cur] != Cell::Goal)
                                grid[cur] = Cell::Path;
                            cur = parent[cur];
                        }
                        finished = true;
                    } else {
                        // Explore neighbors
                        std::vector<std::pair<int,int>> dirs = {
                            {1,0}, {-1,0}, {0,1}, {0,-1}
                        };
                        for (auto [dx, dy] : dirs) {
                            int nx = x + dx, ny = y + dy;
                            if (nx < 0 || nx >= GRID_W || ny < 0 || ny >= GRID_H) continue;
                            int ni = ny * GRID_W + nx;
                            if (grid[ni] == Cell::Empty || grid[ni] == Cell::Goal) {
                                if (parent[ni] == -1) { // unvisited
                                    frontier.push({nx, ny});
                                    parent[ni] = i;
                                    if (grid[ni] != Cell::Goal) grid[ni] = Cell::Frontier;
                                }
                            }
                        }

                        // Mark current cell as visited
                        if (grid[i] == Cell::Empty || grid[i] == Cell::Frontier) {
                            grid[i] = Cell::Visited;
                        }
                    }
                }
            }
        }

        // ------------------------------
        // Rendering
        // ------------------------------
        window.clear();

        sf::RectangleShape rect({(float)CELL, (float)CELL});

        for (int y = 0; y < GRID_H; ++y) {
            for (int x = 0; x < GRID_W; ++x) {
                rect.setPosition({(float)(x * CELL), (float)(y * CELL)});
                rect.setFillColor(colorFor(grid[idx(x, y)]));
                window.draw(rect);
            }
        }

        // Hover highlight (edit mode only)
        if (!searching && hoverX >= 0 && hoverY >= 0) {
            rect.setPosition({(float)(hoverX * CELL), (float)(hoverY * CELL)});
            rect.setFillColor(sf::Color(200, 200, 200, 100));
            window.draw(rect);
        }

        window.display();
    }

    return 0;
}
