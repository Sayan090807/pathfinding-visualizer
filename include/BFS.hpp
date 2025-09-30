#pragma once

#include "Grid.hpp"
#include <queue>
#include <vector>

class BFS {
public:
    BFS(Grid& grid);  

    void start(int startX, int startY, int goalX, int goalY); // reset + prepare BFS
    void step();                // run one step of BFS (for animation)
    bool isFinished() const;    // check if BFS has ended

private:
    void reconstructPath();     // backtrack when goal is found

    Grid& m_grid;               
    std::queue<std::pair<int, int>> m_frontier; 
    std::vector<int> m_parent;  
    int m_goalIndex;            
    bool m_finished;            
};
