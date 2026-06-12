#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Config.hpp"

class Tower
{
public:
    sf::CircleShape shape;
    sf::Vector2f position;
    float range = Config::TOWER_RANGE;
    float damage = Config::TOWER_DAMAGE;

    Tower(float x, float y);
};