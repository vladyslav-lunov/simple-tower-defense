#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Level
{
public:
    Level();

    int gridWidth;
    int gridHeight;

    std::vector<std::vector<sf::Vector2i>> enemyPaths;
    std::vector<std::vector<bool>> pathCells;
    std::vector<std::vector<bool>> forbiddenForTower;

    const std::vector<sf::Vector2i> &getPath(size_t index) const;
    bool canPlaceTower(int gridX, int gridY) const;

private:
    void buildForbiddenMask();
    std::vector<sf::Vector2i> getCellsBetween(sf::Vector2i a, sf::Vector2i b) const;
};