#pragma once
#include <vector>
#include <cmath>
#include <SFML/Graphics.hpp>
#include "Config.hpp"

class Enemy
{
public:
    std::vector<sf::Vector2f> path;
    sf::RectangleShape shape;
    sf::RectangleShape healthBar;
    int currentWaypoint = 0;
    float speed = Config::ENEMY_SPEED;
    float health = Config::ENEMY_MAX_HEALTH;
    float maxHealth = Config::ENEMY_MAX_HEALTH;

    Enemy(float x, float y, float size);

    void update(float deltaTime);
};
