#pragma once
#include <SFML/Graphics.hpp>

namespace Config
{
    constexpr float TILE_SIZE = 40.f;
    constexpr float TOWER_RANGE = 100.f;
    constexpr float TOWER_DAMAGE = 20.f;
    constexpr float ENEMY_SPEED = 40.f;
    constexpr float ENEMY_MAX_HEALTH = 100.f;
    constexpr int GRID_W = 20;
    constexpr int GRID_H = 15;
    constexpr float TOWER_FIRE_RATE = 0.5f;
    constexpr float PROJECTILE_SPEED = 300.f;

    inline sf::Vector2f gridToPixels(sf::Vector2i gridPos)
    {
        return sf::Vector2f(gridPos.x * TILE_SIZE, gridPos.y * TILE_SIZE);
    }
}
