#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Config.hpp"
#include "Renderable.hpp"
#include "Updatable.hpp"

class Tower : public Renderable, public Updatable
{
public:
    sf::CircleShape shape;
    sf::Vector2f position;
    float range = Config::TOWER_RANGE;
    float damage = Config::TOWER_DAMAGE;
    float fireRate = Config::TOWER_FIRE_RATE;
    float cooldown = 0.f;

    Tower(float x, float y);

    void render(sf::RenderWindow &window) override;
    void update(float deltaTime) override;

    bool canFire() const;
    void resetCooldown();
};