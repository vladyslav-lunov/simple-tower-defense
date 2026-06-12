#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Tile.hpp"
#include "Enemy.hpp"
#include "Tower.hpp"
#include "Projectile.hpp"

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
    std::vector<sf::Vector2f> mEnemyPath;

    int mEnemiesToSpawn = 10;

    void processInput();
    void update(float deltaTime);
    void render();
    void handleTowerPlacement();
};