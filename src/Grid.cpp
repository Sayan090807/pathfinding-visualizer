#include "Grid.hpp"
#include <algorithm>

Grid::Grid(int width, int height, int cellSize)
    : m_width(width), m_height(height), m_cellSize(cellSize),
      m_cells(width * height, Cell::Empty) {} 

int Grid::index(int x, int y) const {
    return y * m_width + x;
}

void Grid::setCell(int x, int y, Cell cell) {
    m_cells[index(x, y)] = cell;
}

Cell Grid::getCell(int x, int y) const {
    return m_cells[index(x, y)];
}

void Grid::clear() {
    std::fill(m_cells.begin(), m_cells.end(), Cell::Empty);
}

void Grid::draw(sf::RenderWindow& window) {
    sf::RectangleShape rect({(float)m_cellSize, (float)m_cellSize});

    for (int y = 0; y < m_height; ++y) {
        for (int x = 0; x < m_width; ++x) {
            rect.setPosition(sf::Vector2f(
                static_cast<float>(x * m_cellSize),
                static_cast<float>(y * m_cellSize)
            ));            
            rect.setFillColor(colorFor(m_cells[index(x, y)]));
            window.draw(rect);
        }
    }
}

void Grid::toggleWall(int x, int y) {
    int i = index(x, y);

    if (m_cells[i] == Cell::Wall) {
        m_cells[i] = Cell::Empty;
    } else {
        m_cells[i] = Cell::Wall;
    }
}

void Grid::setStart(int x, int y) {
    for (auto& c : m_cells) {
        if (c == Cell::Start) c = Cell::Empty;
    }
    m_cells[index(x, y)] = Cell::Start;
}

void Grid::setGoal(int x, int y) {
    for (auto& c : m_cells) {
        if (c == Cell::Goal) c = Cell::Empty;
    }
    m_cells[index(x, y)] = Cell::Goal;
}
