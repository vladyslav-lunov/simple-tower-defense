#include "Game.hpp"

Game::Game()
    : mWindow(sf::VideoMode(800, 600), "Tower Defense"),
      mEnemiesToSpawn(10)
{
    for (int i = 0; i < Config::GRID_W; ++i)
        for (int j = 0; j < Config::GRID_H; ++j)
            mGrid.emplace_back(i * Config::TILE_SIZE, j * Config::TILE_SIZE, Config::TILE_SIZE);

    mEnemyPath = {{0, 200}, {200, 200}, {200, 400}, {400, 400}, {400, 80}, {600, 80}, {600, 400}, {760, 400}};
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
    for (auto &enemy : mEnemies)
        enemy.update(dt);

    for (auto &tower : mTowers)
        tower.update(dt);

    for (auto &tower : mTowers)
    {
        if (!tower.canFire())
            continue;

        for (auto &enemy : mEnemies)
        {
            sf::Vector2f toEnemy = enemy.shape.getPosition() - tower.position;
            float distance = std::sqrt(toEnemy.x * toEnemy.x + toEnemy.y * toEnemy.y);

            if (distance <= tower.range)
            {
                mProjectiles.emplace_back(tower.shape.getPosition(), enemy.shape.getPosition(), Config::PROJECTILE_SPEED, tower.damage);
                tower.resetCooldown();
                break;
            }
        }
    }

    for (auto &projectile : mProjectiles)
        projectile.update(dt);

    for (auto &projectile : mProjectiles)
    {
        if (projectile.hit)
            continue;

        for (auto &enemy : mEnemies)
        {
            if (enemy.shape.getGlobalBounds().contains(projectile.shape.getPosition()))
            {
                enemy.health -= projectile.damage;
                projectile.hit = true;
                break;
            }
        }
    }

    mEnemies.erase(std::remove_if(mEnemies.begin(), mEnemies.end(), [](const Enemy &e)
                                  { return e.health <= 0; }),
                   mEnemies.end());

    mProjectiles.erase(std::remove_if(mProjectiles.begin(), mProjectiles.end(), [](const Projectile &p)
                                      { return p.hit; }),
                       mProjectiles.end());

    if (mSpawnClock.getElapsedTime().asSeconds() > 2.f && mEnemiesToSpawn > 0)
    {
        auto enemy = Enemy(0, 200, Config::TILE_SIZE);
        enemy.path = mEnemyPath;
        mEnemies.push_back(enemy);
        mSpawnClock.restart();
        mEnemiesToSpawn--;
    }
}

void Game::render()
{
    mWindow.clear();
    for (auto &tile : mGrid)
    {
        tile.render(mWindow);
    }
    for (auto &enemy : mEnemies)
    {
        enemy.render(mWindow);
    }
    for (auto &tower : mTowers)
    {
        tower.render(mWindow);
    }
    for (auto &projectile : mProjectiles)
    {
        projectile.render(mWindow);
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