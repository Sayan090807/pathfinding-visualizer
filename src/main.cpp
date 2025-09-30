#include <SFML/Graphics.hpp>
#include "Colors.hpp"
#include "Grid.hpp"
#include "Tools.hpp"
#include "BFS.hpp"

#include <optional>

// ----------------------------------------------------
// Main
// ----------------------------------------------------
int main() {
    sf::RenderWindow window(sf::VideoMode({640u, 360u}), "Pathfinding Visualizer");
    window.setFramerateLimit(60);

    const int GRID_W = 64;
    const int GRID_H = 36;
    const int CELL   = 10;

    Grid grid(GRID_W, GRID_H, CELL);
    Tool currentTool = Tool::Wall;

    // Attach BFS to this grid
    BFS bfs(grid);

    int hoverX = -1, hoverY = -1;
    bool searching = false;

    while (window.isOpen()) {
        while (auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) window.close();

            if (event->is<sf::Event::KeyPressed>()) {
                auto key = event->getIf<sf::Event::KeyPressed>();

                // Switch painting tool
                if (key->code == sf::Keyboard::Key::Num1) currentTool = Tool::Wall;
                if (key->code == sf::Keyboard::Key::Num2) currentTool = Tool::Start;
                if (key->code == sf::Keyboard::Key::Num3) currentTool = Tool::Goal;

                // Clear grid
                if (key->code == sf::Keyboard::Key::C) {
                    grid.clear();
                    searching = false;
                }

                // Start BFS
                if (key->code == sf::Keyboard::Key::Space) {
                    int startX = -1, startY = -1;
                    int goalX = -1, goalY = -1;

                    // Search for Start + Goal
                    for (int y = 0; y < grid.height(); ++y) {
                        for (int x = 0; x < grid.width(); ++x) {
                            if (grid.getCell(x, y) == Cell::Start) {
                                startX = x; startY = y;
                            }
                            if (grid.getCell(x, y) == Cell::Goal) {
                                goalX = x; goalY = y;
                            }
                        }
                    }

                    if (startX != -1 && goalX != -1) {
                        bfs.start(startX, startY, goalX, goalY);
                        searching = true;
                    }
                }
            }

            // Mouse input
            if (!searching && event->is<sf::Event::MouseButtonPressed>()) {
                auto mouse = event->getIf<sf::Event::MouseButtonPressed>();
                if (mouse->button == sf::Mouse::Button::Left && hoverX >= 0 && hoverY >= 0) {
                    if (currentTool == Tool::Wall) grid.toggleWall(hoverX, hoverY);
                    else if (currentTool == Tool::Start) grid.setStart(hoverX, hoverY);
                    else if (currentTool == Tool::Goal)  grid.setGoal(hoverX, hoverY);
                }
            }
        }

        // Hover logic
        sf::Vector2i pixel = sf::Mouse::getPosition(window);
        hoverX = pixel.x / CELL;
        hoverY = pixel.y / CELL;
        if (hoverX < 0 || hoverX >= GRID_W || hoverY < 0 || hoverY >= GRID_H) {
            hoverX = hoverY = -1;
        }

        // BFS step
        if (searching && !bfs.isFinished()) {
            bfs.step();
        }

        // Draw everything
        window.clear();
        grid.draw(window);

        // Hover highlight
        if (!searching && hoverX >= 0 && hoverY >= 0) {
            sf::RectangleShape rect({(float)CELL, (float)CELL});
            rect.setPosition({(float)(hoverX * CELL), (float)(hoverY * CELL)});
            rect.setFillColor(sf::Color(200, 200, 200, 100));
            window.draw(rect);
        }

        window.display();
    }

    return 0;
}
