#include "Projectile.hpp"
#include <cmath>

Projectile::Projectile(sf::Vector2f startPos, sf::Vector2f targetPos, float speed, float damage)
    : damage(damage)
{
    shape.setRadius(4.f);
    shape.setFillColor(sf::Color::Yellow);
    shape.setPosition(startPos);

    sf::Vector2f direction = targetPos - startPos;
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    if (length != 0)
        direction /= length;

    velocity = direction * speed;
}

void Projectile::update(float deltaTime)
{
    shape.move(velocity * deltaTime);
}

void Projectile::render(sf::RenderWindow &window)
{
    window.draw(shape);
}