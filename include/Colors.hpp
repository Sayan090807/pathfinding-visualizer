#pragma once

// Use SFML's color types
#include <SFML/Graphics.hpp> 

// All possible cell states in Grid
enum class Cell {
    Empty,
    Wall, 
    Start,
    Goal,
    Visited,
    Frontier,
    Path
};

/* Example:
   sf::Color col = colorFor(Cell::Start);
   -> returns green
*/
inline sf::Color colorFor(Cell c) {
    switch(c) {
        case Cell::Empty:       return {0, 0, 0};         // black
        case Cell::Wall:        return {255, 255, 255};   // white
        case Cell::Start:       return {0, 255, 0};       // green
        case Cell::Goal:        return {255, 0, 0};       // red
        case Cell::Visited:     return {0, 0, 255};       // blue
        case Cell::Frontier:    return {255, 0, 255};     // magenta
        case Cell::Path:        return {255, 255, 0};     // yellow
    }
    return sf::Color::White; // fallback
}
