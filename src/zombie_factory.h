#pragma once

#include "ecm.h"
#include "object_pool.h"
#include "characters/zombie_basic.h"
#include <SFML/Graphics.hpp>
#include <random>
#include <functional>
#include <memory>

class ZombieSpawner {
public:
    ZombieSpawner(sf::FloatRect spawnArea, float spawnInterval);

    void update(double dt);
    void startWave();
    void stopWave();

private:
    sf::FloatRect _spawnArea;
    float _spawnInterval;
    float _timer;
    bool _waveActive;
    std::default_random_engine _randomEngine;
    ObjectPool<Zombie> _zombiePool = ObjectPool<Zombie>(100);

    void configureZombie(Entity* zombie);
    sf::Vector2f getRandomSpawnPosition();
    void spawnZombie();
};
