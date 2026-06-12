#include "Game.hpp"

Game::Game()
    : mWindow(sf::VideoMode(800, 600), "Tower Defense"),
      mEnemiesToSpawn(5)
{
    for (int i = 0; i < Config::GRID_W; ++i)
        for (int j = 0; j < Config::GRID_H; ++j)
            mGrid.emplace_back(i * Config::TILE_SIZE, j * Config::TILE_SIZE, Config::TILE_SIZE);
}

void Game::run()
{

    while (mWindow.isOpen())
    {
        float dt = mClock.restart().asSeconds();
        processInput();
        update(dt);
        render();
    }
}

void Game::processInput()
{
    sf::Event event;
    while (mWindow.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            mWindow.close();

        if (event.type == sf::Event::MouseButtonPressed)
            handleTowerPlacement(); // ← виносимо в окремий метод
    }
}

void Game::update(float dt)
{
    // логіка ворогів + башт
    // спавн
    for (auto &enemy : mEnemies)
    {
        if (static_cast<size_t>(enemy.currentWaypoint) < enemy.path.size())
        {
            for (auto &tower : mTowers)
            {
                sf::Vector2f toEnemy = enemy.shape.getPosition() - tower.position;
                float distance = std::sqrt(toEnemy.x * toEnemy.x + toEnemy.y * toEnemy.y);

                if (distance < tower.range)
                {
                    enemy.health -= tower.damage * dt;
                }
            }
        }
        enemy.update(dt);
    }

    mEnemies.erase(std::remove_if(mEnemies.begin(), mEnemies.end(), [&](const Enemy &e)
                                  { return e.health <= 0; }),
                   mEnemies.end());

    if (mSpawnClock.getElapsedTime().asSeconds() > 2.f && mEnemiesToSpawn > 0)
    {
        auto enemy = Enemy(0, 200, Config::TILE_SIZE);
        enemy.path = {{0, 200}, {200, 200}, {200, 400}, {400, 400}, {400, 80}, {600, 80}, {600, 400}, {760, 400}};
        mEnemies.push_back(enemy);
        mSpawnClock.restart();
        mEnemiesToSpawn--;
    }
}

void Game::render()
{
    mWindow.clear();
    for (const auto &tile : mGrid)
    {
        mWindow.draw(tile.shape);
    }
    for (auto &enemy : mEnemies)
    {
        mWindow.draw(enemy.shape);
        mWindow.draw(enemy.healthBar);
    }
    for (const auto &tower : mTowers)
    {
        mWindow.draw(tower.shape);
    }
    mWindow.display();
}

void Game::handleTowerPlacement()
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(mWindow);
    int gridX = mousePos.x / static_cast<int>(Config::TILE_SIZE);
    int gridY = mousePos.y / static_cast<int>(Config::TILE_SIZE);
    if (gridX >= 0 && gridX < Config::GRID_W && gridY >= 0 && gridY < Config::GRID_H)
    {
        int index = gridX * Config::GRID_H + gridY;
        if (mGrid[index].occupied)
        {
            mGrid[index].shape.setFillColor(sf::Color::Transparent);
            mGrid[index].occupied = false;
            mTowers.erase(std::remove_if(mTowers.begin(), mTowers.end(), [&](const Tower &tower)
                                         { return tower.position == sf::Vector2f(gridX * Config::TILE_SIZE, gridY * Config::TILE_SIZE); }),
                          mTowers.end());
        }
        else
        {
            mGrid[index].shape.setFillColor(sf::Color::Blue);
            mGrid[index].occupied = true;
            mTowers.emplace_back(Tower(gridX * Config::TILE_SIZE, gridY * Config::TILE_SIZE));
        }
    }
}