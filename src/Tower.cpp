#include "Tower.hpp"

Tower::Tower(float x, float y)
{
    position = sf::Vector2f(x, y);
    shape.setRadius(15.f);
    shape.setFillColor(sf::Color::Green);
    shape.setPosition(x + 5.f, y + 5.f);
}

void Tower::render(sf::RenderWindow &window)
{
    window.draw(shape);
}

void Tower::update(float deltaTime)
{
    if (cooldown > 0.f)
        cooldown -= deltaTime;
}

bool Tower::canFire() const
{
    return cooldown <= 0.f;
}

void Tower::resetCooldown()
{
    cooldown = fireRate;
}
