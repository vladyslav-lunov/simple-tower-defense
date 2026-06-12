#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Tile
{
public:
    bool occupied = false;
    sf::RectangleShape shape;

    Tile(float x, float y, float size)
    {
        shape.setSize(sf::Vector2f(size, size));
        shape.setPosition(x, y);
        shape.setOutlineColor(sf::Color::White);
        shape.setOutlineThickness(1.f);
        shape.setFillColor(sf::Color::Transparent);
    }
};