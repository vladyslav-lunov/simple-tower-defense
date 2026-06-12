#include "Level.hpp"

Level::Level()
    : gridWidth(20), gridHeight(15)
{
    enemyPaths.push_back({{0, 5}, {5, 5}, {5, 10}, {10, 10}, {10, 2}, {15, 2}, {15, 10}, {19, 10}});
    enemyPaths.push_back({{0, 12}, {8, 12}, {8, 3}, {14, 3}, {14, 8}, {19, 8}});
}

const std::vector<sf::Vector2i> &Level::getPath(size_t index) const
{
    return enemyPaths[index % enemyPaths.size()];
}