#pragma once
#include <SFML/Graphics.hpp>

class Updatable
{
public:
    virtual ~Updatable() = default;
    virtual void update(float deltaTime) = 0;
};