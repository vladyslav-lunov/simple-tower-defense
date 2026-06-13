#pragma once
#include "Enemy.hpp"

class WaveManager
{
private:
    int mWaveNumber;
    int mEnemiesSpawnedInWave;
    int mEnemiesPerWave;

    float mSpawnTimer;
    float mSpawnInterval;

    float mPauseTimer;
    float mPauseBetweenWaves;
    bool mWaveInProgress;
    bool mAllEnemiesSpawned;

    void startNextWave();

public:
    WaveManager(/* args */);

    bool update(float deltaTime, int aliveEnemies);
    float getHealthMultiplier() const;
    float getSpeedMultiplier() const;
    int getCurrentWaveNumber() const;

    bool isPaused() const;
    float getPauseTimeRemaining() const;
};
