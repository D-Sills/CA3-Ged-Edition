
#include "../engine/system_resources.h"
#include "cmp_projectile_emitter.h"

ProjectileEmitterComponent::ProjectileEmitterComponent(Entity *p, int poolSize, float fireRate, float speed, int damage)
        : Component(p) {
    // Initialize projectile pool
    _projectilePool = ObjectPool<ProjectileComponent>(poolSize);

    _fireRate = fireRate;

    _projectilePool.forEach([speed, damage](auto proj) {
        proj->setSpeed(speed);
        proj->setDamage(damage);
    });
}

void ProjectileEmitterComponent::update(double dt) {
    _timeSinceLastFire += dt;

    // Update projectiles
    _projectilePool.forEach([dt](auto proj) {
        proj->update(dt);
    });
}

void ProjectileEmitterComponent::render() {
    _projectilePool.forEach([](auto proj) {
        if (proj->isVisible()) {
            proj->render();
        }
    });
}

void ProjectileEmitterComponent::fireProjectile(const sf::Vector2f& position, float angle) {
    if (_timeSinceLastFire < _fireRate) return;

    auto proj = _projectilePool.acquireObject();
    if (proj) {
        proj->fire(position, angle);
        //_fireSound.play(); // TODO: Use AudioManager when available
        _timeSinceLastFire = 0.0f;
    }
}

void ProjectileEmitterComponent::setFireRate(float fireRate) {
    _fireRate = fireRate;
}

void ProjectileEmitterComponent::setProjectileSpeed(float speed) {
    _projectilePool.forEach([speed](auto proj) {
        proj->setSpeed(speed);
    });
}

void ProjectileEmitterComponent::setProjectileDamage(int damage) {
    _projectilePool.forEach([damage](auto proj) {
        proj->setDamage(damage);
    });
}
