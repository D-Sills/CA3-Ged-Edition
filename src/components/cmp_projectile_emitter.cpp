
#include "../engine/system_resources.h"
#include "cmp_projectile_emitter.h"

ProjectileEmitterComponent::ProjectileEmitterComponent(Entity* p, int poolSize, float fireRate)
        : Component(p), _poolSize(poolSize), _fireRate(fireRate), _timeSinceLastFire(0.0f) {
    // Load fire sound
    _fireSoundBuffer = *Resources::get<sf::SoundBuffer>("FireSound.wav");
    _fireSound.setBuffer(_fireSoundBuffer);

    // Initialize projectile pool
    for (int i = 0; i < _poolSize; ++i) {
        auto projectile = _parent->scene->makeEntity();
        projectile->addComponent<ProjectileComponent>(/* Texture, Angle, Speed, Damage */);
        _projectiles.push_back(projectile->getComponent<ProjectileComponent>());
    }
}

void ProjectileEmitterComponent::update(double dt) {
    _timeSinceLastFire += dt;

    // Update projectiles
    for (auto& proj : _projectiles) {
        proj->update(dt);
    }
}

void ProjectileEmitterComponent::render() {
    for (auto& proj : _projectiles) {
        proj->render();
    }
}

void ProjectileEmitterComponent::fireProjectile(const sf::Vector2f& position, float angle) {
    if (_timeSinceLastFire < _fireRate) return;

    for (auto& proj : _projectiles) {
        if (!proj->isVisible()) {
            proj->fire(position, angle);
            _fireSound.play(); //TODO: audio manager
            _timeSinceLastFire = 0.0f;
            break;
        }
    }
}

void ProjectileEmitterComponent::setFireRate(float fireRate) {
    _fireRate = fireRate;
}

void ProjectileEmitterComponent::setProjectileSpeed(float speed) {
    for (auto& proj : _projectiles) {
        proj->setSpeed(speed);
    }
}

void ProjectileEmitterComponent::setProjectileDamage(int damage) {
    for (auto& proj : _projectiles) {
        proj->setDamage(damage);
    }
}
