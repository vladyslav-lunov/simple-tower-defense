#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <random>
#include "Tile.hpp"
#include "Enemy.hpp"
#include "Tower.hpp"
#include "Projectile.hpp"
#include "Level.hpp"
#include "WaveManager.hpp"
#include "Config.hpp"

class Game
{
public:
    Game();
    void run();

private:
    sf::RenderWindow mWindow;
    sf::Clock mClock;
    std::mt19937 mRandomEngine;

    std::vector<Tile> mGrid;
    std::vector<Enemy> mEnemies;
    std::vector<Tower> mTowers;
    std::vector<Projectile> mProjectiles;

    Level mLevel;
    WaveManager mWaveManager;
    int mPlayerHealth;

    void processInput();
    void update(float dt);
    void render();
    void handleTowerPlacement();
    void spawnEnemy();
};