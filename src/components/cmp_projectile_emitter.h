#pragma once
#include "ecm.h"
#include "cmp_projectile.h"
#include "../object_pool.h"
#include <SFML/Audio.hpp>
#include <vector>

class ProjectileEmitterComponent : public Component {
public:
    ProjectileEmitterComponent(Entity* p, float fireRate, float speed, int damage);

    void update(double dt) override;
    void render() override;
    bool fireProjectile(const sf::Vector2f& position, float angle);
    void setFireRate(float fireRate);
    void setProjectileSpeed(float speed);
    void setProjectileDamage(int damage);

private:
    ObjectPool<ProjectileComponent> _projectilePool = ObjectPool<ProjectileComponent>(100);
    float _fireRate = 0.5;
    float _timeSinceLastFire = 100;

};

