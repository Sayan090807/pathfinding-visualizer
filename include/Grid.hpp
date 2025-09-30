#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "Colors.hpp"

class Grid {
public:
    Grid(int width, int height, int cellSize); // Constructor

    void clear();                           // reset all cells
    void draw(sf::RenderWindow& window);    // draw the grid
    void setCell(int x, int y, Cell cell);  // set a cell type
    Cell getCell(int x, int y) const;       // read a cell type
    int index(int x, int y) const;          // map(x, y) -> index

    // edit logic
    void toggleWall(int x, int y);          // left click to toggle a wall
    void setStart(int x, int y);            // place/move start
    void setGoal(int x, int y);             // place/move goal

    int width() const { return m_width; }
    int height() const { return m_height; }
    int cellSize() const { return m_cellSize; }

private:
    int m_width, m_height, m_cellSize;
    std::vector<Cell> m_cells; // stores all cells in a 1D array
};
