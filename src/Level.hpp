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

    const std::vector<sf::Vector2i> &getPath(size_t index) const;
};