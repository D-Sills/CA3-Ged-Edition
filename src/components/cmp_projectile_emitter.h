#pragma once
#include "ecm.h"
#include "cmp_projectile.h"
#include "../object_pool.h"
#include <SFML/Audio.hpp>
#include <vector>

class ProjectileEmitterComponent : public Component {
public:
    ProjectileEmitterComponent(Entity* p, int poolSize, float fireRate, float speed, int damage);

    void update(double dt) override;
    void render() override;
    void fireProjectile(const sf::Vector2f& position, float angle);
    void setFireRate(float fireRate);
    void setProjectileSpeed(float speed);
    void setProjectileDamage(int damage);

private:
    ObjectPool<ProjectileComponent> _projectilePool = ObjectPool<ProjectileComponent>(0);
    float _fireRate{};
    float _timeSinceLastFire{};

};

