#include "Enemy.hpp"

Enemy::Enemy(float x, float y, float size)
{
    shape.setSize(sf::Vector2f(size, size));
    shape.setPosition(x, y);
    shape.setFillColor(sf::Color::Red);
    healthBar.setSize(sf::Vector2f(size, 5.f));
    healthBar.setFillColor(sf::Color::Green);
    healthBar.setPosition(x, y - 10.f);
}

void Enemy::update(float deltaTime)
{
    healthBar.setSize(sf::Vector2f(health / maxHealth * shape.getSize().x, 5.f));
    if (static_cast<size_t>(currentWaypoint) >= path.size())
        return;
    sf::Vector2f target = path[currentWaypoint];
    sf::Vector2f enemyDirection = target - shape.getPosition();
    sf::Vector2f healthBarOffset(0, -10.f);
    healthBar.setPosition(shape.getPosition() + healthBarOffset);
    float length = std::sqrt(enemyDirection.x * enemyDirection.x + enemyDirection.y * enemyDirection.y);
    if (length < speed * deltaTime)
    {
        shape.setPosition(target);
        currentWaypoint++;
    }
    else
    {
        enemyDirection /= length;
        shape.move(enemyDirection * speed * deltaTime);
    }
}
