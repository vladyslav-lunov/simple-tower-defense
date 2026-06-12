#pragma once
#include <SFML/Graphics.hpp>
#include "Updatable.hpp"
#include "Renderable.hpp"

class Projectile : public Renderable, public Updatable
{
public:
    sf::CircleShape shape;
    sf::Vector2f velocity;
    float damage;
    bool hit = false;

    Projectile(sf::Vector2f startPos, sf::Vector2f targetPos, float speed, float damage);

    void update(float deltaTime) override;
    void render(sf::RenderWindow &window) override;
};