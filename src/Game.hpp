#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Tile.hpp"
#include "Enemy.hpp"
#include "Tower.hpp"
#include "Projectile.hpp"
#include "Level.hpp"

class Game
{
public:
    Game();
    void run();

private:
    sf::RenderWindow mWindow;
    sf::Clock mClock;
    sf::Clock mSpawnClock;

    std::vector<Tile> mGrid;
    std::vector<Enemy> mEnemies;
    std::vector<Tower> mTowers;
    std::vector<Projectile> mProjectiles;
    Level mLevel;

    int mEnemiesToSpawn = 10;

    void processInput();
    void update(float deltaTime);
    void render();
    void handleTowerPlacement();
};