#pragma once
#include "ecm.h"
#include "cmp_projectile.h"
#include "../object_pool.h"
#include <SFML/Audio.hpp>
#include <vector>

class ProjectileEmitterComponent : public Component {
public:
    explicit ProjectileEmitterComponent(Entity* p);

    void update(double dt) override;
    void render() override;
    bool fireProjectile(const sf::Vector2f& position, float angle);
    void setFireRate(float fireRate);
    void setProjectileSpeed(float speed);
    void setProjectileDamage(int damage);

private:
    ObjectPool<ProjectileComponent> _projectilePool;
    float _fireRate = 0.5;
    float _timeSinceLastFire = 100;
    float _speed = 1000;
    int _damage = 1;
};

