#include "BFS.hpp"
#include "Colors.hpp"

BFS::BFS(Grid& grid)
    : m_grid(grid), m_finished(false), m_goalIndex(-1) {}

bool BFS::isFinished() const {
    return m_finished;
}

void BFS::start(int startX, int startY, int goalX, int goalY) {
    // Reset everything
    m_finished = false;
    m_frontier = {};
    m_parent.assign(m_grid.width() * m_grid.height(), -1);

    // Map (x,y) -> index
    int startIndex = m_grid.index(startX, startY);
    m_goalIndex = m_grid.index(goalX, goalY);

    // Mark start and goal
    m_grid.setCell(startX, startY, Cell::Start);
    m_grid.setCell(goalX, goalY, Cell::Goal);

    // Push start into queue
    m_frontier.push({startX, startY});
}

void BFS::step() {
    if (m_finished) return;

    if (m_frontier.empty()) {
        m_finished = true;
        return;
    }

    auto [x, y] = m_frontier.front();
    m_frontier.pop();
    int i = m_grid.index(x, y);

    if (i == m_goalIndex) {
        reconstructPath();
        m_finished = true;
        return;
    }

    std::vector<std::pair<int,int>> dirs = {
        {1, 0}, {-1, 0}, {0, 1}, {0, -1}
    };

    for (auto [dx, dy] : dirs) {
        int nx = x + dx;
        int ny = y + dy;

        if (nx < 0 || nx >= m_grid.width() ||
            ny < 0 || ny >= m_grid.height()) continue;

        int ni = m_grid.index(nx, ny);

        if (m_parent[ni] == -1 &&
            (m_grid.getCell(nx, ny) == Cell::Empty || m_grid.getCell(nx, ny) == Cell::Goal)) {

            m_parent[ni] = i;
            m_frontier.push({nx, ny});

            if (m_grid.getCell(nx, ny) != Cell::Goal) {
                m_grid.setCell(nx, ny, Cell::Frontier);
            }
        }
    }

    if (m_grid.getCell(x, y) != Cell::Start) {
        m_grid.setCell(x, y, Cell::Visited);
    }
}

void BFS::reconstructPath() {
    int cur = m_goalIndex;

    while (cur != -1) {
        int x = cur % m_grid.width();
        int y = cur / m_grid.width();

        Cell cell = m_grid.getCell(x, y);
        if (cell != Cell::Start && cell != Cell::Goal) {
            m_grid.setCell(x, y, Cell::Path);
        }

        cur = m_parent[cur];
    }
}
