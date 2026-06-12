#include "Game.hpp"

Game::Game()
    : mWindow(sf::VideoMode(800, 600), "Tower Defense"),
      mEnemiesToSpawn(10)
{
    for (int i = 0; i < mLevel.gridWidth; ++i)
        for (int j = 0; j < mLevel.gridHeight; ++j)
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
        const auto &path = mLevel.getPath(static_cast<size_t>(0));
        auto enemy = Enemy(Config::gridToPixels(path.front()).x, Config::gridToPixels(path.front()).y, Config::TILE_SIZE);

        for (const auto &point : path)
            enemy.path.push_back(Config::gridToPixels(point));

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

    if (gridX < 0 || gridX >= mLevel.gridWidth || gridY < 0 || gridY >= mLevel.gridHeight)
        return;

    int index = gridX * mLevel.gridHeight + gridY;
    sf::Vector2f pixelPos = Config::gridToPixels({gridX, gridY});

    if (mGrid[index].occupied)
    {
        mGrid[index].shape.setFillColor(sf::Color::Transparent);
        mGrid[index].occupied = false;
        mTowers.erase(std::remove_if(mTowers.begin(), mTowers.end(), [&](const Tower &tower)
                                     { return tower.position == pixelPos; }),
                      mTowers.end());
    }
    else
    {
        mGrid[index].shape.setFillColor(sf::Color::Blue);
        mGrid[index].occupied = true;
        mTowers.emplace_back(pixelPos.x, pixelPos.y);
    }
}