#include "zombie_factory.h"

#include <utility>
#include "engine/engine.h"
#include "prefabs/zombie_basic.h"
#include "audio_manager.h"

ZombieSpawner::ZombieSpawner(sf::FloatRect spawnArea, float spawnInterval)
        : _spawnArea(spawnArea), _spawnInterval(spawnInterval), _timer(0.0f), _waveActive(false),
          _zombiePool(50,  [](const std::shared_ptr<Entity>& entity) { entity->addComponent<Zombie>();}) {
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
    AudioManager::get_instance().playSound("gong");
    _waveActive = true;
}

void ZombieSpawner::stopWave() {
    _waveActive = false;
}

sf::Vector2f ZombieSpawner::getRandomSpawnPosition() {
    const sf::View& view = Engine::GetWindow().getView();
    const sf::Vector2f& center = view.getCenter();
    const sf::Vector2f& size = view.getSize();

    // Calculate view bounds
    sf::FloatRect viewBounds(center.x - size.x / 2, center.y - size.y / 2, size.x, size.y);

    // Offset to ensure spawning off-screen
    float offset = 100.0f; // You can adjust this value

    // Randomize the side from which the zombie will spawn
    std::uniform_int_distribution<int> sideDist(0, 3);
    int side = sideDist(_randomEngine);

    std::uniform_real_distribution<float> xDist, yDist;

    switch (side) {
        case 0: // Top
            xDist = std::uniform_real_distribution<float>(viewBounds.left, viewBounds.left + viewBounds.width);
            yDist = std::uniform_real_distribution<float>(viewBounds.top - offset, viewBounds.top);
            break;
        case 1: // Bottom
            xDist = std::uniform_real_distribution<float>(viewBounds.left, viewBounds.left + viewBounds.width);
            yDist = std::uniform_real_distribution<float>(viewBounds.top + viewBounds.height, viewBounds.top + viewBounds.height + offset);
            break;
        case 2: // Left
            xDist = std::uniform_real_distribution<float>(viewBounds.left - offset, viewBounds.left);
            yDist = std::uniform_real_distribution<float>(viewBounds.top, viewBounds.top + viewBounds.height);
            break;
        case 3: // Right
            xDist = std::uniform_real_distribution<float>(viewBounds.left + viewBounds.width, viewBounds.left + viewBounds.width + offset);
            yDist = std::uniform_real_distribution<float>(viewBounds.top, viewBounds.top + viewBounds.height);
            break;
    }

    return {xDist(_randomEngine), yDist(_randomEngine)};
}


void ZombieSpawner::configureZombie(Entity* zombie) {


    //auto player = Engine::_activeScene->getEcm().find("player")[0];
    //auto playerPos = player->getPosition();




}

void ZombieSpawner::spawnZombie() {
    auto zombie = _zombiePool.acquireObject();
    if (zombie) {
        zombie->setPosition(getRandomSpawnPosition());
        auto z = zombie->get_components<Zombie>()[0];
        z->init();
        z->setOnRelease([this, z]() {
            z->tearDown();
            _zombiePool.releaseObject((shared_ptr<Entity> &) z->_parent);

        });
        //std::cout << zombie->getComponents().size() << std::endl;
        //std::cout << "Zombie spawned at " << zombie->getPosition().x << ", " << zombie->getPosition().y << std::endl;
        //std::cout << "Zombie pool size: " << _zombiePool.getPool().size() << std::endl;
    }
}
