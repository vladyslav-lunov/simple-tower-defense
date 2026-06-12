#include "Tower.hpp"

Tower::Tower(float x, float y)
{
    position = sf::Vector2f(x, y);
    shape.setRadius(15.f);
    shape.setFillColor(sf::Color::Green);
    shape.setPosition(x + 5.f, y + 5.f);
}
