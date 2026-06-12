#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <iostream>

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

class Enemy
{
public:
    std::vector<sf::Vector2f> path;
    sf::RectangleShape shape;
    sf::RectangleShape healthBar;
    int currentWaypoint = 0;
    float speed = 40.f;
    float health = 100.f;
    float maxHealth = 100.f;

    Enemy(float x, float y, float size)
    {
        shape.setSize(sf::Vector2f(size, size));
        shape.setPosition(x, y);
        shape.setFillColor(sf::Color::Red);

        healthBar.setSize(sf::Vector2f(size, 5.f));
        healthBar.setFillColor(sf::Color::Green);
        healthBar.setPosition(x, y - 10.f);
    }

    void update(float deltaTime)
    {
        healthBar.setSize(sf::Vector2f(health / maxHealth * shape.getSize().x, 5.f));
        if (currentWaypoint >= path.size())
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
};

class Tower
{
public:
    sf::CircleShape shape;
    sf::Vector2f position;
    float range = 100.f;
    float damage = 20.f;

    Tower(float x, float y)
    {
        position = sf::Vector2f(x, y);
        shape.setRadius(15.f);
        shape.setFillColor(sf::Color::Green);
        shape.setPosition(x + 5.f, y + 5.f);
    }
};

int main()
{

    sf::RenderWindow window(sf::VideoMode(800, 600), "Tower Defense");
    std::vector<Tile> grid;
    sf::Clock clock;
    std::vector<Enemy> enemies;
    int spawnedEnemies = 5;
    sf::Clock spawnClock;

    std::vector<Tower> towers;

    for (int i = 0; i < 20; ++i)
    {
        for (int j = 0; j < 15; ++j)
        {
            grid.emplace_back(Tile(i * 40.f, j * 40.f, 40.f));
        }
    }

    while (window.isOpen())
    {
        window.setTitle("Tower Defense");

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed)
            {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                int gridX = mousePos.x / 40;
                int gridY = mousePos.y / 40;
                if (gridX >= 0 && gridX < 20 && gridY >= 0 && gridY < 15)
                {
                    int index = gridX * 15 + gridY;
                    if (grid[index].occupied)
                    {
                        grid[index].shape.setFillColor(sf::Color::Transparent);
                        grid[index].occupied = false;
                        towers.erase(std::remove_if(towers.begin(), towers.end(), [&](const Tower &tower)
                                                    { return tower.position == sf::Vector2f(gridX * 40.f, gridY * 40.f); }),
                                     towers.end());
                    }
                    else
                    {
                        grid[index].shape.setFillColor(sf::Color::Blue);
                        grid[index].occupied = true;
                        towers.emplace_back(Tower(gridX * 40.f, gridY * 40.f));
                    }
                }
            }
        }

        float deltaTime = clock.restart().asSeconds();

        for (auto &enemy : enemies)
        {
            if (enemy.currentWaypoint < enemy.path.size())
            {
                for (auto &tower : towers)
                {
                    sf::Vector2f toEnemy = enemy.shape.getPosition() - tower.position;
                    float distance = std::sqrt(toEnemy.x * toEnemy.x + toEnemy.y * toEnemy.y);

                    if (distance < tower.range)
                    {
                        enemy.health -= tower.damage * deltaTime;
                    }
                }
            }
        }

        enemies.erase(std::remove_if(enemies.begin(), enemies.end(), [&](const Enemy &e)
                                     { return e.health <= 0; }),
                      enemies.end());

        if (spawnClock.getElapsedTime().asSeconds() > 2.f && spawnedEnemies > 0)
        {
            auto enemy = Enemy(0, 200, 40.f);
            enemy.path = {{0, 200}, {200, 200}, {200, 400}, {400, 400}, {400, 80}, {600, 80}, {600, 400}, {760, 400}};
            enemies.push_back(enemy);
            spawnClock.restart();
            spawnedEnemies--;
        }

        // Rendering
        window.clear();
        for (const auto &tile : grid)
        {
            window.draw(tile.shape);
        }
        for (auto &enemy : enemies)
        {
            enemy.update(deltaTime);
            window.draw(enemy.shape);
            window.draw(enemy.healthBar);
        }
        for (const auto &tower : towers)
        {
            window.draw(tower.shape);
        }
        window.display();
    }
    return 0;
}
