#include "WaveManager.hpp"

WaveManager::WaveManager()
    : mWaveNumber(0),
      mEnemiesSpawnedInWave(0),
      mEnemiesPerWave(0),
      mSpawnTimer(0.f),
      mSpawnInterval(1.5f),
      mPauseTimer(3.f),
      mPauseBetweenWaves(5.f),
      mWaveInProgress(false),
      mAllEnemiesSpawned(false)
{
}

void WaveManager::startNextWave()
{
    mWaveNumber++;
    mEnemiesPerWave = 5 + mWaveNumber;
    mEnemiesSpawnedInWave = 0;
    mSpawnTimer = 0.f;
    mWaveInProgress = true;
    mAllEnemiesSpawned = false;
}

bool WaveManager::update(float deltaTime, int aliveEnemies)
{
    if (!mWaveInProgress)
    {
        mPauseTimer -= deltaTime;
        if (mPauseTimer <= 0.f)
            startNextWave();

        return false;
    }

    if (mAllEnemiesSpawned)
    {
        if (aliveEnemies == 0)
        {
            mWaveInProgress = false;
            mPauseTimer = mPauseBetweenWaves;
        }
        return false;
    }

    mSpawnTimer -= deltaTime;
    if (mSpawnTimer <= 0.f)
    {
        mSpawnTimer = mSpawnInterval;
        mEnemiesSpawnedInWave++;

        if (mEnemiesSpawnedInWave >= mEnemiesPerWave)
            mAllEnemiesSpawned = true;

        return true;
    }

    return false;
}

float WaveManager::getHealthMultiplier() const
{
    return 1.0f + (mWaveNumber - 1) * 0.15f;
}

float WaveManager::getSpeedMultiplier() const
{
    return 1.0f + (mWaveNumber - 1) * 0.05f;
}

int WaveManager::getCurrentWaveNumber() const
{
    return mWaveNumber;
}

bool WaveManager::isPaused() const
{
    return !mWaveInProgress;
}

float WaveManager::getPauseTimeRemaining() const
{
    return mPauseTimer;
}
