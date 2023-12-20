#include "zombie_factory.h"

#include <utility>
#include "engine/engine.h"

ZombieSpawner::ZombieSpawner(sf::FloatRect spawnArea, float spawnInterval)
        : _spawnArea(spawnArea), _spawnInterval(spawnInterval), _timer(0.0f), _waveActive(false) {
    _randomEngine.seed(std::random_device()());
    _zombiePool.forEach([](const std::shared_ptr<Entity>& entity) {
        auto zombie = entity->get_components<Zombie>()[0];
        zombie->init(); // Use a default or random start position
    });
}

void ZombieSpawner::update(double dt) {
    if (!_waveActive) return;

    _timer += dt;
    if (_timer >= _spawnInterval) {
        spawnZombie();
        _timer = 0.0f;
    }
}

void ZombieSpawner::startWave() {
    _waveActive = true;
}

void ZombieSpawner::stopWave() {
    _waveActive = false;
}

sf::Vector2f ZombieSpawner::getRandomSpawnPosition() {
    std::uniform_real_distribution<float> xDist(_spawnArea.left, _spawnArea.width);
    std::uniform_real_distribution<float> yDist(_spawnArea.top, _spawnArea.height);
    return {xDist(_randomEngine), yDist(_randomEngine)};
}

void ZombieSpawner::configureZombie(Entity* zombie) {
    //auto player = Engine::_activeScene().ents.find("player")[0];
    //auto playerPos = player->getPosition();
    auto zombiePos = zombie->getPosition();

    auto ai = zombie->get_components<ZombieAIComponent>()[0];
    //ai->setTarget(player);


}

void ZombieSpawner::spawnZombie() {
    auto zombie = _zombiePool.acquireObject();
    if (zombie) {
        zombie->setPosition(getRandomSpawnPosition());
        configureZombie(zombie.get());
    }
}
