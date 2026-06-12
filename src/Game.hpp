#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Tile.hpp"
#include "Enemy.hpp"
#include "Tower.hpp"

class Game
{
public:
    Game();
    void run();

private:
    void processInput();
    void update(float deltaTime);
    void render();
    void handleTowerPlacement();

    sf::RenderWindow mWindow;
    std::vector<Tile> mGrid;
    std::vector<Enemy> mEnemies;
    std::vector<Tower> mTowers;
    sf::Clock mClock;
    sf::Clock mSpawnClock;
    int mEnemiesToSpawn = 5;
};