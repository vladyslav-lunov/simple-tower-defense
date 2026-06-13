#include "Level.hpp"

Level::Level()
    : gridWidth(20), gridHeight(15)
{
    enemyPaths.push_back({{0, 5}, {5, 5}, {5, 10}, {10, 10}, {10, 2}, {15, 2}, {15, 10}, {19, 10}});
    enemyPaths.push_back({{0, 12}, {8, 12}, {8, 3}, {14, 3}, {14, 8}, {19, 8}});
    buildForbiddenMask();
}

void Level::buildForbiddenMask()
{
    forbiddenForTower.assign(gridWidth, std::vector<bool>(gridHeight, false));
    pathCells.assign(gridWidth, std::vector<bool>(gridHeight, false));

    for (const auto &path : enemyPaths)
    {
        for (size_t i = 0; i + 1 < path.size(); ++i)
        {
            auto segmentCells = getCellsBetween(path[i], path[i + 1]);

            for (const auto &cell : segmentCells)
            {
                pathCells[cell.x][cell.y] = true;

                for (int dx = -1; dx <= 1; ++dx)
                {
                    for (int dy = -1; dy <= 1; ++dy)
                    {
                        int nx = cell.x + dx;
                        int ny = cell.y + dy;

                        if (nx >= 0 && nx < gridWidth && ny >= 0 && ny < gridHeight)
                            forbiddenForTower[nx][ny] = true;
                    }
                }
            }
        }
    }
}

const std::vector<sf::Vector2i> &Level::getPath(size_t index) const
{
    return enemyPaths[index % enemyPaths.size()];
}

bool Level::canPlaceTower(int gridX, int gridY) const
{
    if (gridX < 0 || gridX >= gridWidth || gridY < 0 || gridY >= gridHeight)
        return false;

    return !forbiddenForTower[gridX][gridY];
}

std::vector<sf::Vector2i> Level::getCellsBetween(sf::Vector2i a, sf::Vector2i b) const
{
    std::vector<sf::Vector2i> cells;

    int dx = (b.x > a.x) ? 1 : (b.x < a.x) ? -1
                                           : 0;
    int dy = (b.y > a.y) ? 1 : (b.y < a.y) ? -1
                                           : 0;

    sf::Vector2i current = a;
    cells.push_back(current);

    while (current != b)
    {
        current.x += dx;
        current.y += dy;
        cells.push_back(current);
    }

    return cells;
}
