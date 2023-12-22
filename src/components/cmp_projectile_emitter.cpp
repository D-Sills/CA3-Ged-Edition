#include "../audio_manager.h"
#include "cmp_projectile_emitter.h"
#include "../prefabs/player.h"

ProjectileEmitterComponent::ProjectileEmitterComponent(Entity *p) : Component(p),
_projectilePool(10,  [](const std::shared_ptr<Entity>& entity) { entity->addComponent<ProjectileComponent>();}) {}

ProjectileEmitterComponent::~ProjectileEmitterComponent() {
    _projectilePool.clear();
}

void ProjectileEmitterComponent::update(double dt) {
    _timeSinceLastFire += dt;
}

void ProjectileEmitterComponent::render() {}

bool ProjectileEmitterComponent::fireProjectile(const sf::Vector2f& position, float angle) {
    if (_timeSinceLastFire < _fireRate) return false;

    auto entity = _projectilePool.acquireObject();
    if (entity) {
        auto proj = entity->get_components<ProjectileComponent>()[0];
        proj->init();
        proj->setDamage(_damage);
        proj->setSpeed(_speed);
        proj->setOnRelease([this, proj]() {
            _projectilePool.releaseObject((shared_ptr<Entity> &) proj->_parent);
            std::cout << "Projectile released" << std::endl;
        });
        proj->fire(position, angle);

        _timeSinceLastFire = 0.0f;
        return true;
    }
    return false;
}

void ProjectileEmitterComponent::setFireRate(float fireRate) {
    _fireRate = fireRate;
}

void ProjectileEmitterComponent::setProjectileSpeed(float speed) {
    _speed = speed;
}

void ProjectileEmitterComponent::setProjectileDamage(int damage) {
    _damage = damage;
}