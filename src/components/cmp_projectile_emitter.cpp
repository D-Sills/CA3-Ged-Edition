
#include "../engine/system_resources.h"
#include "../audio_manager.h"
#include "cmp_projectile_emitter.h"
#include "../prefabs/player.h"

ProjectileEmitterComponent::ProjectileEmitterComponent(Entity *p,float fireRate, float speed, int damage)
        : Component(p), _fireRate(fireRate) {
    setProjectileDamage(damage);
    setProjectileSpeed(speed);
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
        //_parent->get_components<Player>()[0]->setState(PlayerState::SHOOTING);
        proj->fire(position, angle);
        proj->setOnRelease([this, entity]() {
            _projectilePool.releaseObject(entity);
        });

        AudioManager::get_instance().playSound("Shoot_001");
        _timeSinceLastFire = 0.0f;
        return true;
    }
    return false;
}

void ProjectileEmitterComponent::setFireRate(float fireRate) {
    _fireRate = fireRate;
}

void ProjectileEmitterComponent::setProjectileSpeed(float speed) {
    _projectilePool.forEach([speed](const std::shared_ptr<Entity>& entity) {
        auto proj = entity->get_components<ProjectileComponent>()[0];
        if (proj) {
            proj->setSpeed(speed);
        }
    });
}

void ProjectileEmitterComponent::setProjectileDamage(int damage) {
    _projectilePool.forEach([damage](const std::shared_ptr<Entity>& entity) {
        auto proj = entity->get_components<ProjectileComponent>()[0];
        if (proj) {
            proj->setDamage(damage);
        }
    });
}