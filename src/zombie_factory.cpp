#include "zombie_factory.h"

#include <utility>
#include "engine/engine.h"
#include "prefabs/zombie_basic.h"

ZombieSpawner::ZombieSpawner(sf::FloatRect spawnArea, float spawnInterval)
        : _spawnArea(spawnArea), _spawnInterval(spawnInterval), _timer(0.0f), _waveActive(false) {
    _randomEngine.seed(std::random_device()());
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
    // spawn off-screen
    _spawnArea = Engine::GetWindow().getView().getViewport();
    _spawnArea.left -= 100.0f;
    _spawnArea.top -= 100.0f;
    _spawnArea.width += 200.0f;
    _spawnArea.height += 200.0f;

    std::uniform_real_distribution<float> xDist(_spawnArea.left, _spawnArea.width);
    std::uniform_real_distribution<float> yDist(_spawnArea.top, _spawnArea.height);
    return {xDist(_randomEngine), yDist(_randomEngine)};
}

void ZombieSpawner::configureZombie(Entity* zombie) {
    zombie->setPosition(getRandomSpawnPosition());

    //auto player = Engine::_activeScene->getEcm().find("player")[0];
    //auto playerPos = player->getPosition();

    auto z = zombie->get_components<Zombie>()[0];
    z->init();


}

void ZombieSpawner::spawnZombie() {
    auto zombie = _zombiePool.acquireObject();
    if (zombie) {

        configureZombie(zombie.get());
        std::cout << zombie->getComponents().size() << std::endl;
        std::cout << "Zombie spawned at " << zombie->getPosition().x << ", " << zombie->getPosition().y << std::endl;
        std::cout << "Zombie pool size: " << _zombiePool.getPool().size() << std::endl;
    }
}
